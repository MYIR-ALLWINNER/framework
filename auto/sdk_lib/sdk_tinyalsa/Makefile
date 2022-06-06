TARGET = libtinyalsa.so

include ../makefile_cfg

LDFLAGS := -rdynamic -lpthread -fPIC -shared 

INCS += -I./ \
		-I$(SDK_LIB)/include 
	
CSRCS := mixer.c \
		pcm.c
		
CPPSRCS := 

COBJS := $(CSRCS:.c=.o)
CPPOBJS := $(CPPSRCS:.cpp=.o)

CFLAGS+=-g -O0 -pipe -Wall -W -Wno-unused-parameter -D_REENTRANT -fPIC 
CPPFLAGS=-g -O0 -pipe -Wall -W -Wno-unused-parameter -D_REENTRANT -fPIC

all: CHECK $(TARGET) 
	@echo "make finish!!!"

CHECK :
	@echo -e $(TOOLTRAIN_ERR_STRING)

$(COBJS) : %.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(DEFINES)
$(CPPOBJS) : %.o: %.cpp
	$(CPP) -c $< -o $@ $(CPPFLAGS) $(DEFINES)

$(TARGET) : $(COBJS) $(CPPOBJS) 
	$(CPP) -o $(TARGET) $(COBJS) $(CPPOBJS) $(LIBS) $(LDFLAGS)
	cp $(TARGET) $(SDK_LIBS)
	@echo -e '\e[1;33m cp $(TARGET) $(SDK_LIBS) \e[0m'

.PHONY:clean cleanall install distclean

clean: 
	-rm -f $(TARGET) $(COBJS) $(CPPOBJS) *.d

cleanall:clean
	-rm -f $(SDK_LIBS)/$(TARGET) *.d

distclean:cleanall 
	
