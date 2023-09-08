/**
    Header files
*/

#include <gio/gio.h>    /** GIO for dbus*/
#include <glib-2.0/glib.h>  /** GLIB for main loop*/  
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "dbusmediavideoCommon.h"
#include "dbusmediavideoclient.h"
#include "libgdbusmediavideo.h"


/**
    instance init
*/
#define RET_SIGNAL_HANDLE_SIZE 3
GMainLoop *pcMediaVideoLoop = NULL;
typedef  ComAwGdbusMediavideo ComAwGdbusMediaVideo;
ComAwGdbusMediaVideo *pcMediaVideoProxy = NULL;
fn_signal_handler cMediaVideosingal_cb_srv=NULL;
bool cMediaVideoDeInitDBusCommunication(void);
bool cMediaVideoDBusServiceIsReady(void);
int cMediaVideoSetCmd(const gint in_arg1, const gint in_arg2,const gint in_arg3,const char* in_arg4, gint *out_arg2, GError** pError);
int cMediaVideoGetCmd(const gint in_arg1, const gint in_arg2, gint  *out_arg, GError** pError);


int cMediaVideoClientSetCmd( int in_arg1, int in_arg2, int in_arg3, const char* in_arg4,  int *out_arg2)
{
	GError *syncMethodError = NULL;

	int ret =  cMediaVideoSetCmd(  in_arg1,  in_arg2,  in_arg3,  in_arg4,  out_arg2,&syncMethodError);

	return ret;
}

int cMediaVideoClientRegSingalHandl(void* cb)
{
	cMediaVideosingal_cb_srv=cb;
	return 0;
}

static gboolean SignalMediaVideoHandler(ComAwGdbusMediaVideo *object,  GVariant *arg, gpointer userdata)
{
    /** get the value from GVariant */
    gint int_arg1 = 0;
	gint int_arg2 = 0;
    //gchar *char_arg = NULL;
	gint int_arg3 = 0;

    g_variant_get(arg, "(iii)", &int_arg1,&int_arg2, &int_arg3); 
    g_print("SignalMediaVideoHandler: Int value: %d,Int value: %d, String value: %d\n", int_arg1,int_arg2, int_arg3);

	if(cMediaVideosingal_cb_srv!=NULL)
		cMediaVideosingal_cb_srv(int_arg1,int_arg2,int_arg3,userdata);
	
    //g_free(char_arg);

    return TRUE;
}

static void cbOwnerNameChangedNotify(GObject *object, GParamSpec *pspec, gpointer userdata)
{
    gchar *pname_owner = NULL;
    pname_owner = g_dbus_proxy_get_name_owner((GDBusProxy*)object);

    if (NULL != pname_owner){
        g_print("DBus service is ready!\n");
        g_free(pname_owner);
    }
    else{
        g_print("DBus service is NOT ready!\n");
        g_free(pname_owner);
    }
}

int cMediaVideoGetCmd(const gint in_arg1, const gint in_arg2, gint  *out_arg, GError** pError)
{
	GVariant *in_arg = NULL;
	GError *Error = NULL;

		if(pcMediaVideoProxy == NULL)
		{
			g_print("client myMethod_1 call ret pcMediaVideoProxy ==NULL \n");
			return -2;
		}
		
		
		/** generate the input parameters */
		in_arg = g_variant_new("(ii)", in_arg1, in_arg2);

    gboolean ret =com_aw_gdbus_mediavideo_call_method_cmd_get_sync(pcMediaVideoProxy, in_arg, out_arg, NULL, pError);
	if(!ret)
	{
		g_print("client myMethod_1 call ret fail \n");
		
		if (*pError != NULL){
	        g_print("client myMethod_1: ret Failed to call method. Reason: %s.\n", (*pError)->message);
	        g_error_free(*pError);
			
	    }
		cMediaVideoDeInitDBusCommunication();
		return -2;
	}

    if (*pError == NULL){
        g_print("client myMethod_1 call, in_arg = %s out_arg = %s.\n", in_arg, *out_arg);
    }
    else{
        g_print("client myMethod_1: Failed to call method. Reason: %s.\n", (*pError)->message);
        g_error_free(*pError);
		return -1;
    }

    return 0;
}
int cMediaVideoSetCmd(const gint in_arg1, const gint in_arg2,const gint in_arg3,const char* in_arg4, gint *out_arg2, GError** pError)
{
    GVariant *in_arg = NULL;
    //gint  out_arg ;
    GError *Error = NULL;
	if(pcMediaVideoProxy == NULL)
	{
		g_print("client myMethod_1 call ret pcMediaVideoProxy ==NULL \n");
		return -2;
	}

    /** generate the input parameters */
    in_arg = g_variant_new("(iiis)", in_arg1, in_arg2,in_arg3, in_arg4);
	GVariant *out_arg = NULL;

    /** call the server's dbus methods */
     gboolean ret = com_aw_gdbus_mediavideo_call_method_cmd_set_sync(pcMediaVideoProxy, in_arg, &out_arg, NULL, pError);
	if(!ret)
	{
		g_print("client cMediaVideoSetCmd call ret fail \n");
		
		if (*pError != NULL){
	        g_print("client cMediaVideoSetCmd: ret Failed to call method. Reason: %s.\n", (*pError)->message);
	        g_error_free(*pError);
			
	    }
		cMediaVideoDeInitDBusCommunication();
		return -2;
	}
		
    if(NULL == *pError){
        /** get the result from the output parameter */
        g_print("client cMediaVideoSetCmd call, in_arg1 = %d, in_arg2 = %d, \n", in_arg1, in_arg2);
		soutval_t *p = (soutval_t *)out_arg2;
		g_variant_get(out_arg, "(iiix)", &p->val0, &p->val1,&p->val2,&p->val3); 
		
        return 0; 
    }
    else{
        g_print("client myMethod_2: Failed to call method. Reason: %s.\n", (*pError)->message);
        g_error_free(*pError);
		return -1;
    }

    return 0; 
}

