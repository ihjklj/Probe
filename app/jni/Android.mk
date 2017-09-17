LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libtest
LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_SRC_FILES := nativeHeader.cpp
LOCAL_CFLAGS := -static
LOCAL_LDLIBS := -dl 
LOCAL_LDFLAGS := -L. -lc -lstdc++ -llog

include $(BUILD_SHARED_LIBRARY)

