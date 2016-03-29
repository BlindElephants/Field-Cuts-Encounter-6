//
//  fc_scoreManager.cpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/27/16.
//
//

#include "fc_scoreManager.hpp"

#define absActiveLifespan 30
#define delActiveLifespan 10


fc_scoreManager::fc_scoreManager() {
    font.load("courier", 12);
    conditionEvents.clear();
    triggerLimitingEvents.clear();
    deleteEvents.clear();
    
    scoreLength = scoreLength + ofRandom(-240, 120);
    
    //section 1
    float section_1_start_time = 0;
    float section_1_end_time = (scoreLength * 0.2) + ofRandom(-30, 30);
    float section_1_duration = section_1_end_time - section_1_start_time;
    
    float section_2_start_time = section_1_end_time;
    float section_2_end_time = section_2_start_time + (scoreLength * 0.1714) + ofRandom(-30, 30);
    float section_2_duration = section_2_end_time - section_2_start_time;
    
    float section_3_start_time = section_2_end_time;
    float section_3_end_time = section_3_start_time + (scoreLength * 0.314) + ofRandom(-30, 30);
    float section_3_duration = section_3_end_time - section_3_start_time;
    
    float section_4_start_time = section_3_end_time;
    float section_4_end_time = section_4_start_time + (scoreLength * 0.13333) + ofRandom(-15, 15);
    float section_4_duration = section_4_end_time - section_4_start_time;
    
    float section_5_start_time = section_4_end_time;
    float section_5_end_time = scoreLength;
    float section_5_duration = section_5_end_time - section_5_start_time;

    sectionStartTimes.clear();
    sectionStartTimes.push_back(section_1_start_time);
    sectionStartTimes.push_back(section_2_start_time);
    sectionStartTimes.push_back(section_3_start_time);
    sectionStartTimes.push_back(section_4_start_time);
    sectionStartTimes.push_back(section_5_start_time);
    
    int section_1_num_conditions = 9;
    int section_2_num_conditions = 12;
    int section_3_num_conditions = 29;
    int section_4_num_conditions = 13;
    int section_5_num_conditions = 28;

    for(int i = 0 ; i < section_1_num_conditions ; i ++ ) {
        if(i == 0) {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, 1, 0, 0);
//            _c.triggerAtTime = ofRandom(5, 10);
            _c.triggerAtTime = ofRandom(40, 120);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
        } else if(i == 1) {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, 0, 1, 0);
//            _c.triggerAtTime = ofRandom(5, 10);
            _c.triggerAtTime = ofRandom(40, 120);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
            
        } else if(i == 2) {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, 0, 0, 1);
