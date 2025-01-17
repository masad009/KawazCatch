//
//  MainScene.cpp
//  KawazCatch
//
//  Created by niwaka on 2015/04/05.
//
//

#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"

USING_NS_CC;

/// フルーツの画面上端からのマージン(px)
const int FRUIT_TOP_MARGIN = 40;
/// 制限時間
const float TIME_LIMIT_SECOND = 60;
/// フルーツの出現率
const int FRUIT_SPAWN_RATE = 20;

// コンストラクタ
MainScene::MainScene()
:_score(0)
,_second(TIME_LIMIT_SECOND)
,_state(GameState::PLAYING)
,_player(NULL)
,_scoreLabel(NULL)
,_secondLabel(NULL)
{
}

// デストラクタ
MainScene::~MainScene()
{
    // _playerをreleaseしてメモリリークを防ぎます
    CC_SAFE_RELEASE_NULL(_player);
    CC_SAFE_RELEASE_NULL(_scoreLabel);
    CC_SAFE_RELEASE_NULL(_secondLabel);
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

        // 画面サイズを取り出す
        auto winSize = Director::getInstance()->getWinSize();
        newPosition = newPosition.getClampPoint(Vec2(0,position.y), Vec2(winSize.width,position.y));
        _player->setPosition(newPosition);
    };
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    
    // updateを毎フレーム実行するように登録する
    this->scheduleUpdate();
    
    // スコアラベルの追加
    auto scoreLabel = Label::createWithSystemFont(StringUtils::toString(_score),"Marker Felt", 16);
    
    scoreLabel->enableShadow(Color4B::BLACK, Size(0.5,0.5),3);
    scoreLabel->enableOutline(Color4B::BLACK,1.5);
    
    scoreLabel->setPosition(Vec2(size.width/ 2.0 * 1.5, size.height - 40 ));
    this->setScoreLabel(scoreLabel);
    this->addChild(_scoreLabel);
    
    // タイマーラベルの追加
    int second = static_cast<int>(_second); // int型にキャストする
    auto secondLabel = Label::createWithSystemFont(StringUtils::toString(second), "Marker Felt", 16);
    this->setSecondLabel(secondLabel);
    secondLabel->enableShadow(Color4B::BLACK,Size(0.5,0.5),3);
    secondLabel->enableOutline(Color4B::BLACK, 1.5);
    secondLabel->setPosition(Vec2(size.width /2.0, size.height -40));
    this->addChild(secondLabel);
    
    // タイマーヘッダーの追加
    auto secondLabelHeader = Label::createWithSystemFont("TIME","Marker Felt" ,16);
    secondLabelHeader->enableShadow(Color4B::BLACK,Size(0.5,0.5),3);
    secondLabelHeader->enableOutline(Color4B::BLACK,1.5);
    secondLabelHeader->setPosition(Vec2(size.width/2.0, size.height -20));
    this->addChild(secondLabelHeader);
    
    
    // スコアヘッダーの追加
    auto scoreLabelHeader = Label::createWithSystemFont("SCORE", "Marker Felt", 16);
    scoreLabelHeader->enableShadow(Color4B::BLACK,Size(0.5,0.5), 3);
    scoreLabelHeader->enableOutline(Color4B::BLACK, 1.5);
    scoreLabelHeader->setPosition(Vec2(size.width/2.0 * 1.5,size.height - 20));
    this->addChild(scoreLabelHeader);
    return true;
}


