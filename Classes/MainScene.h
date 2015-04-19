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
    enum class GameState
    {
        /// ゲーム中
        PLAYING,
        /// スコア表示
        RESULT
    };
    static cocos2d::Scene*createScene();
    void update(float dt);
    CREATE_FUNC(MainScene);
    // _player変数と、getPlayer()メソッド、setPlayer(Sprite *)メソッドが自動的に実装される
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite *>, _fruits, Fruits);
    CC_SYNTHESIZE(int,_score, Score);
    CC_SYNTHESIZE(float, _second, Second);
    CC_SYNTHESIZE(GameState, _state, State);
    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *, _player, Player);
    CC_SYNTHESIZE_RETAIN(cocos2d::Label *, _scoreLabel,ScoreLabel);
    CC_SYNTHESIZE_RETAIN(cocos2d::Label *, _secondLabel, SecondLabel);
                         
    
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
    
    /** ゲームが終了したときに呼び出されます
     *
     */
    void onResult();
    
    
};



#endif /* defined(__KawazCatch__MainScene__) */
