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

    static {
        System.loadLibrary("LProbe");
    }
}