//            _c.triggerAtTime = ofRandom(5, 10);
            _c.triggerAtTime = ofRandom(40, 120);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
            
        } else {
            conditionEvent _c;
            buildConditionEvent(_c, LIKELY, ofRandom(1, 1.25), ofRandom(1, 1.25), ofRandom(1, 1.25));
            _c.triggerAtTime = ofRandom(section_1_start_time + 40, section_1_end_time - 40);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
        }
    }
    buildNormalLimitingEvent(1);
    for(int i = 0 ; i < 6 ; i ++ ) buildNormalLimitingEvent(ofRandom(section_1_start_time + 40, section_1_end_time - 20));
    for(int i = 0 ; i < 3 ; i ++ ) buildHeldTriggerLimitingEvent(ofRandom(section_1_start_time + 40, section_1_start_time + (section_1_duration * 0.6)), ofRandom(8, 16));
    for(int i = 0 ; i < 3 ; i ++ ) {
        buildHeldTriggerLimitingEvent(MEG, ofRandom(section_1_start_time + 40, section_1_start_time + (section_1_duration * 0.9)), ofRandom(10, 18));
        buildHeldTriggerLimitingEvent(JACOB, ofRandom(section_1_start_time + 40, section_1_start_time + (section_1_duration * 0.9)), ofRandom(10, 18));
        buildHeldTriggerLimitingEvent(HALEY, ofRandom(section_1_start_time + 40, section_1_start_time + (section_1_duration * 0.9)), ofRandom(10, 18));
    }
    buildDeleteAllEvent(MEG, ofRandom(section_1_end_time - 20, section_1_end_time));
    buildDeleteAllEvent(JACOB, ofRandom(section_1_end_time - 20, section_1_end_time));
    buildDeleteAllEvent(HALEY, ofRandom(section_1_end_time - 20, section_1_end_time));
    
    float section_2_probA = ofRandom(0.75, 1.25);
    float section_2_probB = ofRandom(0.75, 1.25);
    float section_2_probC = ofRandom(0.75, 1.25);
    
    for(int i = 0 ; i < section_2_num_conditions ; i ++ ) {
        if(i == 0) {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, 1, 0, 0);
            _c.triggerAtTime = ofRandom(section_2_start_time, section_2_start_time + 20);
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
        } else if(i == 1) {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, 0, 1, 0);
            _c.triggerAtTime = ofRandom(section_2_start_time, section_2_start_time + 20);
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
        } else if(i == 2) {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, 0, 0, 1);
            _c.triggerAtTime = ofRandom(section_2_start_time, section_2_start_time + 20);
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
        } else {
            conditionEvent _c;
            buildConditionEvent(_c, LIKELY, section_2_probA, section_2_probB, section_2_probC);
            _c.triggerAtTime = ofRandom(section_2_start_time + 30, section_2_end_time - 60);
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
        }
    }
    buildNormalLimitingEvent(ofRandom(section_2_start_time, section_2_start_time + 20));
    for(int i = 0 ; i < 6 ; i ++ ) buildNormalLimitingEvent(ofRandom(section_2_start_time + 20, section_2_end_time));
    for(int i = 0 ; i < 8 ; i ++ ) {
        buildHeldTriggerLimitingEvent(MEG, ofRandom(section_2_start_time + 20, section_2_end_time - 30), ofRandom(8, 20));
        buildHeldTriggerLimitingEvent(JACOB, ofRandom(section_2_start_time + 20, section_2_end_time - 30), ofRandom(8, 20));
        buildHeldTriggerLimitingEvent(HALEY, ofRandom(section_2_start_time + 20, section_2_end_time - 30), ofRandom(8, 20));
    }
    for(int i = 0 ; i < 4 ; i ++ ) buildHeldTriggerLimitingEvent(ofRandom(section_2_start_time + (section_2_duration * 0.75), section_2_end_time), ofRandom(8, 10));
    
    
    for(int i = 0 ; i < section_3_num_conditions ; i ++ ) {
        if(i == 0) {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, 1, 0, 0);
            _c.triggerAtTime = ofRandom(section_3_start_time + 5, section_3_start_time + 30);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
        } else if(i == 1) {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, 0, 1, 0);
            _c.triggerAtTime = ofRandom(section_3_start_time + 5, section_3_start_time + 30);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
            
        } else if(i == 2) {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, 0, 0, 1);
            _c.triggerAtTime = ofRandom(section_3_start_time + 5, section_3_start_time + 30);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
            
        } else {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, ofRandom(1, 1.25), ofRandom(1, 1.25), ofRandom(1, 1.25));
            _c.triggerAtTime = ofRandom(section_3_start_time + 10, section_3_end_time - 40);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
        }
    }
    buildNormalLimitingEvent(section_3_start_time);
    
    for(int i = 0 ; i < 12 ; i ++ ) {
        buildHeldTriggerLimitingEvent(MEG, ofRandom(section_3_start_time + 20, section_3_end_time - 90), 20);
        buildHeldTriggerLimitingEvent(JACOB, ofRandom(section_3_start_time + 20, section_3_end_time - 90), 20);
        buildHeldTriggerLimitingEvent(HALEY, ofRandom(section_2_start_time + 20, section_3_end_time - 90), 20);
    }
    for(int i = 0 ; i < 3 ; i ++ ) {buildHeldTriggerLimitingEvent(ofRandom(section_3_start_time + (section_3_duration * 0.6), section_3_end_time), 12);}
    
    for(int i = 0 ; i < 3 ; i ++ ) {
        buildDeleteMostActive(MEG, ofRandom(section_3_start_time + (section_3_duration * 0.5), section_3_start_time + (section_3_duration * 0.9)));
        buildDeleteMostActive(JACOB, ofRandom(section_3_start_time + (section_3_duration * 0.5), section_3_start_time + (section_3_duration * 0.9)));
        buildDeleteMostActive(HALEY, ofRandom(section_3_start_time + (section_3_duration * 0.5), section_3_start_time + (section_3_duration * 0.9)));
    }
    
    buildDeleteAllEvent(MEG, ofRandom(section_3_start_time + (section_3_duration * 0.9), section_3_end_time));
    buildDeleteAllEvent(JACOB, ofRandom(section_3_start_time + (section_3_duration * 0.9), section_3_end_time));
    buildDeleteAllEvent(HALEY, ofRandom(section_3_start_time + (section_3_duration * 0.9), section_3_end_time));

    for(int i = 0 ; i < section_4_num_conditions ; i ++ ) {
        if(i == 0) {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, 1, 1, 1);
            _c.triggerAtTime = ofRandom(section_4_start_time, section_4_start_time + 20);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
        } else if(i == 1) {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, 1, 1, 1);
            _c.triggerAtTime = ofRandom(section_4_start_time + 5, section_4_start_time + 30);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
            
        } else if(i == 2) {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, 1, 1, 1);
            _c.triggerAtTime = ofRandom(section_4_start_time + 15, section_4_start_time + 30);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
            
        } else {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, ofRandom(1, 1.25), ofRandom(1, 1.25), ofRandom(1, 1.25));
            _c.triggerAtTime = ofRandom(section_4_start_time + 10, section_4_end_time - 40);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
        }
    }
    
    for(int i = 0 ; i < 4 ; i ++ ) {buildNormalLimitingEvent(ofRandom(section_4_start_time, section_4_end_time));}
    
    for(int i = 0 ; i < 7 ; i ++ ) {
        buildHeldTriggerLimitingEvent(ofRandom(section_4_start_time + 10, section_4_end_time - 10), ofRandom(10, 20));
    }
    
    for(int i = 0 ; i < 2 ; i ++ ) {
        buildRapidTriggerLimitingEvent(MEG, ofRandom(section_4_start_time + 20, section_4_end_time - 20), ofRandom(3, 6.5));
        buildRapidTriggerLimitingEvent(MEG, ofRandom(section_4_start_time + 20, section_4_end_time - 20), ofRandom(3, 6.5));
        buildRapidTriggerLimitingEvent(MEG, ofRandom(section_4_start_time + 20, section_4_end_time - 20), ofRandom(3, 6.5));
    }
    
    buildDeleteAllEvent(MEG, ofRandom(section_4_end_time - 10, section_4_end_time));
    buildDeleteAllEvent(JACOB, ofRandom(section_4_end_time - 10, section_4_end_time));
    buildDeleteAllEvent(HALEY, ofRandom(section_4_end_time - 10, section_4_end_time));
    
    
    for(int i = 0 ; i < section_5_num_conditions ; i ++ ) {
        if(i == 0) {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, 1, 1, 1);
            _c.triggerAtTime = ofRandom(section_5_start_time, section_5_start_time + 20);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
        } else if(i == 1) {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, 1, 1, 1);
            _c.triggerAtTime = ofRandom(section_5_start_time + 5, section_5_start_time + 30);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
            
        } else if(i == 2) {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, 1, 1, 1);
            _c.triggerAtTime = ofRandom(section_5_start_time + 15, section_5_start_time + 30);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
            
        } else {
            conditionEvent _c;
            buildConditionEvent(_c, VERYLIKELY, ofRandom(1, 1.25), ofRandom(1, 1.25), ofRandom(1, 1.25));
            _c.triggerAtTime = ofRandom(section_5_start_time + 10, section_5_end_time - 40);
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = DIE_AFTER_TRIGGER_DURATION;
            (_c.c.abs_del == ABS) ? _c.c.conditionTimerLimit = absActiveLifespan : _c.c.conditionTimerLimit = delActiveLifespan;
            addConditionInOrder(_c);
        }
    }
    
    buildNormalLimitingEvent(ofRandom(section_5_start_time, section_5_start_time + 2));
    
    for(int i = 0 ; i < 2 ; i ++ ) {
        buildHeldTriggerLimitingEvent(MEG, ofRandom(section_5_start_time + 5, section_5_end_time - 20), 10);
        buildHeldTriggerLimitingEvent(JACOB, ofRandom(section_5_start_time + 5, section_5_end_time - 20), 10);
        buildHeldTriggerLimitingEvent(HALEY, ofRandom(section_5_start_time + 5, section_5_end_time - 20), 10);
    }
    
    for(int i = 0 ; i < 4 ; i ++ ) {buildRapidTriggerLimitingEvent(ofRandom(section_5_start_time + 10, section_5_end_time - 35), ofRandom(2, 8));}
    
    
    for(int i = 0 ; i < 3 ; i ++ ) buildDeleteMostActive(makePerformerName(), ofRandom(section_5_start_time + (section_5_duration * 0.25), section_5_start_time + (section_5_duration * 0.6)));
    
    buildDeleteAllEvent(section_5_end_time - ofRandom(5, 15));
    
}

