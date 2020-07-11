#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	appName = ofFilePath::getBaseName(ofFilePath::getCurrentExePath());
	saveScreen = false;
	
	gui.setup();
	gui.add(r.setup("r", 0, 0, 255));
	gui.add(g.setup("g", 0, 0, 255));
	gui.add(b.setup("b", 0, 0, 255));
	gui.add(min.setup("min", -16, -50, 0));
	gui.add(max.setup("max", 10, 0, 50));
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSeedRandom(mouseX * 5000);

	ofBackground(219, 219, 227);
	ofSetLineWidth(1.3);
	ofNoFill();

	const int RADIUS = 25;		// starting radius of the square
	const int JITTER = 15;		// the amount we're allowing to shift the center of the shape
	const int MAX_QUADS = 25;	//
	const int ALPHA = 200;

	ofColor teal(0, 160, 160, ALPHA);
	ofColor blue(0, 72, 150, ALPHA);
	ofColor purple(97, 67, 157, ALPHA);
	ofColor orange(200, 135, 99, ALPHA);
	ofColor black(24, 28, 29, 180);			// looked too dark using the same alpha as the rest

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			float x = ofMap(i, 0, 7, 200, 600);
			float y = ofMap(j, 0, 7, 200, 600);

			/*
			counts/rough percentages of colors
				teal: 22/64 = .34375
				orange: 12/64 = .1875
				purple: 14/64 = .21875
				blue: 11/64 = .171975
				black: 4/64 = .0625
			*/
			float rand = ofRandom(0, 1);

			if (rand < 0.34) {
				ofSetColor(teal);
			}
			else if (rand < 0.55) {
				ofSetColor(purple);
			}
			else if (rand < 0.73) {
				ofSetColor(orange);
			}
			else if (rand < 0.9) {
				ofSetColor(blue);
			}
			else {
				ofSetColor(black);
			}

			ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);

			for (int k = 0; k < MAX_QUADS; k++) {
				int newX = x + ofRandom(-JITTER, JITTER);
				int newY = y + ofRandom(-JITTER, JITTER);

				ofBeginShape();

				// bottom left
				ofVertex(newX - (RADIUS + ofRandom(min, max)), newY + (RADIUS + ofRandom(min, max)));

				// bottom right
				// i liked how the bottom right corners were protruding out for the rightmost column,
				// so let the points extend further out
				if (i == 7) {
					ofVertex(newX + (RADIUS + ofRandom(min, max + JITTER)), newY + (RADIUS + ofRandom(min, max)));
				}
				else {
					ofVertex(newX + (RADIUS + ofRandom(min, max)), newY + (RADIUS + ofRandom(min, max)));
				}

				// top right
				ofVertex(newX + (RADIUS + ofRandom(min, max)), newY - (RADIUS + ofRandom(min, max)));

				//top left
				ofVertex(newX - (RADIUS + ofRandom(min, max)), newY - (RADIUS + ofRandom(min, max)));

				ofEndShape(true);

				//gui.draw();
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	saveScreen = true;

	if (saveScreen) {
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());

		image.save(appName + "_" + ofGetTimestampString() + ".png");
		saveScreen = false;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
