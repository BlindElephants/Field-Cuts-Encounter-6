//
//  fc_deviceAccelParser.cpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/25/16.
//
//

#include "fc_deviceAccelParser.hpp"

fc_deviceAccelParser::fc_deviceAccelParser() {
    udp.Close();
    udp.Create();
    udp.Bind(8010);
    udp.SetNonBlocking(true);
}

void fc_deviceAccelParser::setDevices(vector<fc_device* > devices) {
    deviceReferences = devices;
    deviceAddresses.clear();
    for(int i = 0 ; i < deviceReferences.size() ; i ++ ) {
        string _a = deviceReferences[i] -> getAddress();
        vector < string > _split;
        _split = ofSplitString(_a, ".");
        deviceAddresses.push_back(_split[_split.size() - 1]);
    }
    if(deviceReferences.size() != deviceAddresses.size()) throw "error: references and addresses size mismatch";
}

void fc_deviceAccelParser::update() {
    char udpMsg[100000];
    while(udp.Receive(udpMsg, 100000)) {
        string msg = udpMsg;
        if(msg!="") {
            vector < string > splitMsg;
            splitMsg = ofSplitString(msg, " ");
            int thisIndex = 0;
            
            for(int i = 0 ; i < deviceAddresses.size() ; i ++ ) {
                if(splitMsg[0] == deviceAddresses[i]) {
                    thisIndex = i;
                    break;
                }
            }
            deviceReferences[thisIndex] -> updateAccelerometer(ofToFloat(splitMsg[1]),
                                                               ofToFloat(splitMsg[2]),
                                                               ofToFloat(splitMsg[3]));
            deviceReferences[thisIndex] -> updateAccelAverages();
        }
    }
}