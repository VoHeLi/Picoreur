#pragma once


class oxr_instance{
public:
    int _instance_id;
    inline oxr_instance(int instance_id){
        _instance_id = instance_id;
    }
};