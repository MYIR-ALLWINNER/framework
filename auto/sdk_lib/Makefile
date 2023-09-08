#
# Reference http://www.gnu.org/software/make/manual/make.html
#
CONFIG_USE_LOGCAT = true

MAKE = make -j32

ifneq ($(CONFIG_USE_LOGCAT), true)
#exclude_dirs += ./liblog% ./logcat% 
else
DEFINES += -DUSE_LOGCAT
LOGCAT = logcat
endif

SUBDIRS := \
	sdk_audioenc \
	sdk_storage \
	sdk_sound \
	sdk_misc \
	sdk_log \
	sdk_shm \
	sdk_ctrl \
	sdk_config \
	sdk_camera \
	sdk_memory  \
	sdk_decoder   \
	sdk_encoder   \
	live555 \
	sdk_stream_player
	

#	dbusmedia 
#	videoproxy


all:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir ;\
		if [ "$$?" != "0" ]; then\
			echo "compile $$dir fail"; \
			exit 1 ; \
		fi;\
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
	
distclean:
	for dir in $(SUBDIRS);\
	do $(MAKE) -C $$dir distclean;\
	done
	
cleanall:distclean
	for dir in $(SUBDIRS);\
	do $(MAKE) -C $$dir cleanall;\
	done
