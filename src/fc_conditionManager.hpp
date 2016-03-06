//
//  fc_conditionManager.hpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/25/16.
//
//

#ifndef fc_conditionManager_hpp
#define fc_conditionManager_hpp

#include "ofMain.h"
#include "fc_device.hpp"
#include "fc_conditionStream.hpp"

class fc_conditionManager {
public:
    fc_conditionManager(vector < fc_device* > _devices, int _thisDeviceIndex, int _numRelayChannels);
    
    void setDeviceReference(vector < fc_device* > _devices);
    
    void checkAllConditions();
    void makeNewCondition(int _targetRelayChannel, int _sourceDevice, Parameter _x_y_z, Parameter _abs_del, Parameter _MT_LT, float _threshold, TriggerType _triggerType, float _triggerSetDuration, Lifespan _conditionLifespan, float _conditionTimer);
    
    int getNumberConditionsInRelay(int _relayChannel);
    int getNumberActiveConditionsInRelay(int _relayChannel);
    
    int getNumberConditions();
    int getNumberActiveConditions();
    
    void drawConditionStreams(float _x, float _y, float _gap);
    
    void deleteAllConditions();
    void deleteMostActiveCondition();
    
private:
    vector < fc_device* > devices;
    vector < fc_conditionStream* > conditionStreams;
    int thisDeviceIndex;
};

#endif /* fc_conditionManager_hpp */
