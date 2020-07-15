#pragma once

#include "ofMain.h"

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
		
    ofImage original;
    ofImage saver;
    ofImage drawer;
	
	int thresh = 1;

	int position = 0;

	ofVideoGrabber grabber;

	ofImage newImage;
	ofImage newImage2;

	ofImage imgGray;
	ofImage imgColor;

	vector <ofImage> images;

	ofEasyCam cam;

	ofShader shader;
	ofShader shader2;
	ofShader shader3;

	bool isPaused = false;
	bool stopFlicker = false;

	int whereToSkip;
	int howMuchToSkip;
};
