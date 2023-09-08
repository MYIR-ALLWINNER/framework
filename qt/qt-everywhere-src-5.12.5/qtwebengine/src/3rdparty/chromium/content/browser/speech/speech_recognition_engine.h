// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SPEECH_SPEECH_RECOGNITION_ENGINE_H_
#define CONTENT_BROWSER_SPEECH_SPEECH_RECOGNITION_ENGINE_H_

#include <stdint.h>
#include <memory>
#include <string>
#include <vector>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/sequence_checker.h"
#include "base/strings/string_piece.h"
#include "content/browser/speech/audio_encoder.h"
#include "content/browser/speech/chunked_byte_buffer.h"
#include "content/common/content_export.h"
#include "content/public/browser/speech_recognition_session_preamble.h"
#include "services/network/public/cpp/simple_url_loader_stream_consumer.h"
#include "services/network/public/mojom/url_loader_factory.mojom.h"
#include "third_party/blink/public/mojom/speech/speech_recognition_error.mojom.h"
#include "third_party/blink/public/mojom/speech/speech_recognition_grammar.mojom.h"
#include "third_party/blink/public/mojom/speech/speech_recognition_result.mojom.h"

namespace net {
class URLRequestContextGetter;
}

namespace network {
class SharedURLLoaderFactory;
}

namespace content {

class AudioChunk;
struct SpeechRecognitionError;

// A speech recognition engine supporting continuous recognition by means of
// interaction with the Google streaming speech recognition webservice.
//
// This class establishes two HTTPS connections with the webservice for each
// session, herein called "upstream" and "downstream". Audio chunks are sent on
// the upstream by means of a chunked HTTP POST upload. Recognition results are
// retrieved in a full-duplex fashion (i.e. while pushing audio on the upstream)
// on the downstream by means of a chunked HTTP GET request. Pairing between the
// two stream is handled through a randomly generated key, unique for each
// request, which is passed in the &pair= arg to both stream request URLs. In
// the case of a regular session, the upstream is closed when the audio capture
// ends (notified through a |AudioChunksEnded| call) and the downstream waits
// for a corresponding server closure (eventually some late results can come
// after closing the upstream). Both streams are guaranteed to be closed when
// |EndRecognition| call is issued.
//
// The expected call sequence is:
// StartRecognition      Mandatory at beginning of SR.
//   TakeAudioChunk      For every audio chunk pushed.
//   AudioChunksEnded    Finalize the audio stream (omitted in case of errors).
// EndRecognition        Mandatory at end of SR (even on errors).
//
// No delegate callbacks are performed before StartRecognition or after
// EndRecognition. If a recognition was started, the caller can free the
// SpeechRecognitionEngine only after calling EndRecognition.

class CONTENT_EXPORT SpeechRecognitionEngine {
 public:
  class Delegate {
   public:
    // Called whenever a result is retrieved.
    virtual void OnSpeechRecognitionEngineResults(
        const std::vector<blink::mojom::SpeechRecognitionResultPtr>&
            results) = 0;
    virtual void OnSpeechRecognitionEngineEndOfUtterance() = 0;
    virtual void OnSpeechRecognitionEngineError(
        const blink::mojom::SpeechRecognitionError& error) = 0;

   protected:
    virtual ~Delegate() {}
  };

  // Engine configuration.
  struct CONTENT_EXPORT Config {
    Config();
    ~Config();

    std::string language;
    std::vector<blink::mojom::SpeechRecognitionGrammar> grammars;
    bool filter_profanities;
    bool continuous;
    bool interim_results;
    uint32_t max_hypotheses;
    std::string origin_url;
    int audio_sample_rate;
    int audio_num_bits_per_sample;
    std::string auth_token;
    std::string auth_scope;
    scoped_refptr<SpeechRecognitionSessionPreamble> preamble;
  };

  // set_delegate detached from constructor for lazy dependency injection.
  void set_delegate(Delegate* delegate) { delegate_ = delegate; }

  // Duration of each audio packet.
  static const int kAudioPacketIntervalMs;

  // |deprecated_url_request_context_getter| is only for poking at the
  // Accept-Language header.
  // TODO(mmenke): Remove |deprecated_url_request_context_getter| as an
  // argument.
  SpeechRecognitionEngine(
      scoped_refptr<network::SharedURLLoaderFactory> shared_url_loader_factory,
      scoped_refptr<net::URLRequestContextGetter>
          deprecated_url_request_context_getter);
  ~SpeechRecognitionEngine();

  // Sets the URL requests are sent to for tests.
  static void set_web_service_base_url_for_tests(
      const char* base_url_for_tests);

  void SetConfig(const Config& config);
  void StartRecognition();
  void EndRecognition();
  void TakeAudioChunk(const AudioChunk& data);
  void AudioChunksEnded();
  bool IsRecognitionPending() const;
  int GetDesiredAudioChunkDurationMs() const;

