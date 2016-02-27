//
//  fc_conditionManager.cpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/25/16.
//
//

#include "fc_conditionManager.hpp"

fc_conditionManager::fc_conditionManager() {
    conditions.clear();
    allRelayCounter.clear();
}

void fc_conditionManager::setDevices(vector<fc_device *> _devices) {
    devices = _devices;
    cout << devices.size() << endl;
    cout << _devices.size() << endl;
    bool b = false;
    for(int i = 0 ; i < devices.size() ; i ++ ) {
        allRelayCounter.push_back(b);
        allRelayCounter.push_back(b);
        allRelayCounter.push_back(b);
        allRelayCounter.push_back(b);
    }
    cout << "number of relay counters: " << allRelayCounter.size() << endl;

}

void fc_conditionManager::checkAllConditions() {
    if(conditions.size() > 0) {
        for(int i = 0 ; i < conditions.size() ; i ++ ) {
            float val = devices.at(conditions[i] -> sourceDevice) -> getLastAccelValue(conditions[i] -> abs_del, conditions[i] -> x_y_z);
            if(conditions[i] -> MT_LT == MT) {
                if(val > conditions[i] -> threshold) allRelayCounter[(conditions[i] -> targetDevice * 4) + (conditions[i] -> targetRelayChannel)] = true;
            } else {
                if(val < conditions[i] -> threshold) allRelayCounter[(conditions[i] -> targetDevice * 4) + (conditions[i] -> targetRelayChannel)] = true;
            }
        }
    }
    for(int i = 0 ; i < allRelayCounter.size() ; i ++ ) {
        devices.at(i / numberOfRelayChannels) -> setRelay(i % numberOfRelayChannels, allRelayCounter[i]);
        allRelayCounter[i] = false;
    }
}

void fc_conditionManager::makeNewCondition(int _sourceDevice,
                                           Parameter _x_y_z,
                                           Parameter _abs_del,
                                           Parameter _MT_LT,
                                           float _threshold,
                                           int _targetDevice,
                                           int _targetRelay) {
    fc_condition * c = new fc_condition();
    c -> sourceDevice = _sourceDevice;
    c -> x_y_z = _x_y_z;
    c -> abs_del = _abs_del;
    c -> MT_LT = _MT_LT;
    c -> threshold = _threshold;
    c -> targetDevice = _targetDevice;
    c -> targetRelayChannel = _targetRelay;
    c -> triggerType = OPEN;
    c -> triggerSetDuration = 0;
    c -> conditionLifespan = INFINITE;
    c -> conditionTimer = 0;
    
    conditions.push_back(c);
}

void fc_conditionManager::makeNewCondition(int _sourceDevice,
                                           Parameter _x_y_z,
                                           Parameter _abs_del,
                                           Parameter _MT_LT,
                                           float _threshold,
                                           int _targetDevice,
                                           int _targetRelay,
                                           TriggerType _triggerType,
                                           float _triggerSetDuration) {
    fc_condition * c = new fc_condition();
    c -> sourceDevice = _sourceDevice;
    c -> x_y_z = _x_y_z;
    c -> abs_del = _abs_del;
    c -> MT_LT = _MT_LT;
    c -> threshold = _threshold;
    c -> targetDevice = _targetDevice;
    c -> targetRelayChannel = _targetRelay;
    c -> triggerType = _triggerType;
    c -> triggerSetDuration = _triggerSetDuration;
    c -> conditionLifespan = INFINITE;
    c -> conditionTimer = 0;
    
    conditions.push_back(c);
}

void fc_conditionManager::makeNewCondition(int _sourceDevice,
                                           Parameter _x_y_z,
                                           Parameter _abs_del,
                                           Parameter _MT_LT,
                                           float _threshold,
                                           int _targetDevice,
                                           int _targetRelay,
                                           Lifespan _conditionLifespan,
                                           float _conditionTimer) {
    fc_condition * c = new fc_condition();
    c -> sourceDevice = _sourceDevice;
    c -> x_y_z = _x_y_z;
    c -> abs_del = _abs_del;
    c -> MT_LT = _MT_LT;
    c -> threshold = _threshold;
    c -> targetDevice = _targetDevice;
    c -> targetRelayChannel = _targetRelay;
    c -> triggerType = OPEN;
    c -> triggerSetDuration = 0;
    c -> conditionLifespan = _conditionLifespan;
    c -> conditionTimer = _conditionTimer;
    
    conditions.push_back(c);
}

void fc_conditionManager::makeNewCondition(int _sourceDevice,
                                           Parameter _x_y_z,
                                           Parameter _abs_del,
                                           Parameter _MT_LT,
                                           float _threshold,
                                           int _targetDevice,
                                           int _targetRelay,
                                           TriggerType _triggerType,
                                           float _triggerSetDuration,
                                           Lifespan _conditionLifespan,
                                           float _conditionTimer) {
    fc_condition * c = new fc_condition();
    c -> sourceDevice = _sourceDevice;
    c -> x_y_z = _x_y_z;
    c -> abs_del = _abs_del;
    c -> MT_LT = _MT_LT;
    c -> threshold = _threshold;
    c -> targetDevice = _targetDevice;
    c -> targetRelayChannel = _targetRelay;
    c -> triggerType = _triggerType;
    c -> triggerSetDuration = _triggerSetDuration;
    c -> conditionLifespan = _conditionLifespan;
    c -> conditionTimer = _conditionTimer;
    
    conditions.push_back(c);
}

void fc_conditionManager::deleteCondition(int _conditionIndex) {
    if(_conditionIndex < conditions.size()) {
        conditions.erase(conditions.begin() + _conditionIndex);
    }
}

void fc_conditionManager::deleteRandomCondition() {
    conditions.erase(conditions.begin() + (int) ofRandom(conditions.size()));
}

void fc_conditionManager::getNumDevices() {
    cout << devices.size() << endl;
}
