//
//  fc_deviceAccelParser.hpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/25/16.
//
//

#ifndef fc_deviceAccelParser_hpp
#define fc_deviceAccelParser_hpp

#include "ofMain.h"
#include "ofxUDPManager.h"

#include "fc_device.hpp"

class fc_deviceAccelParser {
public:
    fc_deviceAccelParser();
    void setDevices(vector < fc_device* > devices);
    void update();
    
private:
    ofxUDPManager udp;
    vector < fc_device* > deviceReferences;
    vector < string > deviceAddresses;
    
};

#endif /* fc_deviceAccelParser_hpp */
