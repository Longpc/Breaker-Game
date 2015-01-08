#ifndef __SPRITE_SCENE_H__
#define __SPRITE_SCENE_H__
#include "cocos2d.h"
#include "Define.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "MyBodyParser.h"
USING_NS_CC;
using namespace std;
class SpriteSheetScene :public Layer
{
public:
	SpriteSheetScene();
	~SpriteSheetScene();
	PhysicsWorld* _myWorld;
	void setPhysicWorld(PhysicsWorld* world) {
		_myWorld = world;
	}
	static Scene* createScene();
	static SpriteSheetScene* create();
	virtual bool init();
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
private:
	Sprite* _backButton;
	Sprite* _ballMan;
	Size size;
	Action *walkAction;
	Action *moveAction;
	bool moving;
};


#endif