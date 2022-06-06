/*
 * ALSA Capture Test
 *
 * Copyright (c) 2014 Alexei A. Smekalkine
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <alsa/asoundlib.h>

#define DURATION  50  /* 5 seconds */

#define CHANNELS  2
#define RATE      44100

#define LATENCY  1000  /* 1ms */

snd_pcm_t* init_capture(snd_pcm_uframes_t *buffer_size, size_t *count)
{
    int rc;
	snd_pcm_uframes_t period_size;
	snd_pcm_t *pcm;

	/* Open and initialize PCM device */
	rc = snd_pcm_open (&pcm, "default", SND_PCM_STREAM_CAPTURE, 0);
	if (rc < 0)
		goto no_device;
    
    rc = snd_pcm_set_params (pcm, SND_PCM_FORMAT_S16_LE,
				 SND_PCM_ACCESS_RW_INTERLEAVED, CHANNELS, RATE,
				 1, LATENCY);
	if (rc < 0)
		goto no_set_params;

	rc = snd_pcm_get_params (pcm, buffer_size, &period_size);
	if (rc < 0)
		goto no_get_params;

	/* Allocate software buffer */
	*count = snd_pcm_frames_to_bytes (pcm, *buffer_size);
	
    return pcm;

no_get_params:
no_set_params:
	snd_pcm_close (pcm);
no_device:
	fprintf (stderr, "unable initialize capture device: %s\n",
		 snd_strerror(rc));
	return NULL;
}

void deinit_capture(snd_pcm_t *pcm)
{
	snd_pcm_drain (pcm);
	snd_pcm_close (pcm);
}

int main (int argc, char *argv[])
{
	int rc;
	snd_pcm_t *pcm;
	snd_pcm_uframes_t buffer_size, period_size;
	void *buffer = NULL;
	size_t count;
	ssize_t rest;

	/* We do not want garbage on the terminal */
	if (isatty (1)) {
		fprintf (stderr, "usage:\n\talsa-capture > output-file\n");
		return 1;
	}

    pcm = init_capture(&buffer_size, &count);

    buffer = malloc (count);
	if (buffer == NULL) {
		perror ("buffer allocation");
		return NULL;
	}

	/* Main loop */
	for (rest = DURATION * RATE; rest > 0;) {
		rc = snd_pcm_readi (pcm, buffer, buffer_size);
		if (rc < 0) {
			if (snd_pcm_recover (pcm, rc, 1) < 0)
				fprintf (stderr, "pcm read error: %s\n",
					 snd_strerror(rc));
			/* Try to ignore errors */
		}
		else {
			count = snd_pcm_frames_to_bytes (pcm, rc);
			write (1, buffer, count);
			rest -= rc;
		}
	}
    
    deinit_capture(pcm);
	free (buffer);
	return 0;
}
