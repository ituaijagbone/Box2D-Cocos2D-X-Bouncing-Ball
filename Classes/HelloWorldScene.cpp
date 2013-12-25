#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// Create Sprite and add it to layer
	_ball = CCSprite::create("ball.png", CCRectMake(0, 0, 52, 52));
	_ball->setPosition(ccp(100, 100));
	this->addChild(_ball);


	// Create world
	b2Vec2 gravity = b2Vec2(0.0f, -8.0f);
	_world = new b2World(gravity);

	// Create edge around entire screen
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	
	b2Body *groundBody = _world->CreateBody(&groundBodyDef);
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	// Wall definitions
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width/PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height/PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(0, winSize.height/PTM_RATIO), b2Vec2(winSize.width/PTM_RATIO, winSize.height/PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(winSize.width/PTM_RATIO, winSize.height/PTM_RATIO), b2Vec2(winSize.width/PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	// Create ball body and shape
	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(100/PTM_RATIO, 220/PTM_RATIO);
	ballBodyDef.userData = _ball;
	_body = _world->CreateBody(&ballBodyDef);

	b2CircleShape circle;
	circle.m_radius = 26.0/PTM_RATIO;

	b2FixtureDef ballShapeDef;
	ballShapeDef.shape = &circle;
	ballShapeDef.density = 1.0f;
	ballShapeDef.friction = 0.2f;
	ballShapeDef.restitution = 0.8f;
	this->_body->CreateFixture(&ballShapeDef);

	this->setTouchEnabled(true);
	this->schedule(schedule_selector(HelloWorld::tick));
	//this->schedule(schedule_selector(HelloWorld::kick), 5.0);
    return true;
}

void HelloWorld::tick(float dt) {
	_world->Step(dt, 10, 10);
	for (b2Body *b = _world->GetBodyList(); b; b=b->GetNext()) {
		if (b->GetUserData() != NULL) {
			CCSprite *ballData = (CCSprite *)b->GetUserData();
			ballData->setPosition(ccp(b->GetPosition().x * PTM_RATIO,
				b->GetPosition().y * PTM_RATIO));
			ballData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}

void HelloWorld::kick(float dt) {
	b2Vec2 force = b2Vec2(30, 30);
	_body->ApplyLinearImpulse(force, _body->GetPosition());
}

void HelloWorld::ccTouchesBegan(CCSet * touches, CCEvent * event) {
	b2Vec2 force = b2Vec2(-30, 30);
	_body->ApplyLinearImpulse(force, _body->GetPosition());
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


HelloWorld::~HelloWorld() {
	delete _world;
	_body = NULL;
	_world = NULL;
}