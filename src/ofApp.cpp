#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    conditionManager.setDevices(deviceManager.getDevices());
    
    ofBackground(ofColor::black);
}

//--------------------------------------------------------------
void ofApp::update(){
    deviceManager.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(ofColor::white);
    deviceManager.drawDeviceDebug(16, 16);
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
}

void ofApp::exit() {
    
}
