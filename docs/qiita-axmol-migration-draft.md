# 10年以上前に作った cocos2d-x ミニゲームを Axmol へ移植し始めた話

## はじめに
昔作った cocos2d-x 2.x のミニゲームを久しぶりに開くと、

- API が古い
- ビルド環境がそのままでは動かない
- どこから直すべきか分からない

という3連コンボに遭遇しがちです。

今回は、2014年前後に作った `rendaPower` という小さなミニゲームを題材に、**cocos2d-x 2.x のコードを Axmol 向けに置き換え始めた手順**をまとめます。

この記事では、プロジェクト全体を一気に最新化するのではなく、まずは `Classes` 配下のゲームロジックを Axmol 記法へ寄せるところまでを扱います。

---

## 元コードの雰囲気
移植前は典型的な cocos2d-x 2.x で、こんな要素が並んでいました。

- `CCLayer`, `CCScene`, `CCSprite`
- `CCDirector::sharedDirector()`
- `CCLabelTTF`
- `menu_selector(...)`
- `callfunc_selector(...)`
- `SimpleAudioEngine`

この世代のコードは、**クラス名に `CC` 接頭辞が付く**、**singleton 取得が `sharedDirector()`**、**コールバックが専用マクロ**、という特徴があります。

Axmol ではこのあたりがかなり整理されているので、まずはそこを置換していきます。

---

## 最初にやったこと: include と型名の置換
一番最初に手を付けたのは、ゲームロジックの中心である `Classes` ディレクトリです。

### 変更前
```cpp
#include "cocos2d.h"

class TitleScene : public cocos2d::CCLayer
```

### 変更後
```cpp
#include "axmol.h"

class TitleScene : public ax::Layer
```

同じノリで、以下を順番に変えました。

- `CCLayer` → `Layer`
- `CCScene` → `Scene`
- `CCSprite` → `Sprite`
- `CCMenu` → `Menu`
- `CCMenuItemImage` → `MenuItemImage`
- `CCLabelTTF` → `Label`
- `cocos2d::` → `ax::`

この置換だけでも、ファイル全体の古さが一気に薄れます。

---

## `sharedDirector()` を `Director::getInstance()` へ
cocos2d-x 2.x では頻出だったのがこれです。

```cpp
CCDirector::sharedDirector()->replaceScene(...);
```

Axmol では次の形に変わります。

```cpp
Director::getInstance()->replaceScene(...);
```

地味ですが、シーン遷移・画面サイズ取得・終了処理など、あらゆる場所に出てくるので、ここを早めに機械的に直すと後が楽になります。

---

## コールバックマクロの移行
旧コードでやや面倒なのが、メニューや遅延処理のコールバックです。

### メニューの変更
変更前:
```cpp
CCMenuItemLabel::create(label, this, menu_selector(TitleScene::NextScene));
```

変更後:
```cpp
MenuItemLabel::create(label, AX_CALLBACK_1(TitleScene::nextScene, this));
```

### 遅延後の関数呼び出し
変更前:
```cpp
CCCallFunc::create(this, callfunc_selector(SplashScene::nextScene));
```

変更後:
```cpp
CallFunc::create(AX_CALLBACK_0(SplashScene::nextScene, this));
```

この変更に合わせて、関数名も `NextScene` のような古い命名から `nextScene` へ寄せました。

---

## オーディオは `SimpleAudioEngine` から一旦卒業
古い cocos2d-x プロジェクトでは `SimpleAudioEngine` を使っていることが多いですが、Axmol では `AudioEngine` を使う方が自然です。

今回はまず最小限として、アプリのライフサイクル処理だけを差し替えました。

```cpp
audio::AudioEngine::pauseAll();
audio::AudioEngine::resumeAll();
```

まだ BGM や SE を本格実装していない段階なら、**最初から全部置き換えようとせず、必要な箇所だけ置換する**のが安全でした。

---

## ついでにリソース参照も掃除した
移植を進めていると、API 置換より先に「画像パスが今の配置と合っていない」問題に当たることがあります。

今回も、例えば以下を修正しました。

- `HelloWorld.png` → `base/HelloWorld.png`
- `CloseNormal.png` → `base/CloseNormal.png`
- `Default-568h@2x.png` → `logo/Default-568h@2x.png`

昔のプロジェクトは、resource search path や IDE 側コピー設定に依存して「たまたま動いていた」ケースがあるので、**この機会に実ファイル構成へ寄せる**のがおすすめです。

---

## ミニゲーム画面も少しだけ今風に整理
今回は `ShuttleScene` に以下を追加して、移植後の見た目が分かりやすいようにしました。

- 宇宙っぽい背景色
- 惑星スプライト
- ロケットスプライト
- ロケットの上下アニメーション
- 「Axmol移植中」というラベル

この段階で重要なのは、ゲームを完成させることよりも、**Axmol でシーン生成・表示・アクション再生が普通に書ける状態へ戻すこと**だと思っています。

---

## ここから先にやること
今回の修正は、あくまで「コードを Axmol 風に置き換えた第一歩」です。
今後は以下が必要になります。

1. Axmol のテンプレートから新しいプロジェクト土台を作る
2. 旧 Xcode / Android プロジェクト設定を捨てて、CMake ベースへ寄せる
3. タッチ入力やサウンド再生を `EventListener` / `AudioEngine::play2d()` へ更新する
4. アセットの search path と解像度戦略を整理する

---

## おわりに
古い cocos2d-x プロジェクトの移植は、全部を同時に直そうとするとかなり重いです。
でも、

1. `Classes` を Axmol 記法へ寄せる
2. 旧 API を機械的に置換する
3. リソース参照を現状に合わせる

という順番で進めると、かなり心理的負担が軽くなります。

同じように「昔の自作ゲームをもう一度動かしたい」と思っている人の参考になればうれしいです。
