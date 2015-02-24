#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__
#include "cocos2d.h"
#include "Define.h"
#include "TestTime.h"
#include "Ball.h"
#include "HelloWorldScene.h"
#include "TestBodyParser.h"
#include "SpriteSheetScene.h"
#include "cocos2d\cocos\ui\CocosGUI.h"
USING_NS_CC;
using namespace std;
using namespace ui;
class GameOverScene : public Layer
{
public:
	GameOverScene();
	~GameOverScene();

	static Scene* createScene(int gameScore);
	static GameOverScene* create(int score);
	virtual bool init(int score);
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
	virtual void pSomthing();
	virtual void touchButton(Object *pSender, TouchEventType type);
private:
	cocos2d::Sprite* playButton;
	cocos2d::Sprite* exitButton;
	cocos2d::Label* gameScoreView;
	cocos2d::Label* testBodyParser;
	cocos2d::Label* testSpriteSheet;
	int gameScore;
	int selectFlg = -1;
	Size size;
	virtual void replayGame();
	virtual void exitGame();

};

#endif