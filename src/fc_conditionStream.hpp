//
//  fc_conditionStream.hpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/28/16.
//
//

#ifndef fc_conditionStream_hpp
#define fc_conditionStream_hpp

#include "ofMain.h"
#include "fc_condition.hpp"
#include "fc_device.hpp"
#include "ofxOsc.h"

class fc_scoreManager;

class fc_conditionStream {
public:
    fc_conditionStream(int _thisDeviceIndex, int _thisRelayChannelIndex);
    
    void setDevices(vector < fc_device* > _devices);
    vector < int > checkAllConditions();
    void makeNewCondition(int _sourceDevice, Parameter _x_y_z, Parameter _abs_del, Parameter _MT_LT, float _threshold, TriggerType _triggerType, float _triggerSetDuration, Lifespan _conditionLifespan, float _conditionTimer);
    
    int getNumberConditions();
    int getNumberActiveConditions();
    
    void drawConditions(float _x, float _y);
    
    void deleteAllConditions();
    void deleteCondition(int _index);
    
    int getMostActiveCondition();
    float getActiveTimer(int _index);
    
    void setOscRefs(ofxOscSender *toFloor, ofxOscSender *toSound);
    void setScoreManager(fc_scoreManager *_scoreManager);
    
private:
    vector < fc_condition* > conditions;
    vector < fc_device* > devices;
    
    int thisDeviceIndex;
    int thisRelayChannelIndex;
    int numActiveConditions = 0;
    
    ofTrueTypeFont font;
    
    bool sendToOsc = false;
    ofxOscSender *sendToFloor;
    ofxOscSender *sendToSound;
    fc_scoreManager *scoreManager;
};

#endif /* fc_conditionStream_hpp */
