//
//Test of "ofxQuadWarp" addons
//Written by schogoHgc on 02/06/2015


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
    mov.loadMovie("TestMov1.mov");
    mov.play();
    
    int x = 40;
    int y = 40;
    int w[NUM];
    int h[NUM];
    int wMov;
    int hMov;
    
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
//        warper[i].load();
        
        fbo[i].begin();
        ofClear(255, 255, 255,0);
        fbo[i].end();

        x += 100;
        y += 100;
    }
    
//for Movie File
    wMov = mov.width/2;
    hMov = mov.height/2;
    
    fboMov.allocate(wMov, hMov);

    movWarper.setSourceRect(ofRectangle(0, 0, wMov, hMov));
    movWarper.setTopLeftCornerPosition(ofPoint(x, y));
    movWarper.setTopRightCornerPosition(ofPoint(x + wMov, y));
    movWarper.setBottomLeftCornerPosition(ofPoint(x, y + hMov));
    movWarper.setBottomRightCornerPosition(ofPoint(x + wMov, y + hMov));

    movWarper.setup();
    
    fboMov.begin();
    ofClear(255, 255, 255,0);
    fboMov.end();

//for PC Camera
    int wCam = 300;
    int hCam = 300;
    
    camGrab.setVerbose(true);
    camGrab.initGrabber(wCam, hCam);
    
    fboCam.allocate(wMov, hMov);
    
    camWarper.setSourceRect(ofRectangle(0, 0, wCam, hCam));
    camWarper.setTopLeftCornerPosition(ofPoint(x+100, y));
    camWarper.setTopRightCornerPosition(ofPoint(x+100 + wCam, y));
    camWarper.setBottomLeftCornerPosition(ofPoint(x+100, y + hCam));
    camWarper.setBottomRightCornerPosition(ofPoint(x+100 + wCam, y + hCam));
    
    camWarper.setup();
    
    fboCam.begin();
    ofClear(255, 255, 255,0);
    fboCam.end();
    
   
}

//--------------------------------------------------------------
void ofApp::update(){
    if (ofGetFrameNum()% 5 !=0) {
        return;
    }
    
    mov.update();
    camGrab.update();

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
        
        ofSetColor(ofColor::white);

    }
    
// for Movie File
    fboMov.begin();
    mov.draw(0, 0);
    fboMov.end();
    
    ofMatrix4x4 mat = movWarper.getMatrix();
    
    ofPushMatrix();
    ofMultMatrix(mat);
    fboMov.draw(0, 0);
    ofPopMatrix();
    
    ofSetColor(ofColor::magenta);
    movWarper.drawQuadOutline();
    
    ofSetColor(ofColor::yellow);
    movWarper.drawCorners();
    
    ofSetColor(ofColor::magenta);
    movWarper.drawHighlightedCorner();
    
    ofSetColor(ofColor::red);
    movWarper.drawSelectedCorner();
    
    ofSetColor(ofColor::white);

    
// for PC Camera
    fboCam.begin();
    camGrab.draw(0, 0);
    fboCam.end();
    
    ofMatrix4x4 matC = camWarper.getMatrix();
    
    ofPushMatrix();
    ofMultMatrix(matC);
    fboCam.draw(0, 0);
    ofPopMatrix();
    
    ofSetColor(ofColor::magenta);
    camWarper.drawQuadOutline();
    
    ofSetColor(ofColor::yellow);
    camWarper.drawCorners();
    
    ofSetColor(ofColor::magenta);
    camWarper.drawHighlightedCorner();
    
    ofSetColor(ofColor::red);
    camWarper.drawSelectedCorner();

    
}

//--------------------------------------------------------------
void ofApp::exit(){
    for (int i=0; i<NUM; i++) {
        warper[i].save();
    }
    movWarper.save();
    camWarper.save();
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

    //for Movie
    // movWarper
    if (key == 'i' || key == 'I') {
        toggle();
        movWarper.toggleShow();
    }
    
    if (key == 'o' || key == 'O') {
        if (!bOn) {
            return;
        }
        movWarper.load();
    }
    
    if (key == 'p' || key == 'P') {
        if (!bOn) {
            return;
        }
        movWarper.save();
    }


    //for PC Camera
    // camWarper
    if (key == 'j' || key == 'J') {
        toggle();
        camWarper.toggleShow();
    }
    
    if (key == 'k' || key == 'K') {
        if (!bOn) {
            return;
        }
        camWarper.load();
    }
    
    if (key == 'l' || key == 'L') {
        if (!bOn) {
            return;
        }
        camWarper.save();
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
