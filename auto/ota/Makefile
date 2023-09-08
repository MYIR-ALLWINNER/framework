PRJT_PWD=${PWD}
include ${PRJT_PWD}/../../../../.buildconfig

TARGET = upgrade
LIBS = -lm
CC = ${LICHEE_TOOLCHAIN_PATH}/bin/${LICHEE_CROSS_COMPILER}-gcc
CFLAGS = -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o *.map
	-rm -f $(TARGET)
