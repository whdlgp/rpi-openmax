#ifndef _OMX_PRINT_UTIL_H_
#define _OMX_PRINT_UTIL_H_

void set_verbose();
void reset_verbose();

void say(const char* message, ...);
void die(const char* message, ...);

void omx_die(OMX_ERRORTYPE error, const char* message, ...);

void dump_event(OMX_HANDLETYPE hComponent, OMX_EVENTTYPE eEvent, OMX_U32 nData1, OMX_U32 nData2);
void dump_port(OMX_HANDLETYPE hComponent, OMX_U32 nPortIndex, OMX_BOOL dumpformats);

#endif
