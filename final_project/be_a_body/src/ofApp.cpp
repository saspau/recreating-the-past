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
	lime = ofColor(201, 201, 40);
	lightPink = ofColor(248, 120, 120);
	lighterPink = ofColor(255, 199, 199);
	peach = ofColor(255, 200, 169);

	ofBackground(beige);
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetVerticalSync(true);
	//ofSetFrameRate(30);

	appName = ofFilePath::getBaseName(ofFilePath::getCurrentExePath());
	saveScreen = false;

	gui.setup();
	gui.add(thresh.setup("thresh", 80, 0, 255));
	gui.add(lag.setup("lag", 10, 1, 50));
	gui.add(gradientStep.setup("gradientStep", 0.005, 0.001, 0.01));
	gui.add(initialAlpha.setup("initialAlpha", 255, 100, 255));
	gui.add(alphaStep.setup("alphaStep", 7, 1, 10));
	gui.add(trailSize.setup("trailSize", 50, 0, 150));
	gui.add(maxGroups.setup("maxGroups", 5, 1, 10));
	gui.add(sampleSpacing.setup("sampleSpacing", 6, 1, 20));
	gui.add(smoothing.setup("smoothing", 1, 1, 10));
	gui.add(minFreq.setup("min", 0, 0, 63));
	gui.add(maxFreq.setup("max", 1, 0, 63));
	gui.add(band1.setup("band1", 0, 0, 128));
	gui.add(band2.setup("band2", 6, 0, 128));
	gui.add(band3.setup("band3", 58, 0, 128));
	gui.add(t.setup("time", 0.75, 0.0, 3.0));
	gui.add(xMove.setup("x", 3300, 0, 4000));
	gui.add(yMove.setup("y", -180, -1000, 3000));

	// get these dynamically using directory path
	vector <string> gradientFiles = { "gradient_cool.png", "gradient_warm.png", "gradient_ocean.png", "gradient_shuga.png" };
	ofImage img;
	for (int i = 0; i < gradientFiles.size(); i++) {
		ofLoadImage(img, gradientFiles[i]);

		ofxColorGradient<ofColor> gradient;
		gradient.loadFromImage(img, 3);

		gradients.push_back(gradient);
	}


	clips = { "pt1.mov", "pt2.mov" ,"pt3.mov" ,"pt4.mov" ,"pt5.mov" ,"pt6.mov" };

	song.loadSound("shuga.mp3");
	fftSmooth = new float [8192];
	for (int i = 0; i < 8192; i++) {
		fftSmooth[i] = 0;
	}

	bands = 128;
	song.setVolume(0.3);

	player.load("pt1.mov");
	player.setLoopState(OF_LOOP_NONE);

}

