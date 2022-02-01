#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup();
	gui.add(jitter.setup("jitter", 40, 0, 50));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(232, 223, 217);
	ofSetColor(0);
	ofNoFill();
	ofSetLineWidth(2);
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofSeedRandom(mouseX * 100);

	int x = 500; // ofGetWidth() / 2
	int y = 512; // ofGetHeight() / 2

	for (int i = 0; i < 30; i++) {
		float r = ofMap(i, 0, 29, 19, 575);
		int newY = y + ofRandom(-jitter, jitter);
		ofDrawRectangle(500, newY, r, r);
		gui.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
