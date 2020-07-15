#include "ofApp.h"

// TODO: gain more control over what parts of the files go missing somehow
// TODO: fill in some of the spaces? more shapes? text?
// TODO: put the shaders on 3D shapes?
//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(10);
    
	shader.load("", "shader.frag");
	shader2.load("", "shader2.frag");
	shader3.load("", "shader3.frag");


    original.setImageType(OF_IMAGE_COLOR);

	grabber.setup(848, 480);

	imgGray.allocate(grabber.getWidth(), grabber.getHeight(), OF_IMAGE_GRAYSCALE);
	imgColor.allocate(grabber.getWidth(), grabber.getHeight(), OF_IMAGE_COLOR);

	ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){
    
	// (1) reaction diffusion type outcome
	/*
    // resize the output so the jpeg blocks change from frame to frame:
    
    original.resize(original.getWidth()+ofRandom(-200,200),
                    original.getHeight()+ofRandom(-200,200));
    original.resize(original.getWidth()+ofRandom(-200,200),
                    original.getHeight()+ofRandom(-200,200));
    
    // save out:
    
    original.save("test.jpg", OF_IMAGE_QUALITY_BEST);
    
    // load :
    
    original.load("test.jpg");
    
    // resize back to original size:
    
    original.resize(800, 480);
    */


		grabber.update();
		if (!isPaused) {
			for (int z = 0; z < 10; z++) {
				for (int i = 0; i < grabber.getHeight(); i++) {
					ofColor color = grabber.getPixels().getColor(position, i);
					if (position % 10 < ofMap(position, 0, grabber.getWidth(), 1, 8)) {
						imgGray.setColor(position, i, 0);
						imgColor.setColor(position, i, 0);
					}
					/*if (position % 15 < 4) {
						img.setColor(position, i, 255);
					}*/
					else {
						imgGray.setColor(position, i, color);
						imgColor.setColor(position, i, color);
					}
				}
				imgGray.update();
				imgColor.update();

				position++;
				if (position >= grabber.getWidth()) {
					position = 0;

				}
			}
		}


		if (ofGetFrameNum() % 60)  shader.load("", "shader.frag");

		if (ofGetFrameNum() % 30) shader2.load("", "shader2.frag");

		if (ofGetFrameNum() % 60)  shader3.load("", "shader3.frag");

		//ofImage imgTemp;
		//images.push_back(imgTemp);
		//images.back().setUseTexture(false);

		if (!stopFlicker) {
			ofBuffer buffer;
			ofSaveImage(grabber.getPixels(), buffer, OF_IMAGE_FORMAT_JPEG, OF_IMAGE_QUALITY_BEST);

			//int randomSkip = ofRandom(ofGetWidth());
			//int whereToSkip = ofMap(randomSkip, 0, ofGetWidth(), 0, buffer.size(), true);
			//whereToSkip = ofMap(mouseX, 0, ofGetWidth(), 0, buffer.size(), true); //MAX((int)ofRandom(buffer.size() - 1), 0); //counter; //ofMap(mouseX, 0, ofGetWidth(), 0, buffer.size(), true);
			//cout << "whereToSkip: " << whereToSkip << endl;
			whereToSkip = 8340; //1000; // 65000; //8340;



			//int left = buffer.size() - whereToSkip;
			//howMuchToSkip = ofMap(mouseY, 0, ofGetHeight(), 0, left*0.5, true); //(int)ofRandom(left*0.7); //ofMap(mouseY, 0, ofGetHeight(), 0, left*0.5, true);
			//cout << "howMuchToSkip: " << howMuchToSkip << endl;
			howMuchToSkip = 870; //1500; // 90; //870;

			ofBuffer buffer2;
			for (int i = 0; i < buffer.size(); i++) {
				if (i < whereToSkip ||
					i >(whereToSkip + howMuchToSkip)) {
					buffer2.append(buffer.getData() + i, 1);
				}
				else {
					char * data = new char[1];
					data[0] = 157; //ofRandom(0, 255); //127;
					buffer2.append(data, 1);
					delete data;

				}
			}
			newImage.load(buffer2);
		}

		/*images.back().setFromPixels(newImage.getPixels());

		if (images.size() > 2) {
			images.erase(images.begin());
		}*/


	if (ofGetFrameNum() % 60 == 0) {
		ofBuffer buffer3;
		ofSaveImage(grabber.getPixels(), buffer3, OF_IMAGE_FORMAT_JPEG, OF_IMAGE_QUALITY_BEST);

		whereToSkip = 18700; //ofMap(mouseX, 0, ofGetWidth(), 0, buffer3.size(), true);
		int left = buffer3.size() - whereToSkip;
		howMuchToSkip = 2100; // ofMap(mouseY, 0, ofGetHeight(), 0, left*0.5, true);

		ofBuffer buffer4;
		for (int i = 0; i < buffer3.size(); i++) {
			if (i < whereToSkip ||
				i >(whereToSkip + howMuchToSkip)) {
				buffer4.append(buffer3.getData() + i, 1);
			}
			else {
				char * data2 = new char[1];
				data2[0] = 57; //ofRandom(0, 255); //127;
				buffer4.append(data2, 1);
				delete data2;

			}
		}
		newImage2.load(buffer4);
	}



	//if (images.size() > 0) {
	//	float time = ofGetElapsedTimef();
	//	for (int z = 0; z < 1; z++) {
	//		for (int y = 0; y < newImage.getHeight(); y++) {
	//				//ofMap(y, 0, grabber.getHeight(), 0, images.size());
	//			//ofRandom(images.size() - 1);
	//			for (int x = 0; x < newImage.getWidth(); x++) {
	//				//if ((y < ofGetHeight() / 2) && (x < ofGetHeight() / 2)) {
	//				//	xScale = 0.05;
	//				//	yScale = 0.05;
	//				//}
	//				//else {
	//				//	xScale = 0.13;
	//				//	yScale = 0.13;
	//				//}
	//				int whichImage = ofMap(ofNoise(x*0.0001, y*0.0001, time*0.3), 0, 1, 0, images.size() - 1);
	//				ofColor color = images[whichImage].getColor(x, y);
	//				img.setColor(x, y, color);
	//			}
	//		}
	//	}
	//	img.update();
	//}
	//else {
	//	cout << "NO IMAGES" << endl;
	//}


}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(255);
	//cam.begin();
	//cam.enableOrtho();

    //original.draw(0,0);

	//img.draw(0, grabber.getHeight(), grabber.getWidth(), grabber.getHeight());



	//ofPushMatrix();
	//ofScale(0.5, 0.5);
	/*float time = ofGetElapsedTimef();

	for (int i = 0; i < img.getWidth(); i++) {
		for (int j = 0; j < img.getHeight(); j++) {
			ofColor color = img.getColor(i, j);
			float brightness = color.getBrightness();
			ofSetColor(color);
			ofDrawRectangle(i, j, ofMap(brightness, 0, 255, -100, 100), 3, 3);
		}
	}*/

	//ofPopMatrix();
	//cam.end();
   
	ofSetColor(255);

	shader.begin();
	shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniform2f("mouse", mouseX, mouseY);

	// for (2)
	shader.setUniformTexture("img", newImage, 0);

	ofDrawRectangle(0+50, 0+50, grabber.getWidth(), grabber.getHeight());
	ofDrawRectangle(grabber.getWidth() + 500, 0 + 250, 200, 350);
	ofDrawRectangle(ofGetWidth() - grabber.getWidth() - 50 - 150, 0 + 50, 100, 175);
	ofDrawRectangle(ofGetWidth() - grabber.getWidth(), 0 + 50, 350, 150);
	//ofDrawCircle(mouseX,mouseY,100);
	shader.end();


	if (newImage2.isAllocated() && ofGetElapsedTimef() > 10.0) {
		ofSetRectMode(OF_RECTMODE_CENTER);

		shader2.begin();
		shader2.setUniform1f("time", ofGetElapsedTimef());
		shader2.setUniform2f("mouse", mouseX, mouseY);

		// for (2)
		shader.setUniformTexture("img", newImage2, 0);

		ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() / 2, 500, 800);

		if (ofGetElapsedTimef() > 13.0) {
			ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() / 2 - 150, 500, 250);
		}
		if (ofGetElapsedTimef() > 17.0) {
			ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() / 2 + 150, 500, 250);
		}
		//ofDrawCircle(mouseX,mouseY,100);
		shader2.end();
	}


	ofSetRectMode(OF_RECTMODE_CORNER);
	if (ofGetElapsedTimef() > 20.0) {
		if ((int)ofGetElapsedTimef() % 20 > 10) {
			ofSetColor(66, 12, 76);
			shader3.begin();
			shader3.setUniform1f("time", ofGetElapsedTimef());
			shader3.setUniform2f("mouse", mouseX, mouseY);

			// for (2)
			shader3.setUniformTexture("img", imgColor, 0);

			ofDrawRectangle(ofGetWidth() - imgColor.getWidth() - 50, ofGetHeight() - imgColor.getHeight() - 50, imgColor.getWidth(), imgColor.getHeight());
			//ofDrawCircle(0, 0, 200);
			//ofDrawCircle(ofGetWidth() - img.getWidth()/2, ofGetHeight() - img.getHeight()/2, 200);
			shader3.end();
		}
		else {
			ofSetColor(66, 12, 76);
			shader3.begin();
			shader3.setUniform1f("time", ofGetElapsedTimef());
			shader3.setUniform2f("mouse", mouseX, mouseY);

			// for (2)
			shader3.setUniformTexture("img", imgGray, 0);

			ofDrawRectangle(ofGetWidth() - imgGray.getWidth() - 50, ofGetHeight() - imgGray.getHeight() - 50, imgGray.getWidth(), imgGray.getHeight());
			//ofDrawCircle(0, 0, 200);
			//ofDrawCircle(ofGetWidth() - img.getWidth()/2, ofGetHeight() - img.getHeight()/2, 200);
			shader3.end();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') {
		isPaused = !isPaused;
	}
    
	if (key == OF_KEY_SHIFT) {
		stopFlicker = !stopFlicker;
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
