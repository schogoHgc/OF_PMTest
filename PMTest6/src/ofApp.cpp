//
//Test of "ofxQuadWarp" addons
// Written schogoHgc on 02/04/2015


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    img.loadImage("TestImg1.png");
    
    int x = (ofGetWidth() - img.width) *0.5;
    int y = (ofGetHeight() - img.height) *0.5;
    int w = img.width;
    int h = img.height;
    
    fbo.allocate(w, h);
    
    warper.setSourceRect(ofRectangle(0, 0, w, h));
    warper.setTopLeftCornerPosition(ofPoint(x, y));
    warper.setTopRightCornerPosition(ofPoint(x + w, y));
    warper.setBottomLeftCornerPosition(ofPoint(x, y + h));
    warper.setBottomRightCornerPosition(ofPoint(x + w, y + h));
    
    warper.setup();
    warper.load();

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
    
    fbo.begin();
    img.draw(0, 0);
    fbo.end();
    
    ofMatrix4x4 mat = warper.getMatrix();
    
    ofPushMatrix();
    ofMultMatrix(mat);
    fbo.draw(0, 0);
    ofPopMatrix();
    
    ofSetColor(ofColor::magenta);
    warper.drawQuadOutline();
    
    ofSetColor(ofColor::yellow);
    warper.drawCorners();
    
    ofSetColor(ofColor::magenta);
    warper.drawHighlightedCorner();
    
    ofSetColor(ofColor::red);
    warper.drawSelectedCorner();
    

}

void ofApp::exit(){
    warper.save();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 's' || key == 'S') {
        warper.toggleShow();
    }
    
    if (key == 'd' || key == 'D') {
        warper.load();
    }
    
    if (key == 'f' || key == 'F') {
        warper.save();
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
