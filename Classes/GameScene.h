#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <ui/UIButton.h>
#include "SceneManager.h"

USING_NS_CC;

using namespace cocos2d::ui;

class GameScene : public Layer
{
public:
    static Scene *createScene();

    CREATE_FUNC(GameScene);

private:
    bool init();

    void getVoice();

    void update(float delta);

    int portInit();
    void portTerminate();

    void pauseBtnCallback(Ref *pSender, Widget::TouchEventType type);

    bool isPause;
    bool isTerminate;

    SceneManager *sceneMa;
    Label *label;
    Sprite *sprite;
    Button *pauseBtn;
    Animate *action;

    float maxY; // maximum position y of sprite, or you can call it ceiling
    float minVoice; // minimum voice, voice below this will be ignored
    float maxVoice; // maximum voice, will be update when a louder voice happened
    float s; // sensitivity, determine how easy to control the sprite using voice
    float speed; // instantaneous speed, >0 meanings going up and <0 meanings going down
    float maxSpeed; // maximum speed, simulates the effect of air resistance, sprite has a maximum speed when going down
    float a; // acceleration, simulates natural acceleration 'g'
};

#endif // __HELLOWORLD_SCENE_H__
