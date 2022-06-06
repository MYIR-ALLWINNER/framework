Target = malitest

include ../makefile_cfg

SDK_PATH = ../../sdk_lib
LDFLAGS = -L$(SDK_PATH)/lib64 -Wno-implicit-function-declaration 
	

INC = -I./ \
		-I $(SDK_PATH)/include/opengl/include \
		-I $(SDK_PATH)/include/opengl/include/khronos/original/

CSRCS = mali_test.c 
#LIBS += -law_opengles
LIBS +=  $(LICHEE_BR_OUT)/host/aarch64-buildroot-linux-gnu/sysroot/usr/lib/libmali.so

all: $(Target) 

$(Target): mali_test.c
	$(CC) -g mali_test.c -o $(Target) $(INC) $(LIBS) $(LDFLAGS) 
	@echo "generate encoder success!!!"
	@cp -f $(Target) $(INSTATLL_PATH)
	@echo -e '\e[1;33m cp -f $(Target) $(INSTATLL_PATH) \e[0m'
	
.PHONY:clean cleanall

clean: 
	@rm -f $(Target)
cleanall:clean
	-rm -f $(INSTATLL_PATH)/$(Target) 
	
distclean:cleanall 
	
install:
	-cp $(Target) $(INSTATLL_PATH)	
