#include "GameOverScene.h"
USING_NS_CC;
Scene* GameOverScene::createScene(int score) {
	auto scene = cocos2d::Scene::create();
	auto layer = GameOverScene::create(score);
	scene->addChild(layer);
	return scene;
}
GameOverScene* GameOverScene::create(int score) {
	GameOverScene *layer = new GameOverScene();
	if (layer->init(score)) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}
bool GameOverScene::init(int score) {
	if (!Layer::init()) {
		return false;
	}
	size = Director::getInstance()->getWinSize();
	std::stringstream text;
	text << "Score: " << score << std::endl;
	cocos2d::log("%s", text.str().c_str());
	string str;
	if (score >= 0) {
		str = text.str().c_str();
	}
	else {
		str = "Hello";
	}
	string gameName;
	/*// define supported target platform macro which CC uses.
	#define CC_PLATFORM_UNKNOWN            0
	#define CC_PLATFORM_IOS                1
	#define CC_PLATFORM_ANDROID            2
	#define CC_PLATFORM_WIN32              3
	#define CC_PLATFORM_MARMALADE          4
	#define CC_PLATFORM_LINUX              5
	#define CC_PLATFORM_BADA               6
	#define CC_PLATFORM_BLACKBERRY         7
	#define CC_PLATFORM_MAC                8
	#define CC_PLATFORM_NACL               9
	#define CC_PLATFORM_EMSCRIPTEN        10
	#define CC_PLATFORM_TIZEN             11
	#define CC_PLATFORM_QT5               12
	#define CC_PLATFORM_WP8               13
	#define CC_PLATFORM_WINRT             14
	*/
	if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) {
		gameName = "BLOCK BREAKER";
	}
	else {
		gameName = "BLOCK\nBREAKER";
	}
	auto gameLabel = Label::create(gameName, "fonts/1.ttf", 70);
	gameLabel->setPosition(Vec2(size.width / 2, size.height - END_BUTTON_MARGIN_Y));
	addChild(gameLabel);
	
	gameScoreView = Label::create(str, "fonts/3.ttf", 50);
	playButton = Sprite::create("replay.png");
	exitButton = Sprite::create("exit.png");
	testBodyParser = Label::create("TEST BODY", "fonts/3.ttf", 30);
	testBodyParser->setPosition(Vec2(testBodyParser->getContentSize().width, size.height / 2));
	testSpriteSheet = Label::create("SPRITE SHEET", "fonts/3.ttf", 30);
	testSpriteSheet->setPosition(Vec2(testSpriteSheet->getContentSize().width, testBodyParser->getPositionY() - testSpriteSheet->getContentSize().height));
	gameScoreView->setPosition(Vec2(size.width / 2, size.height/2+SCORE_MARGIN));
	playButton->setPosition(Vec2(size.width/2 - END_BUTTON_MARGIN_X, size.height / 2 - END_BUTTON_MARGIN_Y));
	exitButton->setPosition(Vec2(size.width/2 + END_BUTTON_MARGIN_X, size.height / 2 - END_BUTTON_MARGIN_Y));
	addChild(gameScoreView);
	addChild(playButton);
	addChild(exitButton);
	addChild(testBodyParser);
	addChild(testSpriteSheet);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameOverScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameOverScene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameOverScene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(GameOverScene::onTouchCancelled, this);
	touchListener->setEnabled(true);
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	/*Time time = Time::Time(12, 52, 23);
	time.print();
	time.setHour(1);
	time.setMinute(2);
	time.print();
	cocos2d::log("Time: %d : %d : %d", time.getHour(), time.getMinute(), time.getSecond());
	Time time2;
	time2.print();
	time2.setTime(1, 1, 1);
	time2.print();
	time2.nextSecond();
	time2.print();
	Time time3(3, 3, 3);
	time3.print(); */
	/*
	auto button = Button::create();
	button->loadTextures("ball.png", "close.png", "play.png");
	button->setTouchEnabled(true);
	button->setPosition(Vec2(300, 300));
	button->addTouchEventListener(this, toucheventselector(GameOverScene::touchButton)); */
	return true;
}
void GameOverScene::touchButton(Object *pSender, TouchEventType type)
{
	switch (type)
	{
	case ui::TOUCH_EVENT_BEGAN:
		gameScoreView->setString("UIButton Click.");
		break;
	case ui::TOUCH_EVENT_MOVED:
		// TODO
		break;
	case ui::TOUCH_EVENT_ENDED:
		// TODO
		break;
	case ui::TOUCH_EVENT_CANCELED:
		// TODO
		break;
	default:
		// TODO
		break;
	}
}
bool GameOverScene::onTouchBegan(Touch* touch, Event* event) {
	cocos2d::log("TOuch begin");
	Vec2 point = touch->getLocation();
	Rect rect = playButton->getBoundingBox();
	if (rect.containsPoint(point)) {
		playButton->setScale(1.1f);
		//replayGame();
		selectFlg = REPLAY;
		return true;
	}
	rect = exitButton->getBoundingBox();
	if (rect.containsPoint(point))
	{
		exitButton->setScale(1.1f);
		//exitGame();
		selectFlg = EXIT;
		return true;
	}
	rect = testBodyParser->getBoundingBox();
	if (rect.containsPoint(point)) {
		auto scene = BodyTestScene::createScene();
		Director::getInstance()->replaceScene(scene);
		return true;
	}
	rect = testSpriteSheet->getBoundingBox();
	if (rect.containsPoint(point)) {
		auto scene = SpriteSheetScene::createScene();
		Director::getInstance()->replaceScene(scene);
		return true;
	}
	selectFlg = -1;
	auto ball = Ball::Ball("ball.png", 1, "hehe");
	ball.getSprite()->setPosition(point);
	//ball.doSomething(&GameOverScene::pSomthing); //E
	addChild(ball.getSprite());
	
	return false;
}
void GameOverScene::pSomthing() {
	cocos2d::log("Something is Running");
}
void GameOverScene::onTouchEnded(Touch* touch, Event* event)
{
	//cocos2d::log("touch ended");
	playButton->setScale(1.0f);
	exitButton->setScale(1.0f);
	if (selectFlg == REPLAY) {
		replayGame();
		return;
	}
	if (selectFlg == EXIT) {
		exitGame();
		return;
	}
}

void GameOverScene::onTouchMoved(Touch* touch, Event* event)
{
	//cocos2d::log("touch moved");
}

void GameOverScene::onTouchCancelled(Touch* touch, Event* event)
{
	//cocos2d::log("touch cancelled");
}
void GameOverScene::replayGame() {
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}
void GameOverScene::exitGame() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
GameOverScene::GameOverScene() {

}
GameOverScene::~GameOverScene() {

}