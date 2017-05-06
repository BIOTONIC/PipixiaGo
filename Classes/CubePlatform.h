#ifndef __PLATFORM__
#define __PLATFORM__

#include "cocos2d.h"
#include "../cocos2d/extensions/cocos-ext.h"
#include<time.h>

#define random(x) (rand()%x)

USING_NS_CC;
USING_NS_CC_EXT;

class CubePlatform : public Node
{
public:
    CREATE_FUNC(CubePlatform);

    virtual bool init();

    void addSprite(Scale9Sprite *scale9Sprite);

    void initPlatform(int i);

    void resetPlatform();

    cocos2d::Rect myGetBoundingBox();

    bool isBump();

    void setIsBump(bool);

    void setSize(float x);

    void setPos(float x, float y);

    void setX(float x);

    float getX();

    float getY();

private:
    void setV();

    int type;
    Vector<Scale9Sprite *> m_sprite;
    bool Bump;
};

#endif