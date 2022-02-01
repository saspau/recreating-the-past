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

		void drawBasicSquare(ofColor color);
		void drawChevron(ofColor chevronColor);
		void drawHorizontalChevron(ofColor chevronColor);
		void flipXAxis();
		void flipYAxis();

		string appName;
		bool saveScreen;
		int frameCounter = 0;

		int innerWidth, innerHeight, numSquares;
		float xPadding, yPadding, length;
		
		ofColor cream, red, blue;
};
