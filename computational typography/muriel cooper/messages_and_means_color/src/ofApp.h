#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void drawMeansMessages(ofTrueTypeFont font);

		string appName;
		bool saveScreen;

		const string MEANS = "MEANS";
		const string MESSAGES = "MESSAGES";

		// amount to shift each letter towards the previous one
		const int KERN = -7;
			

		ofEasyCam cam;
		ofTrueTypeFont font;
		ofImage img;

		ofxIntSlider leftMeansX;
		ofxIntSlider leftMsgX;
		ofxIntSlider rightMeansX;
		ofxIntSlider rightMsgX;

		ofxIntSlider leftMeansY;
		ofxIntSlider leftMsgY;
		ofxIntSlider rightMeansY;
		ofxIntSlider rightMsgY;

		ofxIntSlider gr;
		ofxIntSlider gg;
		ofxIntSlider gb;
		ofxIntSlider ga;

		ofxIntSlider pr;
		ofxIntSlider pg;
		ofxIntSlider pb;
		ofxIntSlider pa;

		ofxIntSlider rr;
		ofxIntSlider rg;
		ofxIntSlider rb;
		ofxIntSlider ra;

		ofColor green;
		ofColor pink;
		ofColor purple;

		ofxPanel gui;
		
};
