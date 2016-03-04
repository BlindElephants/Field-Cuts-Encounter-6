//
//  fc_conditionStream.cpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/28/16.
//
//

#include "fc_conditionStream.hpp"

fc_conditionStream::fc_conditionStream(int _thisDeviceIndex, int _thisRelayChannelIndex) {
    conditions.clear();
    font.load("courier", 8);
    thisDeviceIndex = _thisDeviceIndex;
    thisRelayChannelIndex = _thisRelayChannelIndex;
}

void fc_conditionStream::setDevices(vector<fc_device *> _devices) {devices = _devices;}

void fc_conditionStream::checkAllConditions() {
    numActiveConditions = 0;
    if(conditions.size() > 0) {
        bool relaySetting = false;
        for(int i = conditions.size() - 1 ; i >= 0 ; i -- ) {
//            cout << "condition: " << i << " condition timer: " << conditions[i] -> conditionTimer << " active timer: " << conditions[i] -> conditionActiveTime << " active num: " << conditions[i] -> conditionActiveNum << endl;;
            conditions[i] -> conditionTimer += ofGetLastFrameTime();
            if(conditions[i] -> isActive) conditions[i] -> conditionActiveTime += ofGetLastFrameTime();
            if(!(conditions[i] -> isActive) && (conditions[i] -> conditionLifespan == DIE_AFTER_TRIGGER_NUM) && (conditions[i] -> conditionActiveNum >= conditions[i] -> conditionActiveNumLimit)) {
                conditions.erase(conditions.begin() + i);
                cout << "erased because trigger number high" << endl;
            } else if((conditions[i] -> conditionLifespan == DIE_AFTER_TRIGGER_DURATION) && (conditions[i] -> conditionActiveTime >= conditions[i] -> conditionTimerLimit)) {
                conditions.erase(conditions.begin() + i);
                cout << "erased because trigger duration number high " << endl;
            } else if((conditions[i] -> conditionLifespan == DIE_AFTER_TIME) && (conditions[i] -> conditionTimer >= conditions[i] -> conditionTimerLimit)) {
                conditions.erase(conditions.begin() + i);
                cout << "erased because timer high" << endl;
            } else {
                float val = devices[conditions[i] -> sourceDevice] -> getLastAccelValue(conditions[i] -> abs_del, conditions[i] -> x_y_z);
                if(conditions[i] -> MT_LT == LT) {
                    if(conditions[i] -> threshold > val) {
                        relaySetting = true;
                        if(!(conditions[i] -> isActive)) {
                            conditions[i] -> conditionActiveNum ++ ;
                        }
                        conditions[i] -> isActive = true;
                    } else {
                        conditions[i] -> isActive = false;
                    }
                } else {
                    if(conditions[i] -> threshold < val) {
                        relaySetting = true;
                        if(!(conditions[i] -> isActive)) {
                            conditions[i] -> conditionActiveNum ++ ;
                        }
                        conditions[i] -> isActive = true;
                    } else {
                        conditions[i] -> isActive = false;
                    }
                }
                if(conditions[i] -> isActive) numActiveConditions ++ ;
            }
        }
        cout << "num active conditions: " << numActiveConditions << endl;
        devices[thisDeviceIndex] -> setRelay(thisRelayChannelIndex, relaySetting);
    }
}

void fc_conditionStream::makeNewCondition(int _sourceDevice, Parameter _x_y_z, Parameter _abs_del, Parameter _MT_LT, float _threshold, TriggerType _triggerType, float _triggerSetDuration, Lifespan _conditionLifespan, float _conditionTimer) {
    fc_condition * c = new fc_condition();
    c -> sourceDevice = _sourceDevice;
    c -> x_y_z = _x_y_z;
    c -> abs_del = _abs_del;
    c -> MT_LT = _MT_LT;
    c -> threshold = _threshold;
    c -> triggerType = _triggerType;
    c -> triggerSetDuration = _triggerSetDuration;
    c -> conditionLifespan = _conditionLifespan;
    if(_conditionLifespan == DIE_AFTER_TRIGGER_NUM) {
        c -> conditionActiveNumLimit = _conditionTimer;
    } else {
        c -> conditionTimerLimit = _conditionTimer;
    }
    conditions.push_back(c);
}

int fc_conditionStream::getNumberConditions() {return conditions.size();}
int fc_conditionStream::getNumberActiveConditions() {return numActiveConditions;}

float fc_conditionStream::drawAllConditions(float _x, float _y) {
    if(conditions.size() > 0) {
        ofPushMatrix();
        ofTranslate(_x, 0);
        for(int i = 0 ; i < conditions.size() ; i ++ ) {
            if(conditions[i] -> isActive) {
                font.drawString("TRUE", 0, _y);
            } else {
                font.drawString("FALSE", 0, _y);
            }
            
            font.drawString(" | ", 60, _y);
            font.drawString("source: " + ofToString(conditions[i] -> sourceDevice), 90, _y);
            font.drawString(" | ", 190, _y);
            if(conditions[i] -> x_y_z == X) {
                font.drawString("X", 220, _y);
            } else if(conditions[i] -> x_y_z == Y) {
                font.drawString("Y", 220, _y);
            } else if(conditions[i] -> x_y_z == Z) {
                font.drawString("Z", 220, _y);
            }
            
            if(conditions[i] -> abs_del == ABS) {
                font.drawString("ABS", 240, _y);
            } else if(conditions[i] -> abs_del == DEL) {
                font.drawString("DEL", 240, _y);
            }
            
            if(conditions[i] -> MT_LT == MT) {
                font.drawString(">", 280, _y);
            } else if(conditions[i] -> MT_LT) {
                font.drawString("<", 280, _y);
            }
            
            font.drawString(ofToString(conditions[i] -> threshold), 310, _y);
            
            if(conditions[i] -> conditionLifespan == DIE_AFTER_TIME) {
                font.drawString("TIME LIMIT: ", 390, _y);
                font.drawString(ofToString(conditions[i] -> conditionTimer), 540, _y);
            } else if(conditions[i] -> conditionLifespan == DIE_AFTER_TRIGGER_DURATION) {
                font.drawString("ACTIVE TIMER: ", 390, _y);
                font.drawString(ofToString(conditions[i] -> conditionActiveTime), 540, _y);
            } else if(conditions[i] -> conditionLifespan == DIE_AFTER_TRIGGER_NUM) {
                font.drawString("ON MSGS: ", 390, _y);
                font.drawString(ofToString(conditions[i] -> conditionActiveNum), 540, _y);
            }
            _y += 12;
        }
        ofPopMatrix();
        return (conditions.size() * 12);
    }
}