#ifndef _OMX_CAMERA_H_
#define _OMX_CAMERA_H_

#include "omx_common.h"
#include "omx_print_util.h"

typedef struct omx_camera_t {
    common_interface interface;
    
    //wait camera until ready
    void (*block_until_camera_ready)(void);

    //start and stop capturing
    void (*capture_start)(void);
    void (*capture_stop)(void);

    //Check the camera input buffer directly.
    int ready;
    OMX_BUFFERHEADERTYPE *buffer_in;
} omx_camera_t;

void camera_create(void);

extern omx_camera_t omx_camera;

#endif
