//
//  fc_conditionManager.cpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/25/16.
//
//

#include "fc_conditionManager.hpp"

fc_conditionManager::fc_conditionManager(vector < fc_device* > _devices, int _thisDeviceIndex, int _numRelayChannels) {
    devices.clear();
    devices = _devices;
    thisDeviceIndex = _thisDeviceIndex;
    conditionStreams.clear();
    for(int i = 0 ; i < _numRelayChannels ; i ++ ) {
        fc_conditionStream *_cs = new fc_conditionStream(thisDeviceIndex, i);
        _cs -> setDevices(devices);
        conditionStreams.push_back(_cs);
    }
}

void fc_conditionManager::setDeviceReference(vector<fc_device *> _devices) {
    devices = _devices;
    for(int i = 0 ; i < conditionStreams.size() ; i ++ ) {
        conditionStreams[i] -> setDevices(devices);
    }
}

void fc_conditionManager::checkAllConditions() {
    
    for(int i = 0 ; i < conditionStreams.size() ; i ++ ) {
        conditionStreams[i] -> checkAllConditions();
    }
}

void fc_conditionManager::makeNewCondition(int _targetRelayChannel, int _sourceDevice, Parameter _x_y_z, Parameter _abs_del, Parameter _MT_LT, float _threshold, TriggerType _triggerType, float _triggerSetDuration, Lifespan _conditionLifespan, float _conditionTimer) {
    conditionStreams[_targetRelayChannel] -> makeNewCondition(_sourceDevice, _x_y_z, _abs_del, _MT_LT, _threshold, _triggerType, _triggerSetDuration, _conditionLifespan, _conditionTimer);
    for(int i = 0 ; i < conditionStreams.size() ; i ++ ) {
        cout << " | " << i << ": " << conditionStreams[i] ->getNumberConditions() << endl;
    }
}

int fc_conditionManager::getNumberConditionsInRelay(int _relayChannel) {
    if(_relayChannel < conditionStreams.size()) {
        return conditionStreams[_relayChannel] -> getNumberConditions();
    } else {
        return -1;
        cout << "error: bad relay channel index" << endl;
    }
}

int fc_conditionManager::getNumberActiveConditionsInRelay(int _relayChannel) {
    if(_relayChannel < conditionStreams.size()) {
        return conditionStreams[_relayChannel] -> getNumberActiveConditions();
    } else {
        return -1;
        cout << "error: bad relay channel index" << endl;
    }
}
int fc_conditionManager::getNumberConditions() {
    int _c = 0;
    for(int i = 0 ; i < conditionStreams.size() ; i ++ ) {
        _c += conditionStreams[i] -> getNumberConditions();
    }
    return _c;
}

int fc_conditionManager::getNumberActiveConditions() {
    int _c = 0;
    for(int i = 0 ; i < conditionStreams.size() ; i ++ ) {
        _c += conditionStreams[i] -> getNumberActiveConditions();
    }
    return _c;
}

void fc_conditionManager::drawConditions(float _x, float _y) {
    if(conditionStreams.size() > 0) {
        float y = 0;
        for(int i = 0 ; i < conditionStreams.size() ; i ++ ) {
            y = conditionStreams[i] -> drawAllConditions(_x, _y + y);
        }
    }
}