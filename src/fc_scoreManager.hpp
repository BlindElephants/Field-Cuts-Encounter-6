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

class fc_scoreManager {
public:
    fc_scoreManager() {};
    
    void toggleRun();
    void update();
    void draw(float _x, float _y, float _w, float _h);
    
private:
    bool runScore;
    float scoreTimer = 0;
    float scoreLength = 60 * 2;
};

#endif /* fc_scoreManager_hpp */
