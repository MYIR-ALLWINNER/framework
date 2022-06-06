/*
 * ALSA Playback Test, based on Capture Test
 *
 * Copyright (c) 2014 Alexei A. Smekalkine
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <alsa/asoundlib.h>

#include "bipbuf.h"

#define LATENCY  1000  /* 1ms */

snd_pcm_t* init_playback()
{
	snd_pcm_t *pcm;
	ssize_t rc;
	/* Open and initialize PCM device */
	rc = snd_pcm_open (&pcm, "default", SND_PCM_STREAM_PLAYBACK, 0);
	if (rc < 0)
		goto no_device;

	rc = snd_pcm_set_params (pcm, SND_PCM_FORMAT_S16_LE,
				 SND_PCM_ACCESS_RW_INTERLEAVED, 2, 44100,
				 1, LATENCY);
	if (rc < 0)
		goto no_set_params;

    return pcm;

no_set_params:
	snd_pcm_close (pcm);
no_device:
	fprintf (stderr, "unable initialize capture device: %s\n",
		 snd_strerror(rc));
	return NULL;
}

int main (int argc, char *argv[])
{
	ssize_t rc;
	snd_pcm_t *pcm;
	struct bipbuf *b;
	void *data;
	size_t count;
	int run;
    int file_fd;

	/* We do not want garbage on the terminal */
	b = bipbuf_alloc (BUFSIZ);
	if (b == NULL) {
		perror ("alsa-play");
		return 1;
	}
    file_fd = open(argv[1], O_RDONLY);

    pcm = init_playback();
	/* Main loop */
	for (run = 1; run;) {
		data = bipbuf_reserve (b, &count);
		if (count > 0) {
			rc = read (file_fd, data, count);
			if (rc <= 0)
				run = 0;  /* Oops: drop data in buffer already? */
			else
				bipbuf_commit (b, rc);
		}

		data = bipbuf_get (b, &count);
		if (count > 0) {
			rc = snd_pcm_writei (pcm, data,
					     snd_pcm_bytes_to_frames (pcm, count));
			if (rc < 0) {
				if (snd_pcm_recover (pcm, rc, 1) < 0)
					fprintf (stderr, "pcm write error: %s\n",
						 snd_strerror (rc));
				/* Try to ignore errors */
			}
			else
				bipbuf_eat (b, snd_pcm_frames_to_bytes (pcm, rc));
		}
	}

	snd_pcm_drain (pcm);
	snd_pcm_close (pcm);
	bipbuf_free (b);
	return 0;

}
