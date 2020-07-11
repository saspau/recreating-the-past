#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	appName = ofFilePath::getBaseName(ofFilePath::getCurrentExePath());
	saveScreen = false;

	//img.load("original-crop.jpg");
	font.load("HelveticaBold.ttf", 100, true, true, true);

	gui.setup();

	// 
	gui.add(leftMeansX.setup("leftMeansX", 110, 110, 130));
	gui.add(leftMsgX.setup("leftMsgX", 20, 20, 40));
	gui.add(rightMeansX.setup("rightMeansX", 880, 870, 890));
	gui.add(rightMsgX.setup("rightMsgX", 536, 535, 560));

	gui.add(leftMeansY.setup("leftMeansY", -132, -120, -140));
	gui.add(leftMsgY.setup("leftMsgY", 0, -10, 10));
	gui.add(rightMeansY.setup("rightMeansY", 100, 90, 110));
	gui.add(rightMsgY.setup("rightMsgY", 230, 220, 240));

	// green sliders
	gui.add(gr.setup("gr", 0, 0, 255));
	gui.add(gg.setup("gg", 80, 0, 255));
	gui.add(gb.setup("gb", 28, 0, 255));
	gui.add(ga.setup("ga", 60, 0, 255));

	// pink sliders
	gui.add(pr.setup("pr", 255, 0, 255));
	gui.add(pg.setup("pg", 25, 0, 255));
	gui.add(pb.setup("pb", 0, 0, 255));
	gui.add(pa.setup("pa", 123, 0, 255));

	// purple sliders
	gui.add(rr.setup("rr", 48, 0, 255));
	gui.add(rg.setup("rg", 0, 0, 255));
	gui.add(rb.setup("rb", 95, 0, 255));
	gui.add(ra.setup("ra", 57, 0, 255));

	ofSetBackgroundAuto(true);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	//ofDisableBlendMode();
	//ofDisableAlphaBlending();

	green.r = gr;
	green.g = gg;
	green.b = gb;
	green.a = ga;

	purple.r = rr;
	purple.g = rg;
	purple.b = rb;
	purple.a = ra;

	pink.r = pr;
	pink.g = pg;
	pink.b = pb;
	pink.a = pa;

	ofColor background(28, 13, 9, 50);
	ofBackground(background);

	// uncomment to display the original photo in the background
	//ofSetColor(255, 255, 255, 100);
	//img.draw(0, 0, 900, 900);
	
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	for (int i = 0; i < 6; i++) {
		// green
		ofPushMatrix();
			ofSetColor(green);
			ofRotateDeg(45);
			drawMeansMessages(font);
		ofPopMatrix();

		// purple
		ofPushMatrix();
			ofSetColor(purple);
			ofTranslate(900, 0);
			ofRotateDeg(135);
			drawMeansMessages(font);
		ofPopMatrix();

		//pink
		ofPushMatrix();
			ofSetColor(pink);
			ofTranslate(0, 900);
			ofRotateDeg(-45);
			drawMeansMessages(font);
		ofPopMatrix();
	}

	//cam.end();

	//gui.draw();
}

/// draws one "set" of MEANS/MESSAGES (e.g., the green set) unrotated
void ofApp::drawMeansMessages(ofTrueTypeFont font){

	// top left (when font is right-side up)
	ofPushMatrix();
		vector<ofPath> leftMeans = font.getStringAsPoints(MEANS);
		ofTranslate(leftMeansX, leftMeansY);
		for (int i = 0; i < leftMeans.size(); i++) {
			ofTranslate(KERN, 0);
			leftMeans[i].draw();
		}
	ofPopMatrix();

	// top left
	ofPushMatrix();
		ofTranslate(leftMsgX, leftMsgY);
		vector<ofPath> leftMsg = font.getStringAsPoints(MESSAGES);
		for (int i = 0; i < leftMsg.size(); i++) {
			ofTranslate(KERN, 0);
			leftMsg[i].draw();
		}
	ofPopMatrix();

	// bottom right
	ofPushMatrix();
		ofTranslate(rightMeansX, rightMeansY);
		vector<ofPath> rightMeans = font.getStringAsPoints(MEANS);
		for (int i = 0; i < rightMeans.size(); i++) {
			ofTranslate(KERN, 0);
			rightMeans[i].draw();
		}
	ofPopMatrix();

	// bottom right
	ofPushMatrix();
		ofTranslate(rightMsgX, rightMsgY);
		vector<ofPath> rightMsg = font.getStringAsPoints(MESSAGES);
		for (int i = 0; i < rightMsg.size(); i++) {
			ofTranslate(KERN, 0);
			rightMsg[i].draw();
		}
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// TODO: fix screen capture. currently isn't capturing all colors/layers properly.
	saveScreen = true;

	if (saveScreen) {
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());

		image.save(appName + "_" + ofGetTimestampString() + ".png");
		saveScreen = false;
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
