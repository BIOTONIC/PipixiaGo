#ifndef _SceneManager_H_
#define _SceneManager_H_

#include "Cube.h"

USING_NS_CC;

class SceneManager : public Node
{
public:
    CREATE_FUNC(SceneManager);

    virtual bool init();

    virtual void update(float dt);

    int isCollision(Sprite *sprite);

    void SetIsMove(bool move);

private:
    void createThing();

    bool isMove;
    Vector<Cube *> m_cube;

    Sprite *background1;
    Sprite *background2;
};

#endif
