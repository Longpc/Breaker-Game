#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
	auto infoLayer = InforLayer::create();
	scene->addChild(infoLayer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pha.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("base.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("win.mp3");
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->setAccelerometerEnabled(true);
	auto aListener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAccleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(aListener, this);


	_screenBolder = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(Size(visibleSize.width-100,visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	boundBody->getShape(0)->setRestitution(1.0f);
	boundBody->getShape(0)->setFriction(0.0f);
	boundBody->getShape(0)->setDensity(1.0f);
	_screenBolder->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	_screenBolder->setPhysicsBody(boundBody);
	boundBody->setContactTestBitmask(CONTACT_TEST_BITMASK);
	this->addChild(_screenBolder);
	_screenBolder->setTag(TAG_WALL);

	_ball = Sprite::create("ball.png", Rect(0, 0, 90, 90));
	//_ball->setScale(5.5f);
	_ball->setPosition(visibleSize.width / 2, 100);
	auto ballBd = PhysicsBody::createCircle(_ball->getContentSize().width / 2.);
	ballBd->getShape(0)->setRestitution(1.0f);
	ballBd->getShape(0)->setFriction(0.0f);
	ballBd->getShape(0)->setDensity(1.0f);
	ballBd->setGravityEnable(false);
	ballBd->setRotationEnable(true);
	Vect force = Vect(INIT_VECTOR_X, INIT_VECTOR_Y);
	ballBd->applyImpulse(force);
	_ball->setPhysicsBody(ballBd);
	ballBd->setContactTestBitmask(CONTACT_TEST_BITMASK);
	_ball->setTag(TAG_BALL);
	
	this->addChild(_ball);
	auto rotateBall = RotateBy::create(0.5f, 360);
	auto repeatRotate = RepeatForever::create(rotateBall);
	//_ball->runAction(repeatRotate);

	_baseLine = Sprite::create("base.png");
	_baseLine->setPosition(visibleSize.width / 2, _baseLine->getContentSize().height / 2);
	auto _baseLineBd = PhysicsBody::createBox(_baseLine->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	_baseLineBd->getShape(0)->setRestitution(1.002f);
	_baseLineBd->getShape(0)->setFriction(0.0f);
	_baseLineBd->getShape(0)->setDensity(1.0f);
	_baseLineBd->setGravityEnable(false); //
	_baseLineBd->setDynamic(false);
	_baseLineBd->setContactTestBitmask(CONTACT_TEST_BITMASK);
	//Vect force2 = Vect(2002000.0f, -2002000.0f); //Vector Luc x,y
	//_baseLineBd->applyImpulse(force2);
	
	_baseLine->setPhysicsBody(_baseLineBd);
	
	/*MyBodyParser::getInstance()->parseJsonFile("baseline.json");
	auto _baselineBody = MyBodyParser::getInstance()->bodyFormJson(_baseLine, "baseline");
	if (_baselineBody != nullptr) {
		_baselineBody->setDynamic(false);
		_baselineBody->setContactTestBitmask(CONTACT_TEST_BITMASK);
		_baselineBody->getShape(0)->setRestitution(1.005f);
		_baselineBody->getShape(0)->setFriction(0.0f);
		_baselineBody->getShape(0)->setDensity(1.0f);
		_baselineBody->setGravityEnable(false);
		_baseLine->setPhysicsBody(_baselineBody);
	} */
	_baseLine->setTag(TAG_BASE);
	this->addChild(_baseLine);
	_closeButon = Sprite::create("close.png");
	_closeButon->setPosition(Vec2(visibleSize.width - _closeButon->getContentSize().width / 2, visibleSize.height - _closeButon->getContentSize().height / 2));
	addChild(_closeButon);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	srand(time(NULL));
	initBlocks();
	auto dispath = Director::getInstance()->getEventDispatcher();
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	dispath->addEventListenerWithSceneGraphPriority(contactListener, this);
	gameScoreLabel = Label::create("Score: 0", "fonts/3.ttf", 35);
	gameScoreLabel->setPosition(Vec2(0 + gameScoreLabel->getContentSize().width, visibleSize.height - SCORE_MARGIN));
	addChild(gameScoreLabel);
	/*A.addChild(gameScoreLabel);
	if (A.isVisible()){
		cocos2d::log("Visiable");
	} */
	this->scheduleUpdate();
    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* evnet) {
	Point p = touch->getLocation();
	Rect rect = _closeButon->getBoundingBox();
	if (rect.containsPoint(p)) {
		winGame();
		return false;
	}
	return true;
}
void HelloWorld::onTouchEnded(Touch* touch, Event* event) {

}
void HelloWorld::onTouchMoved(Touch* touch, Event* event){
	Point touchLocation = touch->getLocation();
	_baseLine->setPositionX(touchLocation.x);
}
void HelloWorld::update(float dt) {
	auto pos = _baseLine->getPosition();
	pos.x = _moveX;
	_baseLine->setPosition(pos);
}
void HelloWorld::onAccleration(Acceleration *pAccelerationValue, Event *event) {
#define DEC 1.0f
#define SPEED 30
	float maxX = visibleSize.width - _baseLine->getContentSize().width / 2;
	float minX = _baseLine->getContentSize().width / 2;

	_moveX = _moveX*DEC + SPEED*pAccelerationValue->x;

	if (_moveX > maxX) {
		_moveX = maxX;
	}
	else if (_moveX < minX) {
		_moveX = minX;
	}
}
bool HelloWorld::onContactBegin(const PhysicsContact &contact) {
	auto spriteA = contact.getShapeA()->getBody()->getNode();
	auto spriteB = contact.getShapeB()->getBody()->getNode();

	// Kiểm tra loại đối tượng
	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();
	if (tagA == TAG_BLOCK) {
		spriteA->removeFromParentAndCleanup(true);
	}
	if (tagB == TAG_BLOCK) {
		spriteB->removeFromParentAndCleanup(true);
	}
	if (tagA == TAG_BLOCK || tagB == TAG_BLOCK) {
		
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pha.wav");
		callUpdateScore(A);
	}
	if (tagA == TAG_BASE || tagB == TAG_BASE) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("base.wav");
	}
	return true;
}
void HelloWorld::callUpdateScore(InforLayer &layer) {
	HelloWorld::gameScore++;
	cocos2d::log("Game Score: %d", gameScore);
	std::stringstream text;
	text << "Score: " << gameScore << std::endl;
	cocos2d::log("%s", text.str().c_str());
	string str = text.str().c_str();
	gameScoreLabel->setString(str);
	if (gameScore == BLOCKS_NUMBER) {
		unsigned int winID = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("win.mp3");
		CCDelayTime * delayAction = CCDelayTime::create(2);
		CCCallFunc * callFunc = CCCallFunc::create(this, callfunc_selector(HelloWorld::winGame));
		this->runAction(CCSequence::createWithTwoActions(delayAction, callFunc));
		
	}
}
void HelloWorld::winGame() {
	auto scene = GameOverScene::createScene(gameScore);
	Director::getInstance()->replaceScene(scene);
}
void HelloWorld::initBlocks() {

	for (int i = 0; i < BLOCKS_NUMBER; i++)
	{
		blockArray.push_back(createBlockWithRandomNumber(rand() % 4 + 1));

		float randX = rand() % int(visibleSize.width - MARGIN_X*2 )+ MARGIN_X;
		float randy = rand() % int(visibleSize.height/2) + visibleSize.height / 2/* -blockArray[0]->getContentSize().height/2 */- SCORE_MARGIN *2;
		blockArray[i]->setPosition(Vec2(randX, randy));
		auto blockBody = PhysicsBody::createBox(blockArray[i]->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
		blockBody->getShape(0)->setDensity(10.0f);
		blockBody->getShape(0)->setFriction(0.0f);
		blockBody->getShape(0)->setRestitution(1.f);
		blockBody->setDynamic(false);
		blockBody->setContactTestBitmask(CONTACT_TEST_BITMASK);
		blockArray[i]->setPhysicsBody(blockBody);
		blockArray[i]->setTag(TAG_BLOCK);
		this->addChild(blockArray[i]);
	}
}
Sprite* HelloWorld::createBlockWithRandomNumber(int number) {
	std::stringstream name;
	name << "" << number << ".png";
	return cocos2d::Sprite::create(name.str().c_str());
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
HelloWorld::HelloWorld() {

}
HelloWorld::~HelloWorld() {
	cocos2d::log("On HelloWorld Destruct");
	
	/*if (_ball) {
		_ball->release();
		_ball = NULL;
	}
	if (_baseLine) {
		_baseLine->release();
		_baseLine = NULL;
	}
	if (_screenBolder) {
		_screenBolder->release();
		_screenBolder = NULL;
	}
	if (_closeButon) {
		_closeButon->release();
		_closeButon = NULL;
	}
	if (blockArray.size() >0) {
		blockArray.empty();
	}
	if (gameScoreLabel) {
		gameScoreLabel->release();
		gameScoreLabel = NULL;
	} */
}

