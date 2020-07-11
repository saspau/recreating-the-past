#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofPixels.h"

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
		void setColor(ofColor color, bool& isRed);

		string appName;
		bool saveScreen;
		
		ofxFloatSlider seed;
		ofxIntSlider xjitter;
		ofxIntSlider yjitter;
		ofxFloatSlider swap;
		//ofxIntSlider width;
		//ofxIntSlider length;
		/*ofxIntSlider wMin;
		ofxIntSlider wMax;
		ofxIntSlider hMin;
		ofxIntSlider hMax;*/
		ofxIntSlider rSat;
		ofxIntSlider rA;
		ofxIntSlider oA;
		ofxIntSlider oSat;
		ofxPanel gui;

		ofColor red;
		ofColor orange;

		ofImage grain;
};
