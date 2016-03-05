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
    conditionEvents.clear();
    triggerLimitingEvents.clear();
    deleteEvents.clear();
    
    //section 1
    float section_1_start_time = 0;
    float section_1_end_time = (scoreLength * 0.2) + ofRandom(-30, 30);
    cout << "section 1:" << endl;
    cout << "--------- start: " << section_1_start_time << endl;
    cout << "---------   end: " << section_1_end_time << endl;
    
    float section_2_start_time = section_1_end_time;
    float section_2_end_time = section_2_start_time + (scoreLength * 0.1714) + ofRandom(-30, 30);
    cout << endl;
    cout << "section 2:" << endl;
    cout << "--------- start: " << section_2_start_time << endl;
    cout << "---------   end: " << section_2_end_time << endl;
    
    float section_3_start_time = section_2_end_time;
    float section_3_end_time = section_3_start_time + (scoreLength * 0.314) + ofRandom(-30, 30);
    cout << endl;
    cout << "section 3: " << endl;
    cout << "--------- start: " << section_3_start_time << endl;
    cout << "---------   end: " << section_3_end_time << endl;
    
    float section_4_start_time = section_3_end_time;
    float section_4_end_time = section_4_start_time + (scoreLength * 0.13333) + ofRandom(-15, 15);
    cout << endl;
    cout << "section 4: " << endl;
    cout << "--------- start: " << section_4_start_time << endl;
    cout << "---------   end: " << section_4_end_time << endl;
    
    float section_5_start_time = section_4_end_time;
    float section_5_end_time = scoreLength + ofRandom(-30, 30);
    cout << endl;
    cout << "section 5: " << endl;
    cout << "--------- start: " << section_5_start_time << endl;
    cout << "---------   end: " << section_5_end_time << endl;
    cout << endl;
    
    sectionStartTimes.clear();
    sectionStartTimes.push_back(section_1_start_time);
    sectionStartTimes.push_back(section_2_start_time);
    sectionStartTimes.push_back(section_3_start_time);
    sectionStartTimes.push_back(section_4_start_time);
    sectionStartTimes.push_back(section_5_start_time);
    
    int section_1_num_conditions = 40;
    int section_2_num_conditions = 11;
    int section_3_num_conditions = 29;
    int section_4_num_conditions = 13;
    int section_5_num_conditions = 28;
    
    vector < PerformerName > section_1_condition_targets;
    vector < PerformerName > section_2_condition_targets;
    vector < PerformerName > section_3_condition_targets;
    vector < PerformerName > section_4_condition_targets;
    vector < PerformerName > section_5_condition_targets;
    
    
    float probJacob = ofRandom(0.075, 0.2);
    float probMeg = probJacob + ofRandom(0.4, 0.5);
    
    for(int i = 0 ; i < section_1_num_conditions ; i ++ ) {
        conditionEvent _c;
        cout << "CONDITION:" << endl;
//        cout << "------ time: " << section_1_start_time, section_1_end_time) << endl;
        float thisCondition = ofRandom(1);
        _c.triggerAtTime = ofRandom(section_1_start_time, section_1_end_time - ((section_1_end_time - section_1_start_time) * 0.1));
        
        if(thisCondition <= probJacob) {
            cout << "------ target: JACOB" << endl;
            _c.targetName = JACOB;
        } else if(thisCondition <= probMeg) {
            cout << "------ target: MEG" << endl;
            _c.targetName = MEG;
        } else {
            cout << "------ target: HALEY" << endl;
            _c.targetName = HALEY;
        }
        int _x_y_z = (int) ofRandom(3);
        if(_x_y_z == 0) {
            cout << ", X";
            _c.c.x_y_z = X;
        } else if (_x_y_z == 1) {
            cout << ", Y";
            _c.c.x_y_z = Y;
        } else if (_x_y_z == 2) {
            cout << ", Z";
            _c.c.x_y_z = Z;
        }
        float _abs_del = ofRandom(1);
        if(_abs_del <= 0.9) {
            cout << ", ABS";
            _c.c.abs_del = ABS;
            if((int)ofRandom(2) == 0) {
                _c.c.MT_LT = MT;
                cout << " > ";
            } else {
                _c.c.MT_LT = LT;
                cout << " < ";
            }
        } else {
            cout << ", DEL";
            _c.c.abs_del = DEL;
            _c.c.MT_LT = MT;
            cout << " > ";
        }
        if(ofRandom(1) <= 0.05) {
            _c.sourceName = _c.targetName;
        } else {
            vector < PerformerName > sourceName;
            sourceName.clear();
            sourceName.push_back(MEG);
            sourceName.push_back(JACOB);
            sourceName.push_back(HALEY);
            sourceName.erase(sourceName.begin() + _c.targetName);
            _c.sourceName = sourceName[(int) ofRandom(2)];
        }
        if((int) ofRandom(2) == 0) {
            _c.sourceDevice = WRIST;
        } else {
            _c.sourceDevice = PACK;
        }
        _c.c.triggerType = OPEN;
        _c.c.conditionLifespan = INFINITE;
        if(_c.c.abs_del == ABS) {
            if(_c.c.MT_LT == MT) {
                _c.c.threshold = getNormal(100, 3200);
                cout << _c.c.threshold << endl;
            } else {
                _c.c.threshold = getNormal(100, 800);
                cout << _c.c.threshold << endl;
            }
        } else {
            _c.c.threshold = getNormal(100, 800);
            cout << _c.c.threshold << endl;
        }
        
        _c.targetRelayChannel = (int) ofRandom(4);
        
        addConditionInOrder(_c);
    }
    cout << endl << endl;
    for(int i = 0 ; i < conditionEvents.size() ; i ++ ) {
        cout << conditionEvents[i].triggerAtTime << endl;
    }
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
                    
                    if(conditionEvents[0].c.sourceDevice == PACK) {
                        sourceDeviceIndex = performersRef -> at(conditionEvents[0].sourceName).getPackIndex();
                    } else {
                        sourceDeviceIndex = performersRef -> at(conditionEvents[0].sourceName).getWristIndex();
                    }
                    
                    performersRef -> at(conditionEvents[0].targetName).makeNewCondition(conditionEvents[0].targetRelayChannel, sourceDeviceIndex, conditionEvents[0].c.x_y_z, conditionEvents[0].c.abs_del, conditionEvents[0].c.MT_LT, conditionEvents[0].c.threshold, conditionEvents[0].c.conditionLifespan, 0);
                    cout << endl << "condition event at " << scoreTimer << endl;
                    conditionEvents.erase(conditionEvents.begin());
                }
                
                nextConditionEvent = conditionEvents[0].triggerAtTime;
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
            ofSetColor(ofColor::blue);
            float this_x = ofMap(conditionEvents[i].triggerAtTime, 0, scoreLength, 0, _w);
            ofDrawLine(_x + this_x, _y - 25, _x + this_x, _y + _h);
        }
    }
    
    
}

void fc_scoreManager::addConditionInOrder(conditionEvent _c) {
    if(conditionEvents.size() == 0) {
        conditionEvents.push_back(_c);
    } else if(_c.triggerAtTime > conditionEvents[conditionEvents.size()-1].triggerAtTime) {
        conditionEvents.push_back(_c);
    } else {
        for(int i = 0 ; i < conditionEvents.size() ; i ++ ) {
            if(_c.triggerAtTime < conditionEvents[i].triggerAtTime) {
                conditionEvents.insert(conditionEvents.begin() + (i), _c);
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

void fc_scoreManager::setPerformersRef(vector<fc_performer> * _pr) {
    performersRef = _pr;
}