//
//  fc_scoreManager.cpp
//  Field_Cuts_6_SCORE
//
//  Created by Blind Elephants on 2/27/16.
//
//

#include "fc_scoreManager.hpp"

void fc_scoreManager::toggleRun() {
    runScore = !runScore;
}

void fc_scoreManager::update() {
    if(runScore) {
        scoreTimer += ofGetLastFrameTime();
    }
}

void fc_scoreManager::draw(float _x, float _y, float _w, float _h) {
    ofSetColor(ofColor::white);
    ofNoFill();
    ofDrawRectangle(_x, _y, _w, _h);
    
    ofFill();
    ofDrawRectangle(_x, _y, ofMap(scoreTimer, 0, scoreLength, 0, _w), _h);
    
}