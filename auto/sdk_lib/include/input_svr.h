
#ifndef INPUT_SVR_H
#define INPUT_SVR_H
#ifdef __cplusplus
extern "C" {
#endif

#define NAME_MAX    32
//define msg info
typedef enum MSG_TYPE{
    TYPE_NONE   = 0x0,
    TYPE_SHOCK  = 0x1,
    TYPE_KEY    = 0x2,
    TYPE_REVERSE= 0x3,
}MSG_TYPE_T;

typedef enum MSG_CODE{
    CODE_NONE   = 0xF0,
    CODE_SHOCK  = 0xF1,
    CODE_HOME   = 0xF2,
    CODE_POWER  = 0xF3,
    CODE_REAR   = 0xF4,
    CODE_REVERSE= 0xF5,
}MSG_CODE_T;

typedef enum MSG_VALUE{
    VALUE_NONE  = 0xF04,
    VALUE_SHOCK = 0xF01,
    VALUE_UP    = 0xF02,
    VALUE_DOWN  = 0xF03,
    VALUE_REVERSE_HOLD  = 0xF04,
    VALUE_REVERSE_START  = 0xF05,
    VALUE_REVERSE_STOP  = 0xF06,
}MSG_VALUE_T;

typedef enum STATUS {
    SVR_NONE    = 0xFF1,
    SVR_INIT    = 0xFF2,
    SVR_EXIT    = 0xFF3,
}STATUS_T;

typedef struct input_msg {
    MSG_TYPE_T    type;
    MSG_CODE_T    code;
    MSG_VALUE_T   value;
}input_msg_t;


typedef enum car_reverse_status {
	CAR_REVERSE_HOLD  = 0,
	CAR_REVERSE_START = 1,
	CAR_REVERSE_STOP  = 2,
}reverse_status_t;

typedef  void (*input_msg_cb)(struct input_msg *msg, void *arg);

typedef struct input_handler{
    //you need init the name
    char                *name;
    STATUS_T            status;
    input_msg_t         msg;
    //you need init the msg_cb 
    input_msg_cb        msg_cb;      
    //pri for msg_cb
    void                *pri;
    //we will init this pt
    struct input_handler *next;
}input_handler_t;

typedef void(*reverse_cb)(int reverse_status, void *usr_data);
int reverse_svr_init(reverse_cb usr_sb, void *usr_data);
int get_reverse_event(void);
void reverse_svr_exit(void);

/* APIs */
int input_svr_register(struct input_handler *hdl);
int input_svr_unregister(struct input_handler *hdl);

int input_svr_init(void);
int input_svr_exit(void);


#define d_prt printf

#ifdef __cplusplus
}
#endif

#endif /* INPUT_SVR_H */


