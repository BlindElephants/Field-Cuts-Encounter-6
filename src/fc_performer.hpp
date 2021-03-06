//
//  fc_performer.hpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/27/16.
//
//

#ifndef fc_performer_hpp
#define fc_performer_hpp

#include "ofMain.h"
#include "fc_conditionManager.hpp"
#include "fc_device.hpp"
#include "ofxOsc.h"

class fc_scoreManager;

enum PerformerName {
    MEG, JACOB, HALEY, NUM_PERFORMERS
};

class fc_performer {
public:
    fc_performer(PerformerName _name);
    
    void setDeviceReferences(vector < fc_device* > _devices);
    void setDevices(int _wristIndex, int _packIndex, int _numberRelayChannels);
    void update();
    void makeNewCondition(int _targetRelayChannel, int _sourceDevice, Parameter _x_y_z, Parameter _abs_del, Parameter _MT_LT, float _threshold, Lifespan _conditionLifespan, float _conditionTimer);
    int getWristIndex();
    int getPackIndex();
    void drawConditions(float _x, float _y);
    void drawDeviceDurRec(float _x, float _y);
    void deleteAllConditions();
    void deleteMostActiveCondition();
    void deleteRandomCondition();
    void deleteSelectCondition(int _relayChannel, int _index);
    
    void sendOffMessage();
    void setConditionManagerOscRefs(ofxOscSender *toFloor, ofxOscSender *toSound);
    void setScoreManagerRef(fc_scoreManager *_scoreManager);
    
private:
    fc_conditionManager* conditionManager;
    
    vector < fc_device* > devices;
    
    PerformerName name;
    int packIndex;
    int wristIndex;
    int conditionManagerIndex;
    
};

#endif /* fc_performer_hpp */
