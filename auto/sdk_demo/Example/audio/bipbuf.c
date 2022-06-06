#include <stdio.h>
#include <stdlib.h>
#include "bipbuf.h"

static void fatal (const char *msg)
{
	fprintf (stderr, "fatal: %s\n", msg);
	abort ();
}

struct bipbuf {
	char *head, *tail, *a_head, *a_tail, *b_tail;
	int is_a_active;
};

struct bipbuf *bipbuf_alloc (size_t size)
{
	struct bipbuf *b;

	if ((b = malloc (sizeof (*b))) == NULL)
		goto no_object;

	if ((b->head = malloc (size)) == NULL)
		goto no_buffer;

	b->tail = b->head + size;
	b->a_head = b->a_tail = b->b_tail = b->head;
	b->is_a_active = 1;
	return b;

no_buffer:
	free (b);
no_object:
	return NULL;
}

void bipbuf_free (struct bipbuf *b)
{
	if (b == NULL)
		return;

	free (b->head);
	free (b);
}

int bipbuf_is_empty (struct bipbuf *b)
{
	return b->a_head == b->a_tail;
}

void *bipbuf_reserve (struct bipbuf *b, size_t *size)
{
	if (b->is_a_active) {
		*size = b->tail - b->a_tail;
		return b->a_tail;
	}

	*size = b->a_head - b->b_tail;
	return b->b_tail;
}

void bipbuf_commit (struct bipbuf *b, size_t size)
{
	size_t a_avail, b_avail;

	if (!b->is_a_active) {
		b->b_tail += size;
		if (b->b_tail > b->a_head)
			fatal ("bipbuf overflow on commit");
		return;
	}

	b->a_tail += size;
	if (b->a_tail > b->tail)
		fatal ("bipbuf overflow on commit");

	a_avail = b->tail - b->a_tail;
	b_avail = b->a_head - b->head;

	if (b_avail > a_avail)
		b->is_a_active = 0;
}

void *bipbuf_get (struct bipbuf *b, size_t *size)
{
	*size = b->a_tail - b->a_head;
	return b->a_head;
}

void bipbuf_eat (struct bipbuf *b, size_t size)
{
	b->a_head += size;  /* TODO: check for overflow here? */

	if (b->a_head < b->a_tail)  /* is A region not empty? */
		return;

	/* move B region to A */
	b->a_head = b->head;
	b->a_tail = b->b_tail;
	b->b_tail = b->head;
	b->is_a_active = 1;
}
