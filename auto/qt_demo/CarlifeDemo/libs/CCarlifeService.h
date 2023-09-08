typedef struct TouchActionPosition{
	unsigned int x ;
	unsigned int y ;
}S_TOUCH_ACTION_POSITION;

enum TouchActionType{
	TOUCH_ACTION_DOWN = 0,
	TOUCH_ACTION_UP = 1,
	TOUCH_ACTION_MOVE = 2,
};
int carlife_service_send_touch_action(TouchActionType type, S_TOUCH_ACTION_POSITION* pstPosition);
int carlife_service_get_video_info(int *pWidth, int * pHight, int * pFrameRate);
int carlife_service_get_connection_status();
int carlife_service_init();
int carlife_service_destroy();
int carlife_service_connect_to_mobile();

#include "layerControl.h"
extern  LayerCtrl* LayerCreate_DE();

/*
example code
if(carlife_service_get_connection_status() != 1)
		{
			printf("2 carlife_service_destroy\n");
			carlife_service_destroy();
			//sleep(1);
			printf("carlife_service_init\n");
			carlife_service_init();
			
			carlife_service_connect_to_mobile();
		}
		

*/





