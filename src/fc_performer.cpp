//
//  fc_performer.cpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/27/16.
//
//

#include "fc_performer.hpp"

fc_performer::fc_performer(PerformerName _name) {
    name = _name;
}

void fc_performer::setDevices(int _wristIndex, int _packIndex, int _numberRelayChannels) {
    wristIndex = _wristIndex;
    packIndex  = _packIndex;
    conditionManager = new fc_conditionManager(devices, packIndex, _numberRelayChannels);
}

void fc_performer::update() {
    conditionManager -> checkAllConditions();
}

void fc_performer::setDeviceReferences(vector < fc_device* > _devices) {
    devices = _devices;
    conditionManager -> setDeviceReference(devices);
}

void fc_performer::makeNewCondition(int _targetRelayChannel, int _sourceDevice, Parameter _x_y_z, Parameter _abs_del, Parameter _MT_LT, float _threshold, TriggerType _triggerType, float _triggerSetDuration, Lifespan _conditionLifespan, float _conditionTimer) {
    conditionManager -> makeNewCondition(_targetRelayChannel, _sourceDevice, _x_y_z, _abs_del, _MT_LT, _threshold, _triggerType, _triggerSetDuration, _conditionLifespan, _conditionTimer);
}

int fc_performer::getWristIndex() {
    return wristIndex;
}

int fc_performer::getPackIndex() {
    return packIndex;
}