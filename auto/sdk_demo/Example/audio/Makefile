TARGETS = alsa-play alsa-cap

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

PREFIX ?= /usr/local

install: $(TARGETS)
	install -D -d $(DESTDIR)/$(PREFIX)/bin
	install -s -m 0755 $^ $(DESTDIR)/$(PREFIX)/bin

alsa-cap: CFLAGS += `pkg-config alsa --cflags --libs`
alsa-play: CFLAGS += `pkg-config alsa --cflags --libs`
alsa-play: bipbuf.o
