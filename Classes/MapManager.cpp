#include "MapManager.h"

bool MapManager::init()
{
    srand((unsigned) time(NULL));

    score = 0;
    isMove = false;
    createThing();

    this->scheduleUpdate();

    return true;
}

void MapManager::createThing()
{
    for (int i = 0; i < 3; i++)
    {
        CubePlatform *plt = CubePlatform::create();

        plt->addSprite(Scale9Sprite::create("Resources/cube_1.png"));
        plt->addSprite(Scale9Sprite::create("Resources/cube_2.png"));
        plt->addSprite(Scale9Sprite::create("Resources/cube_3.png"));

        plt->initPlatform(i);

        this->addChild(plt, 2);

        m_platform.pushBack(plt);

    }

    // set background
    background1 = Sprite::create("Resources/game_bg_1.png");
    background1->setAnchorPoint(cocos2d::Point(0.0f, 0.0f));
    background1->setPosition(cocos2d::Point(0.0f, 0.0f));
    addChild(background1, 1);

    background2 = Sprite::create("Resources/game_bg_2.png");
    background2->setAnchorPoint(cocos2d::Point(0.0f, 0.0f));
    background2->setPosition(cocos2d::Point(1100.0f, 0.0f));
    addChild(background2, 1);

    background3 = Sprite::create("Resources/game_bg_3.png");
    background3->setAnchorPoint(cocos2d::Point(0.0f, 0.0f));
    background3->setPosition(cocos2d::Point(0.0f, 0.0f));
    addChild(background3, 0);

    background4 = Sprite::create("Resources/game_bg_4.png");
    background4->setAnchorPoint(cocos2d::Point(0.0f, 0.0f));
    background4->setPosition(cocos2d::Point(1100.0f, 0.0f));
    addChild(background4, 0);

}

void MapManager::update(float dt)
{
    if (!isMove)
    {
        return;
    }
    for (auto plt : m_platform)
    {
        plt->setX(plt->getX() - 1);

        //Sprite *sprite = cube->getSprite();
        //float Y = sprite->getPositionX();
        //sprite->setPositionX(Y - 1);
        if (plt->getX() < -200)
        {
            plt->resetPlatform();
        }
    }

    background1->setPositionX(background1->getPositionX() - 0.5);
    background2->setPositionX(background2->getPositionX() - 0.5);

    CCRect rcBounding1 = background1->boundingBox();
    CCRect rcBounding2 = background2->boundingBox();

    if (rcBounding1.getMaxX() <= 0)
    {
        background1->setPositionX(rcBounding1.size.width);
    }
    if (rcBounding2.getMaxX() <= 0)
    {
        background2->setPositionX(rcBounding2.size.width);
    }

    background3->setPositionX(background3->getPositionX() - 0.2);
    background4->setPositionX(background4->getPositionX() - 0.2);

    rcBounding1 = background3->boundingBox();
    rcBounding2 = background4->boundingBox();

    if (rcBounding1.getMaxX() <= 0)
    {
        background3->setPositionX(rcBounding1.size.width);
    }
    if (rcBounding2.getMaxX() <= 0)
    {
        background4->setPositionX(rcBounding2.size.width);
    }
}

int MapManager::isCollision(Sprite *sprite)
{
    for (auto plt : m_platform)
    {
        if (plt->myGetBoundingBox().intersectsRect(sprite->getBoundingBox()))
        {
            float x = plt->getX() - sprite->getPosition().x;
            float y = plt->getY() - sprite->getPosition().y;

            if (x < 0)
                x = -x;
            if (y < 0)
                y = -y;

            auto size1 = plt->myGetBoundingBox().size;
            auto size2 = sprite->getBoundingBox().size;

            float a1 = (size1.width + size2.width) / 2;
            float a2 = (size1.height + size2.height) / 2;

            // up
            if (x / a1 < y / a2)
            {
                if (plt->isBump() == false)
                {
                    score++;
                }
                plt->setIsBump(true);

                return 1;
            }// left
            else
            {
                return 2;
            }

        }
    }
    return 0;
}

void MapManager::setIsMove(bool m)
{
    isMove = m;
}

int MapManager::getScore()
{
    return score;
}
