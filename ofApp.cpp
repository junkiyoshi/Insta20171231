#include "ofApp.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
ofApp::~ofApp() {
	for (int i = this->particles.size() - 1; i > -1; i--) {
		delete this->particles[i];
		this->particles.erase(this->particles.begin() + i);
	}
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 120, true, false, true);
	this->words.push_back("HAPPY");
	this->words.push_back("NEW");
	this->words.push_back("YEAR");

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = this->particles.size() - 1; i > -1; i--) {
		this->particles[i]->update();

		if (this->particles[i]->isDead()) {
			delete this->particles[i];
			this->particles.erase(this->particles.begin() + i);
		}
	}

	this->fbo.begin();
	ofClear(0);

	ofTranslate(10, 200);
	
	float distance;
	for (int i = 0; i < this->particles.size(); i++) {
		for (int j = i; j < this->particles.size(); j++) {
			distance = this->particles[i]->get_location().distanceSquared(this->particles[j]->get_location());
			if (distance < 100) {
				ofSetColor(this->particles[i]->get_body_color(), this->particles[i]->get_alpha());
				ofDrawLine(this->particles[i]->get_location(), this->particles[j]->get_location());
			}
		}
	}

	this->fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw() {
	this->fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	for (int word_index = 0; word_index < this->words.size(); word_index++) {
		this->font_paths = this->font.getStringAsPoints(this->words[word_index]);
		for (int moji_index = 0; moji_index < this->words[word_index].size(); moji_index++) {
			for (int polyline_index = 0; polyline_index < (int)this->font_paths[moji_index].getOutline().size(); polyline_index++) {
				ofPolyline polyline = this->font_paths[moji_index].getOutline()[polyline_index].getResampledBySpacing(5);
				if (polyline_index != 0)ofNextContour(true);

				vector<ofPoint> points = polyline.getVertices();
				for (int point_index = 0; point_index < (int)points.size(); point_index++) {
					ofColor color;
					color.setHsb(ofRandom(255), 255, 255);
					ofVec3f location = ofVec3f(points[point_index].x + (150 * word_index), points[point_index].y + (200 * word_index));

					this->particles.push_back(new Particle(location, ofVec2f(ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5)), color));
				}
			}
		}
	}
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}