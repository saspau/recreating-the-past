#include "ofApp.h"


// TODO: play with camera/angles/z-index? size of trails?
// TODO: play with the shapes from past histories?
//--------------------------------------------------------------
void ofApp::setup() {

	pink = ofColor(237, 18, 136);
	beige = ofColor(253, 234, 199);
	teal = ofColor(89, 151, 136);
	orange = ofColor(237, 124, 33);
	gold = ofColor(251, 172, 0);
	cerulean = ofColor(0, 144, 174);
	red = ofColor(222, 82, 6);
	brown = ofColor(129, 82, 60);

	ofBackground(beige);
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetVerticalSync(true);
	//ofSetFrameRate(30);

	appName = ofFilePath::getBaseName(ofFilePath::getCurrentExePath());
	saveScreen = false;

	gui.setup();
	gui.add(thresh.setup("thresh", 50, 0, 255));
	gui.add(lag.setup("lag", 10, 1, 20));
	gui.add(gradientStep.setup("gradientStep", 0.005, 0.001, 0.01));
	gui.add(initialAlpha.setup("initialAlpha", 255, 100, 255));
	gui.add(alphaStep.setup("alphaStep", 3, 1, 10));
	gui.add(trailSize.setup("trailSize", 50, 0, 150));
	gui.add(maxGroups.setup("maxGroups", 5, 1, 10));
	gui.add(sampleSpacing.setup("sampleSpacing", 8, 1, 20));
	gui.add(smoothing.setup("smoothing", 1, 1, 10));
	gui.add(minFreq.setup("min", 0, 0, 63));
	gui.add(maxFreq.setup("max", 1, 0, 63));
	gui.add(band1.setup("band1", 0, 0, 128));
	gui.add(band2.setup("band2", 5, 0, 128));
	gui.add(band3.setup("band3", 58, 0, 128));

	// get these dynamically using directory path
	vector <string> gradientFiles = { "gradient_cool.png", "gradient_warm.png", "gradient_ocean.png", "gradient_shuga.png" };
	ofImage img;
	for (int i = 0; i < gradientFiles.size(); i++) {
		ofLoadImage(img, gradientFiles[i]);

		ofxColorGradient<ofColor> gradient;
		gradient.loadFromImage(img, 3);

		gradients.push_back(gradient);
	}


	song.loadSound("shuga.mp3");
	fftSmooth = new float [8192];
	for (int i = 0; i < 8192; i++) {
		fftSmooth[i] = 0;
	}

	bands = 128;
	//song.set	Loop(false);
	song.setVolume(0.3);

	player.load("input.mov");
	player.play();
	player.setLoopState(OF_LOOP_NORMAL);

	song.play();

}

//--------------------------------------------------------------
void ofApp::update() {

	ofSoundUpdate();

	float * value = ofSoundGetSpectrum(bands);
	for (int i = 0; i < bands; i++) {
		fftSmooth[i] *= 0.9f;
		if (fftSmooth[i] < value[i]) {
			fftSmooth[i] = value[i];
		}
	}

	player.update();
	if (player.isFrameNew()) {
		convertColor(player, camGray, CV_RGB2GRAY);
		camGray.update();

		threshImg.setFromPixels(camGray.getPixels());
		threshold(threshImg, (float)thresh, false); // set to true to invert
		threshImg.update();

		finder.setSortBySize(true);
		finder.findContours(threshImg);
	}

}

