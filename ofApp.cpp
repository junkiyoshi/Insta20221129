#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableDepthTest();
	//ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	auto ico_sphere = ofIcoSpherePrimitive(250, 3);
	this->base_mesh = ico_sphere.getMesh();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->draw_mesh = this->base_mesh;

	vector<ofColor> color_list = { ofColor(0, 255, 255, 128) };

	auto noise_seed = ofRandom(1000);
	for (int k = 0; k < color_list.size(); k++) {

		noise_seed += ofRandom(1000);
		int index = 0;
		for (auto& v : this->draw_mesh.getVertices()) {

			for (int i = 0; i < 16; i++) {

				auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.001, noise_seed + (ofGetFrameNum() + i) * 0.0015)), 0, 1, -30, 30) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.001, noise_seed + (ofGetFrameNum() + i) * 0.0015)), 0, 1, -30, 30) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
				auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.001, noise_seed + (ofGetFrameNum() + i) * 0.0015)), 0, 1, -30, 30) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

				v = glm::vec4(v, 0) * rotation_z * rotation_y * rotation_x;
			}

			this->draw_mesh.addColor(color_list[k]);
			index++;
		}

	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 1.6666666666666666);

	this->draw_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}