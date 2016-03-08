//
//  fc_networking.cpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 3/7/16.
//
//

#include "fc_networking.hpp"

fc_networking::fc_networking(string _floorHostName, int _floorPortNumber, string _soundHostName, int _soundPortNumber) {
    sendToFloor.setup(_floorHostName, _floorPortNumber);
    sendToSound.setup(_soundHostName, _soundPortNumber);
}

void fc_networking::sendOnMessageToFloor(int _targetIndex, int _relayChannelIndex, vector <int> _conditionSources) {
    if(_conditionSources.size() > 0) {
        for(int i = 0 ; i < _conditionSources.size() ; i ++ ) {
            ofxOscMessage m;
            m.setAddress("/on");
            m.addIntArg(_targetIndex);
            m.addIntArg(_relayChannelIndex);
            m.addIntArg(_conditionSources[i]);
            sendToFloor.sendMessage(m);
        }
    }
}

void fc_networking::sendOffMessageToFloor(int _targetIndex, int _relayChannelIndex) {
    ofxOscMessage m;
    m.setAddress("/off");
    m.addIntArg(_targetIndex);
    m.addIntArg(_relayChannelIndex);
    sendToFloor.sendMessage(m);
}

void fc_networking::sendOnMessageToSound(int _targetIndex, int _relayChannelIndex) {
    ofxOscMessage m;
    m.setAddress("/on");
    m.addIntArg(_targetIndex);
    m.addIntArg(_relayChannelIndex);
    sendToSound.sendMessage(m);
}

void fc_networking::sendOffMessageToSound(int _targetIndex, int _relayChannelIndex) {
    ofxOscMessage m;
    m.setAddress("/off");
    m.addIntArg(_targetIndex);
    m.addIntArg(_relayChannelIndex);
    sendToSound.sendMessage(m);
}