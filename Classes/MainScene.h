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
    void update(float dt);
    CREATE_FUNC(MainScene);
    // _player変数と、getPlayer()メソッド、setPlayer(Sprite *)メソッドが自動的に実装される
    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *, _player, Player);
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite *>, _fruits, Fruits);
    
private:
    enum class FruitType
    {
        /// リンゴ
        APPLE,
        /// ぶどう
        GRAPE,
        /// みかん
        ORANGE,
        /// バナナ
        BANANA,
        /// さくらんぼ
        CHERRY,
        /// 最大値
        COUNT
    };

    /** 画面にフルーツを新たに配置して、それを返します
     * @return
     */
    cocos2d::Sprite* addFruit();

    /** マップからフルーツを取り除きます
     * @param fruit 削除するフルーツ
     * @return ただしk削除されたか
     */
    bool removeFruit(cocos2d::Sprite * fruit);

    /** フルーツを取得します
     * @param Sprite* 取得するフルーツ
     */
    void catchFruit(cocos2d::Sprite* fruit);

};



#endif /* defined(__KawazCatch__MainScene__) */
