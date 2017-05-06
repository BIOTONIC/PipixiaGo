#include "CubePlatform.h"

bool CubePlatform::init()
{
    //srand((unsigned)time(NULL));

    type = -1;
    Bump = false;

    return true;
}

void CubePlatform::addSprite(Scale9Sprite *scale9Sprite)
{
    //scale9Sprite->setCapInsets(Rect(60,0,60,0));

    this->addChild(scale9Sprite);

    m_sprite.pushBack(scale9Sprite);
}

void CubePlatform::initPlatform(int i)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Bump = false;

    float ix = visibleSize.width * 0.8 * i;

    if (i == 0)
        ix = 250;

    int iy = random((int) (visibleSize.height * 0.4 + 60));

    setPos(ix, iy);

    setSize(random(200) + 300);

    if (i == 1)
        setSize(240);


    setV();
}

void CubePlatform::resetPlatform()
{
    initPlatform(2);


}

cocos2d::Rect CubePlatform::myGetBoundingBox()
{
    auto sprite = m_sprite.at(type);

    return sprite->getBoundingBox();
}


bool CubePlatform::isBump()
{

    return Bump;
}

void CubePlatform::setSize(float x)
{

    for (auto sprite : m_sprite)
    {
        sprite->setContentSize(cocos2d::Size(x, 60));
    }

}

void CubePlatform::setIsBump(bool b)
{
    Bump = b;
}


void CubePlatform::setPos(float x, float y)
{
    for (auto sprite : m_sprite)
    {
        sprite->setPosition(x, y);
    }
}

void CubePlatform::setX(float x)
{
    for (auto sprite : m_sprite)
    {
        sprite->setPositionX(x);
    }
}

float CubePlatform::getX()
{
    auto sprite = m_sprite.at(type);

    return sprite->getPositionX();
}

float CubePlatform::getY()
{
    auto sprite = m_sprite.at(type);

    return sprite->getPositionY();
}

void CubePlatform::setV()
{
    int num = m_sprite.size();
    int i = 0;
    int n = random(num);
    type = n;
    for (auto sprite: m_sprite)
    {
        if (i == n)
            sprite->setVisible(true);
        else
            sprite->setVisible(false);
        i++;
    }
}
