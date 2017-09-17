package com.ihjklj.probe.aspectj;

import android.content.Context;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Pointcut;
import org.aspectj.lang.reflect.MethodSignature;

/**
 * Created by Administrator on 2017/9/12.
 */

@Aspect
public class AspectSecurity {

    @Pointcut("execution(@SecurityCheck * *(..))")
    public void runSecurity(){}

    @Around("runSecurity()")
    public Object aroundAspectJ(ProceedingJoinPoint joinPoint) throws Throwable {
        MethodSignature method = (MethodSignature) joinPoint.getSignature();
        SecurtiyCheck security = method.getMethod().getAnnotation(SecurtiyCheck.class);
        String permission = security.value();
        Context context = AspectUtil.getContext(joinPoint.getThis());
        Object object = null;
        if (context != null){
            if (AspectUtil.checkPermission(context, permission)){
                object = joinPoint.proceed();
                AspectUtil.d("have permission.");
            } else {
                AspectUtil.d("no permission!");
            }
        }

        return null;
    }
}
