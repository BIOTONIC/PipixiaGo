#ifndef __RESULT_SCENE_H__
#define __RESULT_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class ResultScene : public Layer
{
public:
    static Scene *createScene();

    CREATE_FUNC(ResultScene);

private:
    bool init();

    void replayEvent(Ref *pSender);
};


#endif //__RESULT_SCENE_H__