//--------------------------------------------------------------
void ofApp::draw() {
	//// background for right-hand panel (where the trails are drawn)
	//if (backgroundIdx == 0) {
	//	ofBackground(255);
	//}
	//else if (backgroundIdx == 1) {
	//	ofBackground(0);
	//}
	//else if (backgroundIdx == 2) {
	//	ofBackground(255);	// affects the color of the image
	//	camGray.draw(grabber.getWidth() + (margin * 2), margin);
	//}
	//else {
	//	ofBackground(255);	// affects the color of the image
	//	grabber.draw(grabber.getWidth() + (margin * 2), margin);
	//}

	ofSetRectMode(OF_RECTMODE_CENTER);

	// draw the live video input
	ofSetColor(beige);
	//grabber.draw(margin, margin);
	//player.draw(margin, margin, 640, 480);

	// affects the outline of the polyline
	ofSetColor(beige, 200);
	ofSetLineWidth(1.5);
	if (song.getIsPlaying()) {
		if (song.getPositionMS() < 57000) {

			ofPushMatrix();
			ofScale(1.5, 1.5);
			ofTranslate(200, 300);

			if (song.getPositionMS() > 14500) {
				drawFigure(gold, band1, 0, 1, 0, 200);
			}
			else {
				drawFigure(orange, band2, 0.001, .1, 0, 205);
			}
			//}

			ofTranslate(400, 0);
			//if (song.getIsPlaying()) {
			if (song.getPositionMS() > 14500) {
				drawFigure(gold, band1, 0, 1, 0, 200);
			}
			else {
				drawFigure(orange, band2, 0.001, .1, 0, 205);
			}
			//}

			ofTranslate(-100, 0);
			//if (song.getIsPlaying()) {
			drawFigure(orange, band2, 0.001, .1, 0, 205);
			//}

			ofTranslate(-200, 0);
			//if (song.getIsPlaying()) {
			drawFigure(orange, band2, 0.001, .1, 0, 205);
			//}

			ofTranslate(100, 0);
			//if (song.getIsPlaying()) {
			if (song.getPositionMS() > 28750) {
				drawFigure(cerulean, band3, 0.0003, 0.04, 50, 235);
			}
			else if (song.getPositionMS() > 14500) {
				drawFigure(gold, band1, 0, 1, 0, 200);
			}
			else {
				drawFigure(orange, band2, 0.001, .1, 0, 205);
			}
			//}

			ofPopMatrix();
		}


		else if (song.getPositionMS() < 88700) {
			ofSetRectMode(OF_RECTMODE_CORNER);
			ofPushMatrix();
			ofScale(1.5, 1.5);
			ofTranslate(100, 100);

			drawPathGroup(35);

			ofPopMatrix();

			if (song.getPositionMS() > 63000 && song.getPositionMS() < 64000 && !pPressed) {
				keyPressed('p');
				keyPressed('p');
				pPressed = true;
				cout << "1" << endl;
			}

			if (song.getPositionMS() > 64000) {
				pPressed = false;
				ofPushMatrix();
				ofScale(1.5, 1.5);
				ofTranslate(300, 300);

				drawPathGroup(70);

				ofPopMatrix();
			}

			if (song.getPositionMS() > 70000 && song.getPositionMS() < 71000 && !pPressed) {
				keyPressed('p');
				keyPressed('p');
				pPressed = true;
				cout << "2" << endl;
			}

			if (song.getPositionMS() > 71000) {
				pPressed = false;
				ofPushMatrix();
				ofScale(1.5, 1.5);
				ofTranslate(500, 100);

				drawPathGroup(100);

				ofPopMatrix();
			}

			if (song.getPositionMS() > 77000 && song.getPositionMS() < 78000 && !pPressed) {
				keyPressed('p');
				keyPressed('p');
				pPressed = true;
				cout << "3" << endl;
			}

			if (song.getPositionMS() > 78000) {
				pPressed = false;
				ofPushMatrix();
				ofScale(1.5, 1.5);
				ofTranslate(700, 300);

				drawPathGroup(150);

				ofPopMatrix();
			}
		}
		//else if (song.getPositionMS() )

	}



	// draw a little "pause" symbol in the top left
	//drawPause();


	//ofSetColor(255);
	//for (int i = minFreq; i < maxFreq; i++) {
	//	//cout << fftSmooth[i] << endl;
	//	//if (fftSmooth[i] >= minFreq && fftSmooth[i] <= maxFreq)
	//	ofCircle(ofGetWidth() / 2, ofGetHeight() / 2, -(fftSmooth[i] * 150));
	//	//float col = ofMap(fftSmooth[i], 0, 1, 50, 255);
	//	//ofSetColor(col);
	//}


	gui.draw();
}


void ofApp::drawFigure(ofColor color, int band, float min, float max, int alphaMin, int alphaMax) {
	ofSetRectMode(OF_RECTMODE_CENTER);

	// find contours
	ofPolyline line = finder.getPolyline(0);
	line = line.getResampledBySpacing(sampleSpacing);
	line = line.getSmoothed(smoothing);
	line.draw();

	ofPath path;

	// choose a gradient to color the path history
	//ofColor col = gradients[gradientIdx].getColorAtPercent(pct);
	ofColor col = color;
	col.a = ofMap(fftSmooth[band], min, max, alphaMin, alphaMax);
	cout << fftSmooth[band] << endl;

	//ofColor c = ofMap(fftSmooth[band], 0, 1, 100, 0);

	// determine which direction we're moving across the gradient
	if (pct >= 0.95) inc = false;
	if (pct <= 0.05) inc = true;

	// move across the gradient
	if (inc) pct += gradientStep;
	else pct -= gradientStep;

	path.setFillColor(col);

	//// convert the polyline to a path object
	for (int i = 0; i < line.getVertices().size(); i++) {
		path.curveTo(line.getVertices()[i]);
	}

	path.draw();
	//ofSetColor(col);
	//ofDrawRectangle(0, 0, 200, 200);

}

