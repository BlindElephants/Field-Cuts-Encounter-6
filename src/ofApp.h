#pragma once

#include "ofMain.h"
#include "ofxAnimatable.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#include "fc_deviceManager.hpp"
#include "fc_conditionManager.hpp"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void exit();

    
    int devSel = 0;
    
    fc_deviceManager deviceManager;
    fc_conditionManager conditionManager;
};
