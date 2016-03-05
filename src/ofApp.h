#pragma once

#include "ofMain.h"
#include "ofxAnimatable.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#include "fc_deviceManager.hpp"

#include "fc_performer.hpp"

#include "fc_scoreManager.hpp"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    ofTrueTypeFont font;
    fc_deviceManager deviceManager;
    vector < fc_performer > performers;
    fc_scoreManager scoreManager;
};
