#include "Grabber.h"

Grabber::Grabber(int pin){
	grabber_state_ = grabberUndefined;
	pin_ = pin;
}

void Grabber::init(){
	servo_.attach(pin_);
}

void Grabber::open(){
	servo_.write(155);
	grabber_state_ = grabberOpened;
}

void Grabber::close(){
	servo_.write(80);
	grabber_state_ = grabberClosed;
}

int Grabber::getGrabber(){
	return (int)grabber_state_;
}