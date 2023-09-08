include ../makefile_cfg


override CFLAGS := -W -Wall -Wextra -ansi -pedantic -O3 -Wno-unused-function $(CFLAGS)
override CXXFLAGS := -W -Wall -Wextra -ansi -pedantic -O3 $(CXXFLAGS)

all: pngdecodetest png2bmptest

%.o: %.cpp
	@mkdir -p `dirname $@`
	$(CPP) -I ./ $(CXXFLAGS) -c $< -o $@

pngdecodetest: lodepng.o example_decode.o 
	$(CPP) $^ $(CXXFLAGS) -o $@

png2bmptest: lodepng.o example_png2bmp.o 
	$(CPP) $^ $(CXXFLAGS) -o $@
	
clean:
	rm -f *.o pngdecodetest png2bmptest
