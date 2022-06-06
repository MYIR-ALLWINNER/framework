Target = G2dDemo

include ../makefile_cfg

EXT_OBJS = 

############################
# end deprecated interface #
############################
SRCS := $(shell find -name "*.cpp")
SRCS += $(shell find -name "*.c")

OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
OBJS += $(patsubst %.cpp, %.o, $(wildcard *.cpp))

#some marcos
CCFLAGS += -g -Wl,--no-undefined -Wno-write-strings

INCLUDES += -I./ \
			 -I $(SDK_PATH)/include \
			 -I $(SDK_PATH)/include/disp2 

LIBRARIES += -L$(SDK_PATH)/lib64 -L$(SDK_PATH)/cedarx/lib
LIBRARIES += -lsdk_g2d -lsdk_memory -lMemAdapter -lVE -lcdc_base -lcdx_ion
# Target rules
all: build
	@echo "make finish!!!"

build:${Target}

%.o : %.cpp
	$(CPP) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

%.o : %.c
	$(CC) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

${Target}: $(OBJS) $(EXT_OBJS)
	$(CPP) $(CCFLAGS) $(INCLUDES) $+ -o $@ $(LIBRARIES)
	@echo "generate $(Target) success!!!"
	@cp -f $(Target) $(INSTATLL_PATH)
	@echo -e '\e[1;33m cp -f $(Target) $(INSTATLL_PATH) \e[0m'

	
.PHONY:clean cleanall install distclean

clean:
	-rm -f $(Target) $(OBJS) $(CPPOBJS)
#rm *.d
cleanall:clean
	-rm -f $(INSTATLL_PATH)/$(Target) 

distclean:cleanall 

install:
	-cp $(Target) $(INSTATLL_PATH)