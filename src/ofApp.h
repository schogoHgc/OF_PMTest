#pragma once

#include "ofMain.h"
#include "ofxQuadWarp.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
        void toggle();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    static const int NUM = 3;
    
    ofxQuadWarp warper[NUM];
    ofImage img[NUM];
    ofFbo fbo[NUM];
    
    ofxQuadWarp movWarper;
    ofVideoPlayer mov;
    ofFbo fboMov;


    ofPoint points[10];
    
    bool bOn;
};
