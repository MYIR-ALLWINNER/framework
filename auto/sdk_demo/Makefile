#
# Reference http://www.gnu.org/software/make/manual/make.html
#
CONFIG_USE_LOGCAT = true

MAKE = make -j32

exclude_dirs := include bin videoservice yuvPlayerTest xplayerdemoH264

ifneq ($(CONFIG_USE_LOGCAT), true)
exclude_dirs += ./liblog% ./logcat% 
else
DEFINES += -DUSE_LOGCAT
LOGCAT = logcat
endif

dirs := $(shell find . -maxdepth 1 -type d)
dirs := $(basename $(patsubst ./%,%,$(dirs)))
dirs := $(filter-out $(exclude_dirs),$(dirs))
SUBDIRS := $(dirs)

all:
	for dir in $(SUBDIRS);\
	do $(MAKE) -C $$dir || exit $$?; \
	done

.PHONY: clean distclean cleanall
$(SUBDIRS):ECHO
	+$(MAKE) -C $@
ECHO:
	@echo begin compile $(SUBDIRS)

clean: $(clean_dirs) 
	for dir in $(SUBDIRS);\
	do $(MAKE) -C $$dir clean;\
	done

install:
	for dir in $(SUBDIRS);\
	do $(MAKE) -C $$dir install;\
	done
	
distclean:
	for dir in $(SUBDIRS);\
	do $(MAKE) -C $$dir distclean;\
	done
	
cleanall:
	for dir in $(SUBDIRS);\
	do $(MAKE) -C $$dir cleanall;\
	done
