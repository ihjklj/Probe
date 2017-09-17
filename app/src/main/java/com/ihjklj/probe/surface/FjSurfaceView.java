package com.ihjklj.probe.surface;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import com.ihjklj.probe.R;
import com.ihjklj.probe.androidinterface.JumpListener;
import com.ihjklj.probe.aspectj.TimeInterface;
import com.ihjklj.probe.util.LOG;
import com.ihjklj.probe.util.UtilMethod;

/**
 * Created by ihjklj on 2017/9/16.
 */

public class FjSurfaceView extends SurfaceView implements SurfaceHolder.Callback {

    private boolean mIsHomePagComplete = false;
    private SurfaceHolder mHolder;
    private Context mContext;
    private JumpListener mListener;

    public FjSurfaceView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        init(context, 1);
    }

    public FjSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs, 0);
        init(context, 2);
    }

    public FjSurfaceView(Context context) {
        super(context);
        init(context, 3);
    }

    private void init(Context context, int flag){
        mHolder = getHolder();
        mHolder.addCallback(this);
        mContext = context;
    }

    public void setListener(JumpListener listener){
        mListener = listener;
    }

    public boolean isSurfaceComplete(){
        return mIsHomePagComplete;
    }

    @TimeInterface
    public void run(){
        UtilMethod.Sleep(100);
        new Thread(new Runnable() {
            @Override
            public void run() {
                if (mListener != null){
                    UtilMethod.Sleep(2000);
                    mListener.runJump();
                }
            }
        }).start();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        //
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        Canvas canvas = holder.lockCanvas();
        Bitmap back = BitmapFactory.decodeResource(FjSurfaceView.this.getResources(), R.drawable.test);
        canvas.drawBitmap(back, 0, 0, null);
        holder.unlockCanvasAndPost(canvas);

        run();
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        //
    }
}
