#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    font.load("courier", 12);
    
    conditionManager.setDevices(deviceManager.getDevices());
    
    ofBackground(ofColor::black);
    ofToggleFullscreen();
    
    addCondition.addListener(this, &ofApp::addConditionPressed);
    
    gui.setup();
    gui.add(addCondition.setup("add condition"));
    
    for(int i = 0 ; i < 12 ; i ++ ) {
        conditionManager.makeNewCondition((int)ofRandom(6), X, ABS, MT, ofRandom(1800, 3200), (int)ofRandom(4, 7), (int)ofRandom(4));
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    deviceManager.update();
    conditionManager.checkAllConditions();
    scoreManager.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(ofColor::white);
    deviceManager.drawDeviceDebug(16, 16);
    conditionManager.drawAllConditions(16, 500);
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
    
    if(key == ' ') conditionManager.getNumDevices();
    
    if(key == '+') ofToggleFullscreen();
    if(key == 'p') deviceManager.setPingAll(true, 0.075);
    if(key == 'c') conditionManager.deleteRandomCondition();
    
    if(key == 's') scoreManager.toggleRun();
}

void ofApp::exit() {
    
}

void ofApp::addConditionPressed() {
    
}