void fc_scoreManager::toggleRun() {
    runScore = !runScore;
}
void fc_scoreManager::update() {
    if(runScore) {
        scoreTimer += ofGetLastFrameTime();
        if(scoreTimer >= nextConditionEvent) {
            if(conditionEvents.size() > 0) {
                if(scoreTimer >= conditionEvents[0].triggerAtTime) {
                    int sourceDeviceIndex;
                    if(conditionEvents[0].sourceDevice == PACK) {
                        sourceDeviceIndex = performersRef -> at(conditionEvents[0].sourceName).getPackIndex();
                    } else {
                        sourceDeviceIndex = performersRef -> at(conditionEvents[0].sourceName).getWristIndex();
                    }
                    performersRef -> at(conditionEvents[0].targetName).makeNewCondition(conditionEvents[0].targetRelayChannel, sourceDeviceIndex, conditionEvents[0].c.x_y_z, conditionEvents[0].c.abs_del, conditionEvents[0].c.MT_LT, conditionEvents[0].c.threshold, conditionEvents[0].c.conditionLifespan, conditionEvents[0].c.conditionTimerLimit);
                    cout << endl << "condition event at " << scoreTimer << endl;
                    conditionEvents.erase(conditionEvents.begin());
                }
                nextConditionEvent = conditionEvents[0].triggerAtTime;
            }
        }
        if(scoreTimer >= nextTriggerLimitingEvent) {
            if(triggerLimitingEvents.size() > 0) {
                if(scoreTimer >= triggerLimitingEvents[0].triggerAtTime) {
                    deviceManagerRef -> setSetDurationDevice(performersRef -> at(triggerLimitingEvents[0].targetName).getPackIndex(), triggerLimitingEvents[0].useSetDuration, triggerLimitingEvents[0].setDuration);
                    deviceManagerRef -> setSetRecoveryDevice(performersRef -> at(triggerLimitingEvents[0].targetName).getPackIndex(), triggerLimitingEvents[0].useSetRecovery, triggerLimitingEvents[0].setRecovery);
                    triggerLimitingEvents.erase(triggerLimitingEvents.begin());
                }
                nextTriggerLimitingEvent = triggerLimitingEvents[0].triggerAtTime;
            }
        }
        if(scoreTimer >= nextDeleteEvent) {
            if(deleteEvents.size() > 0) {
                if(scoreTimer >= deleteEvents[0].triggerAtTime) {
                    if(deleteEvents[0].deleteType == ALL) {
                        performersRef -> at(deleteEvents[0].targetName).deleteAllConditions();
                    } else if(deleteEvents[0].deleteType == MOSTACTIVE) {
                        performersRef -> at(deleteEvents[0].targetName).deleteMostActiveCondition();
                    }
                    deleteEvents.erase(deleteEvents.begin());
                }
                nextDeleteEvent = deleteEvents[0].triggerAtTime;
            }
        }
    }
}
void fc_scoreManager::draw(float _x, float _y, float _w, float _h) {
    ofSetColor(ofColor::white);
    ofNoFill();
    ofDrawRectangle(_x, _y, _w, _h);
    
    ofFill();
    ofDrawRectangle(_x, _y, ofMap(scoreTimer, 0, scoreLength, 0, _w), _h);
    
    ofSetColor(ofColor::red);
    if(sectionStartTimes.size() > 0) {
        for(int i = 0 ; i < sectionStartTimes.size() ; i ++ ) {
            float this_x = ofMap(sectionStartTimes[i], 0, scoreLength, 0, _w);
            ofDrawLine(_x + this_x, _y - 25, _x + this_x, _y + _h);
        }
    }
    
    ofSetColor(ofColor::white);
    font.drawString(ofToString(scoreTimer) + " / " + ofToString(scoreLength), _x + 8, _y + _h + 16);
    
    if(conditionEvents.size() > 0) {
        for(int i = 0 ; i < conditionEvents.size() ; i ++ ) {
            ofSetColor(ofColor::lightBlue);
            float this_x = ofMap(conditionEvents[i].triggerAtTime, 0, scoreLength, 0, _w);
            ofDrawLine(_x + this_x, _y - 25, _x + this_x, _y + _h);
        }
    }
    
    if(triggerLimitingEvents.size() > 0) {
        for(int i = 0 ; i < triggerLimitingEvents.size() ; i ++ ) {
            ofSetColor(ofColor::orange);
            float this_x = ofMap(triggerLimitingEvents[i].triggerAtTime, 0, scoreLength, 0, _w);
            ofDrawLine(_x + this_x, _y - 10, _x + this_x, _y + _h);
        }
    }
    
    if(deleteEvents.size() > 0) {
        for(int i = 0 ; i < deleteEvents.size() ; i ++ ) {
            ofSetColor(ofColor::purple);
            float this_x = ofMap(deleteEvents[i].triggerAtTime, 0, scoreLength, 0, _w);
            ofDrawLine(_x + this_x, _y - 30, _x + this_x, _y + _h);
        }
    }
    
}
void fc_scoreManager::addConditionInOrder(conditionEvent _c) {
    
    cout << "adding condition: " << _c.sourceName << " - " << _c.sourceDevice << " - " << _c.c.threshold << " - " << _c.targetName << endl;
    
    if(conditionEvents.size() == 0) {
        conditionEvents.push_back(_c);
        nextConditionEvent = conditionEvents[0].triggerAtTime;

    } else if(_c.triggerAtTime >= conditionEvents[conditionEvents.size()-1].triggerAtTime) {
        conditionEvents.push_back(_c);
        nextConditionEvent = conditionEvents[0].triggerAtTime;

    } else {
        for(int i = 0 ; i < conditionEvents.size() ; i ++ ) {
            if(_c.triggerAtTime < conditionEvents[i].triggerAtTime) {
                conditionEvents.insert(conditionEvents.begin() + (i), _c);
                nextConditionEvent = conditionEvents[0].triggerAtTime;
                break;
            }
        }
    }
}
void fc_scoreManager::addTriggerLimitingEventInOrder(triggerLimitingEvent _t) {
    if(triggerLimitingEvents.size() == 0) {
        triggerLimitingEvents.push_back(_t);
        nextTriggerLimitingEvent = triggerLimitingEvents[0].triggerAtTime;
    } else if(_t.triggerAtTime >= triggerLimitingEvents[triggerLimitingEvents.size() - 1].triggerAtTime) {
        triggerLimitingEvents.push_back(_t);
        nextTriggerLimitingEvent = triggerLimitingEvents[0].triggerAtTime;
    } else {
        for(int i = 0 ; i < triggerLimitingEvents.size() ; i ++ ) {
            if(_t.triggerAtTime < triggerLimitingEvents[i].triggerAtTime) {
                triggerLimitingEvents.insert(triggerLimitingEvents.begin() + (i), _t);
                nextTriggerLimitingEvent = triggerLimitingEvents[0].triggerAtTime;
                break;
            }
        }
    }
}

