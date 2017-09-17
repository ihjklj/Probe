package com.ihjklj.probe.aspectj;

/**
 * Created by ihjklj on 2017/9/17.
 */

import java.util.concurrent.TimeUnit;

/**
 * Class representing a StopWatch for measuring time.
 */
public class TimeWatcher {

    private long startTime;
    private long elapsedTime;

    public TimeWatcher() {
        //empty
    }

    private void reset() {
        startTime = 0;
        elapsedTime = 0;
    }

    public void start() {
        reset();
        startTime = System.nanoTime();
    }

    public void stop() {
        if (startTime != 0) {
            elapsedTime = System.nanoTime() - startTime;
        } else {
            reset();
        }
    }

    public long getTotalTimeMillis() {
        return (elapsedTime != 0) ? TimeUnit.NANOSECONDS.toMillis(elapsedTime) : 0;
    }
}