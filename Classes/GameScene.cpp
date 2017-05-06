#include <iostream>
#include "GameScene.h"
#include "ResultScene.h"
#include "PortInclude.h"

Scene *GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    pauseBtn = Button::create(
            "Resources/pause_btn.png",
            "Resources/pause_btn.png");

    pauseBtn->setPosition(Vec2(origin.x + visibleSize.width - pauseBtn->getContentSize().width / 2,
                               origin.y + visibleSize.height - pauseBtn->getContentSize().height / 2));

    pauseBtn->addTouchEventListener(CC_CALLBACK_2(GameScene::pauseBtnCallback, this));

    this->addChild(pauseBtn, 1);

    label = Label::createWithTTF("game scene", "Resources/fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 2);

    // add sprite
    sprite = Sprite::create("Resources/actor_1.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width / 6 * 2 + origin.x, visibleSize.height / 5 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 3);

    // add animation sprite
    auto animation = Animation::create();
    for (int i = 0; i < 6; i++)
    {
        char pngName[100] = {0};
        sprintf(pngName, "Resources/actor_%d.png", i + 1);
        animation->addSpriteFrameWithFile(pngName);
    }
    animation->setDelayPerUnit(0.3f);
    animation->setRestoreOriginalFrame(true);
    action = Animate::create(animation);
    sprite->runAction(RepeatForever::create(action));

    sceneMa = (SceneManager *) SceneManager::create();
    this->addChild(sceneMa);

    this->schedule(schedule_selector(GameScene::update));

    // init values

    maxSpeed = 4;

    a = maxSpeed / 60 / 1;

    speed = 10;

    minVoice = 0.01;

    maxVoice = minVoice;

    s = 2;

    maxY = origin.y + visibleSize.height - sprite->getBoundingBox().size.height / 2;

    isPause = false;

    isTerminate = false;

    portInit();

    return true;
}

int GameScene::portInit()
{
    fflush(stdout);

    // total numbers of samples
    numSamples = RECORD_TIME * SAMPLE_RATE * NUM_CHANNELS;

    // allocate memory for these samples
    recordedSamples = (SAMPLE *) malloc(numSamples * sizeof(SAMPLE));
    if (recordedSamples == NULL)
    {
        printf("Could not allocate record array.\n");
        exit(1);
    }
    for (int i = 0; i < numSamples; i++)
    {
        recordedSamples[i] = 0;
    }

    err = Pa_Initialize();
    if (err != paNoError) goto error;

    inputParameters.device = Pa_GetDefaultInputDevice();
    if (inputParameters.device == paNoDevice)
    {
        fprintf(stderr, "Error: No default input device.\n");
        goto error;
    }
    inputParameters.channelCount = NUM_CHANNELS;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    // record some audio
    err = Pa_OpenStream(
            &stream,
            &inputParameters,
            NULL, //&outputParameters
            SAMPLE_RATE,
            FRAMES_PER_BUFFER,
            0, // paClipOff, we won't output out of range samples so don't bother clipping them
            NULL, // no callback, use blocking API
            NULL); // no callback, so no callback userData

    if (err != paNoError) goto error;
    err = Pa_StartStream(stream);
    if (err != paNoError) goto error;
    printf("Now recording!!\n");
    fflush(stdout);

    return 0;

    error:
    portTerminate();
    fprintf(stderr, "An error occured while using the portaudio stream\n");
    fprintf(stderr, "Error number: %d\n", err);
    fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
    return -1;
}

void GameScene::portTerminate()
{
    if (!isTerminate)
    {
        Pa_CloseStream(stream);
        Pa_Terminate();
        isTerminate = true;
    }
    return;
}

void GameScene::update(float delta)
{
    // get input voice per frame and then set y position of the sprite

    sceneMa->SetIsMove(false);

    getVoice();

    if (isPause)
    {
        return;
    }

    float posY = sprite->getPosition().y;


    if (posY < -100)
    {
        isPause = true;
        portTerminate();

        auto resultScene = ResultScene::createScene();
        Director::getInstance()->replaceScene(resultScene);
    }

    if (speed > 0 && posY > maxY)
    {
        // sprite is at the top
        speed = 0;
    } else
    {
        // go up & go down
        sprite->setPositionY(posY + speed);
    }

    if (!sceneMa->isCollision(sprite))
    {
        if (speed > (-1 * maxSpeed))
            // add speed by acceleration when going down
            speed -= a;
        sceneMa->SetIsMove(true);
    } else
    {
        if (speed < 0 && sceneMa->isCollision(sprite) == 1)
        {
            // is collide when going down
            speed = 0;
            maxVoice = minVoice;
        }
    }

}

void GameScene::getVoice()
{
    // read input voice samples stream into recordedSamples
    if (recordedSamples == nullptr)
    {
        return;
    }
    err = Pa_ReadStream(stream, recordedSamples, numSamples);
    if (err != paNoError)
    {
        portTerminate();
        fprintf(stderr, "An error occured while using the portaudio stream\n");
        fprintf(stderr, "Error number: %d\n", err);
        fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
        return;
    }

    // get maximum voice in all samples
    max = 0;
    for (int i = 0; i < numSamples; i++)
    {
        val = recordedSamples[i];
        if (val < 0)
        {
            // ABS
            val = -val;
        }
        if (val > max)
        {
            max = val;
        }
    }

    if (!isPause)
    {
        label->setString(StringUtils::format("%.4f", max));
    }

    sceneMa->SetIsMove(false);

    if (maxVoice < max)
    {
        // update maxVoice and speed
        maxVoice = max;
        speed += max * s;
    }
}

void GameScene::pauseBtnCallback(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        isPause = !isPause;
        if (isPause)
        {
            pauseBtn->loadTextureNormal("Resources/resume_btn.png");
        } else
        {
            pauseBtn->loadTextureNormal("Resources/pause_btn.png");
        }

    }
}