 private:
  class UpstreamLoader;
  class DownstreamLoader;

  Delegate* delegate_;

  // Response status codes from the speech recognition webservice.
  static const int kWebserviceStatusNoError;
  static const int kWebserviceStatusErrorNoMatch;

  // Frame type for framed POST data. Do NOT change these. They must match
  // values the server expects.
  enum FrameType {
    FRAME_PREAMBLE_AUDIO = 0,
    FRAME_RECOGNITION_AUDIO = 1
  };

  // Data types for the internal Finite State Machine (FSM).
  enum FSMState {
    STATE_IDLE = 0,
    STATE_BOTH_STREAMS_CONNECTED,
    STATE_WAITING_DOWNSTREAM_RESULTS,
    STATE_MAX_VALUE = STATE_WAITING_DOWNSTREAM_RESULTS
  };

  enum FSMEvent {
    EVENT_END_RECOGNITION = 0,
    EVENT_START_RECOGNITION,
    EVENT_AUDIO_CHUNK,
    EVENT_AUDIO_CHUNKS_ENDED,
    EVENT_UPSTREAM_ERROR,
    EVENT_DOWNSTREAM_ERROR,
    EVENT_DOWNSTREAM_RESPONSE,
    EVENT_DOWNSTREAM_CLOSED,
    EVENT_MAX_VALUE = EVENT_DOWNSTREAM_CLOSED
  };

  struct FSMEventArgs {
    explicit FSMEventArgs(FSMEvent event_value);
    ~FSMEventArgs();

    FSMEvent event;

    // In case of EVENT_AUDIO_CHUNK, holds the chunk pushed by |TakeAudioChunk|.
    scoped_refptr<const AudioChunk> audio_data;

    // In case of EVENT_DOWNSTREAM_RESPONSE, hold the current chunk bytes.
    std::unique_ptr<std::vector<uint8_t>> response;

   private:
    DISALLOW_COPY_AND_ASSIGN(FSMEventArgs);
  };

  void OnUpstreamDataComplete(bool success, int response_code);

  void OnDownstreamDataReceived(base::StringPiece new_response_data);
  void OnDownstreamDataComplete(bool success, int response_code);

  // Entry point for pushing any new external event into the recognizer FSM.
  void DispatchEvent(const FSMEventArgs& event_args);

  // Defines the behavior of the recognizer FSM, selecting the appropriate
  // transition according to the current state and event.
  FSMState ExecuteTransitionAndGetNextState(const FSMEventArgs& event_args);

  // The methods below handle transitions of the recognizer FSM.
  FSMState ConnectBothStreams(const FSMEventArgs& event_args);
  FSMState TransmitAudioUpstream(const FSMEventArgs& event_args);
  FSMState ProcessDownstreamResponse(const FSMEventArgs& event_args);
  FSMState RaiseNoMatchErrorIfGotNoResults(const FSMEventArgs& event_args);
  FSMState CloseUpstreamAndWaitForResults(const FSMEventArgs& event_args);
  FSMState CloseDownstream(const FSMEventArgs& event_args);
  FSMState AbortSilently(const FSMEventArgs& event_args);
  FSMState AbortWithError(const FSMEventArgs& event_args);
  FSMState Abort(blink::mojom::SpeechRecognitionErrorCode error);
  FSMState DoNothing(const FSMEventArgs& event_args);
  FSMState NotFeasible(const FSMEventArgs& event_args);

  std::string GetAcceptedLanguages() const;
  std::string GenerateRequestKey() const;

  // Upload a single chunk of audio data. Handles both unframed and framed
  // upload formats, and uses the appropriate one.
  void UploadAudioChunk(const std::string& data, FrameType type, bool is_final);

  Config config_;
  std::unique_ptr<UpstreamLoader> upstream_loader_;
  std::unique_ptr<DownstreamLoader> downstream_loader_;
  scoped_refptr<network::SharedURLLoaderFactory> shared_url_loader_factory_;
  scoped_refptr<net::URLRequestContextGetter>
      deprecated_url_request_context_getter_;
  std::unique_ptr<AudioEncoder> encoder_;
  std::unique_ptr<AudioEncoder> preamble_encoder_;
  ChunkedByteBuffer chunked_byte_buffer_;
  bool got_last_definitive_result_;
  bool is_dispatching_event_;
  bool use_framed_post_data_;
  FSMState state_;

  SEQUENCE_CHECKER(sequence_checker_);

  DISALLOW_COPY_AND_ASSIGN(SpeechRecognitionEngine);
};

}  // namespace content

#endif  // CONTENT_BROWSER_SPEECH_SPEECH_RECOGNITION_ENGINE_H_