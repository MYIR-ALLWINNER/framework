/**
    Header files
*/

#include <gio/gio.h>   // GIO for dbus
#include <glib-2.0/glib.h>   // GLIB for main loop
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "libgdbusmediavideo.h"
#include "dbusmediavideoserver.h"
#include "dbusmediavideoCommon.h"
/**
    Instance init
*/
GMainLoop         *psMediaVideoLoop     = NULL;

typedef  ComAwGdbusMediavideo ComAwGdbusMediaVideo;

ComAwGdbusMediaVideo  *psMediaVideoSkeleton = NULL;
void *sMediaVideoservdata=NULL;


void sMediaVideobusAcquiredCB(GDBusConnection* connection, const gchar* bus_name, gpointer user_data);
void sMediaVideonameAcquiredCB(GDBusConnection* connection, const gchar* bus_name, gpointer user_data);
void sMediaVideonameLostCB(GDBusConnection* connection, const gchar* bus_name, gpointer user_data);
void* sMediaVideorun(void*);
//static int thread_create(void);
bool sMediaVideoInitDBusCommunicationServer(void);
bool sMediaVideoDeinitDBusCommunicationServer(void);
fn_set_cmd_handler mediavideo_setcmd_hdl=NULL;

/**
    Normal functions
*/
int sMediaVideoEmitSignal(int i_arg1,int i_arg2,int i_arg3)
{

	GVariant *in_arg = NULL;
	in_arg = g_variant_new("(iii)", i_arg1, i_arg2,i_arg3);

	com_aw_gdbus_mediavideo_emit_signalmediovideo(psMediaVideoSkeleton, in_arg);
	
    return TRUE;
}

int sMediaVideoServRegSetCmdHandl(void* cb)
{
	mediavideo_setcmd_hdl =cb;
	return 0;
}

int MediaVideoSetCmd(ComAwGdbusMediaVideo     *object,
							 
                               GDBusMethodInvocation *invocation,
                               GVariant           *in_arg  ,
                               gpointer               user_data)
{

	gint in_arg1 = 0;
	gint in_arg2 = 0;
	gint in_arg0 = 0;
	char* in_arg3 ;
	gint out_arg = 0;

	g_variant_get(in_arg, "(iiis)", &in_arg0, &in_arg1, &in_arg2, &in_arg3);
	soutval_t outval;
	
	if(mediavideo_setcmd_hdl!=NULL)
	{
		out_arg = mediavideo_setcmd_hdl(in_arg0, in_arg1, in_arg3, &outval,user_data);
	}
	g_free(in_arg3);
	GVariant *out_arg2 = NULL;
	out_arg2 = g_variant_new("(iiix)", outval.val0,outval.val1,outval.val2,outval.val3);

    com_aw_gdbus_mediavideo_complete_method_cmd_set(object, invocation, out_arg2);

    return TRUE;
}

int MediaVideoGetCmd(ComAwGdbusMediaVideo     *object,
                               GDBusMethodInvocation *invocation,
                               GVariant           *in_arg,
                               gpointer               user_data)
{
  gint in_arg1 = 0;
  gint in_arg2 = 0;
  gint out_arg = 0;

  /** Get the input parameters */
  g_variant_get(in_arg, "(ii)", &in_arg1, &in_arg2);

  g_print("Server MediaVideoGetCmd call. Parameter: in_arg1 = %d , in_arg2 = %d.\n", in_arg1, in_arg2);

  /** Generate the output parameters */
  //out_arg2 = in_arg1 + in_arg2;
  //out_arg = g_variant_new("(si)", out_arg1, out_arg2);

  com_aw_gdbus_mediavideo_complete_method_cmd_get(object, invocation, out_arg);

  return TRUE;

}

