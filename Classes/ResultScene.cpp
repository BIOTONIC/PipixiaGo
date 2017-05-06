#include "ResultScene.h"
#include "GameScene.h"

Scene *ResultScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = ResultScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool ResultScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto winSize = Director::getInstance()->getWinSize();

    // set result background
    auto background = Sprite::create("Resources/result_bg.png");
    background->setAnchorPoint(cocos2d::Point(0.0f, 0.0f));
    background->setPosition(cocos2d::Point(0.0f, 0.0f));
    addChild(background, 0);

    // set game over sprite
    auto gameover = Sprite::create("Resources/gameover.png");
    gameover->setPosition(cocos2d::Point(400.0f, 400.0f));
    addChild(gameover, 1);

    // set replay button
    auto replayBtn = Sprite::create("Resources/replay.png");
    replayBtn->setPosition(cocos2d::Point(0.0f, -10.0f));
    addChild(replayBtn, 2);

    // add replay button to menu
    auto replayMenuItem = MenuItemSprite::create(replayBtn, NULL, CC_CALLBACK_1(ResultScene::replayEvent, this));
    auto menu = Menu::create(replayMenuItem, NULL);
    addChild(menu, 3);
    return true;
}


void ResultScene::replayEvent(Ref *sender)
{
    auto gameScene = GameScene::createScene();

    Director::getInstance()->replaceScene(gameScene);
}
