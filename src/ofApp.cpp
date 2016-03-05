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
    deviceManager.setSetDuration(true, ofRandom(0.1, 1.2));
    deviceManager.setSetRecovery(true, ofRandom(1, 8));
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0 ; i < performers.size() ; i ++ ) performers[i].update();
    scoreManager.update();
    deviceManager.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(ofColor::white);
    deviceManager.drawDeviceDebug(16, 16);
    scoreManager.draw(0, ofGetHeight() - 60, ofGetWidth(), 24);
    ofSetColor(ofColor::white);
    font.drawString(ofToString(ofGetFrameRate()), ofGetWidth() - 80, ofGetHeight() - 16);

    if(performers.size() > 0) {
        for(int i = 0 ; i < performers.size() ; i ++ ) {
            ofSetColor(ofColor::white);
            ofNoFill();
            ofDrawRectangle(6 + (i * 464), 160, 458, 440);
            performers[i].drawDeviceDurRec(12 + (i * 464), 172);
            performers[i].drawConditions(12 + (i * 464), 200);
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '+') ofToggleFullscreen();
    if(key == 'p') deviceManager.togglePingAll();
    if(key == 's') scoreManager.toggleRun();
}
