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
    void addDeleteEventInOrder(deleteEvent _d);
    
    void setPerformersRef(vector < fc_performer > *_pr);
    void setDevicesRef(fc_deviceManager *_deviceManager);
    
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
