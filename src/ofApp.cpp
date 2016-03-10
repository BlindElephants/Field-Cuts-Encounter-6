#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    font.load("courier", 12);
    ofBackground(ofColor::black);
    ofToggleFullscreen();
    scoreManager.setPerformersRef(&performers);
    
    fc_performer _a = *new fc_performer(MEG);
    _a.setDevices(deviceManager.makeNewDevice("10.0.1.4", false), deviceManager.makeNewDevice("10.0.1.9", true), 4);
    performers.push_back(_a);
    fc_performer _b = *new fc_performer(JACOB);
    _b.setDevices(deviceManager.makeNewDevice("10.0.1.5", false), deviceManager.makeNewDevice("10.0.1.11", true), 4);
    performers.push_back(_b);
    fc_performer _c = *new fc_performer(HALEY);
    _c.setDevices(deviceManager.makeNewDevice("10.0.1.7", false), deviceManager.makeNewDevice("10.0.1.10", true), 4);
    performers.push_back(_c);
    for(int i = 0 ; i < performers.size() ; i ++ ) {
        performers[i].setDeviceReferences(deviceManager.getDevices());
    }
    deviceManager.setSetDuration(true, ofRandom(0.1, 1.2));
    deviceManager.setSetRecovery(true, ofRandom(1, 8));
    
    sendToSound.setup("10.0.1.13", 57120);
    sendToFloor.setup("10.0.1.15", 8010);
    
    deviceManager.setAllDeviceOscRefs(&sendToFloor, &sendToSound);
    
    for(int i = 0 ; i < performers.size() ; i ++ ) {
        performers[i].setConditionManagerOscRefs(&sendToFloor, &sendToSound);
        performers[i].setScoreManagerRef(&scoreManager);
    }
    
    scoreManager.setDevicesRef(&deviceManager);
    
    makeNewCondition_toggle.addListener(this, &ofApp::makeNewCondition);
    
    addGui.setup();
    addGui.add(source_select_performer.setup("source performer", 0, 0, 2));
    addGui.add(wrist_pack_toggle.setup("WRIST(true) / pack", true));
    addGui.add(x_y_z_slider.setup("X Y Z", 0, 0, 2));
    addGui.add(abs_del_toggle.setup("abs / DEL(true)", true));
    addGui.add(mt_lt_toggle.setup("mt / LT(true)" , true));
    addGui.add(threshold.setup("threshold", 140, 600, 3400));
    addGui.add(target_select_performer.setup("target performer", 0, 0, 2));
    addGui.add(target_relay_channel.setup("target relay channel", 0, 0, 3));
    addGui.add(makeNewCondition_toggle.setup("make new condition"));
    addGui.setPosition(ofGetWidth() - 204, 600);
    
    delete_all.addListener(this, &ofApp::deleteAllCondition);
    delete_select.addListener(this, &ofApp::deleteSelectCondition);
    
    delGui.setup();
    delGui.add(performer_select.setup("performer select", 0, 0, 2));
    delGui.add(relay_channel_select.setup("relay channel", 0, 0, 3));
    delGui.add(delete_all.setup("delete_all"));
    delGui.add(condition_select.setup("condition select", 0, 0, 12));
    delGui.add(delete_select.setup("delete select"));
    delGui.setPosition(ofGetWidth() - 408, 600);
    
    
    triggerLimMake.addListener(this, &ofApp::makeTriggerLimiterNow);
    
    triggerLimGui.setup();
    triggerLimGui.add(triggerDurationSet.setup("duration set", 0.05, 0.05, 8));
    triggerLimGui.add(triggerRecoverySet.setup("recovery set", 0.05, 0.05, 12));
    triggerLimGui.add(triggerLimMake.setup("make trigger limiter"));
    
    triggerLimGui.setPosition(ofGetWidth() - 612, 600);
    
    sectionGui_sectionOne.addListener(this, &ofApp::jumpToSectionOne);
    sectionGui_sectionTwo.addListener(this, &ofApp::jumpToSectionTwo);
    sectionGui_sectionThree.addListener(this, &ofApp::jumpToSectionThree);
    sectionGui_sectionFour.addListener(this, &ofApp::jumpToSectionFour);
    sectionGui_sectionFive.addListener(this, &ofApp::jumptoSectionFive);
    
    sectionGui.setup();
    sectionGui.add(sectionGui_sectionOne.setup("section ONE"));
    sectionGui.add(sectionGui_sectionTwo.setup("section TWO"));
    sectionGui.add(sectionGui_sectionThree.setup("section THREE"));
    sectionGui.add(sectionGui_sectionFour.setup("section FOUR"));
    sectionGui.add(sectionGui_sectionFive.setup("section FIVE"));
    
    sectionGui.setPosition(ofGetWidth() - 612, 600);
    
    fadeInLights.addListener(this, &ofApp::toggleFadeInLights);
    fadeOutLights.addListener(this, &ofApp::toggleFadeOutLights);
    fadeOutSound.addListener(this, &ofApp::toggleFadeOutSound);
    
    lightsFaderGui.setup();
    lightsFaderGui.add(fadeInLights.setup("fade IN lights"));
    lightsFaderGui.add(fadeOutLights.setup("fade OUT lights"));
    lightsFaderGui.add(fadeOutSound.setup("fade OUT sound"));
    
    lightsFaderGui.setPosition(ofGetWidth() - 816, 600);
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
    addGui.draw();
    delGui.draw();
    triggerLimGui.draw();
