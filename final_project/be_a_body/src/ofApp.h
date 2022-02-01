#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxColorGradient.h"

using namespace ofxCv;

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void drawFigure(ofColor color, int band, float min, float max, int alphaMin, int alphaMax);
	void drawBoundedFigure(ofColor color, int band, float min, float max, int alphaMin, int alphaMax);
	void drawPathGroup(int trail);
	void drawBars(int trail);
	void drawPause();

	const int WIDTH = 848;
	const int HEIGHT = 480;
	int margin = 200;

	float pct = 0.0;
	bool inc = true;

	vector <float> scaleFactors;
	float scaleStep = 0.5;

	bool isPaused = false;
	bool saveScreen;
	string appName;

	vector <ofPolyline> lines;
	vector <ofPath> paths;
	vector <vector <ofPath>> pathGroups;
	vector <bool> groupPlayStatus;
	bool playCurrent = true;

	vector <ofxColorGradient <ofColor>> gradients;
	int gradientIdx = 0;

	ofVideoPlayer player;
	ofVideoPlayer player2;
	ofImage camGray;
	ofImage bgGray;
	ofImage diffImg;
	ofImage threshImg;
	ContourFinder finder;
	bool bRecordBg = false;
	int backgroundIdx = 0;

	ofxPanel gui;
	ofxIntSlider thresh;
	ofxIntSlider lag;
	ofxFloatSlider gradientStep;
	ofxIntSlider initialAlpha;
	ofxIntSlider alphaStep;
	ofxIntSlider trailSize;
	ofxIntSlider maxGroups;

	ofxIntSlider sampleSpacing;
	ofxIntSlider smoothing;

	ofEasyCam cam;

	ofSoundPlayer song;
	float * fftSmooth;
	int bands;

	ofxIntSlider minFreq;
	ofxIntSlider maxFreq;
	ofxIntSlider band1;
	ofxIntSlider band2;
	ofxIntSlider band3;

	ofColor pink, beige, teal, gold, orange, cerulean, red, brown, lime, lightPink, lighterPink, peach;

	bool pPressed = false;

	int numBars = 128;
	vector <ofRectangle> bars;

	ofxFloatSlider t;

	ofPoint leftSmoothed;
	ofPoint leftSmoothed2;
	ofPoint leftSmoothed3;
	ofPoint leftSmoothed4;
	ofPoint rightSmoothed;
	ofPoint rightSmoothed2;
	ofPoint rightSmoothed3;
	ofPoint rightSmoothed4;

	ofxIntSlider xMove;
	ofxIntSlider yMove;

	vector <string> clips;
	int clipIdx = 0;
	int currentIdx = 0;
	bool loadNext = false;

	vector <ofPoint> leftCircles;
	vector <ofPoint> rightCircles;

};
