#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	appName = ofFilePath::getBaseName(ofFilePath::getCurrentExePath());
	saveScreen = false;

	innerWidth = 462;
	innerHeight = 574;

	xPadding = (ofGetWidth() - innerWidth) / 2;
	yPadding = (ofGetHeight() - innerHeight) / 2;

	numSquares = 31; // the smallest square
	length = innerWidth / numSquares;
	length += .5;

	cream.r = 239;
	cream.g = 232;
	cream.b = 226;

	red.r = 188;
	red.g = 36;
	red.b = 9;

	blue.r = 36;
	blue.g = 66;
	blue.b = 181;

	//ofSetFrameRate(1);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSeedRandom(mouseX);

	ofBackground(cream);
	
	ofPushMatrix();
		ofTranslate(xPadding, yPadding);


		ofSetColor(255);
		ofPushMatrix();
		ofDrawRectangle(0, 0, innerWidth, innerHeight);
		ofPopMatrix();

		// top left quadrant
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 10; j++) {
				float x = i * length * 2;
				float y = j * length * 2;

				ofPushMatrix();
					ofTranslate(x, y);

					if ((i + j) % 2 == 0) {
						if (ofRandom(1) > .5) {
							flipYAxis();
						}
						drawChevron(red);
					}
					else {
						if (ofRandom(1) > .5) {
							flipXAxis();
						}
						drawHorizontalChevron(red);
					}

				ofPopMatrix();
			}
		}

		// top right quadrant
		for (int i = 8; i < 16; i++) {
			for (int j = 0; j < 10; j++) {
				float x = i * length * 2;
				float y = j * length * 2;
			
				ofPushMatrix();
					ofTranslate(x, y);
					if ((i + j) % 2 == 0) {
						if (ofRandom(1) > .5) {
							flipYAxis();
						}
						drawChevron(blue);
					}
					else {
						if (ofRandom(1) > .5) {
							flipXAxis();
						}
						drawHorizontalChevron(blue);
					}
			
				ofPopMatrix();
			}
		}

		// bottom left quadrant
		for (int i = 0; i < 8; i++) {
			for (int j = 10; j < 20; j++) {
				float x = i * length * 2;
				float y = j * length * 2;
			
				ofPushMatrix();
					ofTranslate(x, y);

					if ((i + j) % 2 != 0) {
						if (ofRandom(1) > .5) {
							flipYAxis();
						}

						drawChevron(blue);
					}
					else {
						if (ofRandom(1) > .5) {
							flipXAxis();
						}
						drawHorizontalChevron(blue);
					}

				ofPopMatrix();
			}
		}

		// bottom right quadrant
		for (int i = 8; i < 16; i++) {
			for (int j = 10; j < 20; j++) {
				float x = i * length * 2;
				float y = j * length * 2;
			
				ofPushMatrix();
					ofTranslate(x, y);

					if ((i + j) % 2 != 0) {
						if (ofRandom(1) > .5) {
							flipYAxis();
						}
						drawChevron(red);
					}
					else {
						if (ofRandom(1) > .5) {
							flipXAxis();
						}
						drawHorizontalChevron(red);
					}

				ofPopMatrix();
			}
		}
		


	ofPopMatrix();


}

void ofApp::drawBasicSquare(ofColor color) {

	ofColor opposite;

	if (color == red) {
		opposite = blue;
	}
	else {
		opposite = red;
	}

	// draw left right triangle
	ofSetColor(color);
	ofBeginShape();
		ofVertex(0, 0);
		ofVertex(0, length);
		ofVertex(length, length);
	ofEndShape(true);

	// draw right right triangle
	ofSetColor(opposite);
	ofBeginShape();
		ofVertex(0, 0);
		ofVertex(length, 0);
		ofVertex(length, length);
	ofEndShape(true);

}

// draw a downward-facing chevron (like a V)
void ofApp::drawChevron(ofColor chevronColor) {

	// top left
	drawBasicSquare(chevronColor);

	// top right
	ofPushMatrix();
		ofTranslate(length * 2, 0);
		ofScale(-1, 1);
		drawBasicSquare(chevronColor);
	ofPopMatrix();

	// bottom left
	ofPushMatrix();
		ofTranslate(length, length * 2);
		ofScale(-1, -1);
		drawBasicSquare(chevronColor);
	ofPopMatrix();

	// bottom right
	ofPushMatrix();
		ofTranslate(length, length * 2);
		ofScale(1, -1);
		drawBasicSquare(chevronColor);
	ofPopMatrix();

}

void ofApp::drawHorizontalChevron(ofColor chevronColor) {
	ofPushMatrix();
		ofRotateDeg(90);
		ofTranslate(0, -length * 2);
		drawChevron(chevronColor);
	ofPopMatrix();
}

void ofApp::flipXAxis() {
	ofTranslate(length * 2, 0);
	ofScale(-1, 1);
}

void ofApp::flipYAxis() {
	ofTranslate(0, length * 2);
	ofScale(1, -1);
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
