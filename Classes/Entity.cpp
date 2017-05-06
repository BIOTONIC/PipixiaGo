#include "Entity.h"

Entity::Entity()
{
    m_sprite = NULL;
}

Entity::~Entity()
{

}

Sprite *Entity::getSprite()
{
    return m_sprite;
}

void Entity::setSprite(Sprite *spr)
{
    this->m_sprite = spr;
    this->addChild(m_sprite);
}
