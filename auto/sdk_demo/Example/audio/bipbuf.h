#ifndef _BIPBUF_H
#define _BIPBUF_H  1

#include <stddef.h>

struct bipbuf *bipbuf_alloc (size_t size);
void bipbuf_free (struct bipbuf *b);

int bipbuf_is_empty (struct bipbuf *b);

void *bipbuf_reserve (struct bipbuf *b, size_t *size);
void  bipbuf_commit  (struct bipbuf *b, size_t  size);

void *bipbuf_get (struct bipbuf *b, size_t *size);
void  bipbuf_eat (struct bipbuf *b, size_t  size);

#endif  /* _BIPBUF_H */