void *cMediaVideorun(void* arg)
{
    g_print("run call in the client.\n");
    pthread_detach(pthread_self());
    /** start the main event loop which manages all available sources of events */
    g_main_loop_run(pcMediaVideoLoop);
	g_print("run call in the client quit.\n");
	cMediaVideoDBusServiceIsReady();

    return ((void*)0);
}

int cMediaVideothreadCreate(void)
{
    int err;
    pthread_t thr;

    err = pthread_create(&thr, NULL, cMediaVideorun, NULL);

    if(0 != err){
            g_print("Can't create thread: %s\n", strerror(err));
    }
    else{       
            g_print("New thread created: %s\n", strerror(err));
    }

    return err;
}

bool cMediaVideoDBusServiceIsReady(void)
{
    gchar *owner_name = NULL;
    owner_name = g_dbus_proxy_get_name_owner((GDBusProxy*)pcMediaVideoProxy);
    if(NULL != owner_name)
    {
        g_print("Owner Name: %s\n", owner_name);        
        g_free(owner_name);
        return true;
    }
    else
    {   
        g_print("Owner Name is NULL.\n");     
        return false;
    }
}
void *cMediaVideoclientdata=NULL;
bool cMediaVideoregisterClientSignalHandler(ComAwGdbusMediaVideo *pcMediaVideoProxy,void *p)
{
    g_print("cMediaVideoregisterClientSignalHandler call.\n");
    g_signal_connect(pcMediaVideoProxy, "signalmediovideo", G_CALLBACK(SignalMediaVideoHandler), p);

    return TRUE;
}

static bool cMediaVideounregisterClientSignalHandler(ComAwGdbusMediaVideo *pcMediaVideoProxy,void *p)
{
    g_print("cMediaVideounregisterClientSignalHandler call.\n");
	g_signal_handlers_disconnect_by_func(pcMediaVideoProxy, G_CALLBACK(SignalMediaVideoHandler), p);

    return TRUE;
}

bool cMediaVideoInitDBusCommunication(void *p)
{
    bool bRet = TRUE;
    cMediaVideoclientdata=p;
    g_type_init(); 
   
    pcMediaVideoLoop = g_main_loop_new(NULL, FALSE);   /** create main loop, but do not start it.*/

    GError *pcMediaVideoProxyError= NULL;

    do{
        bRet = TRUE;
        pcMediaVideoProxy = com_aw_gdbus_mediavideo_proxy_new_for_bus_sync(G_BUS_TYPE_SESSION,
                                        G_DBUS_PROXY_FLAGS_NONE,
                                        AW_GDBUS_MEDIAVIDEO_BUS_NAME,
                                        AW_GDBUS_MEDIAVIDEO_OBJECT_PATH,
                                        NULL,
                                        &pcMediaVideoProxyError);
         
         if(0 == pcMediaVideoProxy){
             g_print("cMediaVideoInitDBusCommunication: Failed to create proxy. Reason: %s.\n", pcMediaVideoProxyError->message);
             g_error_free(pcMediaVideoProxyError);
             bRet = FALSE;
         }
    }while(FALSE == bRet);
    g_print("cMediaVideoInitDBusCommunication: loop and proxy created.\n");
    if (TRUE == bRet){
        /** Third step: Attach to dbus signals */
        cMediaVideoregisterClientSignalHandler(pcMediaVideoProxy,p);
    }

    cMediaVideothreadCreate();
}

 bool cMediaVideoDeInitDBusCommunication(void)
{
    bool bRet = FALSE;

	if(0 != pcMediaVideoProxy){
		cMediaVideounregisterClientSignalHandler(pcMediaVideoProxy,cMediaVideoclientdata);
		cMediaVideoclientdata =NULL;
	}
    if(0 != pcMediaVideoLoop){
        g_main_loop_quit(pcMediaVideoLoop);
        g_main_loop_unref(pcMediaVideoLoop);
		pcMediaVideoLoop =NULL;
        bRet = TRUE;
    }

    return bRet;
}
/////////////////////////////////////////////////////////////////

/**
    Header files
*/
	int cMediaVideoClientDestory()
{
	cMediaVideoDeInitDBusCommunication();
	return 0;

}

int cMediaVideoClientInit(void *p)
{
    bool bRet = TRUE;

    cMediaVideoInitDBusCommunication(p);
	int retry=0;
    while(!cMediaVideoDBusServiceIsReady())
    {
    	retry++;
		if(retry>4){
			cMediaVideoDeInitDBusCommunication();
			return -1;
		}
        usleep(10000);
    };
    return 0;
}

