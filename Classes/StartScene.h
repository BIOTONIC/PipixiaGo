#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "GameScene.h"

USING_NS_CC;

class StartScene : public Layer
{
public:
    static Scene *createScene();

    CREATE_FUNC(StartScene);

private:
    bool init();

    void playEvent(Ref *sender);

    Sprite *playBtn;
};

#endif //__START_SCENE_H__
