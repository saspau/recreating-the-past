#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	appName = ofFilePath::getBaseName(ofFilePath::getCurrentExePath());
	saveScreen = false;
	
	kern = -15;
	xIndent = 8;
	spacing = 17;
	yIndent = 16;
	r = 598;

	font.load("HelveticaBold.ttf", 100, true, true, true);
	
	gui.setup();
	gui.add(x.setup("indent", 204, 180, 210));
	gui.add(ys.setup("spacing", -276, -350, -250));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(233, 228, 217);
	ofSetColor(55, 47, 43);
	ofNoFill();

	string t = std::string((int('T') - 64), 'T');
	string h = std::string((int('H') - 64), 'H');
	string e = std::string((int('E') - 64), 'E');
	string c = std::string((int('C') - 64), 'C');
	string i = std::string((int('I') - 64), 'I');
	string y = std::string((int('Y') - 64), 'Y');
	string s = std::string((int('S') - 64), 'S');
	string l = std::string((int('L') - 64), 'L');
	string p = std::string((int('P') - 64), 'P');
	string b = std::string((int('B') - 64), 'B');
	string u = std::string((int('U') - 64), 'U');
	string o = std::string((int('O') - 64), 'O');
	string m = std::string((int('M') - 64), 'M');
	string n = std::string((int('N') - 64), 'N');
	string w = std::string((int('W') - 64), 'W');
	string a = std::string((int('A') - 64), 'A');
	string g = std::string((int('G') - 64), 'G');


	ofPushMatrix();

		// i drew everything in the bottom lefthard corner of the screen
		// just so it was easier to compare and calculate
		// now, i'm translating all of it (the square and text) to the proper place
		int X = 204;
		int Y = -276;
		ofTranslate(X, Y);

		// the square
		ofPushMatrix();
			ofTranslate(0, ofGetHeight() - r);
			ofDrawRectangle(0, 0, r, r);
		ofPopMatrix();

		// draw the letters!
		// T
		ofPushMatrix();
			ofTranslate(2, 0);
			drawLetterColumn(font, t, 1, 0.16, 0);
		ofPopMatrix();

		// H
		ofPushMatrix();
			ofTranslate(2, 0);
			drawLetterColumn(font, h, 2, 0.16, -4);
		ofPopMatrix();

		// E
		ofPushMatrix();
			ofTranslate(1, 0);
			drawLetterColumn(font, e, 3, 0.16, -3);
		ofPopMatrix();

		// C
		drawLetterColumn(font, c, 5, 0.32, -4);		// 5 because C is double the height
		
		// I
		drawLetterColumn(font, i, 6, 0.16, 13);

		// T
		drawLetterColumn(font, t, 7, 0.16, 0);

		// Y
		drawLetterColumn(font, y, 8, 0.16, -1);

		ofPushMatrix();
			ofTranslate(-8, 0);
			// S
			drawLetterColumn(font, s, 9, 0.067, 13);
		ofPopMatrix();


		ofPushMatrix();
			ofTranslate(-8, 0);

			// L
			drawLetterColumn(font, l, 10, 0.16, -2);

			// E
			drawLetterColumn(font, e, 11, 0.16, -3);

			// E
			drawLetterColumn(font, e, 12, 0.16, -3);

			// P
			drawLetterColumn(font, p, 13, 0.16, -3);

		ofPopMatrix();

		ofPushMatrix();
			ofTranslate(1, 0);
			// S
			drawLetterColumn(font, s, 13, 0.067, 13);
		ofPopMatrix();

		ofPushMatrix();
			ofTranslate(1, 0);

			// B
			drawLetterColumn(font, b, 14, 0.16, -1);

			// U
			drawLetterColumn(font, u, 15, 0.16, -3);

			// T
			drawLetterColumn(font, t, 16, 0.16, 0);

			// S
			ofPushMatrix();
				ofTranslate(1, 0);
				drawLetterColumn(font, s, 17, 0.16, -2);
			ofPopMatrix();

			ofTranslate(2, 0);

			// O
			drawLetterColumn(font, o, 18, 0.16, -4);

			// M
			drawLetterColumn(font, m, 19, 0.16, -2);

			// E
			drawLetterColumn(font, e, 20, 0.16, -3);

			// O
			drawLetterColumn(font, o, 21, 0.16, -4);

			// N
			drawLetterColumn(font, n, 22, 0.16, -3);

			// E
			drawLetterColumn(font, e, 23, 0.16, -3);

			// I
			drawLetterColumn(font, i, 24, 0.16, 13);

			ofPushMatrix();
				ofTranslate(-8, 0);
				// S
				drawLetterColumn(font, s, 25, 0.067, 13);
			ofPopMatrix();


			ofPushMatrix();
				ofTranslate(-8, 0);
				// W
				drawLetterColumn(font, w, 26, 0.16, -10);

				// A
				drawLetterColumn(font, a, 27, 0.16, 0);

				// T
				drawLetterColumn(font, t, 28, 0.16, 0);

				// C
				drawLetterColumn(font, c, 30, 0.32, -4);

				// H
				drawLetterColumn(font, h, 31, 0.16, -4);

				// I
				drawLetterColumn(font, i, 32, 0.16, 13);

				// N
				drawLetterColumn(font, n, 33, 0.16, -3);

				// G
				drawLetterColumn(font, g, 34, 0.16, -1);
			ofPopMatrix();

		ofPopMatrix();

	ofPopMatrix();

	//gui.draw();
}

// draws in bottom left corner
void ofApp::drawLetterColumn(ofTrueTypeFont font, string letters, int position, float scale, int kernShift) {

	ofPushMatrix();
		vector<ofPath> paths = font.getStringAsPoints(letters);
		ofTranslate(xIndent + position * spacing, ofGetHeight() - yIndent);
		ofRotateDeg(-90);
		ofScale(scale, scale);

		ofRectangle box = font.getStringBoundingBox(letters, 0, 0);
		//ofDrawRectangle(box);
		int medHeight = 96;			// font.stringHeight(t); (at full font size)

		for (int i = 0; i < paths.size(); i++) {
			ofTranslate(kern + kernShift, 0);
			paths[i].draw();
		}
	ofPopMatrix();

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