void sMediaVideobusAcquiredCB(GDBusConnection *connection,
                                const gchar     *bus_name,
                                gpointer         user_data)
{
    GError *pError = NULL;
    g_print("bus_acquired_cb call start.\n");
    /** Second step: Try to get a connection to the given bus. */
	psMediaVideoSkeleton = com_aw_gdbus_mediavideo_skeleton_new ();

    /** Third step: Attach to dbus signals. */
    (void) g_signal_connect(psMediaVideoSkeleton, "handle-method-cmd-set", G_CALLBACK(MediaVideoSetCmd), sMediaVideoservdata);
    (void) g_signal_connect(psMediaVideoSkeleton, "handle-method-cmd-get", G_CALLBACK(MediaVideoGetCmd), sMediaVideoservdata);

    /** Fourth step: Export interface skeleton. */
    (void) g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(psMediaVideoSkeleton),
                                              connection,
                                              AW_GDBUS_MEDIAVIDEO_OBJECT_PATH,
                                              &pError);
    if(pError != NULL){
        g_print("Error: Failed to export object. Reason: %s.\n", pError->message);
        g_error_free(pError);
        g_main_loop_quit(psMediaVideoLoop);
    }
    g_print("bus_acquired_cb call end\n");
}

 void sMediaVideonameAcquiredCB(GDBusConnection *connection,
                                     const gchar     *bus_name,
                                     gpointer         user_data)
{
    g_print("name_acquired_cb call, Acquired bus name: %s.\n", AW_GDBUS_MEDIAVIDEO_BUS_NAME);
}

void sMediaVideonameLostCB(GDBusConnection *connection,
                             const gchar     *bus_name,
                             gpointer         user_data)
{
    if(connection == NULL)
    {
        g_print("name_lost_cb call, Error: Failed to connect to dbus.\n");
    }
    else
    {
        g_print("name_lost_cb call, Error: Failed to obtain bus name: %s.\n", AW_GDBUS_MEDIAVIDEO_BUS_NAME);
    }

    g_main_loop_quit(psMediaVideoLoop);
}

void* sMediaVideorun(void* para)
{
    g_print("run call in the server.\n");
	
    pthread_detach(pthread_self());
        /** Start the Main Event Loop which manages all available sources of events */
    g_main_loop_run( psMediaVideoLoop );

    return ((void*)0);
}

int sMediaVideothreadCreate(void)
{
    int err;
    pthread_t thr;

    err = pthread_create(&thr, NULL, sMediaVideorun, NULL);

    if (err != 0)
    {
        g_print("Can't create thread: %s\n", strerror(err));
    }
    else
    {
        g_print("New thread created: %s\n", strerror(err));
    }

    return err;
}


bool sMediaVideoInitDBusCommunicationServer(void)
{
    bool bRet = TRUE;

    /** init for usage of "g" types */
    g_type_init();

    /** create main loop, but do not start it. */
    psMediaVideoLoop = g_main_loop_new(NULL, FALSE);

    /** first step: connect to dbus */
    (void)g_bus_own_name(G_BUS_TYPE_SESSION,
                        AW_GDBUS_MEDIAVIDEO_BUS_NAME,
                        G_BUS_NAME_OWNER_FLAGS_NONE,
                        &sMediaVideobusAcquiredCB,
                        &sMediaVideonameAcquiredCB,
                        &sMediaVideonameLostCB,
                        NULL,
                        NULL);
#ifndef GDBUSLIB_COM
    /** emit my signal1 every 1 second to trigger example communication */
    //g_timeout_add(1000, (GSourceFunc)EmitMediaVideoSignal, NULL);
#endif
    sMediaVideothreadCreate();

    return bRet;    
}

bool sMediaVideoDeinitDBusCommunicationServer(void)
{
    bool bRet = FALSE;
    if(0 != psMediaVideoLoop){
        g_main_loop_quit(psMediaVideoLoop);
        g_main_loop_unref(psMediaVideoLoop);
        bRet = TRUE;
    }

    return bRet;

}
//////////////////////////////

int sMediaVideoServerInit(void *p)
{
    sMediaVideoInitDBusCommunicationServer();
	sMediaVideoservdata = p;
#ifndef GDBUSLIB_COM

   // sleep(100);
#endif
    return 0;
}


#if 0
extern int mainClient(void);

int main(int argc, char **argv)
{

   if(argc>1){
       if (!strncmp(argv[1], "c", 1))
       {
           mainClient();
       }
       else if (!strncmp(argv[1], "s", 1))
       {
           mainServer();
       }
       
   }
}
#endif


