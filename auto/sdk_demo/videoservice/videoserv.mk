
videoserv: 
	echo -------------------
	$(CPP) -c ./background_video_player.cpp -o ./background_video_player.o -g $(CPPFLAGS) $(DEFINES)  $(CEDAR_MACORS) -DBGVIDEO_SER -I$(INC) -I$(SDK_PATH)/../shm/ -I$(SDK_PATH)/../dbusmedia/
	$(CPP) -c ./bg_video_serv_warper.cpp    -o ./bg_video_serv_warper.o    -g $(CPPFLAGS) $(DEFINES)  $(CEDAR_MACORS)  -DBGVIDEO_SER -I$(INC) -I$(SDK_PATH)/../shm/ -I$(SDK_PATH)/../dbusmedia/
	$(CPP)  -o ./video_serv  ./background_video_player.o ./bg_video_serv_warper.o -DBGVIDEO_SER -L./cedarx/lib/ -Wl,--no-undefined $(CEDAR_LINK_NEW) -lrt -lpthread -lz -lcrypto -lssl $(LIBS) \
		-L$(SDK_PATH) 	 -lvenc_codec -lvenc_base	-lsdk_log -lsdk_camera -lsdk_memory -lsdk_sound -lsdk_storage -lasound  -lsdk_audenc -lsdk_cfg -lsdk_ctrl -lsdk_egl -lsdk_misc  \
		$(TESTLDFLAGS) -L$(SDK_PATH)/libs   -lsdk_shm -lawcommediavideo
