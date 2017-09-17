package com.ihjklj.probe.androidnative;

/**
 * Created by ihjklj on 2017/9/17.
 */

public class NativeMethod {

    public native void start();

    static {
        System.loadLibrary("test");
    }
}
