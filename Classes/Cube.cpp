#include "Cube.h"

bool Cube::init(){
    
    return true;
}

void Cube::initSize(int index){
    
    
    Sprite* sprite = getSprite();
    sprite->setPositionX(resetX(index));
    if (index>0)
        resetSize();
    else{
        sprite->setScaleX(8);
        
        
        
        sprite->setScaleY(2);
    }
    
    
}

void Cube::reset(){
    
    Sprite* sprite = getSprite();
    sprite->setPositionX(resetX(4));
    
    resetSize();
}

float Cube::resetX(int i){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    return origin.x + visibleSize.width / 3 *2 * i;
    
    
    
}

void Cube::resetSize(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* sprite = getSprite();
    float max = visibleSize.width*0.6 / 100;
    float min = visibleSize.width*0.3 / 100;
    sprite->setScaleX(min + (max - min)*CCRANDOM_0_1());
    
    max = visibleSize.height*0.5 / 100;
    min = visibleSize.height*0.15 / 100;
    
    sprite->setScaleY(min + (max - min)*CCRANDOM_0_1());
}
