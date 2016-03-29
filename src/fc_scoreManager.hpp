//
//  fc_scoreManager.hpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/27/16.
//
//

#ifndef fc_scoreManager_hpp
#define fc_scoreManager_hpp

#include "ofMain.h"
#include "ofxGaussian.h"

#include "fc_deviceManager.hpp"
#include "fc_condition.hpp"
#include "fc_performer.hpp"


enum DeviceType {
    WRIST, PACK
};

enum DeleteType {
    ALL, MOSTACTIVE
};

enum ThresholdType {
    BASELINE, UNLIKELY, LIKELY, VERYLIKELY
};

class fc_scoreManager {
public:
    
    struct conditionEvent {
        float triggerAtTime;
        fc_condition c;
        PerformerName targetName;
        int targetRelayChannel;
        PerformerName sourceName;
        DeviceType sourceDevice;
    };
    
    struct triggerLimitingEvent {
        float triggerAtTime;
        PerformerName targetName;
        bool useSetDuration;
        float setDuration;
        bool useSetRecovery;
        float setRecovery;
    };
    
    struct deleteEvent {
        float triggerAtTime;
        PerformerName targetName;
        DeleteType deleteType;
    };
    
    fc_scoreManager();
    
    void toggleRun();
    void update();
    void draw(float _x, float _y, float _w, float _h);

    void addConditionInOrder(conditionEvent _c);
    void addTriggerLimitingEventInOrder(triggerLimitingEvent _t);
    void addTriggerLimitingPair(triggerLimitingEvent _t, triggerLimitingEvent _u);
    
    void addDeleteEventInOrder(deleteEvent _d);
    
    void setPerformersRef(vector < fc_performer > *_pr);
    void setDevicesRef(fc_deviceManager *_deviceManager);
    
    int getParamThresholdCenter(DeviceType _wrist_pack, Parameter _abs_del, Parameter _x_y_z, Parameter _mt_lt);
    void setConditionThreshold(conditionEvent &_c);
    void setConditionThreshold(conditionEvent &_c, ThresholdType _thresholdType);
    
    PerformerName makePerformerName(float _probA, float _probB, float _probC);
    PerformerName makePerformerName();
    
    void makeSourcePerformerName(conditionEvent &_c);
    
    DeviceType makeDeviceType(float _probA, float _probB);
    DeviceType makeDeviceType();
    
    void makeXYZ_and_MTLT(conditionEvent &_c);
    
    void buildConditionEvent(conditionEvent &_c, ThresholdType _thresholdType, float _probPerformerA, float _probPerformerB, float _probPerformerC, float _probWrist, float _probPack);
    void buildConditionEvent(conditionEvent &_c, ThresholdType _thresholdType, float _probPerformerA, float _probPerformerB, float _probPerformerC);
    
    void buildConditionEvent(conditionEvent &_c, ThresholdType _thresholdType);
    
    void buildFollowingConditionEvent(fc_condition &_c);
    
    void buildNormalLimitingEvent(float _time);
    void buildNormalLimitingEvent(PerformerName _target, float _time);
    
    void buildRapidTriggerLimitingEvent(float _time, float _duration);
    void buildRapidTriggerLimitingEvent(PerformerName _target, float _time, float _duration);
    
    void buildHeldTriggerLimitingEvent(float _time, float _duration);
    void buildHeldTriggerLimitingEvent(PerformerName _target, float _time, float _duration);

    void buildDeleteAllEvent(float _time);
    void buildDeleteAllEvent(PerformerName _target, float _time);
    
    void buildDeleteMostActive(float _time);
    void buildDeleteMostActive(PerformerName _target, float _time);
    
    void goToTime(float _time);
    void goToSection1();
    void goToSection2();
    void goToSection3();
    void goToSection4();
    void goToSection5();
    
private:
    bool runScore;
    float scoreTimer = 0;
    float scoreLength = 60 * 35;
    ofTrueTypeFont font;
    
    float nextConditionEvent = 0;
    float nextTriggerLimitingEvent = 0;
    float nextDeleteEvent = 0;
    
    vector < fc_performer > *performersRef;
    fc_deviceManager *deviceManagerRef;
    
    vector < float > sectionStartTimes;
    vector < conditionEvent > conditionEvents;
    vector < triggerLimitingEvent > triggerLimitingEvents;
    vector < deleteEvent > deleteEvents;
};

#endif /* fc_scoreManager_hpp */
