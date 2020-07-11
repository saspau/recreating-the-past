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
		
		void drawLetterColumn(ofTrueTypeFont font, string letters, int position, float scale, int kernShift);
		
		string appName;
		bool saveScreen;
		
		int kern;
		int xIndent;
		int spacing;
		int yIndent;
		int r;

		ofTrueTypeFont font;

		ofxIntSlider x;
		ofxIntSlider ys;
		ofxPanel gui;
};
