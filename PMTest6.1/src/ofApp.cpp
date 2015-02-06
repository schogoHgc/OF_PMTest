//
//Test of "ofxQuadWarp" addons
//Written by schogoHgc on 02/05/2015


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    bOn = true;
    
    img[0].loadImage("TestImg1.png");
    img[1].loadImage("TestImg2.png");
    img[2].loadImage("TestImg3.png");
    
    int x = 0;
    int y = 0;
    int w[NUM];
    int h[NUM];
    
    for (int i=0; i<NUM; i++) {
        w[i] = img[i].width;
        h[i] = img[i].height;
        
        fbo[i].allocate(w[i], h[i]);
        
        warper[i].setSourceRect(ofRectangle(0, 0, w[i], h[i]));
        warper[i].setTopLeftCornerPosition(ofPoint(x, y));
        warper[i].setTopRightCornerPosition(ofPoint(x + w[i], y));
        warper[i].setBottomLeftCornerPosition(ofPoint(x, y + h[i]));
        warper[i].setBottomRightCornerPosition(ofPoint(x + w[i], y + h[i]));
        
        warper[i].setup();
        warper[i].load();
        
        fbo[i].begin();
        ofClear(255, 255, 255,0);
        fbo[i].end();

    }
   
}

//--------------------------------------------------------------
void ofApp::update(){
    if (ofGetFrameNum()% 5 !=0) {
        return;
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    
    for (int i=0; i<NUM; i++) {

        fbo[i].begin();
        img[i].draw(0, 0);
        fbo[i].end();
    
        ofMatrix4x4 mat = warper[i].getMatrix();
    
        ofPushMatrix();
        ofMultMatrix(mat);
        fbo[i].draw(0, 0);
        ofPopMatrix();
        
    }
    
    for (int i=0; i<NUM; i++) {

        ofSetColor(ofColor::magenta);
        warper[i].drawQuadOutline();
    
        ofSetColor(ofColor::yellow);
        warper[i].drawCorners();
    
        ofSetColor(ofColor::magenta);
        warper[i].drawHighlightedCorner();
    
        ofSetColor(ofColor::red);
        warper[i].drawSelectedCorner();

    }
}

//--------------------------------------------------------------

void ofApp::exit(){
    for (int i=0; i<NUM; i++) {
        warper[i].save();
    }
}
//--------------------------------------------------------------
void ofApp::toggle(){
    bOn = !bOn;
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // warper[0]
    if (key == 'x' || key == 'X') {
        toggle();
        warper[0].toggleShow();
    }
    
    if (key == 'c' || key == 'C') {
        if (!bOn) {
            return;
        }
        warper[0].load();
    }
    
    if (key == 'v' || key == 'V') {
        if (!bOn) {
            return;
        }
        warper[0].save();
    }
    
    // warper[1]
    if (key == 's' || key == 'S') {
        toggle();
        warper[1].toggleShow();
    }
    
    if (key == 'd' || key == 'D') {
        if (!bOn) {
            return;
        }
        warper[1].load();
    }
    
    if (key == 'f' || key == 'F') {
        if (!bOn) {
            return;
        }
        warper[1].save();
    }

    // warper[2]
    if (key == 'w' || key == 'W') {
        toggle();
        warper[2].toggleShow();
    }
    
    if (key == 'e' || key == 'E') {
        if (!bOn) {
            return;
        }
        warper[2].load();
    }
    
    if (key == 'r' || key == 'R') {
        if (!bOn) {
            return;
        }
        warper[2].save();
    }


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
