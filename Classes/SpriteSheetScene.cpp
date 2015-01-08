#include "SpriteSheetScene.h"

Scene* SpriteSheetScene::createScene() {
	auto scene = cocos2d::Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, -1000.0f));
	auto layer = SpriteSheetScene::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}
SpriteSheetScene* SpriteSheetScene::create() {
	SpriteSheetScene *layer = new SpriteSheetScene();
	if (layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}
bool SpriteSheetScene::init() {
	if (!Layer::init()) {
		return false;
	}
	size = Director::getInstance()->getWinSize();
	_backButton = Sprite::create("close.png");
	_backButton->setPosition(Vec2(size.width - _backButton->getContentSize().width, size.height - _backButton->getContentSize().height / 2));
	addChild(_backButton);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(SpriteSheetScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SpriteSheetScene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SpriteSheetScene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(SpriteSheetScene::onTouchCancelled, this);
	touchListener->setEnabled(true);
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	///SPRITE SHEET ANIMATION TEST///
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("AnimBear.plist");
	auto ss = SpriteBatchNode::create("AnimBear.png");
	this->addChild(ss);
	Vector<SpriteFrame*> af(8);
	char name[30] = { 0 };
	for (int i = 1; i < 9; i++)
	{
		sprintf(name, "bear%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		af.pushBack(frame);
	}
	Animation *animation = Animation::createWithSpriteFrames(af,0.2f);
	_ballMan = Sprite::createWithSpriteFrameName("bear1.png");
	_ballMan->setPosition(Vec2(size.width / 2, size.height / 2));
	walkAction = RepeatForever::create(Animate::create(animation));
	walkAction->retain();
	ss->addChild(_ballMan);
	_ballMan->runAction(walkAction);


	return true;
}
bool SpriteSheetScene::onTouchBegan(Touch* touch, Event* event) {
	cocos2d::log("TOuch begin");
	Vec2 point = touch->getLocation();
	Rect rec = _backButton->getBoundingBox();

	if (rec.containsPoint(point)) {
		auto scene = GameOverScene::createScene(-1);
		Director::getInstance()->replaceScene(scene);
		return false;
	}
	return true;
}
void SpriteSheetScene::onTouchEnded(Touch* touch, Event* event)
{

}

void SpriteSheetScene::onTouchMoved(Touch* touch, Event* event)
{
	//cocos2d::log("touch moved");
}

void SpriteSheetScene::onTouchCancelled(Touch* touch, Event* event)
{
	//cocos2d::log("touch cancelled");
	Vec2 point = touch->getLocation();

}
SpriteSheetScene::SpriteSheetScene()
{
}

SpriteSheetScene::~SpriteSheetScene()
{
}