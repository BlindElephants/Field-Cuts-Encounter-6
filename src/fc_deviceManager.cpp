//
//  fc_deviceManager.cpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/25/16.
//
//

#include "fc_deviceManager.hpp"

fc_deviceManager::fc_deviceManager() {
    for(int i = 0 ; i < 8 ; i ++ ) {
        fc_device *_f = new fc_device();
        _f -> connect("10.0.1." + ofToString(i + 4));
        devices.push_back(_f);
    }
    
    deviceAccelParser.setDevices(devices);
}


void fc_deviceManager::update() {
    
    //receive and distribute any new accelerometer data to devices
    deviceAccelParser.update();
    
    //check each device for changes in relay channel states since last frame, if so, send message to device
    for(int i = 0 ; i < devices.size() ; i ++ ) {
        devices[i] -> checkAndUpdateRelays();
    }
}

void fc_deviceManager::sendToDevice(int _device, int _relayChannel, bool _gate) {
    if(_device >= 0 && _device < devices.size() && _relayChannel >= 0 && _relayChannel < 4) {
        devices[_device] -> setRelay(_relayChannel, _gate);
    }
}

vector < fc_device* > fc_deviceManager::getDevices() {
    return devices;
}