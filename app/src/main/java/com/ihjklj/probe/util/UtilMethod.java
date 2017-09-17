package com.ihjklj.probe.util;

/**
 * Created by ihjklj on 2017/9/17.
 */

public class UtilMethod {

    public static void Sleep(int time){
        try {
            Thread.sleep(time);
        } catch (Exception e){
            e.printStackTrace();
        }
    }
}
