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
    void sendOffMessage(int performer_index);
    void jumpToSectionOne();
    void jumpToSectionTwo();
    void jumpToSectionThree();
    void jumpToSectionFour();
    void jumptoSectionFive();
    
    ofTrueTypeFont font;
    fc_deviceManager deviceManager;
    vector < fc_performer > performers;
    fc_scoreManager scoreManager;
    
    bool runAll = true;
    
    ofxOscSender sendToFloor;
    ofxOscSender sendToSound;
    
    bool globalLights = false;
    
    ofxPanel addGui;
    
    ofxFloatSlider threshold;
    ofxIntSlider x_y_z_slider;
    ofxToggle mt_lt_toggle;
    ofxToggle abs_del_toggle;
    ofxIntSlider source_select_performer;
    ofxToggle wrist_pack_toggle;
    ofxIntSlider target_select_performer;
    ofxIntSlider target_relay_channel;
    ofxButton makeNewCondition_toggle;
    
    ofxPanel delGui;
    ofxIntSlider performer_select;
    ofxIntSlider relay_channel_select;
    ofxButton delete_all;
    ofxIntSlider condition_select;
    ofxButton delete_select;
    
    ofxPanel sectionGui;
    ofxButton sectionGui_sectionOne;
    ofxButton sectionGui_sectionTwo;
    ofxButton sectionGui_sectionThree;
    ofxButton sectionGui_sectionFour;
    ofxButton sectionGui_sectionFive;
    
    
    void makeNewCondition();
    void deleteAllCondition();
    void deleteSelectCondition();
    
};