//    sectionGui.draw();
    lightsFaderGui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '+') ofToggleFullscreen();
    if(key == 'p') deviceManager.togglePingAll();
    if(key == ' ') scoreManager.toggleRun();
    
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

void ofApp::sendOffMessage(int performer_index) {
    if(performers.size() > performer_index) {
        performers[performer_index].sendOffMessage();
    }
}

void ofApp::makeNewCondition() {
    int source_index;
    if(wrist_pack_toggle) {
        source_index = performers[source_select_performer].getWristIndex();
    } else {
        source_index = performers[source_select_performer].getPackIndex();
    }
    Parameter xyz;
    if(x_y_z_slider == 0) xyz = X;
    if(x_y_z_slider == 1) xyz = Y;
    if(x_y_z_slider == 2) xyz = Z;
    
    Parameter absdel;
    if(abs_del_toggle == 0) absdel = ABS;
    if(abs_del_toggle == 1) absdel = DEL;

    Parameter mtlt;
    if(mt_lt_toggle == 0) mtlt = MT;
    if(mt_lt_toggle == 1) mtlt = LT;
    
    performers[target_select_performer].makeNewCondition(target_relay_channel, source_index , xyz, absdel, mtlt, threshold, INFINITE, 0);
}

void ofApp::deleteAllCondition() {
    performers[performer_select].deleteAllConditions();
}

void ofApp::deleteSelectCondition() {
    performers[performer_select].deleteSelectCondition(relay_channel_select, condition_select);
}

void ofApp::jumpToSectionOne() {scoreManager.goToSection1();}
void ofApp::jumpToSectionTwo() {scoreManager.goToSection2();}
void ofApp::jumpToSectionThree() {scoreManager.goToSection3();}
void ofApp::jumpToSectionFour() {scoreManager.goToSection4();}
void ofApp::jumptoSectionFive() {scoreManager.goToSection5();}

void ofApp::toggleFadeInLights() {
    ofxOscMessage m;
    m.setAddress("/global_lights");
    m.addBoolArg(false);
    sendToFloor.sendMessage(m);
}

void ofApp::toggleFadeOutLights() {
    ofxOscMessage m;
    m.setAddress("/global_lights");
    m.addBoolArg(true);
    sendToFloor.sendMessage(m);
}

void ofApp::toggleFadeOutSound() {
    ofxOscMessage m;
    m.setAddress("/fieldcuts/fadeOut");
    sendToSound.sendMessage(m);
}

void ofApp::makeTriggerLimiterNow() {
    deviceManager.setSetDuration(true, triggerDurationSet);
    deviceManager.setSetRecovery(true, triggerRecoverySet);
}
