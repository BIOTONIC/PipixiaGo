#ifndef __MAP_MANAGER__
#define __MAP_MANAGER__

#include "CubePlatform.h"

USING_NS_CC;

class MapManager : public Node
{
public:
    CREATE_FUNC(MapManager);

    virtual bool init();

    virtual void update(float dt);

    int isCollision(Sprite *sprite);

    void setIsMove(bool m);

    int getScore();

private:
    void createThing();

    bool isMove;
    Vector<CubePlatform *> m_platform;
    int score;
    Sprite *background1;
    Sprite *background2;
    Sprite *background3;
    Sprite *background4;
};

#endif