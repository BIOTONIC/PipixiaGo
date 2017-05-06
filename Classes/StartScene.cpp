#include "StartScene.h"

Scene *StartScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = StartScene::create();

    scene->addChild(layer);

    return scene;
}

bool StartScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // set background
    auto background = Sprite::create("Resources/start_bg_1.png");
    background->setAnchorPoint(cocos2d::Point(0.0f, 0.0f));
    background->setPosition(cocos2d::Point(0.0f, 0.0f));
    addChild(background, 0);

    // set play button
    playBtn = Sprite::create("Resources/start_btn_1.png");
    playBtn->setPosition(cocos2d::Point(130.0f, -35.0f));
    addChild(playBtn, 1);

    // add play button to menu
    auto playMenuItem = MenuItemSprite::create(playBtn, NULL, CC_CALLBACK_1(StartScene::playEvent, this));
    auto menu = Menu::create(playMenuItem, NULL);
    addChild(menu, 2);

    // add animation for play button
    auto animation = Animation::create();
    for (int i = 0; i < 2; i++)
    {
        char pngName[100] = {0};
        sprintf(pngName, "Resources/start_btn_%d.png", i + 1);
        animation->addSpriteFrameWithFile(pngName);
    }
    animation->setDelayPerUnit(0.5f / 2.0f);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(-1);

    auto action = Animate::create(animation);
    playBtn->runAction(Sequence::create(action, action->reverse(), NULL));

    unscheduleUpdate();

    return true;
}

void StartScene::playEvent(Ref *sender)
{
    playBtn->stopAllActions();

    //Create the scene of FishingScene with a transtionFadeBL effect
    auto replaceScene = TransitionFadeBL::create(2, GameScene::createScene());

    //Replace the scene with the trasition effect scene
    Director::getInstance()->replaceScene(replaceScene);
}