package com.ihjklj.probe.model;

/**
 * Created by Administrator on 2017/9/22.
 */

public class ShowModel {

    private String id;
    private String value;

    public ShowModel(String id, String value){
        this.id = id;
        this.value = value;
    }

    public void setId(String id){
        this.id = id;
    }

    public void setValue(String value){
        this.value = value;
    }

    public String getId(){
        return id;
    }

    public String getValue(){
        return value;
    }

    @Override
    public String toString(){
        return "id:" + id + ", value:" + value;
    }
}
