//
//  fc_device.cpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/25/16.
//
//

#include "fc_device.hpp"

void fc_device::connect(string address) {
    udp.Close();
    udp.Create();
    udp.Connect(address.c_str(), 8888);
    udp.SetNonBlocking(true);
    mAddress = address;
    
    accelAbs.clear();
    accelDel.clear();
    
    for(int i = 0 ; i < historyLimit ; i ++ ) {
        accelAbs.push_back(ofVec3f(0,0,0));
        accelDel.push_back(ofVec3f(0,0,0));
    }
    
    for(int i = 0 ; i < 4 ; i ++ ) {
        relayDevice[i].now  = false;
        relayDevice[i].last = false;
    }
    
    font.load("courier", 12);
}

void fc_device::closeConnection() {udp.Close();}

void fc_device::updateAccelerometer(float x, float y, float z) {
    accelAbs.push_back(ofVec3f(x, y, z));
    accelDel.push_back(accelAbs[accelAbs.size() - 1] - accelAbs[accelAbs.size() - 2]);
    
    while(accelAbs.size() > historyLimit) accelAbs.erase(accelAbs.begin());
    while(accelDel.size() > historyLimit) accelDel.erase(accelDel.begin());
}

void fc_device::updateAccelAverages() {
    accelAbsAvg = ofVec3f(0,0,0);
    accelDelAvg = ofVec3f(0,0,0);
    
    for(int i = 0 ; i < accelAbs.size() ; i ++ ) accelAbsAvg += accelAbs[i];
    for(int i = 0 ; i < accelDel.size() ; i ++ ) accelDelAvg += accelDel[i];
    
    accelAbsAvg /= accelAbs.size();
    accelDelAvg /= accelDel.size();
}

void fc_device::ping() {udp.Send(" ", 1);}

void fc_device::sendRelayMessage(int channel, bool set) {
    if(hasRelay && channel >= 0 && channel < 4) {
        int m = channel * 2;
        if(!set) m += 1;
        udp.Send(ofToString(m).c_str(), 1);
    }
}

void fc_device::checkAndUpdateRelays() {
    if(hasRelay) {
        for(int i = 0 ; i < 4 ; i ++ ) {
            if(useSetDuration) {
                if(relayDevice[i].last && relayDevice[i].durationTimer < setDuration) {
                    relayDevice[i].durationTimer += ofGetLastFrameTime();
                    relayDevice[i].now = true;
                } else if(relayDevice[i].last && relayDevice[i].durationTimer >= setDuration) {
                    relayDevice[i].now = false;
                    if(useSetRecovery) relayDevice[i].recoveryTimer = 0;
                }
            }
            if(useSetRecovery) {
                if((!relayDevice[i].last) && relayDevice[i].recoveryTimer < setRecovery) {
                    relayDevice[i].recoveryTimer += ofGetLastFrameTime();
                    relayDevice[i].now = false;
                }
            }
            if(relayDevice[i].now != relayDevice[i].last) {
                sendRelayMessage(i, relayDevice[i].now);
                relayDevice[i].last = relayDevice[i].now;
                relayDevice[i].durationTimer = 0;
                relayDevice[i].recoveryTimer = 0;
            }
        }
    }
}

void fc_device::setRelay(int channel, bool set) {
    if(hasRelay && channel >= 0 && channel < 4) {
        relayDevice[channel].now = set;
    }
}

float fc_device::getLastAccelValue(Parameter ABS_DEL, Parameter X_Y_Z) {
    if(ABS_DEL == ABS) {
        if(X_Y_Z == X) {
            return accelAbs.back().x;
        } else if(X_Y_Z == Y) {
            return accelAbs.back().y;
        } else if(X_Y_Z == Z){
            return accelAbs.back().z;
        }
    } else if(ABS_DEL == DEL) {
        if(X_Y_Z == X) {
            return accelDel.back().x;
        } else if(X_Y_Z == Y) {
            return accelDel.back().y;
        } else if(X_Y_Z == Z) {
            return accelDel.back().z;
        }
    } else {
        throw "error in fc_device::getLastAccelValue";
        return -1;
    }
}

void fc_device::drawDebug(float _x, float _y) {
    ofSetColor(ofColor::white);
    ofPushMatrix();
    ofTranslate(_x, _y);
    font.drawString(mAddress, 0, 0);
    font.drawString(" | ", 100, 0);
    font.drawString("ACCEL ABS: ", 124, 0);
    font.drawString(ofToString(accelAbs.back()), 228, 0);
    font.drawString("ACCEL DEL: ", 408, 0);
    font.drawString(ofToString(accelDel.back()), 512, 0);
    font.drawString(" | ", 692, 0);
    if(hasRelay) {
        font.drawString("RELAY: ", 722, 0);
        for(int i = 0 ; i < 4 ; i ++ ) {
            if(relayDevice[i].now) {
                ofSetColor(ofColor::red);
                font.drawString("TRUE", 792 + (i * 60), 0);
            } else {
                ofSetColor(ofColor::white);
                font.drawString("FALSE", 792 + (i * 60), 0);
            }
        }
    }
    ofPopMatrix();
}

void fc_device::setHasRelay(bool _hasRelay) {
    hasRelay = _hasRelay;
}

void fc_device::setSetDuration(bool _useSetDuration, float _setDuration) {
    useSetDuration = _useSetDuration;
    setDuration    = _setDuration;
}

void fc_device::setSetRecovery(bool _useSetRecovery, float _setRecovery) {
    useSetRecovery = _useSetRecovery;
    setRecovery    = _setRecovery;
    for(int i = 0 ; i < 4 ; i ++ ) {
        relayDevice[i].recoveryTimer = setRecovery;
    }
}