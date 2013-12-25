#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define PTM_RATIO 32.0

#include "cocos2d.h"
#include "Box2D\Box2D.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
public:
	~HelloWorld();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	void tick(float);

	void kick(float);

	void ccTouchesBegan(CCSet *, CCEvent *);
private:
	b2World * _world;
	b2Body * _body;
	CCSprite * _ball;
};

#endif // __HELLOWORLD_SCENE_H__
