
vproxy: 
	echo ----------vproxy---------

	$(CPP) -c ./videoprosy.cpp -o ./videopro.o -rdynamic -fPIC -shared  $(CPPFLAGS) $(DEFINES)  $(CEDAR_MACORS) $(DEFINC) -I$(INC)  -lsdk_shm -I$(SDK_PATH)/../dbusmedia/
	$(CPP)  -o ./libvideoproxy.so ./videopro.o  -rdynamic -fPIC -shared -L./cedarx/lib/ -Wl,--no-undefined $(CEDAR_LINK_NEW) -lrt -lpthread -lz -lcrypto -lssl $(LIBS) -L$(SDK_PATH)  \
		-lsdk_log -lsdk_camera -lsdk_memory -lsdk_sound -lsdk_storage -lsdk_audenc -lsdk_cfg -lsdk_ctrl -lsdk_egl -lsdk_misc  \
		 -L$(SDK_PATH)    -lsdk_shm -lawcommediavideo  -I../shm/ -I../dbusmedia/
	cp ./libvideoproxy.so $(SDK_PATH)/libs