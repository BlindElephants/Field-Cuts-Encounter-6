//
//  fc_networking.hpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 3/7/16.
//
//

#ifndef fc_networking_hpp
#define fc_networking_hpp

#include "ofMain.h"
#include "ofxOsc.h"

class fc_networking {
public:
    fc_networking(string _floorHostName, int _floorPortNumber,string _soundHostName, int _soundPortNumber);
    void sendOnMessageToFloor(int _targetIndex, int _relayChannelIndex, vector < int > _conditionSources);
    void sendOffMessageToFloor(int _targetIndex, int _relayChannelIndex);
    void sendOnMessageToSound(int _targetIndex, int _relayChannelIndex);
    void sendOffMessageToSound(int _targetIndex, int _relayChannelIndex);
private:
    ofxOscSender sendToFloor;
    ofxOscSender sendToSound;
};

#endif /* fc_networking_hpp */