//--------------------------------------------------------------
void ofApp::update() {
	if (loadNext) {
		player.load(clips[clipIdx]);
		currentIdx = clipIdx;
		float pos;
		if (clipIdx == 0) {
			pos = 0.02;
			song.play();
		}
		else if (clipIdx == 1) {
			pos = 0.04;
		}
		else if (clipIdx == 2) {
			pos = 0.047;
		}
		else if (clipIdx == 3) {
			pos = 0.12;
		}
		else if (clipIdx == 4) {
			pos = 0.05;
		}
		else if (clipIdx == 5) {
			pos = 0.045; //.045
			//pos = 0.0;
		}
		player.setPosition(pos);
		player.play();
		loadNext = false;
	}


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
		threshold(threshImg, (float)thresh, true); // set to true to invert
		threshImg.update();

		finder.setSortBySize(true);
		finder.findContours(threshImg);
	}

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetRectMode(OF_RECTMODE_CENTER);

	// draw the live video input
	ofSetColor(beige);
	//grabber.draw(margin, margin);
	//player.draw(margin, margin, 640, 480);

	// affects the outline of the polyline
	ofSetColor(beige, 200);
	ofSetLineWidth(1.5);
	if (song.getIsPlaying()) {

		if (song.getPositionMS() > 56200 && song.getPositionMS() < 57000) {
			clipIdx = 1;
			if (clipIdx != currentIdx) {
				player.close();
				loadNext = true;
			}
		}
		// clones
		else if (song.getPositionMS() < 57000) {

			ofPushMatrix();
			ofScale(0.35, 0.35);
			ofTranslate(3680, 60);
			ofRotateDeg(90);

			if (song.getPositionMS() > 14500) {
				drawFigure(gold, band1, 0, 1, 0, 200);
			}
			else {
				drawFigure(orange, band2, 0.001, .1, 0, 205);
			}
			//}

			ofTranslate(0, 1600);
			//if (song.getIsPlaying()) {
			if (song.getPositionMS() > 14500) {
				drawFigure(gold, band1, 0, 1, 0, 200);
			}
			else {
				drawFigure(orange, band2, 0.001, .1, 0, 205);
			}
			//}

			ofTranslate(0, -400);
			//if (song.getIsPlaying()) {
			drawFigure(orange, band2, 0.001, .1, 0, 205);
			//}

			ofTranslate(0,-800);
			//if (song.getIsPlaying()) {
			drawFigure(orange, band2, 0.001, .1, 0, 205);
			//}

			ofTranslate(0, 400);
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

		else if (song.getPositionMS() > 88100 && song.getPositionMS() < 88700) {
			clipIdx = 2;
			if (clipIdx != currentIdx) {
				player.close();
				loadNext = true;
			}
		}
		// trails
		else if (song.getPositionMS() < 88700) {
			
			if (player.isLoaded()) {
				ofSetRectMode(OF_RECTMODE_CORNER);

				ofPushMatrix();
				ofScale(0.25, 0.25);
				ofTranslate(2000, -100);
				ofRotateDeg(90);
				drawPathGroup(40);

				if (song.getPositionMS() > 63000 && song.getPositionMS() < 64000 && !pPressed) {
					keyPressed('p');
					keyPressed('p');
					pPressed = true;
				}

				if (song.getPositionMS() > 64000) {
					pPressed = false;
					ofTranslate(1200, -1000);

					drawPathGroup(40);
				}

				if (song.getPositionMS() > 70000 && song.getPositionMS() < 71000 && !pPressed) {
					keyPressed('p');
					keyPressed('p');
					pPressed = true;
				}

				if (song.getPositionMS() > 71000) {
					pPressed = false;
					ofTranslate(-1200, -1000);

					drawPathGroup(40);
				}

				if (song.getPositionMS() > 77000 && song.getPositionMS() < 78000 && !pPressed) {
					keyPressed('p');
					keyPressed('p');
					pPressed = true;
				}

				if (song.getPositionMS() > 78000) {
					pPressed = false;
					ofTranslate(1200, -1000);

					drawPathGroup(40);
				}
				ofPopMatrix();
			}
		}

		else if (song.getPositionMS() > 116000 && song.getPositionMS() < 116700) {
			clipIdx = 3;
			if (clipIdx != currentIdx) {
				player.close();
				loadNext = true;
			}
		}
		
		// bounded box
		else if (song.getPositionMS() < 116000) {

			if (player.isLoaded()) {
				ofPushMatrix();
				ofScale(0.4, 0.4);
				ofTranslate(2540, -80);
				ofRotateDeg(90);

				drawBoundedFigure(lighterPink, band2, 0, 1, 0, 200);
				ofPopMatrix();
			}
		}

		else if (song.getPositionMS() > 130000 && song.getPositionMS() < 130500) {
			clipIdx = 4;
			if (clipIdx != currentIdx) {
				player.close();
				loadNext = true;
			}
		}

		// balls
		else if (song.getPositionMS() < 130500) {
			if (player.isLoaded()) {
				ofPushMatrix();
				ofScale(0.4, 0.4);
				ofTranslate(2540, -80);
				ofRotateDeg(90);
				if (finder.size() > 0) {
					ofSetRectMode(OF_RECTMODE_CENTER);

					float time = ofGetElapsedTimef();

					// find contours
					ofPolyline line = finder.getPolyline(0);
					line = line.getResampledBySpacing(sampleSpacing);
					line = line.getSmoothed(smoothing);
					line.draw();

					ofPath path;

					// choose a gradient to color the path history
					//ofColor col = gradients[gradientIdx].getColorAtPercent(pct);
					ofColor col = lime;

					//cout << fftSmooth[band] << endl;

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

					ofRectangle box = line.getBoundingBox();
					ofPoint left, right;
					ofPoint left2, right2;
					ofPoint left3, right3;
					ofPoint left4, right4;
					for (int i = 0; i < line.size(); i++) {
						//if (line[i].x < (box.getCenter().x - box.width * 0.2)) {
							if (i == 0) {
								left = line[i];
								left2 = line[i];
								left3 = line[i];
								left4 = line[i];
								right = line[i];
								right2 = line[i];
								right3 = line[i];
								right4 = line[i];
							}
							else {
								if (line[i].y < left.y) {
									left = line[i];
									left2 = ofPoint(left.x + ofRandom(-10, 10), left.y + ofRandom(-10, 10));
									left3 = ofPoint(left.x + ofRandom(-20, 20), left.y + ofRandom(-20, 20));
									left4 = ofPoint(left.x + ofRandom(-30, 30), left.y + ofRandom(-30, 30));
								}
								if (line[i].y > right.y) {
									right = line[i];
									right2 = ofPoint(right.x + ofRandom(-10, 10), right.y + ofRandom(-10, 10));
									right3 = ofPoint(right.x + ofRandom(-20, 20), right.y + ofRandom(-20, 20));
									right4 = ofPoint(right.x + ofRandom(-30, 30), right.y + ofRandom(-30, 30));
								}
							}
						//}
					}

					leftSmoothed = 0.9 * leftSmoothed + 0.1 * left;
					leftSmoothed2 = 0.85 * leftSmoothed2 + 0.15 * left2;
					leftSmoothed3 = 0.95 * leftSmoothed3 + 0.05 * left3;
					leftSmoothed4 = 0.97 * leftSmoothed4 + 0.03 * left4;

					rightSmoothed = 0.9 * rightSmoothed + 0.1 * right;
					rightSmoothed2 = 0.85 * rightSmoothed2 + 0.15 * right2;
					rightSmoothed3 = 0.95 * rightSmoothed3 + 0.05 * right3;
					rightSmoothed4 = 0.97 * rightSmoothed4 + 0.03 * right4;


					ofSetColor(red);
					ofDrawCircle(leftSmoothed, 20);
					ofDrawCircle(rightSmoothed, 20);

					ofSetColor(gold);
					ofDrawCircle(leftSmoothed2, 16);
					ofDrawCircle(rightSmoothed2, 16);

					ofSetColor(pink);
					ofDrawCircle(leftSmoothed3, 12);
					ofDrawCircle(rightSmoothed3, 12);

					ofSetColor(orange);
					ofDrawCircle(leftSmoothed4, 8);
					ofDrawCircle(rightSmoothed4, 8);

				}
				ofPopMatrix();
			}

		}

		else if (song.getPositionMS() > 158800 && song.getPositionMS() < 159300) {
			clipIdx = 5;
			if (clipIdx != currentIdx) {
				player.close();
				loadNext = true;
			}
		}

		// bars
		else if (song.getPositionMS() < 159300) {
			if (player.isLoaded()) {
				ofPushMatrix();
				ofScale(0.3, 0.3);
				ofTranslate(3265, 280);
				ofRotateDeg(90);

				ofPolyline line = finder.getPolyline(0);
				line = line.getResampledBySpacing(sampleSpacing);
				line = line.getSmoothed(smoothing);
				line.draw();

				ofPath path;

				// choose a gradient to color the path history
				//ofColor col = gradients[gradientIdx].getColorAtPercent(pct);
				ofColor col = lighterPink;
				//col.a = 200;

				//cout << fftSmooth[band] << endl;

				path.setFillColor(col);

				// convert the polyline to a path object
				for (int i = 0; i < line.getVertices().size(); i++) {
					path.curveTo(line.getVertices()[i]);
				}

				path.draw();
				ofPopMatrix();
			}

			float time = ofGetElapsedTimef();
			ofSetColor(lime);
			for (int i = 0; i < 64; i++) {
				// center the drawing
				float xorig = ofGetWidth() / 2;
				float yorig = ofGetHeight() / 2;

				// how large the shape is
				float radius = 380; //+ 75 * sin(time * rScale); // can make the shape radius pulsate?

				// evenly space out the circles
				float theta = i * (TWO_PI / 64);
				float angle = -0.5*time + theta; //-.7

				// calculate the coordinates of the circle
				float x = xorig + radius * cos(angle);
				float y = ofGetHeight() - (yorig + radius * sin(angle));
				//float size = ofMap(fftSmooth[11], .005, .05, 5, 25);
				float size = ofMap(fftSmooth[i], .001, .1, 5, 15);
				ofDrawCircle(x, y, size);
			}

		}
		else {
			if (player.isLoaded()) {
				int pos = song.getPositionMS();

				ofPushMatrix();
				ofScale(0.5, 0.5);
				ofTranslate(xMove, yMove);
				ofRotateDeg(90);


				if (pos > 173450 && pos < 193800) {
					drawFigure(gold, band1, 0, 1, 0, 200);
				}

				ofTranslate(0, 2200);
				if (pos > 173450 && pos < 193800) {
					drawFigure(gold, band1, 0, 1, 0, 200);
				}

				ofTranslate(0, -550);
				if (pos > 166480 && pos < 194200) {
					drawFigure(orange, band2, 0.001, .1, 0, 205);
				}

				ofTranslate(0, -1100);
				if (pos > 166480 && pos < 194200) {
					drawFigure(orange, band2, 0.001, .1, 0, 205);
				}

				ofTranslate(0, 550);
				if (song.getPositionMS() > 159800) {
					drawFigure(cerulean, band3, 0.0003, 0.04, 50, 235);
				}

				ofPopMatrix();

				/*ofPushMatrix();
				ofScale(0.4, 0.4);
				ofTranslate(2540, -80);
				ofRotateDeg(90);

				drawBoundedFigure(lighterPink, band2, 0, 1, 0, 200);
				ofPopMatrix();*/
			
			}
			if (song.getPosition() >= 0.99) {
				player.close();
			}
		}
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


	//gui.draw();
}


void ofApp::drawFigure(ofColor color, int band, float min, float max, int alphaMin, int alphaMax) {
	ofSetRectMode(OF_RECTMODE_CENTER);

	float time = ofGetElapsedTimef();

	// find contours
	ofPolyline line = finder.getPolyline(0);
	line = line.getResampledBySpacing(sampleSpacing);
	line = line.getSmoothed(smoothing);
	line.draw();

	ofPath path;

	// choose a gradient to color the path history
	//ofColor col = gradients[gradientIdx].getColorAtPercent(pct);
	ofColor col = color;
	if (color != cerulean) {
		col.a = ofMap(fftSmooth[band], min, max, alphaMin, alphaMax);
	}
	else {
		col.a = ofMap(t*sin(time), -1*t, 1*t, 0, alphaMax);
	}
	//cout << fftSmooth[band] << endl;

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

}

void ofApp::drawBoundedFigure(ofColor color, int band, float min, float max, int rMinScale, int rMaxScale) {
	ofSetRectMode(OF_RECTMODE_CENTER);

	float time = ofGetElapsedTimef();

	// find contours
	ofPolyline line = finder.getPolyline(0);
	line = line.getResampledBySpacing(sampleSpacing);
	line = line.getSmoothed(smoothing);

	ofPath path;

	ofColor col = color;

	ofSetColor(pink);
	ofRectangle box = line.getBoundingBox();
	//float r = ofMap(t*sin(time), -1 * t, 1 * t, 1.2, 1.8);
	float w = ofMap(ofNoise(time), 0, 1, 1.1, 1.8);
	float h = ofMap(ofNoise(time), 0, 1, 1.5, 2.7);
	//float r = ofMap(fftSmooth[band], .001, .1, 1.1, 2.0);
	ofDrawRectangle(box.getCenter(), box.width * w, box.height * h);

	ofSetColor(lightPink);
	ofSetLineWidth(3);
	ofNoFill();
	ofDrawRectangle(box.getCenter(), box.width * w, box.height * h);
	ofFill();

	//col.a = 127;
	path.setFillColor(col);

	//// convert the polyline to a path object
	for (int i = 0; i < line.getVertices().size(); i++) {
		path.curveTo(line.getVertices()[i]);
	}

	path.draw();
	ofSetLineWidth(4);
	ofSetColor(lightPink);
	line.draw();

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

void ofApp::drawBars(int trail) {
	ofSetColor(lime, 200);

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

//TODO: draw shapes on body
//TODO: draw amp waves


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
	case '5':
		song.setPositionMS(115000);
		break;
	case '6':
		song.setPositionMS(116200);
		break;
	case '7':
		song.setPositionMS(130000);
		break;
	case '8':
		song.setPositionMS(157000);
		break;
	case 'b':
		song.setPositionMS(27750);
		break;
	}

	switch (key) {
	case '1':
		if (clipIdx == 5) {
			clipIdx = 0;
		}
		loadNext = true;
		//player.setPosition(0.02);
		//player.play();
		//song.play();
		break;
	case '2':
		player.stop();
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
