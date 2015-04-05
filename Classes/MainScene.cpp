//
//  MainScene.cpp
//  KawazCatch
//
//  Created by niwaka on 2015/04/05.
//
//

#include "MainScene.h"

USING_NS_CC;

// コンストラクタ
MainScene::MainScene()
:_player(NULL)
{
}

// デストラクタ
MainScene::~MainScene()
{
    // _playerをreleaseしてメモリリークを防ぎます
    CC_SAFE_RELEASE_NULL(_player);
}

// layerをsceneに貼り付けて返すクラスメソッド
Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer =MainScene::create();
    scene->addChild(layer);
    return scene;
}

// cocos2dxではinitで初期化処理を行うことが多いです
// 初期化が成功したらtrue、失敗したらfalseを返す
bool MainScene::init()
{
    if(!Layer::init()){
        return false;
    }
    
    // Directorを取り出す
    auto director = Director::getInstance();
    // 画面サイズを取り出す
    auto size = director->getWinSize();
    // 背景のスプライトを生成する
    auto background = Sprite::create("background.png");
    // スプライトの表示位置を設定する
    background->setPosition(Vec2(size.width /2.0 , size.height / 2.0));
    // 親ノードにスプライトを追加する
    this->addChild(background);
   
    // Spriteを生成して_playerに格納
    this->setPlayer(Sprite::create("player.png"));
    // _playerの位置を設定
    _player->setPosition(Vec2(size.width /2.0, size.height - 445));
    // シーンに_playerを配置
    this->addChild(_player);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event* event){
        // タッチされたときの処理
        log("Touch at (%f, %f)", touch->getLocation().x, touch->getLocation().y);
        return true;
    };
    
    listener->onTouchMoved = [this](Touch* touch, Event* event){
        // タッチ中に動いたときの処理
        // 前回のタッチ位置との差をベクトルで取得する
        Vec2 delta = touch->getDelta();
        
        // 現在のかわずたんの座標を取得する
        Vec2 position = _player->getPosition();
        
        // 現在座標 + 移動量を新たな座標にする
        Vec2 newPosition = position + delta;
        _player->setPosition(newPosition);
    };
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    return true;
}
