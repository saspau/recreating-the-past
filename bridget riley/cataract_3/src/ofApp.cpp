#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	appName = ofFilePath::getBaseName(ofFilePath::getCurrentExePath());
	saveScreen = false;
	edgePadding = 50;

	gui.setup();
	gui.add(amp.setup("amp", 8, 5, 15));
	gui.add(phase.setup("phase", -0.12, -1.0, 1.0));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofColor white(242, 237, 252);
	ofColor red(182, 44, 26);
	ofColor blue(92, 90, 123);
	ofColor blueMax(63, 85, 146);

	ofBackground(white);
	
	ofPushMatrix();
	ofRotateDeg(-2);

	for (int j = 0; j < 400; j++) {
		if (j % 4 < 2) {
			ofSetColor(white);
		}
		else if (j % 4 == 2) {
			if (j > 100 && j < 250) {
				float pct = ofMap(j, 100, 249, 0, 1);
				ofColor r = blue.getLerped(red, pct);
				ofSetColor(r);
			}
			else if (j >= 250 && j < 350) {
				float pct = ofMap(j, 250, 349, 1, 0);
				ofColor r = blue.getLerped(red, pct);
				ofSetColor(r);
			}
			else {
				ofSetColor(blue);
			}
		}
		else {
			if (j > 100 && j < 250) {
				float pct = ofMap(j, 100, 249, 0, 1);
				ofColor r = blue.getLerped(blueMax, pct);
				ofSetColor(r);
			}
			else if (j >= 250 && j < 350) {
				float pct = ofMap(j, 250, 349, 1, 0);
				ofColor r = blue.getLerped(blueMax, pct);
				ofSetColor(r);
			}
			else {
				ofSetColor(blue);
			}
		}

		ofBeginShape();
		for (int i = 0; i < 200; i++) {
			float x = ofMap(i, 0, 199, 0 - edgePadding, ofGetWidth() + edgePadding);
			float y = amp * sin(4 * ofGetElapsedTimef() + i * 0.15 + j * phase) + ofMap(j, 0, 399, 0 - edgePadding, ofGetHeight() + edgePadding);
			ofVertex(x, y);
		}
		ofVertex(ofGetWidth() + edgePadding, ofGetHeight() + edgePadding);
		ofVertex(0, ofGetHeight() + edgePadding);
		ofEndShape(true);
	}
	ofPopMatrix();

	//gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') {
		saveScreen = true;

		if (saveScreen) {
			ofImage image;
			image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());

			image.save(appName + "_" + ofGetTimestampString() + ".png");
			saveScreen = false;
		}
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
