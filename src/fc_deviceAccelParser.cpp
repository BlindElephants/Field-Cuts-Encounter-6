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
    cout << deviceReferences.size() << endl;
    cout << deviceReferences.at(0) -> getDebug() << endl;
}

void fc_deviceAccelParser::update() {
    char udpMsg[100000];
    udp.Receive(udpMsg, 100000);
    string msg = udpMsg;
    
    if(msg!="") {
        vector < string > splitMsg;
        splitMsg = ofSplitString(msg, " ");
        int thisIndex = ofToInt(splitMsg[0]);
        thisIndex -= 4;
        deviceReferences[thisIndex] -> updateAccelerometer(ofToFloat(splitMsg[1]),
                                                           ofToFloat(splitMsg[2]),
                                                           ofToFloat(splitMsg[3]));
        deviceReferences[thisIndex] -> updateAccelAverages();
    }
}