#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"


#include "Define.h"
#include "InfoLayer.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "MyBodyParser.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();
	~HelloWorld();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	//////VARIABLES//////////////////
	Sprite* _ball;
	Sprite* _baseLine;
	Sprite* _screenBolder;
	Sprite* _closeButon;
	PhysicsWorld* _myWorld;
	//////FUNCTIONSSS///////////////
	void setPhysicWorld(PhysicsWorld* world) {
		_myWorld = world;
	}
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	bool onContactBegin(const PhysicsContact &contact);
	void update(float dt);
	virtual void callUpdateScore(InforLayer &layer);
	virtual void winGame();
	virtual void onAccleration(Acceleration *pAccelerationValue, Event *event);
private:
	std::vector<Sprite*> blockArray;
	Size visibleSize;
	int gameScore = 0;
	Label* gameScoreLabel;
	InforLayer A;
	virtual void initBlocks();
	virtual Sprite* createBlockWithRandomNumber(int number);
	float _moveX;
};


#endif // __HELLOWORLD_SCENE_H__
