#include "Ball.h"
using namespace std;
USING_NS_CC;
Ball::Ball(char *fn, int t, String n) {
	
	filename = fn;
	tag = t;
	name = n;
	sprite = Sprite::create(filename);

}

Sprite* Ball::getSprite() const {
	return sprite;
}


int Ball::getTag() const {
	return tag;
}

void Ball::setTag1(int t) {
	tag = t;
}

String Ball::getName() const {
	return name;
}

void Ball::setName(String n) {
	name = n;
}

void Ball::setBall(char *fb, int t, String n) {
	filename = fb;
	tag = t;
	name = n;
}

void Ball::print() const {
	cocos2d::log("%s : %d : %s", filename, tag, name);
}

/*void Ball::doSomething(void (GameOverScene::*func)()) {

} */