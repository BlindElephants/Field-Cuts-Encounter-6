//
//  fc_scoreManager.cpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/27/16.
//
//

#include "fc_scoreManager.hpp"


fc_scoreManager::fc_scoreManager() {
    font.load("courier", 12);
    
    float startTime = 120;
    float currentTime = startTime;
    int numInFirst_8_Minutes = (int) ofRandom(5, 25);
    for(int i = 0 ; i < numInFirst_8_Minutes ; i ++ ) {
        currentTime += ofRandom(5, 25);
        conditionEvent c;
        c.triggerAtTime = currentTime;
        
        int _t = (int)ofRandom(3);
        
        if(_t == 0) {
            c.targetName = MEG;
        } else if(_t == 1) {
            c.targetName = JACOB;
        } else if(_t == 2) {
            c.targetName = HALEY;
        }
        
        int _s = (int)ofRandom(3);
        if(_s == 0) {
            c.targetName = MEG;
        } else if(_s == 1) {
            c.targetName = JACOB;
        } else if(_s == 2) {
            c.targetName = HALEY;
        }
        
        int _sd = (int)ofRandom(2);
        if(_sd == 0) {
            c.sourceDevice = WRIST;
        } else if(_sd == 1){
            c.sourceDevice = PACK;
        }
        
        
        
    }
}

void fc_scoreManager::toggleRun() {
    runScore = !runScore;
}

void fc_scoreManager::update() {
    if(runScore) {
        scoreTimer += ofGetLastFrameTime();
    }
}

void fc_scoreManager::draw(float _x, float _y, float _w, float _h) {
    ofSetColor(ofColor::white);
    ofNoFill();
    ofDrawRectangle(_x, _y, _w, _h);
    
    ofFill();
    ofDrawRectangle(_x, _y, ofMap(scoreTimer, 0, scoreLength, 0, _w), _h);
    
    font.drawString(ofToString(scoreTimer) + " / " + ofToString(scoreLength), _x + 8, _y + _h + 16);
}

void fc_scoreManager::addConditionInOrder(conditionEvent _c) {
    if(conditionEvents.size() == 0) {
        conditionEvents.push_back(_c);
    } else if(_c.triggerAtTime > conditionEvents[conditionEvents.size()-1].triggerAtTime) {
        conditionEvents.push_back(_c);
    } else {
        for(int i = 0 ; i < conditionEvents.size() ; i ++ ) {
            if(_c.triggerAtTime > conditionEvents[i].triggerAtTime) {
                conditionEvents.insert(conditionEvents.begin() + (i + 1), _c);
                break;
            }
        }
    }
}

void fc_scoreManager::addTriggerLimitingEventInOrder(triggerLimitingEvent _t) {
    if(triggerLimitingEvents.size() == 0) {
        triggerLimitingEvents.push_back(_t);
    } else if(_t.triggerAtTime > triggerLimitingEvents[triggerLimitingEvents.size() - 1].triggerAtTime) {
        triggerLimitingEvents.push_back(_t);
    } else {
        for(int i = 0 ; i < triggerLimitingEvents.size() ; i ++ ) {
            if(_t.triggerAtTime > triggerLimitingEvents[i].triggerAtTime) {
                triggerLimitingEvents.insert(triggerLimitingEvents.begin() + (i + 1), _t);
                break;
            }
        }
    }
}