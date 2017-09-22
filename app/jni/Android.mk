LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libLProbe
LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(NDK14)/sources/cxx-stl/stlport/stlport
LOCAL_SRC_FILES := ikNativeFunc.cpp \
					ikThread.cpp \
					ikSocketServer.cpp \
					ikSocketClient.cpp	\
					ikHandleMain.cpp
					
#LOCAL_STATIC_LIBRARIES := $(NDK14)/sources/cxx-stl/stlport/libs/armeabi/libstlport_static.a
					
LOCAL_CFLAGS := -static
#LOCAL_LDLIBS := -dl 
LOCAL_LDFLAGS := -L. -lc -lstdc++ -llog

include $(BUILD_SHARED_LIBRARY)

