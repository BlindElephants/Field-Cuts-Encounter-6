//
//  fc_deviceManager.cpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/25/16.
//
//

#include "fc_deviceManager.hpp"

fc_deviceManager::fc_deviceManager() {
    font.load("courier", 12);

}

int fc_deviceManager::makeNewDevice(string _address, bool hasRelay) {
    fc_device *_f = new fc_device();
    _f -> connect(_address);
    _f -> setHasRelay(hasRelay);
    devices.push_back(_f);
    deviceAccelParser.setDevices(devices);

    return devices.size() - 1;
}


void fc_deviceManager::update() {
    if(pingAll) {
        pingAllTimer += ofGetLastFrameTime();
        if(pingAllTimer >= pingAllPeriod) {
            shouldPing = true;
            pingAllTimer = 0.0;
        } else {
            shouldPing = false;
        }
    }
    
    //receive and distribute any new accelerometer data to devices
    deviceAccelParser.update();
    
    //check each device for changes in relay channel states since last frame, if so, send message to device
    for(int i = 0 ; i < devices.size() ; i ++ ) {
        if(shouldPing) devices[i] -> ping();
        devices[i] -> checkAndUpdateRelays();
    }
}

void fc_deviceManager::sendToDevice(int _device, int _relayChannel, bool _gate) {
    if(_device >= 0 && _device < devices.size() && _relayChannel >= 0 && _relayChannel < 4) {
        devices[_device] -> setRelay(_relayChannel, _gate);
    }
}

vector < fc_device* > fc_deviceManager::getDevices() {return devices;}

void fc_deviceManager::drawDeviceDebug(float x, float y) {
    float _y = y;
    for(int i = 0 ; i < devices.size() ; i ++ ) {
        devices[i] -> drawDebug(x, _y);
        _y += font.getSize() + 2;
    }
}

void fc_deviceManager::togglePingAll(){
    pingAll = !pingAll;
}

void fc_deviceManager::setSetDuration(bool _useSetDuration, float _setDuration) {
    for(int i = 0 ; i < devices.size() ; i ++ ) {
        devices[i] -> setSetDuration(_useSetDuration, _setDuration);
    }
}

void fc_deviceManager::setSetRecovery(bool _useSetRecovery, float _setRecovery) {
    for(int i = 0 ; i < devices.size() ; i ++ ) {
        devices[i] -> setSetRecovery(_useSetRecovery, _setRecovery);
    }
}