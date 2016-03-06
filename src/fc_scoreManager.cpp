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
    
    scoreLength = scoreLength + ofRandom(-240, 120);
    
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
    float section_5_end_time = scoreLength;
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
    
    int section_1_num_conditions = ofRandom(9, 11);
    int section_2_num_conditions = ofRandom(11, 14);
    int section_3_num_conditions = 29;
    int section_4_num_conditions = 13;
    int section_5_num_conditions = 28;

    
    float probJacob = ofRandom(0.075, 0.2);
    float probMeg = probJacob + ((1 - probJacob) / 2);
    
    //make score conditions
    for(int i = 0 ; i < section_1_num_conditions ; i ++ ) {
        conditionEvent _c;
        cout << "CONDITION:" << endl;
        float thisCondition = ofRandom(1);
        _c.triggerAtTime = ofRandom(section_1_start_time, section_1_end_time - ((section_1_end_time - section_1_start_time) * 0.1));
        
        if(i == 0) {
            _c.targetName = MEG;
            cout << "------ target: MEG";
        } else if(i == 1) {
            _c.targetName = JACOB;
            cout << "------ target: JACOB";
        } else if(i == 2) {
            _c.targetName = HALEY;
            cout << "------ target: HALEY";
        } else if(thisCondition <= probJacob) {
            cout << "------ target: JACOB";
            _c.targetName = JACOB;
        } else if(thisCondition <= probMeg) {
            cout << "------ target: MEG";
            _c.targetName = MEG;
        } else {
            cout << "------ target: HALEY";
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
        if(ofRandom(1) <= 0.5) {
            _c.sourceDevice = WRIST;
        } else {
            _c.sourceDevice = PACK;
        }
        _c.c.triggerType = OPEN;
        _c.c.conditionLifespan = INFINITE;
        if(_c.c.abs_del == ABS) {
            if(_c.c.MT_LT == MT) {
                _c.c.threshold = getNormal(180, 2800);
                cout << _c.c.threshold << endl;
            } else {
                _c.c.threshold = getNormal(180, 1200);
                cout << _c.c.threshold << endl;
            }
        } else {
            _c.c.threshold = getNormal(100, 700);
            cout << _c.c.threshold << endl;
        }
        
        _c.targetRelayChannel = (int) ofRandom(4);
        
        addConditionInOrder(_c);
    }
    //make score trigger limits
    for(int a = 0 ; a < 3 ; a ++ ) {
        
        for(int i = 0 ; i < 12 ; i ++ ) {
            triggerLimitingEvent tle;
            tle.triggerAtTime = ofRandom(section_1_start_time, section_1_end_time - ((section_1_end_time - section_1_start_time) * 0.1));
            if(a == 0) {
                tle.targetName = MEG;
            } else if(a == 1) {
                tle.targetName = JACOB;
            } else if(a == 2) {
                tle.targetName = HALEY;
            }
            
            tle.useSetDuration = true;
            tle.setDuration = ofRandom(0.05, 1.0);
            tle.useSetRecovery = true;
            if(tle.setDuration >= 1) {
                tle.setRecovery = ofRandom(3, 12.5);
            } else {
                tle.setRecovery = ofRandom(tle.setDuration, 8);
            }
            addTriggerLimitingEventInOrder(tle);
        }
        
        int numberLongHeldSections = ofRandom(3, 6);
        
        for(int i = 0 ; i < numberLongHeldSections ; i ++ ) {
            triggerLimitingEvent tle;
            
            if(a == 0) {
                tle.targetName = MEG;
            } else if(a == 1) {
                tle.targetName = JACOB;
            } else if(a == 2) {
                tle.targetName = HALEY;
            }
            
            tle.triggerAtTime = ofRandom(section_1_start_time, section_1_end_time - ((section_1_end_time - section_1_start_time) * 0.1));
            tle.useSetDuration = true;
            tle.setDuration = ofRandom(3, 4.5);
            tle.useSetRecovery = true;
            tle.setRecovery = ofRandom(tle.setDuration, tle.setDuration + 4);
            
            addTriggerLimitingEventInOrder(tle);
            
            triggerLimitingEvent tle2;
            
            tle2.targetName = tle.targetName;
            
            tle2.triggerAtTime = tle.triggerAtTime + ofRandom(tle.setDuration, (tle.setDuration + tle.setRecovery) * 3);
            tle2.useSetDuration = true;
            tle2.setDuration = ofRandom(0.05, 2.0);
            tle2.useSetRecovery = true;
            if(tle2.setDuration >= 1) {
                tle2.setRecovery = ofRandom(5, 12.5);
            } else {
                tle2.setRecovery = ofRandom(tle2.setDuration, 8);
            }
            addTriggerLimitingEventInOrder(tle2);
        }
    }
    //make score deletions
    for(int i = 0 ; i < 3 ; i ++ ) {
        deleteEvent _de;
        _de.triggerAtTime = ofRandom(section_1_end_time -(section_1_end_time - section_1_start_time) * 0.1, section_1_end_time);
        if(i == 0) {
            _de.targetName = MEG;
        } else if(i == 1) {
            _de.targetName = JACOB;
        } else if(i == 2) {
            _de.targetName = HALEY;
        }
        _de.deleteType = ALL;
        addDeleteEventInOrder(_de);
    }
    
    float section_2_duration = section_2_end_time - section_2_start_time;
    for(int i = 0 ; i < section_2_num_conditions ; i ++ ) {
        conditionEvent _c;
        float thisConditionTimeRange = section_2_start_time + (section_2_duration / (section_2_num_conditions + 1)) * i;
        _c.triggerAtTime = ofRandom(section_2_start_time, thisConditionTimeRange);
        int thisConditionTarget = ofRandom(3);
        
        if(thisConditionTarget == 0) {
            _c.targetName = MEG;
        } else if(thisConditionTarget == 1) {
            _c.targetName = JACOB;
        } else if(thisConditionTarget == 2) {
            _c.targetName = HALEY;
        }
        
        float thisConditionSource = ofRandom(1);
        
        if(thisConditionSource < 0.1) {
            _c.sourceName = _c.targetName;
        } else {
            vector < PerformerName > sourceName;
            sourceName.clear();
            sourceName.push_back(MEG);
            sourceName.push_back(JACOB);
            sourceName.push_back(HALEY);
            sourceName.erase(sourceName.begin() + _c.targetName);
            _c.sourceName = sourceName[(int)ofRandom(2)];
        }
        
        if(ofRandom(1) < 0.5) {
            _c.sourceDevice = WRIST;
        } else {
            _c.sourceDevice = PACK;
        }
        
        _c.c.triggerType = OPEN;
        _c.c.conditionLifespan = INFINITE;
        
        int thisConditionXYZ = ofRandom(3);
        if(thisConditionXYZ == 0) {
            _c.c.x_y_z = X;
        } else if(thisConditionXYZ == 1) {
            _c.c.x_y_z = Y;
        } else if(thisConditionXYZ == 2) {
            _c.c.x_y_z = Z;
        }
        if(ofRandom(1) < 0.9) {
            _c.c.abs_del = ABS;
            if(ofRandom(1) < 0.5) {
                _c.c.MT_LT = MT;
            } else {
                _c.c.MT_LT = LT;
            }
        } else {
            _c.c.abs_del = DEL;
            _c.c.MT_LT = MT;
        }
        if(_c.c.abs_del == ABS) {
            if(_c.c.MT_LT == MT) {
                _c.c.threshold = getNormal(180, 2800);
            } else {
                _c.c.threshold = getNormal(180, 1200);
            }
        } else {
            _c.c.threshold = getNormal(100, 675);
        }
        _c.targetRelayChannel = ofRandom(4);
        addConditionInOrder(_c);
    }
    
    for(int i = 0 ; i < 20 ; i ++ ) {
        triggerLimitingEvent tle;
        tle.triggerAtTime = ofRandom(section_2_start_time, section_2_end_time - (section_2_duration * 0.2));
        tle.useSetDuration = true;
        tle.setDuration = ofRandom(0.05, 1.25);
        tle.useSetRecovery = true;
        if(tle.setDuration > 0.8) {
            tle.setRecovery = ofRandom(0.8, 3);
        } else {
            tle.setRecovery = ofRandom(0.1, 2);
        }
        tle.targetName = MEG;
        addTriggerLimitingEventInOrder(tle);
        tle.targetName = JACOB;
        addTriggerLimitingEventInOrder(tle);
        tle.targetName = HALEY;
        addTriggerLimitingEventInOrder(tle);
    }
    
    int section_2_long_held_sections = ofRandom(2, 5);
    for(int i = 0 ; i < section_2_long_held_sections ; i ++ ) {
        triggerLimitingEvent tle;
        tle.triggerAtTime = ofRandom(section_2_start_time, section_2_end_time - (section_2_duration * 0.1));
        tle.useSetDuration = true;
        tle.setDuration = ofRandom(3, 8);
        tle.useSetRecovery = true;
        tle.setRecovery = ofRandom(tle.setDuration, tle.setDuration + 4);
        tle.targetName = MEG;
        addTriggerLimitingEventInOrder(tle);
        tle.targetName = JACOB;
        addTriggerLimitingEventInOrder(tle);
        tle.targetName = HALEY;
        addTriggerLimitingEventInOrder(tle);
        
        triggerLimitingEvent tle2;
        tle2.triggerAtTime = tle.triggerAtTime + ofRandom(tle.setDuration, (tle.setDuration + tle.setRecovery) * 3);
        tle2.useSetDuration = true;
        tle2.setDuration = ofRandom(0.05, 0.8);
        tle2.useSetRecovery = true;
        if(tle2.setDuration >= 0.5) {
            tle2.setRecovery = ofRandom(1, 3);
        } else {
            tle2.setRecovery = ofRandom(0.1, 3);
        }
        tle2.targetName = MEG;
        addTriggerLimitingEventInOrder(tle2);
        tle2.targetName = JACOB;
        addTriggerLimitingEventInOrder(tle2);
        tle2.targetName = HALEY;
        addTriggerLimitingEventInOrder(tle2);
    }
    
    for(int i = 0 ; i < 3 ; i ++ ) {
        deleteEvent _de;
        if( i == 0 ) {
            _de.targetName = MEG;
        } else if( i == 1 ) {
            _de.targetName = JACOB;
        } else if( i == 2 ) {
            _de.targetName = HALEY;
        }
        _de.deleteType = ALL;
        _de.triggerAtTime = ofRandom(section_2_start_time + (section_2_duration * 0.95), section_2_end_time);
        addDeleteEventInOrder(_de);
    }
    
    
    float section_3_duration = section_3_end_time - section_3_start_time;
    
    for(int i = 0 ; i < section_3_num_conditions ; i ++ ) {
        conditionEvent _c;
        if(i < 6) {
            _c.triggerAtTime = ofRandom(section_3_start_time, section_3_start_time + (section_3_duration * 0.1));
        } else {
            _c.triggerAtTime = ofRandom(section_3_start_time, section_3_end_time);
        }
        int thisConditionTarget = ofRandom(3);
        
        if(thisConditionTarget == 0) {
            _c.targetName = MEG;
        } else if(thisConditionTarget == 1) {
            _c.targetName = JACOB;
        } else if(thisConditionTarget == 2) {
            _c.targetName = HALEY;
        }
        
        float thisConditionSource = ofRandom(1);
        
        if(thisConditionSource <= 0.05) {
            _c.sourceName = _c.targetName;
        } else {
            vector < PerformerName > sourceName;
            sourceName.clear();
            sourceName.push_back(MEG);
            sourceName.push_back(JACOB);
            sourceName.push_back(HALEY);
            sourceName.erase(sourceName.begin() + _c.targetName);
            _c.sourceName = sourceName[(int)ofRandom(2)];
        }
        
        if(ofRandom(1) < 0.5) {
            _c.sourceDevice = WRIST;
        } else {
            _c.sourceDevice = PACK;
        }
        
        _c.c.triggerType = OPEN;
        _c.c.conditionLifespan = INFINITE;
        
        int thisConditionXYZ = ofRandom(3);
        if(thisConditionXYZ == 0) {
            _c.c.x_y_z = X;
        } else if(thisConditionXYZ == 1) {
            _c.c.x_y_z = Y;
        } else if(thisConditionXYZ == 2) {
            _c.c.x_y_z = Z;
        }
        if(ofRandom(1) < 0.65) {
            _c.c.abs_del = ABS;
            if(ofRandom(1) < 0.5) {
                _c.c.MT_LT = MT;
            } else {
                _c.c.MT_LT = LT;
            }
        } else {
            _c.c.abs_del = DEL;
            _c.c.MT_LT = MT;
        }
        if(_c.c.abs_del == ABS) {
            if(_c.c.MT_LT == MT) {
                _c.c.threshold = getNormal(180, 3000);
            } else {
                _c.c.threshold = getNormal(180, 1000);
            }
        } else {
            _c.c.threshold = getNormal(100, 750);
        }
        _c.targetRelayChannel = ofRandom(4);
        addConditionInOrder(_c);
    }
    
    for(int i = 0 ; i < 3 ; i ++ ) {
        for(int j = 0 ; j < 10 ; j ++ ) {
            triggerLimitingEvent tle;
            if(i == 0) {
                tle.targetName = MEG;
            } else if(i == 1) {
                tle.targetName = JACOB;
            } else if(i == 2) {
                tle.targetName = HALEY;
            }
            tle.triggerAtTime = ofRandom(section_3_start_time, section_3_end_time);
            tle.useSetDuration = true;
            tle.setDuration = ofRandom(0.2, 1.4);
            tle.useSetRecovery = true;
            tle.setRecovery = ofRandom(tle.setDuration, tle.setDuration * 3);
            addTriggerLimitingEventInOrder(tle);
        }
    }
    
    int section_3_long_held_sections = ofRandom(10, 18);
    for(int i = 0 ; i < section_3_long_held_sections ; i ++ ) {
        triggerLimitingEvent tle;
        int thisTarget = ofRandom(3);
        if(thisTarget == 0) {
            tle.targetName = MEG;
        } else if(thisTarget == 1) {
            tle.targetName = JACOB;
        } else if(thisTarget == 2) {
            tle.targetName = HALEY;
        }
        tle.triggerAtTime = ofRandom(section_3_start_time, section_3_end_time);
        tle.useSetDuration = true;
        tle.setDuration = ofRandom(3, 6);
        tle.useSetRecovery = true;
        tle.setRecovery = ofRandom(tle.setDuration / 2, tle.setDuration * 4);
        
        addTriggerLimitingEventInOrder(tle);
        
        triggerLimitingEvent tle2;
        tle2.targetName = tle.targetName;
        tle2.triggerAtTime = tle.triggerAtTime + ofRandom((tle.setDuration + tle.setRecovery) * 0.9, (tle.setDuration + tle.setRecovery) * 2.5);
        tle2.useSetDuration = true;
        tle2.setDuration = ofRandom(0.2, 0.7);
        tle2.useSetRecovery = true;
        tle2.setRecovery = ofRandom(tle2.setDuration * 4, tle2.setDuration * 8);
        addTriggerLimitingEventInOrder(tle2);
    }
    
    int section_3_short_rapid_sections = ofRandom(1, 4);
    for(int i = 0 ; i < section_3_short_rapid_sections ; i ++ ) {
        triggerLimitingEvent tle;
        int thisTarget = ofRandom(3);
        if(thisTarget == 0) {
            tle.targetName = MEG;
        } else if(thisTarget == 1) {
            tle.targetName = JACOB;
        } else if(thisTarget == 2) {
            tle.targetName = HALEY;
        }
        tle.triggerAtTime = ofRandom(section_3_start_time, section_3_end_time);
        tle.useSetDuration = true;
        tle.setDuration = ofRandom(0.05, 0.2);
        tle.useSetRecovery = true;
        tle.setRecovery = ofRandom(0.05, 0.2);
        
        addTriggerLimitingEventInOrder(tle);
        
        triggerLimitingEvent tle2;
        tle2.targetName = tle.targetName;
        tle2.triggerAtTime = tle.triggerAtTime + ofRandom(1.1, 4);
        tle2.useSetDuration = true;
        tle2.setDuration = ofRandom(0.2, 1.4);
        tle2.useSetRecovery = true;
        tle2.setRecovery = ofRandom(tle.setDuration, tle.setDuration * 3);

        addTriggerLimitingEventInOrder(tle2);
    }
    
    for(int i = 0 ; i < 3 ; i ++ ) {
        
        int numberDeletions = ofRandom(2, 7);
        
        for(int j = 0 ; j < numberDeletions ; j ++ ) {
            deleteEvent _de;
            if(i == 0 ) {
                _de.targetName = MEG;
            } else if(i == 1) {
                _de.targetName = JACOB;
            } else if(i == 2) {
                _de.targetName = HALEY;
            }
            
            _de.deleteType = MOSTACTIVE;
            _de.triggerAtTime = ofRandom(section_3_start_time + (section_3_duration * 0.2),
                                         section_3_end_time);
            addDeleteEventInOrder(_de);
        }
    }
    
    for(int i = 0 ; i < 3 ; i ++ ) {
        deleteEvent _de;
        if(i == 0 ) {
            _de.targetName = MEG;
        } else if(i == 1) {
            _de.targetName = JACOB;
        } else if(i == 2) {
            _de.targetName = HALEY;
        }
        _de.deleteType = ALL;
        _de.triggerAtTime = ofRandom(section_3_end_time - (section_3_duration * 0.05),
                                     section_3_end_time);
        addDeleteEventInOrder(_de);
    }
    
    
    //section 4 generation
    float section_4_duration = section_4_end_time - section_4_start_time;
    for(int i = 0 ; i < 3 ; i ++ ) {
        for(int j = 0 ; j < 4 ; j ++ ) {
            conditionEvent _c;
            if(i == 0) {
                _c.targetName = MEG;
            } else if(i == 1) {
                _c.targetName = JACOB;
            } else if(i == 2) {
                _c.targetName = HALEY;
            }
            
            if(j == 0) {
                _c.triggerAtTime = ofRandom(section_4_start_time, section_4_start_time + (section_4_duration * 0.15));
            } else {
                _c.triggerAtTime = ofRandom(section_4_start_time, section_4_end_time);
            }
            
            float thisConditionSource = ofRandom(1);
            
            if(thisConditionSource <= 0.15) {
                _c.sourceName = _c.targetName;
            } else {
                vector < PerformerName > sourceName;
                sourceName.clear();
                sourceName.push_back(MEG);
                sourceName.push_back(JACOB);
                sourceName.push_back(HALEY);
                sourceName.erase(sourceName.begin() + _c.targetName);
                _c.sourceName = sourceName[(int)ofRandom(2)];
            }
            
            if(ofRandom(1) < 0.5) {
                _c.sourceDevice = WRIST;
            } else {
                _c.sourceDevice = PACK;
            }
            
            _c.c.triggerType = OPEN;
            _c.c.conditionLifespan = INFINITE;
            
            int thisConditionXYZ = ofRandom(3);
            if(thisConditionXYZ == 0) {
                _c.c.x_y_z = X;
            } else if(thisConditionXYZ == 1) {
                _c.c.x_y_z = Y;
            } else if(thisConditionXYZ == 2) {
                _c.c.x_y_z = Z;
            }
            if(ofRandom(1) < 0.8) {
                _c.c.abs_del = ABS;
                if(ofRandom(1) < 0.5) {
                    _c.c.MT_LT = MT;
                } else {
                    _c.c.MT_LT = LT;
                }
            } else {
                _c.c.abs_del = DEL;
                _c.c.MT_LT = MT;
            }
            if(_c.c.abs_del == ABS) {
                if(_c.c.MT_LT == MT) {
                    _c.c.threshold = getNormal(180, 3000);
                } else {
                    _c.c.threshold = getNormal(180, 1000);
                }
            } else {
                _c.c.threshold = getNormal(100, 750);
            }
            _c.targetRelayChannel = ofRandom(4);
            addConditionInOrder(_c);
        }
    }
    
    int section_4_number_held_sections = ofRandom(8, 12);
    for(int i = 0 ; i < section_4_num_conditions ; i ++ ) {
        triggerLimitingEvent tle;
        
        tle.triggerAtTime = ofRandom(section_4_start_time, section_4_end_time);
        tle.useSetDuration = true;
        tle.setDuration = ofRandom(4, 9);
        tle.useSetRecovery = true;
        tle.setRecovery = ofRandom(6, 12);
        
        tle.targetName = MEG;
        addTriggerLimitingEventInOrder(tle);
        tle.targetName = JACOB;
        addTriggerLimitingEventInOrder(tle);
        tle.targetName = HALEY;
        addTriggerLimitingEventInOrder(tle);
        
        triggerLimitingEvent tle2;
        tle2.triggerAtTime = tle.triggerAtTime + ofRandom((tle.setDuration + tle.setRecovery) * 1.5,
                                                          (tle.setDuration + tle.setRecovery) * 2);
        tle2.useSetDuration = true;
        tle2.setDuration = ofRandom(0.05, 0.5);
        tle2.useSetRecovery = true;
        tle2.setRecovery = ofRandom(3, 8);
        tle2.targetName = MEG;
        addTriggerLimitingEventInOrder(tle2);
        
        tle2.useSetDuration = true;
        tle2.setDuration = ofRandom(0.05, 0.5);
        tle2.useSetRecovery = true;
        tle2.setRecovery = ofRandom(3, 8);
        tle2.targetName = JACOB;
        addTriggerLimitingEventInOrder(tle2);
        
        tle2.useSetDuration = true;
        tle2.setDuration = ofRandom(0.05, 0.5);
        tle2.useSetRecovery = true;
        tle2.setRecovery = ofRandom(3, 8);
        tle2.targetName = HALEY;
        addTriggerLimitingEventInOrder(tle2);
    }
    
    int section_4_number_rapid_sections = ofRandom(1, 4);
    for(int i = 0 ; i < section_4_number_rapid_sections ; i ++ ) {
        triggerLimitingEvent tle;
        
        tle.triggerAtTime = ofRandom(section_4_start_time, section_4_end_time);
        tle.useSetDuration = true;
        tle.setDuration = ofRandom(0.05, 0.1);
        tle.useSetRecovery = true;
        tle.setRecovery = ofRandom(tle.setDuration, tle.setDuration * 2);
        
        tle.targetName = MEG;
        addTriggerLimitingEventInOrder(tle);
        tle.targetName = JACOB;
        addTriggerLimitingEventInOrder(tle);
        tle.targetName = HALEY;
        addTriggerLimitingEventInOrder(tle);
        
        triggerLimitingEvent tleb;
        
        tleb.triggerAtTime = ofRandom(section_4_start_time, section_4_end_time);
        tleb.useSetDuration = true;
        tleb.setDuration = ofRandom(0.05, 0.15);
        tleb.useSetRecovery = true;
        tleb.setRecovery = ofRandom(tleb.setDuration, tleb.setDuration * 2);
        
        tleb.targetName = MEG;
        addTriggerLimitingEventInOrder(tleb);
        tleb.targetName = JACOB;
        addTriggerLimitingEventInOrder(tleb);
        tleb.targetName = HALEY;
        addTriggerLimitingEventInOrder(tleb);
        
        triggerLimitingEvent tle2;
        tle2.triggerAtTime = tle.triggerAtTime + ofRandom(3, 6);
        tle2.useSetDuration = true;
        tle2.setDuration = ofRandom(0.05, 0.5);
        tle2.useSetRecovery = true;
        tle2.setRecovery = ofRandom(3, 8);
        tle2.targetName = MEG;
        addTriggerLimitingEventInOrder(tle2);
        
        tle2.useSetDuration = true;
        tle2.setDuration = ofRandom(0.05, 0.5);
        tle2.useSetRecovery = true;
        tle2.setRecovery = ofRandom(3, 8);
        tle2.targetName = JACOB;
        addTriggerLimitingEventInOrder(tle2);
        
        tle2.useSetDuration = true;
        tle2.setDuration = ofRandom(0.05, 0.5);
        tle2.useSetRecovery = true;
        tle2.setRecovery = ofRandom(3, 8);
        tle2.targetName = HALEY;
        addTriggerLimitingEventInOrder(tle2);
    }
    
    int section_4_number_delete_events = ofRandom(5, 8);
    for(int i = 0 ; i < section_4_number_delete_events ; i ++ ) {
        deleteEvent _de;
        _de.triggerAtTime = ofRandom(section_4_start_time, section_4_end_time);
        _de.deleteType = MOSTACTIVE;
        
        int target = ofRandom(3);
        if(target == 0) {
            _de.targetName = MEG;
        } else if(target == 1) {
            _de.targetName = JACOB;
        } else if(target == 2) {
            _de.targetName = HALEY;
        }
        addDeleteEventInOrder(_de);
    }
    
    for(int i = 0 ; i < 3 ; i ++ ) {
        for(int j = 0 ; j < 2 ; j ++ ) {
            deleteEvent _de;
            _de.triggerAtTime = ofRandom(section_4_end_time - (section_4_duration * 0.1), section_4_end_time);
            _de.deleteType = MOSTACTIVE;
            if(i == 0 ) {
                _de.targetName = MEG;
            } else if(i == 1) {
                _de.targetName = JACOB;
            } else if(i == 2) {
                _de.targetName = HALEY;
            }
            addDeleteEventInOrder(_de);
        }
    }
    
    float section_5_duration = section_5_end_time - section_5_start_time;
    section_5_num_conditions = ofRandom(section_5_num_conditions - 10, section_5_num_conditions);
    for(int i = 0 ; i < section_5_num_conditions ; i ++ ) {
        conditionEvent _c;
        
        int thisTarget = ofRandom(3);
        if(thisTarget == 0) {
            _c.targetName = MEG;
        } else if(thisTarget == 1) {
            _c.targetName = JACOB;
        } else if(thisTarget == 2) {
            _c.targetName = HALEY;
        }
        
        if(i == 0 || i == 1 || i == 2) {
            _c.triggerAtTime = ofRandom(section_5_start_time, section_5_start_time + (section_5_duration * 0.15));
        } else {
            _c.triggerAtTime = ofRandom(section_5_start_time, section_5_end_time - (section_5_duration * 0.2));
        }
        
        float thisConditionSource = ofRandom(1);
        
        if(thisConditionSource <= 0.15) {
            _c.sourceName = _c.targetName;
        } else {
            vector < PerformerName > sourceName;
            sourceName.clear();
            sourceName.push_back(MEG);
            sourceName.push_back(JACOB);
            sourceName.push_back(HALEY);
            sourceName.erase(sourceName.begin() + _c.targetName);
            _c.sourceName = sourceName[(int)ofRandom(2)];
        }
        
        if(ofRandom(1) < 0.5) {
            _c.sourceDevice = WRIST;
        } else {
            _c.sourceDevice = PACK;
        }
        
        _c.c.triggerType = OPEN;
        _c.c.conditionLifespan = INFINITE;
        
        int thisConditionXYZ = ofRandom(3);
        if(thisConditionXYZ == 0) {
            _c.c.x_y_z = X;
        } else if(thisConditionXYZ == 1) {
            _c.c.x_y_z = Y;
        } else if(thisConditionXYZ == 2) {
            _c.c.x_y_z = Z;
        }
        if(ofRandom(1) < 0.8) {
            _c.c.abs_del = ABS;
            if(ofRandom(1) < 0.5) {
                _c.c.MT_LT = MT;
            } else {
                _c.c.MT_LT = LT;
            }
        } else {
            _c.c.abs_del = DEL;
            _c.c.MT_LT = MT;
        }
        if(_c.c.abs_del == ABS) {
            if(_c.c.MT_LT == MT) {
                _c.c.threshold = getNormal(180, 3000);
            } else {
                _c.c.threshold = getNormal(180, 1000);
            }
        } else {
            _c.c.threshold = getNormal(100, 750);
        }
        _c.targetRelayChannel = ofRandom(4);
        addConditionInOrder(_c);
    }
    
    for(int i = 0 ; i < 15 ; i ++ ) {
        triggerLimitingEvent tle;
        tle.triggerAtTime = ofRandom(section_5_start_time, section_5_end_time);
        tle.useSetDuration = true;
        tle.setDuration = ofRandom(0.1, 4);
        tle.useSetRecovery = true;
        tle.setRecovery = ofRandom(tle.setDuration, tle.setDuration * 4);
        
        tle.targetName = MEG;
        addTriggerLimitingEventInOrder(tle);
        tle.targetName = JACOB;
        addTriggerLimitingEventInOrder(tle);
        tle.targetName = HALEY;
        addTriggerLimitingEventInOrder(tle);
    }
    
    int section_5_delete_events = ofRandom(section_5_num_conditions * 0.25, section_5_num_conditions * 0.8);
    
    for(int i = 0 ; i < section_5_delete_events ; i ++ ) {
        deleteEvent _de;
        _de.triggerAtTime = ofRandom(section_5_start_time, section_5_end_time);
        _de.deleteType = MOSTACTIVE;
        int thisTarget = ofRandom(3);
        if(i == 0) {
            _de.targetName = MEG;
        } else if(i == 1) {
            _de.targetName = JACOB;
        } else if(i == 2) {
            _de.targetName = HALEY;
        }
        addDeleteEventInOrder(_de);
    }
    
    for(int i = 0 ; i < 3 ; i ++ ) {
        deleteEvent _de;
        _de.triggerAtTime = section_5_end_time - 20;
        _de.deleteType = ALL;
        if(i == 0) {
            _de.targetName = MEG;
        } else if(i == 1) {
            _de.targetName = JACOB;
        } else if(i == 2) {
            _de.targetName = HALEY;
        }
        
        addDeleteEventInOrder(_de);
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
                    if(conditionEvents[0].sourceDevice == PACK) {
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
            if(_t.triggerAtTime < triggerLimitingEvents[i].triggerAtTime) {
                triggerLimitingEvents.insert(triggerLimitingEvents.begin() + (i), _t);
                break;
            }
        }
    }
}
void fc_scoreManager::addDeleteEventInOrder(deleteEvent _d) {
    if(deleteEvents.size() == 0) {
        deleteEvents.push_back(_d);
    } else if(_d.triggerAtTime > deleteEvents[deleteEvents.size() - 1].triggerAtTime) {
        deleteEvents.push_back(_d);
    } else {
        for(int i = 0 ; i < deleteEvents.size() ; i ++ ) {
            if(_d.triggerAtTime < deleteEvents[i].triggerAtTime) {
                deleteEvents.insert(deleteEvents.begin() + i, _d);
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