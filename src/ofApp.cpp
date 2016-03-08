#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    font.load("courier", 12);
    ofBackground(ofColor::black);
    ofToggleFullscreen();
    scoreManager.setPerformersRef(&performers);
    
    fc_performer _a = *new fc_performer(MEG);
    _a.setDevices(deviceManager.makeNewDevice("10.0.1.4", false),
                     deviceManager.makeNewDevice("10.0.1.9", true),
                     4);
    performers.push_back(_a);
    fc_performer _b = *new fc_performer(JACOB);
    _b.setDevices(deviceManager.makeNewDevice("10.0.1.5", false),
                     deviceManager.makeNewDevice("10.0.1.11", true),
                     4);
    performers.push_back(_b);
    fc_performer _c = *new fc_performer(HALEY);
    _c.setDevices(deviceManager.makeNewDevice("10.0.1.7", false),
                     deviceManager.makeNewDevice("10.0.1.10", true),
                     4);
    performers.push_back(_c);
    for(int i = 0 ; i < performers.size() ; i ++ ) {
        performers[i].setDeviceReferences(deviceManager.getDevices());
    }
    deviceManager.setSetDuration(true, ofRandom(0.1, 1.2));
    deviceManager.setSetRecovery(true, ofRandom(1, 8));
    
    scoreManager.setDevicesRef(&deviceManager);
    
    sendToSound.setup("10.0.1.13", 57120);
    sendToFloor.setup("10.0.1.15", 8010);
    
    deviceManager.setAllDeviceOscRefs(&sendToFloor, &sendToSound);
    
    for(int i = 0 ; i < performers.size() ; i ++ ) {
        performers[i].setConditionManagerOscRefs(&sendToFloor, &sendToSound);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0 ; i < performers.size() ; i ++ ) performers[i].update();
    if(runAll) scoreManager.update();
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

    if(key == 'P') runAll = !runAll;
    
    if(key == '!') deviceManager.sendSignalDirect(performers[0].getPackIndex(), 0, true);
    if(key == '@') deviceManager.sendSignalDirect(performers[0].getPackIndex(), 1, true);
    if(key == '#') deviceManager.sendSignalDirect(performers[0].getPackIndex(), 2, true);
    if(key == '$') deviceManager.sendSignalDirect(performers[0].getPackIndex(), 3, true);
    
    if(key == 'Q') deviceManager.sendSignalDirect(performers[1].getPackIndex(), 0, true);
    if(key == 'W') deviceManager.sendSignalDirect(performers[1].getPackIndex(), 1, true);
    if(key == 'E') deviceManager.sendSignalDirect(performers[1].getPackIndex(), 2, true);
    if(key == 'R') deviceManager.sendSignalDirect(performers[1].getPackIndex(), 3, true);
    
    if(key == 'A') deviceManager.sendSignalDirect(performers[2].getPackIndex(), 0, true);
    if(key == 'S') deviceManager.sendSignalDirect(performers[2].getPackIndex(), 1, true);
    if(key == 'D') deviceManager.sendSignalDirect(performers[2].getPackIndex(), 2, true);
    if(key == 'F') deviceManager.sendSignalDirect(performers[2].getPackIndex(), 3, true);
    
    if(key == '1') deviceManager.sendSignalDirect(performers[0].getPackIndex(), 0, false);
    if(key == '2') deviceManager.sendSignalDirect(performers[0].getPackIndex(), 1, false);
    if(key == '3') deviceManager.sendSignalDirect(performers[0].getPackIndex(), 2, false);
    if(key == '4') deviceManager.sendSignalDirect(performers[0].getPackIndex(), 3, false);
    
    if(key == 'q') deviceManager.sendSignalDirect(performers[1].getPackIndex(), 0, false);
    if(key == 'w') deviceManager.sendSignalDirect(performers[1].getPackIndex(), 1, false);
    if(key == 'e') deviceManager.sendSignalDirect(performers[1].getPackIndex(), 2, false);
    if(key == 'r') deviceManager.sendSignalDirect(performers[1].getPackIndex(), 3, false);
    
    if(key == 'a') deviceManager.sendSignalDirect(performers[2].getPackIndex(), 0, false);
    if(key == 's') deviceManager.sendSignalDirect(performers[2].getPackIndex(), 1, false);
    if(key == 'd') deviceManager.sendSignalDirect(performers[2].getPackIndex(), 2, false);
    if(key == 'f') deviceManager.sendSignalDirect(performers[2].getPackIndex(), 3, false);
    
    if(key == 'L') {
        globalLights = !globalLights;
        ofxOscMessage m;
        m.setAddress("/global_lights");
        m.addBoolArg(globalLights);
        sendToFloor.sendMessage(m);
    }
}

void ofApp::keyReleased(int key) {
    
}

void ofApp::sendOffMessage(int performer_index) {
    if(performers.size() > performer_index) {
        performers[performer_index].sendOffMessage();
    }
}
