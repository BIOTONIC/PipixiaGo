#ifndef __Entity_H__
#define __Entity_H__

#include "cocos2d.h"

USING_NS_CC;

class Entity : public Node
{
public:
    Entity();

    ~Entity();

    Sprite *getSprite();

    void setSprite(Sprite *spr);

private:
    Sprite *m_sprite;
};

#endif
