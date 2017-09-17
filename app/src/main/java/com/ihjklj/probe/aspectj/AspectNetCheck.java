package com.ihjklj.probe.aspectj;

import android.content.Context;
import android.widget.Toast;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Pointcut;
import org.aspectj.lang.reflect.MethodSignature;

/**
 * Created by Administrator on 2017/9/12.
 */

@Aspect
public class AspectNetCheck {

    @Pointcut()
    public void runNet(){}

    @Around("runNet()")
    public Object AroundSpectJ(ProceedingJoinPoint joinPoint) throws Throwable {
        MethodSignature method = (MethodSignature) joinPoint.getSignature();
        Context context = AspectUtil.getContext(joinPoint.getThis());
        if (context != null){
            if (AspectUtil.isNetworkAvailable(context)){
                Toast.makeText(context, "network is avaiable!", Toast.LENGTH_LONG).show();
                AspectUtil.d("network is avaiable.");
                return joinPoint.proceed();
            } else {
                Toast.makeText(context, "network is not avaialbe!", Toast.LENGTH_LONG).show();
            }
        }
        return null;
    }
}
