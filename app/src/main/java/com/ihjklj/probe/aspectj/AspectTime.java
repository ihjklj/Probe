package com.ihjklj.probe.aspectj;

import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Pointcut;
import org.aspectj.lang.reflect.MethodSignature;

/**
 * Created by ihjklj on 2017/9/17.
 */

@Aspect
public class AspectTime {

    @Pointcut("execution(@TimeInterface * *(..))")
    public void runTimeInterface(){}

    @Around("runTimeInterface()")
    public Object aroundAspectJ(ProceedingJoinPoint joinPoint) throws Throwable {
        MethodSignature method = (MethodSignature) joinPoint.getSignature();
        final String className = method.getDeclaringType().getSimpleName();
        final String methodName = method.getName();

        TimeWatcher watch = new TimeWatcher();
        watch.start();
        Object object = joinPoint.proceed();
        watch.stop();
        final String print = className + " ---> " + methodName + "run " + watch.getTotalTimeMillis();
        AspectUtil.d(print);
        AspectUtil.showToast(AspectUtil.getContext(joinPoint.getThis()), print);
        return object;
    }
}
