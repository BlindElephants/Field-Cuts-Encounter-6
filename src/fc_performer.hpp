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

enum PerformerName {
    MEG, JACOB, HALEY, JEREMY
};

class fc_performer {
public:
    fc_performer() {};
    
    PerformerName name;
    int packIndex;
    int wristIndex;
    
private:
};

#endif /* fc_performer_hpp */
