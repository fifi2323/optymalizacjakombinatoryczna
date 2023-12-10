#pragma once
#include<iostream>
#include"json.hpp"
#include"json_fwd.hpp"
using namespace std;
class Item
{
    private:
        int value, volume, mass, id;
    public:
        Item(int invalue, int involume, int inmass, int inid)
        {
            value = invalue;
            volume = involume;
            mass = inmass;
            id = inid;
        }
        int getValue() const
        {
            return value;
        }
        int getVolume() const
        {
            return volume;
        }
        int getMass() const
        {
            return mass;
        }
        int getId() const
        {
            return id;
        }
        void to_json(nlohmann::json& j) const {
        j = {
            {"value", value},
            {"volume", volume},
            {"mass", mass},
            {"id", id}
        };
    }
};