package com.ihjklj.probe.activity;

import android.app.Activity;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import com.ihjklj.probe.R;
import com.ihjklj.probe.androidnative.NativeMethod;
import com.ihjklj.probe.util.LOG;

/**
 * Created by ihjklj on 2017/9/17.
 */

public class VideoInfoActivity extends Activity {

    private NativeMethod mNativeMethod;

    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.videoinfo);
        LOG.d("2 onCreate");

        init();
    }

    private void init(){
        LOG.d("init");
        mNativeMethod = new NativeMethod();
        mNativeMethod.start();
    }
}
