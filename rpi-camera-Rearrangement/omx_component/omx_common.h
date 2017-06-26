#ifndef _OMX_COMMON_H_
#define _OMX_COMMON_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>  

#include <bcm_host.h>

#include <interface/vcos/vcos_semaphore.h>
#include <interface/vmcs_host/vchost.h>

#include <IL/OMX_Core.h>
#include <IL/OMX_Component.h>
#include <IL/OMX_Video.h>
#include <IL/OMX_Broadcom.h>

// Hard coded parameters
#define VIDEO_WIDTH                     1920
#define VIDEO_HEIGHT                    1080
#define VIDEO_FRAMERATE                 25
#define VIDEO_BITRATE                   10000000
#define CAM_DEVICE_NUMBER               0
#define CAM_SHARPNESS                   0                       // -100 .. 100
#define CAM_CONTRAST                    0                       // -100 .. 100
#define CAM_BRIGHTNESS                  50                      // 0 .. 100
#define CAM_SATURATION                  0                       // -100 .. 100
#define CAM_EXPOSURE_VALUE_COMPENSTAION 0
#define CAM_EXPOSURE_ISO_SENSITIVITY    100
#define CAM_EXPOSURE_AUTO_SENSITIVITY   OMX_FALSE
#define CAM_FRAME_STABILISATION         OMX_TRUE
#define CAM_WHITE_BALANCE_CONTROL       OMX_WhiteBalControlAuto // OMX_WHITEBALCONTROLTYPE
#define CAM_IMAGE_FILTER                OMX_ImageFilterNoise    // OMX_IMAGEFILTERTYPE
#define CAM_FLIP_HORIZONTAL             OMX_FALSE
#define CAM_FLIP_VERTICAL               OMX_FALSE

// useful utilitys for omx
void init_component_handle(const char *name, OMX_HANDLETYPE* hComponent, OMX_PTR pAppData, OMX_CALLBACKTYPE* callbacks); 

void block_until_state_changed(OMX_HANDLETYPE hComponent, OMX_STATETYPE wanted_eState);
void block_until_port_changed(OMX_HANDLETYPE hComponent, OMX_U32 nPortIndex, OMX_BOOL bEnabled);
void block_until_flushed(common_context_t *ctx);

// Dunno where this is originally stolen from...
#define OMX_INIT_STRUCTURE(a) \
    memset(&(a), 0, sizeof(a)); \
    (a).nSize = sizeof(a); \
    (a).nVersion.nVersion = OMX_VERSION; \
    (a).nVersion.s.nVersionMajor = OMX_VERSION_MAJOR; \
    (a).nVersion.s.nVersionMinor = OMX_VERSION_MINOR; \
    (a).nVersion.s.nRevision = OMX_VERSION_REVISION; \
    (a).nVersion.s.nStep = OMX_VERSION_STEP

typedef struct common_interface {
    OMX_HANDLETYPE handle;
    
    void (*init_handle)(void);
    void (*free_handle)(void);

    void (*param_set)(void);
    
    void (*port_enable)(void);
    void (*port_disable)(void);

    void (*idle_state)(void);
    void (*excute_state)(void);
    void (*load_state)(void);
} common_interface;


//common context, flag for flush check, semaphore for critical section

typedef struct common_context_t {
    int flushed; //Controlled by event handler, check OMX component's buffers are flushed

    VCOS_SEMAPHORE_T handler_lock; //Some tasks require a critical section.
} common_context_t;

extern common_context_t ctx;

void common_context_init(void);
void common_context_deinit(void);

//callback(or interrupt) for omx component
//use OMX_CALLBACKTYPE
extern OMX_CALLBACKTYPE callbacks;

//event and buffer check handler should be defined by user.
OMX_ERRORTYPE event_handler(OMX_HANDLETYPE hComponent
                            , OMX_PTR pAppData, OMX_EVENTTYPE eEvent
                            , OMX_U32 nData1
                            , OMX_U32 nData2
                            , OMX_PTR pEventData);

OMX_ERRORTYPE fill_output_buffer_done_handler(  OMX_HANDLETYPE hComponent
                                                , OMX_PTR pAppData
                                                , OMX_BUFFERHEADERTYPE* pBuffer);
 
void callback_init(void);
#endif
