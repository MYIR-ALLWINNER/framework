#ifndef __ALSA_RECIPE_H
#define __ALSA_RECIPE_H

/* Build with TLV support */
#define SALSA_HAS_TLV_SUPPORT	0

/* Build with async support */
#define SALSA_HAS_ASYNC_SUPPORT	0

/* Build with user-space control element support */
#define SALSA_HAS_USER_ELEM_SUPPORT	1

/* Build with chmap API support */
#define SALSA_HAS_CHMAP_SUPPORT	0

/* Build with dummy conf support */
#define SALSA_HAS_DUMMY_CONF	0

/* Enable deprecated attribute for non-working functions */
#define SALSA_MARK_DEPRECATED	1

/* Support string output via snd_output_*() */
#define SALSA_SUPPORT_OUTPUT_BUFFER	0

/* Support floating pointer */
#define SALSA_SUPPORT_FLOAT	0

/* Support 4bit PCM (IMA ADPCM) */
#define SALSA_SUPPORT_4BIT_PCM	1

/* Enable library ABI check */
#define SALSA_CHECK_ABI		0

/* Support ASCII value parser for ctl */
#define SALSA_CTL_ASCII_PARSER	0

/* Default device path prefix */
#define SALSA_DEVPATH "/dev/snd"

#endif /* __ALSA_RECIPE_H */