void fc_scoreManager::addTriggerLimitingPair(fc_scoreManager::triggerLimitingEvent _t, fc_scoreManager::triggerLimitingEvent _u) {
    if(triggerLimitingEvents.size() == 0) {
        triggerLimitingEvents.push_back(_t);
        triggerLimitingEvents.push_back(_u);
        nextTriggerLimitingEvent = triggerLimitingEvents[0].triggerAtTime;
    } else if(_t.triggerAtTime >= triggerLimitingEvents[triggerLimitingEvents.size() - 1].triggerAtTime) {
        triggerLimitingEvents.push_back(_t);
        triggerLimitingEvents.push_back(_u);
        nextTriggerLimitingEvent = triggerLimitingEvents[0].triggerAtTime;
    } else {
        for(int i = triggerLimitingEvents.size() - 1 ; i >= 0 ; i -- ) {
            if(triggerLimitingEvents[i].triggerAtTime >= _t.triggerAtTime && triggerLimitingEvents[i].triggerAtTime <= _u.triggerAtTime ) {
                triggerLimitingEvents.erase(triggerLimitingEvents.begin() + i);
            }
        }
        
        for(int i = 0 ; i < triggerLimitingEvents.size() ; i ++ ) {
            if(_t.triggerAtTime < triggerLimitingEvents[i].triggerAtTime) {
                triggerLimitingEvents.insert(triggerLimitingEvents.begin() + (i), _u);
                triggerLimitingEvents.insert(triggerLimitingEvents.begin() + (i + 1), _t);
                nextTriggerLimitingEvent = triggerLimitingEvents[0].triggerAtTime;
                break;
            }
        }
    }
}


