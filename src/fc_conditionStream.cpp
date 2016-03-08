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


/*TODO: need to add method of storing from whom the active conditions originate.
 Fill a vector with the indices of the condition sources
 Return this vector, need to get it to the fc_performer class which will then send the message to the needed destinations
 */
vector < int > fc_conditionStream::checkAllConditions() {
    vector < int > activeConditionSources;
    activeConditionSources.clear();                         //might not be needed?
    
    numActiveConditions = 0;
    if(conditions.size() > 0) {
        bool relaySetting = false;
        for(int i = conditions.size() - 1 ; i >= 0 ; i -- ) {
//            cout << "condition: " << i << " condition timer: " << conditions[i] -> conditionTimer << " active timer: " << conditions[i] -> conditionActiveTime << " active num: " << conditions[i] -> conditionActiveNum << endl;;
            conditions[i] -> conditionTimer += ofGetLastFrameTime();
            if(conditions[i] -> isActive) conditions[i] -> conditionActiveTime += ofGetLastFrameTime();
            if(!(conditions[i] -> isActive) && (conditions[i] -> conditionLifespan == DIE_AFTER_TRIGGER_NUM) && (conditions[i] -> conditionActiveNum >= conditions[i] -> conditionActiveNumLimit)) {
                conditions.erase(conditions.begin() + i);
                if(sendToOsc) {
                    ofxOscMessage m;
                    m.setAddress("/delete_condition");
                    m.addIntArg(thisDeviceIndex);
                    sendToFloor -> sendMessage(m);
                    
                    
                    ofxOscMessage n;
                    n.setAddress("/fieldcuts/connect");
                    n.addStringArg("off");
                    sendToSound -> sendMessage(n);
                }
                cout << "erased because trigger number high" << endl;
            } else if((conditions[i] -> conditionLifespan == DIE_AFTER_TRIGGER_DURATION) && (conditions[i] -> conditionActiveTime >= conditions[i] -> conditionTimerLimit)) {
                conditions.erase(conditions.begin() + i);
                if(sendToOsc) {
                    ofxOscMessage m;
                    m.setAddress("/delete_condition");
                    m.addIntArg(thisDeviceIndex);
                    sendToFloor -> sendMessage(m);
                    
                    ofxOscMessage n;
                    n.setAddress("/fieldcuts/connect");
                    n.addStringArg("off");
                    sendToSound -> sendMessage(n);
                }
                cout << "erased because trigger duration number high " << endl;
            } else if((conditions[i] -> conditionLifespan == DIE_AFTER_TIME) && (conditions[i] -> conditionTimer >= conditions[i] -> conditionTimerLimit)) {
                conditions.erase(conditions.begin() + i);
                if(sendToOsc) {
                    ofxOscMessage m;
                    m.setAddress("/delete_condition");
                    m.addIntArg(thisDeviceIndex);
                    sendToFloor -> sendMessage(m);
                    
                    ofxOscMessage n;
                    n.setAddress("/fieldcuts/connect");
                    n.addStringArg("off");
                    sendToSound -> sendMessage(n);
                }
                cout << "erased because timer high" << endl;
            } else {
                float val = devices[conditions[i] -> sourceDevice] -> getLastAccelValue(conditions[i] -> abs_del, conditions[i] -> x_y_z);
                if(conditions[i] -> MT_LT == LT) {
                    if(val < conditions[i] -> threshold) {
                        relaySetting = true;
                        if(!(conditions[i] -> isActive)) {
                            conditions[i] -> conditionActiveNum ++ ;
                        }
                        conditions[i] -> isActive = true;
                        activeConditionSources.push_back(conditions[i] -> sourceDevice);
                    } else {
                        conditions[i] -> isActive = false;
                    }
                } else {
                    if(val > conditions[i] -> threshold) {
                        relaySetting = true;
                        if(!(conditions[i] -> isActive)) {
                            conditions[i] -> conditionActiveNum ++ ;
                        }
                        conditions[i] -> isActive = true;
                        activeConditionSources.push_back(conditions[i] -> sourceDevice);
                    } else {
                        conditions[i] -> isActive = false;
                    }
                }
                if(conditions[i] -> isActive) numActiveConditions ++ ;
            }
        }
        devices[thisDeviceIndex] -> setRelay(thisRelayChannelIndex, relaySetting);
        return activeConditionSources;
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
    
    if(sendToOsc) {
        ofxOscMessage m;
        m.setAddress("/make_condition");
        m.addIntArg(_sourceDevice);
        m.addIntArg(thisDeviceIndex);
        sendToFloor -> sendMessage(m);
        
        ofxOscMessage n;
        n.setAddress("/fieldcuts/connect");
        n.addStringArg("on");
        sendToSound -> sendMessage(n);
    }
}

int fc_conditionStream::getNumberConditions() {return conditions.size();}
int fc_conditionStream::getNumberActiveConditions() {return numActiveConditions;}

void fc_conditionStream::drawConditions(float _x, float _y) {
    if(conditions.size() > 0) {
        ofPushMatrix();
        ofTranslate(_x, _y);
        for(int i = 0 ; i < conditions.size() ; i ++ ) {
            ofSetColor(ofColor::white);
            font.drawString(ofToString(i) + ": ", 0, 0);
            if(conditions[i] -> isActive) {
                ofSetColor(ofColor::red);
                font.drawString("TRUE ", 16, 0);
            } else {
                ofSetColor(ofColor::white);
                font.drawString("FALSE", 16, 0);
            }
            
            int _source = conditions[i] -> sourceDevice / 2;
            int _sourceDevice = conditions[i] -> sourceDevice % 2;
            
            if(_source == 0) {
                font.drawString("MEG", 64, 0);
            } else if(_source == 1) {
                font.drawString("JACOB", 64, 0);
            } else if(_source == 2) {
                font.drawString("HALEY", 64, 0);
            }
            
            if(_sourceDevice == 0) {
                font.drawString("WRIST", 112, 0);
            } else if(_sourceDevice == 1) {
                font.drawString("PACK", 112, 0);
            }
            
            if(conditions[i] -> x_y_z == X) {
                font.drawString("X", 160, 0);
            } else if(conditions[i] -> x_y_z == Y) {
                font.drawString("Y", 160, 0);
            } else if(conditions[i] -> x_y_z == Z) {
                font.drawString("Z", 160, 0);
            }
            
            if(conditions[i] -> abs_del == ABS) {
                font.drawString("ABS", 172, 0);
            } else if(conditions[i] -> abs_del == DEL) {
                font.drawString("DEL", 172, 0);
            }
            
            if(conditions[i] -> MT_LT == MT) {
                font.drawString(" > ", 204, 0);
            } else if(conditions[i] -> MT_LT == LT) {
                font.drawString(" < ", 204, 0);
            }
            font.drawString(ofToString(conditions[i] -> threshold), 228, 0);
            
            font.drawString(" | ", 276, 0);
            font.drawString(ofToString(conditions[i] -> conditionActiveNum), 300, 0);
            font.drawString(ofToString(conditions[i] -> conditionActiveTime), 348, 0);
            font.drawString(ofToString(conditions[i] -> conditionTimer), 400, 0);
            
            
            ofTranslate(0, 10);
        }
        ofPopMatrix();
    }
}

void fc_conditionStream::deleteAllConditions() {
    if(conditions.size() > 0 && sendToOsc) {
        ofxOscMessage m;
        m.setAddress("/delete_condition");
        m.addIntArg(thisDeviceIndex);
        sendToFloor -> sendMessage(m);
        
        ofxOscMessage n;
        n.setAddress("/fieldcuts/connect");
        n.addStringArg("off");
        sendToSound -> sendMessage(n);
    }
    
    conditions.clear();
    
}

void fc_conditionStream::deleteCondition(int _index) {
    if(conditions.size() > _index) {
        conditions.erase(conditions.begin() + _index);
        if(sendToOsc) {
            ofxOscMessage m;
            m.setAddress("/delete_condition");
            m.addIntArg(thisDeviceIndex);
            sendToFloor -> sendMessage(m);
            
            ofxOscMessage n;
            n.setAddress("/fieldcuts/connect");
            n.addStringArg("off");
            sendToSound -> sendMessage(n);
        }
    }
}

int fc_conditionStream::getMostActiveCondition() {
    if(conditions.size() > 0) {
        float activeTime = 0;
        int index = 0;
        for(int i = 0 ; i < conditions.size() ; i ++ ) {
            if(conditions[i] -> conditionActiveTime > activeTime) {
                activeTime = conditions[i] -> conditionActiveTime;
                index = i;
            }
        }
        return index;
    } else {
        return -1;
    }
}

float fc_conditionStream::getActiveTimer(int _index) {
    if(conditions.size() > _index) {
        return conditions[_index] -> conditionActiveTime;
    } else {
        return -1;
    }
}

void fc_conditionStream::setOscRefs(ofxOscSender *toFloor, ofxOscSender *toSound) {
    sendToFloor = toFloor;
    sendToSound = toSound;
    sendToOsc = true;
}