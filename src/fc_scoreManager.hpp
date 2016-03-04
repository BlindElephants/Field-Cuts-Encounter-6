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

#include "fc_condition.hpp"
#include "fc_performer.hpp"

enum DeviceType {
    WRIST, PACK
};

enum DeleteType {
    del_ALL, del_MEG, del_JACOB, del_HALEY
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
        
        bool useSetDuration;
        float setDuration;
        
        bool useSetRecovery;
        float setRecovery;
    };
    
    struct deleteEvent {
        float triggerAtTime;
        DeleteType delType;
    };
    
    fc_scoreManager();
    
    void toggleRun();
    void update();
    void draw(float _x, float _y, float _w, float _h);
    
//    void makeConditionEventRandom();
//    void makeConditionEventRandomAbs();
//    void makeConditionEventRandomDel();
//    
//    void addConditionEventToScore(conditionEvent _c);
//    void addTriggerLimitingEventToScore(triggerLimitingEvent _t);
    
    void addConditionInOrder(conditionEvent _c);
    void addTriggerLimitingEventInOrder(triggerLimitingEvent _t);
    
    void setPerformersRef(vector < fc_performer* > _pr);
    
private:
    bool runScore;
    float scoreTimer = 0;
    float scoreLength = 60 * 35;
    ofTrueTypeFont font;
    
    float nextConditionEvent = 0;
    
    vector < fc_performer* > performersRef;
    
    vector < float > sectionStartTimes;
    vector < conditionEvent > conditionEvents;
    vector < triggerLimitingEvent > triggerLimitingEvents;
    vector < deleteEvent > deleteEvents;
    
};

#endif /* fc_scoreManager_hpp */
