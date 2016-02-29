#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    font.load("courier", 12);
    
    
    ofBackground(ofColor::black);
    ofToggleFullscreen();
    
    addCondition.addListener(this, &ofApp::addConditionPressed);
    
    gui.setup();
    gui.add(addCondition.setup("add condition"));
    
    
    fc_performer *_a = new fc_performer(MEG);
    _a -> setDevices(deviceManager.makeNewDevice("10.0.1.4", false),
                     deviceManager.makeNewDevice("10.0.1.8", true),
                     4);
    performers.push_back(_a);
    
    fc_performer *_b = new fc_performer(JACOB);
    _b -> setDevices(deviceManager.makeNewDevice("10.0.1.5", false),
                     deviceManager.makeNewDevice("10.0.1.9", true),
                     4);
    performers.push_back(_b);
    
    fc_performer *_c = new fc_performer(HALEY);
    _c -> setDevices(deviceManager.makeNewDevice("10.0.1.6", false),
                     deviceManager.makeNewDevice("10.0.1.10", true),
                     4);
    performers.push_back(_c);
    
    for(int i = 0 ; i < performers.size() ; i ++ ) {
        performers[i] -> setDeviceReferences(deviceManager.getDevices());
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0 ; i < performers.size() ; i ++ ) {
        performers[i] -> update();
    }
    
    deviceManager.update();
    scoreManager.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(ofColor::white);
    deviceManager.drawDeviceDebug(16, 16);
    gui.draw();
    
    scoreManager.draw(0, ofGetHeight() - 60, ofGetWidth(), 24);
    
    ofSetColor(ofColor::white);
    font.drawString(ofToString(ofGetFrameRate()), ofGetWidth() - 80, ofGetHeight() - 16);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f') deviceManager.sendToDevice(devSel, 0, true);
    if(key == 'v') deviceManager.sendToDevice(devSel, 0, false);
    if(key == 'g') deviceManager.sendToDevice(devSel, 1, true);
    if(key == 'b') deviceManager.sendToDevice(devSel, 1, false);
    if(key == 'h') deviceManager.sendToDevice(devSel, 2, true);
    if(key == 'n') deviceManager.sendToDevice(devSel, 2, false);
    if(key == 'j') deviceManager.sendToDevice(devSel, 3, true);
    if(key == 'm') deviceManager.sendToDevice(devSel, 3, false);
    
    if(key == '0') devSel = 0;
    if(key == '1') devSel = 1;
    if(key == '2') devSel = 2;
    if(key == '3') devSel = 3;
    if(key == '4') devSel = 4;
    if(key == '5') devSel = 5;
    if(key == '6') devSel = 6;
    if(key == '7') devSel = 7;
    
    if(key == '+') ofToggleFullscreen();
    if(key == 'p') deviceManager.togglePingAll();
    
    if(key == 's') scoreManager.toggleRun();
    
    if(key == 'c') {
        performers[HALEY] -> makeNewCondition((int) ofRandom(4), performers[MEG] -> getWristIndex(), X, ABS, LT, 2200, OPEN, (int) ofRandom(4), DIE_AFTER_TRIGGER_NUM, (int) ofRandom(10) + 1);
    }
    
    if(key == 'd') deviceManager.setSetDuration(true, 5);
    if(key == 'e') deviceManager.setSetDuration(false, 5);
    
    if(key == 's') deviceManager.setSetRecovery(true, 5);
    if(key == 'w') deviceManager.setSetRecovery(false, 5);
    
}

void ofApp::exit() {
    
}

void ofApp::addConditionPressed() {
    
}