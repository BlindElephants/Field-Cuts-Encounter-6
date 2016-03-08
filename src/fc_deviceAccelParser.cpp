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
}

void fc_deviceAccelParser::update() {
    char udpMsg[100000];
    while(udp.Receive(udpMsg, 100000)) {
        string msg = udpMsg;
        
        if(msg!="") {
            vector < string > splitMsg;
            splitMsg = ofSplitString(msg, " ");
            int thisIndex = 0;
            if(splitMsg[0] == "4") {
                thisIndex = 0;
            } else if(splitMsg[0] == "9") {
                thisIndex = 1;
            } else if(splitMsg[0] == "5") {
                thisIndex = 2;
            } else if(splitMsg[0] == "11") {
                thisIndex = 3;
            } else if(splitMsg[0] == "7") {
                thisIndex = 4;
            } else if(splitMsg[0] == "10") {
                thisIndex = 5;
            }
            
            deviceReferences[thisIndex] -> updateAccelerometer(ofToFloat(splitMsg[1]),
                                                               ofToFloat(splitMsg[2]),
                                                               ofToFloat(splitMsg[3]));
            deviceReferences[thisIndex] -> updateAccelAverages();
        }
    }
}