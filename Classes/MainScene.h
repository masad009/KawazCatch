//
//  MainScene.h
//  KawazCatch
//
//  Created by niwaka on 2015/04/05.
//
//

#ifndef __KawazCatch__MainScene__
#define __KawazCatch__MainScene__

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
protected:
    MainScene();
    virtual ~MainScene();
    bool init() override;
    
public:
    static cocos2d::Scene*createScene();
    CREATE_FUNC(MainScene);
    // _player変数と、getPlayer()メソッド、setPlayer(Sprite *)メソッドが自動的に実装される
    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *, _player, Player);
    
    
};

#endif /* defined(__KawazCatch__MainScene__) */
