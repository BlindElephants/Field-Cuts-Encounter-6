//
//  fc_conditionStream.cpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/28/16.
//
//

#include "fc_conditionStream.hpp"

fc_conditionStream::fc_conditionStream(int _thisDeviceIndex, int _thisRelayChannelIndex) {
    conditions.clear();
    font.load("courier", 12);
    thisDeviceIndex = _thisDeviceIndex;
    thisRelayChannelIndex = _thisRelayChannelIndex;
}

void fc_conditionStream::setDevices(vector<fc_device *> _devices) {
    devices = _devices;
    cout << devices.size() << endl;
}

void fc_conditionStream::checkAllConditions() {
    numActiveConditions = 0;
    if(conditions.size() > 0) {
        bool relaySetting = false;
        for(int i = conditions.size() - 1 ; i >= 0 ; i -- ) {
            cout << "condition: " << i << " condition timer: " << conditions[i] -> conditionTimer << " active timer: " << conditions[i] -> conditionActiveTime << " active num: " << conditions[i] -> conditionActiveNum << endl;;
            conditions[i] -> conditionTimer += ofGetLastFrameTime();
            if(conditions[i] -> isActive) conditions[i] -> conditionActiveTime += ofGetLastFrameTime();
            if(!(conditions[i] -> isActive) && (conditions[i] -> conditionLifespan == DIE_AFTER_TRIGGER_NUM) && (conditions[i] -> conditionActiveNum >= conditions[i] -> conditionActiveNumLimit)) {
                conditions.erase(conditions.begin() + i);
                cout << "erased because trigger number high" << endl;
            } else if((conditions[i] -> conditionLifespan == DIE_AFTER_TRIGGER_DURATION) && (conditions[i] -> conditionActiveTime >= conditions[i] -> conditionTimerLimit)) {
                conditions.erase(conditions.begin() + i);
                cout << "erased because trigger duration number high " << endl;
            } else if((conditions[i] -> conditionLifespan == DIE_AFTER_TIME) && (conditions[i] -> conditionTimer >= conditions[i] -> conditionTimerLimit)) {
                conditions.erase(conditions.begin() + i);
                cout << "erased because timer high" << endl;
            } else {
                float val = devices[conditions[i] -> sourceDevice] -> getLastAccelValue(conditions[i] -> abs_del, conditions[i] -> x_y_z);
                if(conditions[i] -> MT_LT == MT) {
                    if(conditions[i] -> threshold > val) {
                        relaySetting = true;
                        if(!(conditions[i] -> isActive)) {
                            conditions[i] -> conditionActiveNum ++ ;
                        }
                        conditions[i] -> isActive = true;
                    } else {
                        conditions[i] -> isActive = false;
                    }
                } else {
                    if(conditions[i] -> threshold < val) {
                        relaySetting = true;
                        if(!(conditions[i] -> isActive)) {
                            conditions[i] -> conditionActiveNum ++ ;
                        }
                        conditions[i] -> isActive = true;
                    } else {
                        conditions[i] -> isActive = false;
                    }
                }
                if(conditions[i] -> isActive) numActiveConditions ++ ;
            }
        }
        devices[thisDeviceIndex] -> setRelay(thisRelayChannelIndex, relaySetting);
    }
}

void fc_conditionStream::makeNewCondition(int _sourceDevice, Parameter _x_y_z, Parameter _abs_del, Parameter _MT_LT, float _threshold, TriggerType _triggerType, float _triggerSetDuration, Lifespan _conditionLifespan, float _conditionTimer) {
    fc_condition * c = new fc_condition();
    c -> sourceDevice = _sourceDevice;
    c -> x_y_z = _x_y_z;
    c -> abs_del = _abs_del;
    c -> MT_LT = _MT_LT;
    c -> threshold = _threshold;
    c -> triggerType = _triggerType;
    c -> triggerSetDuration = _triggerSetDuration;
    c -> conditionLifespan = _conditionLifespan;
    if(_conditionLifespan == DIE_AFTER_TRIGGER_NUM) {
        c -> conditionActiveNumLimit = _conditionTimer;
    } else {
        c -> conditionTimerLimit = _conditionTimer;
    }
    conditions.push_back(c);
}

int fc_conditionStream::getNumberConditions() {return conditions.size();}
int fc_conditionStream::getNumberActiveConditions() {return numActiveConditions;}