Sprite* MainScene::addFruit()
{
    // 画面サイズを取り出す
    auto winSize = Director::getInstance()->getWinSize();
    // フルーツの種類を選択する
    int fruitType = rand() % static_cast<int>(FruitType::COUNT);
    // フルーツを作成する
    std::string filename = StringUtils::format("fruit%d.png", fruitType);
    auto fruit = Sprite:: create(filename);
    fruit->setTag(fruitType); // フルーツの種類をタグとして指定する
    
    auto fruitSize = fruit->getContentSize();// フルーツのサイズを取り出す
    float fruitXPos = rand() % static_cast<int>(winSize.width); //X軸のランダムな位置を選択する
    
    fruit->setPosition(Vec2(fruitXPos,winSize.height - FRUIT_TOP_MARGIN - fruitSize.height / 2.0));
    
    this->addChild(fruit);
    _fruits.pushBack(fruit); // _fruitsベクターにフルーツを追加する
    
    // フルーツに動きをつける
    // 地面の座標
    auto ground = Vec2(fruitXPos, 0);
    // ３秒かけてgroundの位置まで落下させるアクション
    auto fall = MoveTo::create(3, ground);

    
    // removeFruitを即座に呼び出すアクション
    auto remove = CallFuncN::create([this](Node * node){
        // NodeをSpriteにダウンキャストする
        auto sprite = dynamic_cast<Sprite *>(node);
        
        // removeFruitを呼び出す
        this->removeFruit(sprite);
    });
    
    // fallとremoveを連続して実行させるアクション
    auto sequence = Sequence::create(fall, remove, NULL);
    fruit->runAction(sequence);
    return fruit;
};

bool MainScene::removeFruit(cocos2d::Sprite *fruit)
{
    // _fruitsにfruitが含まれているかを確認する
    if(_fruits.contains(fruit)){
        // 親ノードから削除する
        fruit->removeFromParent();
        // _fruit配列から削除する
        _fruits.eraseObject(fruit);
        return true;
    }
    return false;
}

void MainScene::update(float dt)
{
    if(_state == GameState::PLAYING)// プレイ中のとき
    {
        // 毎フレーム実行される
        int random = rand() % FRUIT_SPAWN_RATE;
        if(random == 0){// 適当な乱数が0のとき
            this->addFruit();
        }
    
        for(auto& fruit : _fruits){
            Vec2 busketPosition = _player->getPosition() - Vec2(0,10);
            Rect boundingBox = fruit->getBoundingBox(); // フルーツの短形を取り出す
            bool isHit = boundingBox.containsPoint(busketPosition);
            if(isHit){
                this->catchFruit(fruit);
            }
        }
    
        // 残り秒数を減らす
        _second-= dt;
        // 残り秒数の表示を更新する
        int second = static_cast<int>(_second);// int型にキャストする
        _secondLabel->setString(StringUtils::toString(second));
    
        if(_second < 0){ // 制限時間が0になったら
            // リザルト状態へ移行
            _state = GameState::RESULT;
            this->onResult();
        }
    }
};

void MainScene::catchFruit(cocos2d::Sprite *fruit)
{
    // フルーツを削除する
    this->removeFruit(fruit);
    // スコアを一点追加する
    _score +=1;
    // スコア用のラベルの表示を更新している
    _scoreLabel->setString(StringUtils::toString(_score));

}

void MainScene::onResult()
{
    _state = GameState::RESULT;
    auto winSize = Director::getInstance()->getWinSize();
    
    // 「もう一度遊ぶ」ボタン
    auto replayButton = MenuItemImage::create("replay_button.png","replay_button_pressed.png",[](Ref* ref){
        // 「もう一度遊ぶ」ボタンを押した時の処理
        // 新しくMainSceneを作成して置き換えてやる
        auto scene = MainScene::createScene();
        Director::getInstance()->replaceScene(scene);
    });
    
    // 「タイトルへ戻る」ボタン
    auto titleButton = MenuItemImage::create("title_button.png", "title_button_pressed.png", [](Ref* ref){
       // 「タイトルへ戻る」ボタンを押した時の処理
       // 今は何も実装していない
    });
    
    // 2つのボタンからメニューを作成する
    auto menu = Menu::create(replayButton, titleButton, NULL);
    // ボタンを縦に並べる
    menu->alignItemsVerticallyWithPadding(15);// ボタンを縦に並べる
    menu->setPosition(Vec2(winSize.width / 2.0 , winSize.height / 2.0));
    this->addChild(menu);
    
}

void MainScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    // BGMを作成する
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);
    
}



