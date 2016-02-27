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
#include "fc_condition.hpp"
#include "fc_device.hpp"


class fc_conditionManager {
public:
    fc_conditionManager();
    
    void setDevices(vector < fc_device* > _devices);
    void checkAllConditions();
    
    void makeNewCondition(int _sourceDevice,
                          Parameter _x_y_z,
                          Parameter _abs_del,
                          Parameter _MT_LT,
                          float _threshold,
                          int _targetDevice,
                          int _targetRelay);
    
    void makeNewCondition(int _sourceDevice,
                          Parameter _x_y_z,
                          Parameter _abs_del,
                          Parameter _MT_LT,
                          float _threshold,
                          int _targetDevice,
                          int _targetRelay,
                          TriggerType _triggerType,
                          float _triggerSetDuration);
    
    void makeNewCondition(int _sourceDevice,
                          Parameter _x_y_z,
                          Parameter _abs_del,
                          Parameter _MT_LT,
                          float _threshold,
                          int _targetDevice,
                          int _targetRelay,
                          Lifespan _conditionLifespan,
                          float _conditionTimer);
    
    void makeNewCondition(int _sourceDevice,
                          Parameter _x_y_z,
                          Parameter _abs_del,
                          Parameter _MT_LT,
                          float _threshold,
                          int _targetDevice,
                          int _targetRelay,
                          TriggerType _triggerType,
                          float _triggerSetDuration,
                          Lifespan _conditionLifespan,
                          float _conditionTimer);
    
    void deleteCondition(int _conditionIndex);
    void deleteRandomCondition();
    void deleteDeviceCondition(int _deviceIndex);
    void deleteAllConditions();
    void deleteAllDeviceConditions(int _deviceIndex);
    void getNumDevices();
    
private:
    vector < fc_condition* > conditions;
    vector < fc_device* > devices;
    
    int numberOfRelayChannels = 4;
    vector < bool > allRelayCounter;
};

#endif /* fc_conditionManager_hpp */
