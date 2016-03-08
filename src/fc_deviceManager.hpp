//
//  fc_deviceManager.hpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/25/16.
//
//

#ifndef fc_deviceManager_hpp
#define fc_deviceManager_hpp

#include "ofMain.h"

#include "fc_device.hpp"
#include "fc_deviceAccelParser.hpp"

#include "ofxOsc.h"

class fc_deviceManager {
public:
    fc_deviceManager();
    
    int makeNewDevice(string _address, bool hasRelay);
    
    void update();
    void sendToDevice(int _device, int _relayChannel, bool _gate);
    vector < fc_device* > getDevices();
    
    void drawDeviceDebug(float x, float y);
    void togglePingAll();
    
    void setSetDuration(bool _useSetDuration, float _setDuration);
    void setSetRecovery(bool _useSetRecovery, float _setRecovery);
    
    void setSetDurationDevice(int _deviceIndex, bool _useSetDuration, float _setDuration);
    void setSetRecoveryDevice(int _deviceIndex, bool _useSetRecovery, float _setRecovery);
    
    void sendSignalDirect(int _deviceIndex, int _relayChannel, bool _gate);
    void setAllDeviceOscRefs(ofxOscSender *toFloor, ofxOscSender *toSound);
private:
    vector < fc_device* > devices;
    fc_deviceAccelParser deviceAccelParser;
    ofTrueTypeFont font;
    
    bool pingAll = false;
    bool shouldPing = false;
    float pingAllTimer = 0.0;
    float pingAllPeriod = 0.075;
};


#endif /* fc_deviceManager_hpp */
