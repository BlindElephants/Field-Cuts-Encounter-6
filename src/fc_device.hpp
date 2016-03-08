//
//  fc_device.hpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/25/16.
//
//

#ifndef fc_device_hpp
#define fc_device_hpp

#include "ofMain.h"
#include "ofxUDPManager.h"

#include "fc_condition.hpp"
#include "ofxOsc.h"


class fc_device {
public:
    fc_device() {};
    
    void connect(string address);
    void closeConnection();
    void updateAccelerometer(float x, float y, float z);
    void updateAccelAverages();
    void ping();
    void sendRelayMessage(int channel, bool set, int _thisDeviceIndex);
    void checkAndUpdateRelays(int _thisDeviceIndex);
    
    void setRelay(int channel, bool set);
    
    float getLastAccelValue(Parameter ABS_DEL, Parameter X_Y_Z);

    void drawDebug(float _x, float _y);
    void setHasRelay(bool _hasRelay);
    
    void setSetDuration(bool _useSetDuration, float _setDuration);
    void setSetRecovery(bool _useSetRecovery, float _setRecovery);
    void drawSetDurRec(float _x, float _y);
    
    void sendOffMessages(int _thisDeviceIndex);
    
    void clearRelayChannelConditionSources(int _relayChannelIndex);
    void clearAllRelayChannelConditionSource();
    
    void setRelayChannelConditionSources(int _relayChannelIndex, vector < int > _conditionSources);

    void setOscRefs(ofxOscSender *toFloor, ofxOscSender *toSound);
    
private:
    ofxUDPManager udp;
    
    int historyLimit = 20;
    vector < ofVec3f > accelAbs;
    vector < ofVec3f > accelDel;
    
    ofVec3f accelAbsAvg;
    ofVec3f accelDelAvg;
    
    struct relayChannel {
        bool now;
        bool last;
        
        float durationTimer = 0;
        float recoveryTimer = 0;
        
        vector < int > conditionSources;
    };
    
    float setDuration;
    float setRecovery;
    bool useSetDuration = false;
    bool useSetRecovery = false;
    bool hasRelay;
    relayChannel relayDevice[4];
    string mAddress;
    ofTrueTypeFont font;
    
    bool sendToOsc = false;
    ofxOscSender *sendToFloor;
    ofxOscSender *sendToSound;
};

#endif /* fc_device_hpp */
