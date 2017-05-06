#include <iostream>
#include "SceneManager.h"

bool SceneManager::init()
{
    createThing();
    this->scheduleUpdate();
    isMove = false;

    // set background
    background1 = Sprite::create("Resources/game_bg_1.png");
    background1->setAnchorPoint(cocos2d::Point(0.0f, 0.0f));
    background1->setPosition(cocos2d::Point(0.0f, 0.0f));
    addChild(background1, 0);

    background2 = Sprite::create("Resources/game_bg_2.png");
    background2->setAnchorPoint(cocos2d::Point(0.0f,0.0f));
    background2->setPosition(cocos2d::Point(1100.0f,0.0f));
    addChild(background2,0);

    return true;
}

void SceneManager::update(float dt)
{
    if (!isMove)
    {
        return;
    }
    for (auto cube : m_cube)
    {
        Sprite *sprite = cube->getSprite();
        float Y = sprite->getPositionX();
        sprite->setPositionX(Y - 1);
        if (Y < -(sprite->getBoundingBox().size.width / 2))
        {
            cube->reset();
        }
    }

    background1->setPositionX(background1->getPositionX() - 1);
    background2->setPositionX(background2->getPositionX() - 1);

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
}

int SceneManager::isCollision(Sprite *sprite)
{
    for (auto cube : m_cube)
    {
        if (cube->getSprite()->getBoundingBox().intersectsRect(sprite->getBoundingBox()))
        {
            float x = cube->getSprite()->getPosition().x - sprite->getPosition().x;
            float y = cube->getSprite()->getPosition().y - sprite->getPosition().y;

            if (x < 0)
                x = -x;
            if (y < 0)
                y = -y;

            auto size1 = cube->getSprite()->getBoundingBox().size;
            auto size2 = sprite->getBoundingBox().size;

            float a1 = (size1.width + size2.width) / 2;
            float a2 = (size1.height + size2.height) / 2;

            //up
            if ((x / a1) < (y / a2))
            {
                return 1;
            }//left
            else
            {
                return 2;
            }


        }
    }

    return 0;
}

void SceneManager::SetIsMove(bool move)
{
    isMove = move;
}

void SceneManager::createThing()
{
    Cube *cube;
    for (int i = 0; i < 4; i++)
    {
        cube = (Cube *) Cube::create();
        cube->setSprite(Sprite::create("Resources/cube.png"));
        cube->initSize(i);

        this->addChild(cube, 1);
        m_cube.pushBack(cube);
    }
}