void fc_scoreManager::addDeleteEventInOrder(deleteEvent _d) {
    if(deleteEvents.size() == 0) {
        deleteEvents.push_back(_d);
        nextDeleteEvent = deleteEvents[0].triggerAtTime;
    } else if(_d.triggerAtTime >= deleteEvents[deleteEvents.size() - 1].triggerAtTime) {
        deleteEvents.push_back(_d);
        nextDeleteEvent = deleteEvents[0].triggerAtTime;
    } else {
        for(int i = 0 ; i < deleteEvents.size() ; i ++ ) {
            if(_d.triggerAtTime < deleteEvents[i].triggerAtTime) {
                deleteEvents.insert(deleteEvents.begin() + i, _d);
                nextDeleteEvent = deleteEvents[0].triggerAtTime;
                break;
            }
        }
    }
}
void fc_scoreManager::setPerformersRef(vector<fc_performer> * _pr) {
    performersRef = _pr;
}
void fc_scoreManager::setDevicesRef(fc_deviceManager *_deviceManager) {
    deviceManagerRef = _deviceManager;
}
int fc_scoreManager::getParamThresholdCenter(DeviceType _wrist_pack, Parameter _abs_del, Parameter _x_y_z, Parameter _mt_lt) {
    if(_abs_del == ABS ) {
        if(_wrist_pack == WRIST) {
            if(_x_y_z == X) {
                if(_mt_lt == MT) {
                    return 3000;
                } else if(_mt_lt == LT) {
                    return 800;
                } else {
                    return -1;
                }
                
            } else if(_x_y_z == Y) {
                if(_mt_lt == MT) {
                    return 3100;
                } else if(_mt_lt == LT) {
                    return 1100;
                } else {
                    return -1;
                }
            } else if(_x_y_z == Z){
                if(_mt_lt == MT) {
                    return 3000;
                } else if(_mt_lt == LT) {
                    return 900;
                } else {
                    return -1;
                }
            } else {
                return -1;
            }
        } else if(_wrist_pack == PACK) {
            if(_x_y_z == X) {
                if(_mt_lt == MT) {
                    return 3000;
                } else if(_mt_lt == LT) {
                    return 900;
                } else {
                    return -1;
                }
                
            } else if(_x_y_z == Y) {
                if(_mt_lt == MT) {
                    return 3200;
                } else if(_mt_lt == LT) {
                    return 1050;
                } else {
                    return -1;
                }
            } else if(_x_y_z == Z){
                if(_mt_lt == MT) {
                    return 3000;
                } else if(_mt_lt == LT) {
                    return 750;
                } else {
                    return -1;
                }
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    } else if(_abs_del == DEL) {
        if(_mt_lt == MT) {
            return 600;
        } else if(_mt_lt == LT) {
            return 50;
        }
    }
}
void fc_scoreManager::setConditionThreshold(conditionEvent &_c) {
    _c.c.threshold = getParamThresholdCenter(_c.sourceDevice, _c.c.abs_del, _c.c.x_y_z, _c.c.MT_LT);
}
void fc_scoreManager::setConditionThreshold(conditionEvent &_c, ThresholdType _thresholdType) {
    int _baseLine = getParamThresholdCenter(_c.sourceDevice,_c.c.abs_del, _c.c.x_y_z, _c.c.MT_LT);
    if(_thresholdType == BASELINE) {
        _c.c.threshold = _baseLine;
    } else if(_thresholdType == UNLIKELY) {
        if(_c.c.MT_LT == MT) {
            _c.c.threshold = getNormal(10, _baseLine + 150);
        } else if(_c.c.MT_LT == LT) {
            _c.c.threshold = getNormal(10, _baseLine - 150);
        }
    } else if(_thresholdType == LIKELY) {
        _c.c.threshold = getNormal(40, _baseLine);
    } else if(_thresholdType == VERYLIKELY) {
        _c.c.threshold = getNormal(100, _baseLine);
    }
}
PerformerName fc_scoreManager::makePerformerName(float _probA, float _probB, float _probC) {
    int _val = ofRandom(_probA + _probB + _probC);
    if(_val < _probA) {
        return MEG;
    } else if(_val < (_probA + _probB)) {
        return JACOB;
    } else {
        return HALEY;
    }
}
PerformerName fc_scoreManager::makePerformerName() {
    int _sel = (int) ofRandom(3);
    if(_sel == 0) {
        return MEG;
    } else if(_sel == 1) {
        return JACOB;
    } else if(_sel == 2) {
        return HALEY;
    }
}
DeviceType fc_scoreManager::makeDeviceType(float _probA, float _probB) {
    float _val = ofRandom(_probA + _probB);
    if(_val < _probA) {
        return WRIST;
    } else {
        return PACK;
    }
}
DeviceType fc_scoreManager::makeDeviceType() {
    int _sel = (int) ofRandom(2);
    if(_sel == 0 ) {
        return WRIST;
    } else if (_sel == 1) {
        return PACK;
    }
}
void fc_scoreManager::makeXYZ_and_MTLT(conditionEvent &_c) {
    if(_c.sourceDevice == WRIST) {
        int _xyz = (int) ofRandom(3);
        int _mtlt = (int) ofRandom(2);
        
        if(_xyz == 0) {
            _c.c.x_y_z = X;
        } else if(_xyz == 1) {
            _c.c.x_y_z = Y;
        } else if(_xyz == 2) {
            _c.c.x_y_z = Z;
        }
        
        if(_mtlt == 0) {
            _c.c.MT_LT = MT;
        } else if(_mtlt == 1) {
            _c.c.MT_LT = LT;
        }
    } else if(_c.sourceDevice == PACK) {
        int _xyz = (int) ofRandom(2);
        int _mtlt = (int) ofRandom(2);
        if(_xyz == 0) {
            _c.c.x_y_z = X;
        } else if(_xyz == 1) {
            _c.c.x_y_z = Y;
        }
        
        if(_mtlt == 0) {
            _c.c.MT_LT = MT;
        } else if(_mtlt == 1) {
            _c.c.MT_LT = LT;
        }
    }
}
void fc_scoreManager::makeSourcePerformerName(conditionEvent &_c) {
    vector < PerformerName > _perfNames;
    _perfNames.push_back(MEG);
    _perfNames.push_back(JACOB);
    _perfNames.push_back(HALEY);
    
    _perfNames.erase(_perfNames.begin() + _c.targetName);
    
    
    if(ofRandom(1) < 0.1) {
        _c.sourceName = _c.targetName;
    } else {
        if(ofRandom(1) < 0.5) {
            _c.sourceName = _perfNames[0];
        } else {
            _c.sourceName = _perfNames[1];
        }
    }
    
}
void fc_scoreManager::buildConditionEvent(conditionEvent &_c, ThresholdType _thresholdType, float _probPerformerA, float _probPerformerB, float _probPerformerC, float _probWrist, float _probPack) {
    _c.targetName = makePerformerName(_probPerformerA, _probPerformerB, _probPerformerC);
    _c.sourceDevice = makeDeviceType(_probWrist, _probPack);
    makeSourcePerformerName(_c);
    makeXYZ_and_MTLT(_c);
    setConditionThreshold(_c, _thresholdType);
    _c.targetRelayChannel = (int) ofRandom(4);
}



void fc_scoreManager::buildConditionEvent(conditionEvent &_c, ThresholdType _thresholdType, float _probPerformerA, float _probPerformerB, float _probPerformerC) {
    _c.targetName = makePerformerName(_probPerformerA, _probPerformerB, _probPerformerC);
    cout << "performer name: " << _c.targetName << endl;
    _c.sourceDevice = makeDeviceType();
    makeSourcePerformerName(_c);
    makeXYZ_and_MTLT(_c);
    if(ofRandom(1) < 0.5) {
        _c.c.abs_del = ABS;
    } else {
        _c.c.abs_del = DEL;
    }
    setConditionThreshold(_c, _thresholdType);
    _c.targetRelayChannel = (int) ofRandom(4);
}
void fc_scoreManager::buildConditionEvent(fc_scoreManager::conditionEvent &_c, ThresholdType _thresholdType) {
    _c.targetName = makePerformerName();
    _c.sourceDevice = makeDeviceType();
    makeSourcePerformerName(_c);
    makeXYZ_and_MTLT(_c);
    setConditionThreshold(_c, _thresholdType);
    _c.targetRelayChannel = (int) ofRandom(4);
}

void fc_scoreManager::buildFollowingConditionEvent(fc_condition &_c) {
    conditionEvent _n;
    _n.c = _c;
    _n.triggerAtTime = scoreTimer + ofRandom(12, 30);
    buildConditionEvent(_n, LIKELY);
    _n.c.triggerType = OPEN;
    addConditionInOrder(_n);
}

void fc_scoreManager::buildNormalLimitingEvent(float _time) {
    triggerLimitingEvent _t;
    _t.triggerAtTime = _time;
    _t.useSetDuration = true;
    _t.setDuration = ofRandom(0.05, 1);
    _t.useSetRecovery = true;
    _t.setRecovery = ofRandom(4, 12);
    
    _t.targetName = MEG;
    addTriggerLimitingEventInOrder(_t);
    
    _t.targetName = JACOB;
    addTriggerLimitingEventInOrder(_t);
    
    _t.targetName = HALEY;
    addTriggerLimitingEventInOrder(_t);
}
void fc_scoreManager::buildNormalLimitingEvent(PerformerName _target, float _time) {
    triggerLimitingEvent _t;
    _t.triggerAtTime = _time;
    _t.useSetDuration = true;
    _t.setDuration = ofRandom(0.05, 1);
    _t.useSetRecovery = true;
    _t.setRecovery = ofRandom(4, 12);
    
    _t.targetName = _target;
    addTriggerLimitingEventInOrder(_t);
}
void fc_scoreManager::buildRapidTriggerLimitingEvent(float _time, float _duration) {
    triggerLimitingEvent _t;
    _t.triggerAtTime = _time;
    _t.useSetDuration = true;
    _t.setDuration = ofRandom(0.05, 0.125);
    _t.useSetRecovery = true;
    _t.setRecovery = ofRandom(0.05, 0.2);
    
    _t.targetName = MEG;
    addTriggerLimitingEventInOrder(_t);
    _t.targetName = JACOB;
    addTriggerLimitingEventInOrder(_t);
    _t.targetName = HALEY;
    addTriggerLimitingEventInOrder(_t);
    
    buildNormalLimitingEvent(_time + _duration);
}
void fc_scoreManager::buildRapidTriggerLimitingEvent(PerformerName _target, float _time, float _duration) {
    triggerLimitingEvent _t;
    _t.triggerAtTime = _time;
    _t.useSetDuration = true;
    _t.setDuration = ofRandom(0.05, 0.125);
    _t.useSetRecovery = true;
    _t.setRecovery = ofRandom(0.05, 0.2);
    
    _t.targetName = _target;
    addTriggerLimitingEventInOrder(_t);
    
    buildNormalLimitingEvent(_target, _time + _duration);
}
void fc_scoreManager::buildHeldTriggerLimitingEvent(float _time, float _duration) {
    triggerLimitingEvent _t;
    _t.triggerAtTime = _time;
    _t.useSetDuration = true;
    _t.setDuration = ofRandom(5, 9);
    _t.useSetRecovery = true;
    _t.setRecovery = ofRandom(5, 12);
    
    _t.targetName = MEG;
    addTriggerLimitingEventInOrder(_t);
    _t.targetName = JACOB;
    addTriggerLimitingEventInOrder(_t);
    _t.targetName = HALEY;
    addTriggerLimitingEventInOrder(_t);
    
    buildNormalLimitingEvent(_time + _duration);
}
void fc_scoreManager::buildHeldTriggerLimitingEvent(PerformerName _target, float _time, float _duration) {
    triggerLimitingEvent _t;
    _t.triggerAtTime = _time;
    _t.useSetDuration = true;
    _t.setDuration = ofRandom(3, 6);
    _t.useSetRecovery = true;
    _t.setRecovery = ofRandom(5, 12);
    
    _t.targetName = _target;
    addTriggerLimitingEventInOrder(_t);
    
    buildNormalLimitingEvent(_target, _time + _duration);
}
void fc_scoreManager::buildDeleteAllEvent(float _time) {
    deleteEvent _d;
    _d.triggerAtTime = _time;
    _d.deleteType = ALL;
    
    _d.targetName = MEG;
    addDeleteEventInOrder(_d);
    _d.targetName = JACOB;
    addDeleteEventInOrder(_d);
    _d.targetName = HALEY;
    addDeleteEventInOrder(_d);
}
void fc_scoreManager::buildDeleteAllEvent(PerformerName _target, float _time) {
    deleteEvent _d;
    _d.triggerAtTime = _time;
    _d.deleteType = ALL;
    _d.targetName = _target;
    addDeleteEventInOrder(_d);
}
void fc_scoreManager::buildDeleteMostActive(float _time) {
    deleteEvent _d;
    _d.triggerAtTime = _time;
    _d.deleteType = MOSTACTIVE;
    
    _d.targetName = MEG;
    addDeleteEventInOrder(_d);
    _d.targetName = JACOB;
    addDeleteEventInOrder(_d);
    _d.targetName = HALEY;
    addDeleteEventInOrder(_d);
}
void fc_scoreManager::buildDeleteMostActive(PerformerName _target, float _time) {
    deleteEvent _d;
    _d.triggerAtTime = _time;
    _d.deleteType = MOSTACTIVE;
    _d.targetName = _target;
    addDeleteEventInOrder(_d);
}

void fc_scoreManager::goToTime(float _time) {
    scoreTimer = _time;
    
    if(conditionEvents.size() > 0) {
        for(int i = conditionEvents.size() - 1 ; i >= 0 ; i -- ) if(conditionEvents[i].triggerAtTime < _time) conditionEvents.erase(conditionEvents.begin() + i);
    }
    if(triggerLimitingEvents.size() > 0) {
        for(int i = triggerLimitingEvents.size() - 1 ; i >= 0 ; i -- ) if(triggerLimitingEvents[i].triggerAtTime < _time) triggerLimitingEvents.erase(triggerLimitingEvents.begin() + i);
    }
    if(deleteEvents.size() > 0) {
        for(int i = deleteEvents.size() - 1 ; i >= 0 ; i -- ) {
            if(deleteEvents[i].triggerAtTime < _time) deleteEvents.erase(deleteEvents.begin() + i);
        }
    }
    if(conditionEvents.size() > 0) nextConditionEvent = conditionEvents[0].triggerAtTime;
    if(triggerLimitingEvents.size() > 0) nextTriggerLimitingEvent = triggerLimitingEvents[0].triggerAtTime;
    if(deleteEvents.size() > 0) nextDeleteEvent = deleteEvents[0].triggerAtTime;
}

void fc_scoreManager::goToSection1() {
    goToTime(sectionStartTimes[0]);
}

void fc_scoreManager::goToSection2() {
    goToTime(sectionStartTimes[1]);
}

void fc_scoreManager::goToSection3() {
    goToTime(sectionStartTimes[2]);
}

void fc_scoreManager::goToSection4() {
    goToTime(sectionStartTimes[3]);
}

void fc_scoreManager::goToSection5() {
    goToTime(sectionStartTimes[4]);
}