void ofApp::drawPathGroup(int trail) {
	ofSetColor(brown, 200);
	ofSetLineWidth(1.5);

	for (int i = 0; i < pathGroups.size(); i++) {
		bool play = true;
		if (groupPlayStatus.size() > 0) {
			play = groupPlayStatus[i];
		}
		if (play) {	// if group isn't paused (we want the drawing to keep animating)
			for (int j = 0; j < pathGroups[i].size(); j++) {
				ofColor pathCol = pathGroups[i][j].getFillColor();
				pathCol.a -= alphaStep;
				pathGroups[i][j].setFillColor(pathCol);
			}
		}
	}

	for (int i = 0; i < pathGroups.size(); i++) {
		for (int j = 0; j < pathGroups[i].size(); j += lag) {
			//ofPushMatrix();
			//ofScale(0.01 * j, 0.01 * j);
			pathGroups[i][j].draw();
			//ofPopMatrix();
		}
	}


	if (finder.size() > 0) {
		// keep updating the live path history if we're not paused
		// if we are paused, we'll keep redrawing the most recent history
		// comment out condition to continue seeing current trails even when paused
		if (!isPaused) {
			// find contours
			ofPolyline line = finder.getPolyline(0);
			line = line.getResampledBySpacing(sampleSpacing);
			line = line.getSmoothed(smoothing);
			line.draw();
			lines.push_back(line);


			ofPath path;

			// choose a gradient to color the path history
			ofColor col = gradients[3].getColorAtPercent(pct);
			col.a = initialAlpha;

			// determine which direction we're moving across the gradient
			if (pct >= 0.95) inc = false;
			if (pct <= 0.05) inc = true;

			// move across the gradient
			if (inc) pct += gradientStep;
			else pct -= gradientStep;

			path.setFillColor(col);

			// convert the polyline to a path object
			for (int i = 0; i < line.getVertices().size(); i++) {
				path.curveTo(line.getVertices()[i]);
			}

			paths.push_back(path);

			// gradually decrease the alpha for older paths
			for (int i = 0; i < paths.size(); i++) {
				ofColor pathCol = paths[i].getFillColor();
				pathCol.a -= alphaStep;
				paths[i].setFillColor(pathCol);
			}

			// draw the history
			for (int i = 0; i < paths.size(); i += lag) {
				paths[i].draw();
			}

			// erase the oldest part of the trail once it's gotten too long
			if (paths.size() > trail) {
				paths.erase(paths.begin());
				lines.erase(lines.begin());
			}
		}
	}
}


void ofApp::drawPause() {
	if (isPaused) {
		ofSetColor(100);
		ofSetLineWidth(5);
		ofDrawLine(20, 20, 20, 40);
		ofDrawLine(30, 20, 30, 40);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case '3':
		song.setPositionMS(55000);
		break;
	case '4':
		song.setPositionMS(86700);
		break;
	case 'b':
		song.setPositionMS(27750);
		break;
	}

	switch (key) {
	case '1':
		song.play();
		break;
	case '2':
		song.stop();
		break;
	}
	

	// reset the background we are diffing against
	if (key == ' ' || key == OF_KEY_CONTROL) {
		cout << song.getPositionMS() << endl;
	}

	if (key == OF_KEY_DEL) {

		if (!isPaused) {
			// delete everything and start from scratch
			paths = {};
			lines = {};
			pathGroups = {};
		}
		else {
			// just delete the history that we just added
			pathGroups.pop_back();
			groupPlayStatus.pop_back();
		}
	}

	// save a new history/drawing
	if (key == 'p' || key == OF_KEY_TAB) {
		isPaused = !isPaused;

		// only allow `maxGroups` number of paths in the vector (to prevent things from clogging up)
		if (isPaused) {
			if (pathGroups.size() == maxGroups) {
				pathGroups.erase(pathGroups.begin());
			}

			// add current history to vector of all paths
			pathGroups.push_back(paths);

			// switch color gradient
			gradientIdx = ++gradientIdx % gradients.size();

			// default to continue animating this group
			groupPlayStatus.push_back(true);
		}
	}

	// switch between animating and freezing the most recently added history
	if (key == OF_KEY_SHIFT) {
		if (isPaused) {
			playCurrent = !groupPlayStatus.back();
			groupPlayStatus.pop_back();
			groupPlayStatus.push_back(playCurrent);
		}
	}

	// switch to next color gradient
	if (key == OF_KEY_UP) {
		//gradientIdx = ++gradientIdx % gradients.size();
		//band = band + 1;
	}

	// switch to previous color gradient
	if (key == OF_KEY_DOWN) {
		//gradientIdx = --gradientIdx % gradients.size();
		//band = band - 1;
	}

	// switch to next background image/color
	//if (key == OF_KEY_UP) {
	//	backgroundIdx = ++backgroundIdx % 4;
	//}

	//// switch to previous background image/color
	//if (key == OF_KEY_DOWN) {
	//	backgroundIdx = MAX(--backgroundIdx % 4, 0);
	//}

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
