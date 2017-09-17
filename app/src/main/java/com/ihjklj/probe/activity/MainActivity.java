package com.ihjklj.probe.activity;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import com.ihjklj.probe.R;
import com.ihjklj.probe.androidinterface.JumpListener;
import com.ihjklj.probe.surface.FjSurfaceView;
import com.ihjklj.probe.util.LOG;

public class MainActivity extends AppCompatActivity {

    private FjSurfaceView mSurfaceview;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.home);

        LOG.d("onCreate");
        mSurfaceview = (FjSurfaceView)findViewById(R.id.surfaceView);
        mSurfaceview.setListener(new JumpListener() {
            @Override
            public boolean runJump() {
                Intent intent = new Intent(MainActivity.this, VideoInfoActivity.class);
                startActivity(intent);
                finish();
                return false;
            }
        });
    }

    @Override
    protected void onDestroy(){
        super.onDestroy();
        LOG.d("onDestroy");
    }
}
