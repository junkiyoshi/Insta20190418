#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();
	ofSetLineWidth(1.5);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->locations.clear();
	while (this->locations.size() < 500) {

		float R = 300;
		float r = 50;
		float u = ofRandom(0, 360) + ofGetFrameNum() * ofRandom(0.5, 2);
		float v = ofRandom(0, 360);

		this->locations.push_back(this->make_point(R, r, u, v));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (auto& location : this->locations) {

		ofSetColor(39);
		ofDrawSphere(location, 3);
		for (auto& other : this->locations) {

			if (location == other) { continue; }
			float distance = glm::distance(location, other);
			if (distance < 50) {

				ofSetColor(ofMap(distance, 10, 50, 39, 239));
				ofDrawLine(location, other);
			}
		}

	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	float x = (R + r * cos(u)) * cos(v);
	float y = (R + r * cos(u)) * sin(v);
	float z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}