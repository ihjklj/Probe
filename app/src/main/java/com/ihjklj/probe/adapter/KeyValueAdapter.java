package com.ihjklj.probe.adapter;

import com.ihjklj.probe.R;
import com.ihjklj.probe.model.ShowModel;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.List;

/**
 * Created by Administrator on 2017/9/22.
 */

public class KeyValueAdapter extends BaseAdapter {
    private List<ShowModel> mList;
    private LayoutInflater mInflater;

    public KeyValueAdapter(Context context, List<ShowModel> list){
        mInflater = LayoutInflater.from(context);
        mList = list;
    }

    @Override
    public int getCount(){
        return mList.size();
    }

    @Override
    public Object getItem(int position){
        return mList.get(position);
    }

    @Override
    public long getItemId(int position){
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent){
        View view = null;
        ViewHolder viewholder = null;
        ShowModel msg = null;

        if (convertView == null){
            viewholder = new ViewHolder();
            view = mInflater.inflate(R.layout.showlist, null);
            viewholder.id = (TextView)view.findViewById(R.id.key);
            viewholder.value = (TextView)view.findViewById(R.id.value);
            view.setTag(viewholder);
        }
        else {
            view = convertView;
            viewholder = (ViewHolder)view.getTag();
        }

        msg = (ShowModel)getItem(position);
        viewholder.id.setText(msg.getId());
        viewholder.value.setText(msg.getValue());

        return view;
    }

    class ViewHolder{
        TextView id;
        TextView value;
    }
}
