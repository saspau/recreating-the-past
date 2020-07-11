#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	appName = ofFilePath::getBaseName(ofFilePath::getCurrentExePath());
	saveScreen = false;

	gui.setup();
	gui.add(seed.setup("seed", 2050, 0, 10000));
	gui.add(xjitter.setup("xjitter", 8, 0, 30));
	gui.add(yjitter.setup("yjitter", 15, 0, 30));
	gui.add(swap.setup("swap", 0.97, 0.5, 1.0));
	//gui.add(width.setup("width", 56, 50, 75));
	//gui.add(length.setup("length", 61, 50, 75));
	//gui.add(wMin.setup("minwidth", 275, 250, 300));
	//gui.add(wMax.setup("maxwidth", 725, 700, 750));
	//gui.add(hMin.setup("minheight", 370, 350, 400));
	//gui.add(hMax.setup("maxHeight", 880, 850, 900));
	gui.add(rSat.setup("redSat", 220, 220, 255));
	gui.add(rA.setup("redAlpha", 227, 150, 250));
	gui.add(oSat.setup("orSat", 240, 220, 255));
	gui.add(oA.setup("orAlpha", 212, 150, 250));

	red.r = 250;
	red.g = 94;
	red.b = 74;

	orange.r = 246;
	orange.g = 143;
	orange.b = 45;

	// thoughts/questions:
	// paint/ink/paper texture?
	// how much jitter from side to side? up and down? same or different?
	// achieving the right combination of alpha/saturation? what other color attributes could be adjusted?
	// all of the reds appear to be drawn on top of the oranges
	// what percentage of swaps happen in the lower half?
	// balance between size of shapes, size of canvas (squishing the shapes together), and jitter

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(232, 223, 217);
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofSeedRandom(mouseX*100);
	bool isRed;

	int width = 56;
	int length = 61;

	red.a = rA; //227, no sat
	//red.setSaturation(rSat);

	orange.a = oA; //212, no sat
	//orange.setSaturation(oSat);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			float x = ofMap(i, 0, 9, 275, 725);
			float y = ofMap(j, 0, 9, 370, 880);

			if (j < 4) {
				if (j % 2 == 0) {
					if (i % 2 == 0) {
						ofSetColor(red);
						isRed = true;
					}
					else {
						ofSetColor(orange);
						isRed = false;
					}

				}
				else {
					if (i % 2 == 0) {
						ofSetColor(orange);
						isRed = false;
					}
					else {
						ofSetColor(red);
						isRed = true;
					}
				}

			}
			else {
				if (i % 2 == 0) {
					ofSetColor(orange);
					isRed = false;
				}
				else {
					ofSetColor(red);
					isRed = true;
				}
				if (ofRandom(0, 1) > swap) {
					if (isRed) ofSetColor(orange);
					else ofSetColor(red);
					isRed = !isRed;
				}
			}

			int newX = x + ofRandom(-xjitter, xjitter);
			int newY = y + ofRandom(-yjitter, yjitter);

			ofEnableBlendMode(OF_BLENDMODE_MULTIPLY); // magically puts all reds on top of oranges
			ofDrawRectangle(newX, newY, width, length);

			//gui.draw();
		}
	}
}

void ofApp::setColor(ofColor color, bool& isRed) {
	ofSetColor(color);
	if (color == red) {
		isRed = true;
	}
	else {
		isRed = false;
	}
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
