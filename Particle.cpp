#include "Particle.h"

Particle::Particle() : Particle(ofVec2f(0, 0), ofVec2f(0, 0), ofColor(128)) { }

Particle::Particle(ofVec2f location, ofVec2f velocity, ofColor body_color)
{
	this->location = location;
	this->velocity = velocity;
	this->alpha = 255;
	this->body_size = velocity.length() / 2;
	this->body_color = body_color;
}

Particle::~Particle() { }

void Particle::update()
{
	this->location += this->velocity;
	this->alpha -= 3;
}

void Particle::draw()
{

}

ofVec2f Particle::get_location() {
	return this->location;
}

ofColor Particle::get_body_color() {
	return this->body_color;
}

float Particle::get_alpha() {
	return this->alpha;
}

bool Particle::isDead()
{
	return this->alpha < 0;
}