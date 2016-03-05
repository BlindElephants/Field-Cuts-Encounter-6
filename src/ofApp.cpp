#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    font.load("courier", 12);
    ofBackground(ofColor::black);
    ofToggleFullscreen();
    
    
    scoreManager.setPerformersRef(&performers);

    
    fc_performer _a = *new fc_performer(MEG);
    _a.setDevices(deviceManager.makeNewDevice("10.0.1.4", false),
                     deviceManager.makeNewDevice("10.0.1.8", true),
                     4);
    performers.push_back(_a);
    
    fc_performer _b = *new fc_performer(JACOB);
    _b.setDevices(deviceManager.makeNewDevice("10.0.1.5", false),
                     deviceManager.makeNewDevice("10.0.1.9", true),
                     4);
    performers.push_back(_b);
    
    fc_performer _c = *new fc_performer(HALEY);
    _c.setDevices(deviceManager.makeNewDevice("10.0.1.6", false),
                     deviceManager.makeNewDevice("10.0.1.10", true),
                     4);
    performers.push_back(_c);
    
    for(int i = 0 ; i < performers.size() ; i ++ ) {
        performers[i].setDeviceReferences(deviceManager.getDevices());
    }
    
    
    deviceManager.setSetDuration(false, 0);
    deviceManager.setSetRecovery(false, 0);
    

}

//--------------------------------------------------------------
void ofApp::update(){
    scoreManager.update();
    deviceManager.update();
    for(int i = 0 ; i < performers.size() ; i ++ ) performers[i].update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(ofColor::white);
    deviceManager.drawDeviceDebug(16, 16);
    
    scoreManager.draw(0, ofGetHeight() - 60, ofGetWidth(), 24);
    
    ofSetColor(ofColor::white);
    font.drawString(ofToString(ofGetFrameRate()), ofGetWidth() - 80, ofGetHeight() - 16);
    
    ofSetColor(ofColor::white);
    
    performers[0].drawConditions(12, 200);
    performers[1].drawConditions(492, 400);
    performers[2].drawConditions(972, 600);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '+') ofToggleFullscreen();
    if(key == 'p') deviceManager.togglePingAll();
    if(key == 's') scoreManager.toggleRun();

    
    
    if(key == 'd') deviceManager.setSetDuration(true, 5);
    if(key == 'e') deviceManager.setSetDuration(false, 5);
    
    if(key == 's') deviceManager.setSetRecovery(true, 5);
    if(key == 'w') deviceManager.setSetRecovery(false, 5);
    
}
