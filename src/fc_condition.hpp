//
//  fc_condition.hpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/25/16.
//
//

#ifndef fc_condition_hpp
#define fc_condition_hpp

#include "ofMain.h"

enum Parameter {
    X, Y, Z, MT, LT, ABS, DEL
};

enum TriggerType {
    OPEN, SET_DURATION
};

enum Lifespan {
    INFINITE,
    DIE_AFTER_TRIGGER_NUM,
    DIE_AFTER_TRIGGER_DURATION,
    DIE_AFTER_TIME
};

class fc_condition {
public:
    fc_condition() {};
    
    bool isActive;
    int sourceDevice;
    Parameter x_y_z;
    Parameter abs_del;
    Parameter MT_LT;
    float threshold;
    
    //these aren't needed-------
    TriggerType triggerType;
    float triggerSetDuration;
    //--------------------------

    Lifespan conditionLifespan;
    float conditionTimer = 0;
    float conditionActiveTime = 0;
    float conditionTimerLimit = 0;
    int   conditionActiveNum = 0;
    int   conditionActiveNumLimit = 0;
};

#endif /* fc_condition_hpp */
