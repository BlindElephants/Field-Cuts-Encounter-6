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
    font.load("courier", 12);
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
        
        hasConditionsToUpdate.push_back(false);
    }
}

void fc_conditionManager::checkAllConditions() {
    if(conditions.size() > 0) {
        for(int i = 0 ; i < conditions.size() ; i ++ ) {
            conditions[i] -> conditionTimer += ofGetLastFrameTime();
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

void fc_conditionManager::makeNewCondition(int _sourceDevice, Parameter _x_y_z, Parameter _abs_del, Parameter _MT_LT, float _threshold, int _targetDevice, int _targetRelay) {
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
void fc_conditionManager::makeNewCondition(int _sourceDevice, Parameter _x_y_z, Parameter _abs_del, Parameter _MT_LT, float _threshold, int _targetDevice, int _targetRelay, TriggerType _triggerType, float _triggerSetDuration) {
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
void fc_conditionManager::makeNewCondition(int _sourceDevice, Parameter _x_y_z, Parameter _abs_del, Parameter _MT_LT, float _threshold, int _targetDevice, int _targetRelay, Lifespan _conditionLifespan, float _conditionTimer) {
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
void fc_conditionManager::makeNewCondition(int _sourceDevice, Parameter _x_y_z, Parameter _abs_del, Parameter _MT_LT, float _threshold, int _targetDevice, int _targetRelay, TriggerType _triggerType, float _triggerSetDuration, Lifespan _conditionLifespan, float _conditionTimer) {
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
    if(conditions.size() > 0) conditions.erase(conditions.begin() + (int) ofRandom(conditions.size()));
}

void fc_conditionManager::getNumDevices() {cout << devices.size() << endl;}

string fc_conditionManager::printCondition(int index) {
    string _s;
    _s += "SOURCE: " + ofToString(conditions[index] -> sourceDevice);
    _s += " | ";
    
    if(conditions[index] -> x_y_z == X) {
        _s += "X";
    } else if (conditions[index] -> x_y_z == Y) {
        _s += "Y";
    } else if (conditions[index] -> x_y_z == Z) {
        _s += "Z";
    }
    
    _s += " - ";
    if(conditions[index] -> abs_del == ABS) {
        _s += "ABS";
    } else if (conditions[index] -> abs_del == DEL) {
        _s += "DEL";
    }
    
    _s += " ";
    if(conditions[index] -> MT_LT == MT) {
        _s += ">";
    } else if(conditions[index] -> MT_LT == LT) {
        _s += "<";
    }
    
    _s += " ";
    _s += ofToString(conditions[index] -> threshold);
    
    _s += " | TARGET: ";
    _s += ofToString(conditions[index] -> targetDevice);
    _s += "-";
    _s += ofToString(conditions[index] -> targetRelayChannel);
    
    _s += " | ";
    _s += "TRIGTYPE: ";
    if(conditions[index] -> triggerType == OPEN) {
        _s += "OPEN";
    } else {
        _s += "LOCKED DURATION";
        _s += " - " + ofToString(conditions[index] -> triggerSetDuration);
    }
    
    return _s;
}
void fc_conditionManager::drawAllConditions(float x, float y) {
    float _y = y;
    
    for(int i = 0 ; i < conditions.size() ; i ++ ) {
        font.drawString(printCondition(i), x, _y);
        _y += 16;
    }
}
void fc_conditionManager::deleteConditionsOlderThan(float _age) {
    if(conditions.size() > 0) {
        for(int i = conditions.size() - 1 ; i >= 0 ; i -- ) {
            if(conditions[i] -> conditionTimer >= _age) conditions.erase(conditions.begin() + i);
        }
    }
}
void fc_conditionManager::deleteConditionsYoungerThan(float _age) {
    if(conditions.size() > 0) {
        for(int i = conditions.size() - 1 ; i >= 0 ; i -- ) {
            if(conditions[i] -> conditionTimer <= _age) conditions.erase(conditions.begin() + i);
        }
    }
}
void fc_conditionManager::deleteConditionsWithFewerThanHits(int _numHits) {
    if(conditions.size() > 0) {
        for(int i = conditions.size() - 1 ; i >= 0 ; i -- ) {
            if(conditions[i] -> conditionActiveNum < _numHits) conditions.erase(conditions.begin() + i);
        }
    }
}
void fc_conditionManager::deleteConditionsWithMoreThanHits(int _numHits) {
    if(conditions.size() > 0) {
        for(int i = conditions.size() - 1 ; i >= 0 ; i -- ) {
            if(conditions[i] -> conditionActiveNum > _numHits) conditions.erase(conditions.begin() + i);
        }
    }
}
void fc_conditionManager::setAllConditionDurations(TriggerType _durationType, float _durationLength) {
    if(conditions.size() > 0) {
        for(int i = 0 ; i < conditions.size() ; i ++ ) {
            conditions[i] -> triggerType = _durationType;
            conditions[i] -> triggerSetDuration = _durationLength;
        }
    }
}

