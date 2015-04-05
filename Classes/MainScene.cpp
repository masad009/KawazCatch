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
{
}

// デストラクタ
MainScene::~MainScene()
{
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
    return true;
}



