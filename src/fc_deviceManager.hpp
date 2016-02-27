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

class fc_deviceManager {
public:
    fc_deviceManager();
    
    void update();
    void sendToDevice(int _device, int _relayChannel, bool _gate);
    vector < fc_device* > getDevices();
    
    void drawDeviceDebug(float x, float y);
    void setPingAll(bool _pingAll, float _period);
    
    
private:
    vector < fc_device* > devices;
    fc_deviceAccelParser deviceAccelParser;
    ofTrueTypeFont font;
    
    bool pingAll = false;
    bool shouldPing = false;
    float pingAllTimer = 0.0;
    float pingAllPeriod = 0.5;
};


#endif /* fc_deviceManager_hpp */
