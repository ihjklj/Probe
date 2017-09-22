package com.ihjklj.probe.androidnative;

/**
 * Created by ihjklj on 2017/9/17.
 */

public class NativeMethod {

    public native void start();
    public native void stop();
    public native void setQosInterval();
    public native void setValue();
    public native void sendFrameInfo();

    public static void onDataUpload(String aType, String dType, String data) {
        return ;
    }

    static {
        System.loadLibrary("LProbe");
    }
}
