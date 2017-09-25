package com.ihjklj.probe.androidnative;

import com.google.gson.Gson;
import com.ihjklj.probe.util.LOG;

/**
 * Created by ihjklj on 2017/9/17.
 */

public class NativeMethod {

    public static final String VOD_START = "vod_start";
    public static final String LIVE_START = "live_start";
    public static final String LIVE_SWITCH = "live_switch";
    public static final String DATA_TYPE = "data_type";

    public native void start();
    public native void stop();
    public native void setQosInterval();
    public native void setValue();
    public native void sendFrameInfo();

    public static void onDataUpload(String dType, String aType, String data) {
        if (dType.equalsIgnoreCase(DATA_TYPE)) {
            handleData(aType, data);
        } else {
            LOG.d("data type is error!");
        }

        return ;
    }

    private static void handleData(String type, String data) {
        if (type.equalsIgnoreCase(VOD_START) || type.equalsIgnoreCase(LIVE_SWITCH)) {

        }
        else {

        }
    }

    static {
        System.loadLibrary("LProbe");
    }
}
