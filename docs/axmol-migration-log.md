# cocos2d-x 2.x → Axmol 移植ログ

## 目的
- 2014年前後に作った `rendaPower` を、現在でも触りやすい Axmol ベースの構成に寄せる。
- まずは `Classes` 配下のゲームロジックを、cocos2d-x 2.x 固有APIから Axmol API に置き換える。
- あわせて、Qiita 記事化しやすいように移植観点を記録する。

## 作業前の状態
- `CCLayer` / `CCScene` / `CCSprite` / `CCDirector::sharedDirector()` など cocos2d-x 2.x の命名規則を使用。
- `SimpleAudioEngine` 依存が残っていた。
- `menu_selector` / `callfunc_selector` のような旧式コールバックマクロを利用していた。
- 一部リソース参照パスが現在の `Resources` 配置とずれていた。

## 今回実施した内容

### 1. エンジンAPIの置換
- `#include "cocos2d.h"` / `CCApplication.h` を `#include "axmol.h"` ベースへ変更。
- `cocos2d::` 名前空間を `ax::` に変更。
- `CCLayer`, `CCScene`, `CCSprite`, `CCLabelTTF`, `CCMenu` などを `Layer`, `Scene`, `Sprite`, `Label`, `Menu` に置換。
- `CCDirector::sharedDirector()` を `Director::getInstance()` に変更。
- `CCEGLView::sharedOpenGLView()` を `GLViewImpl` ベースの初期化に変更。
- `kResolutionShowAll` を `ResolutionPolicy::SHOW_ALL` に変更。
- `initGLContextAttrs()` と `registerAllPackages()` の雛形を追加し、Axmol テンプレート寄りの `AppDelegate` に整えた。

### 2. コールバックとアクションの更新
- `menu_selector(...)` を `AX_CALLBACK_1(...)` へ変更。
- `callfunc_selector(...)` を `AX_CALLBACK_0(...)` へ変更。
- `ccp(...)` / `CCPointZero` を `Vec2(...)` / `Vec2::ZERO` に変更。
- `NULL` を `nullptr` に統一。

### 3. オーディオ依存の差し替え
- `SimpleAudioEngine` の include を削除。
- アプリがバックグラウンドに入る時は `audio::AudioEngine::pauseAll()`、復帰時は `resumeAll()` を呼ぶ構成に変更。
- BGM/SE をまだ本格再生していないため、まずはライフサイクル対応のみを Axmol 化した。

### 4. ミニゲーム画面の見直し
- `ShuttleScene` に背景色・惑星・ロケットを表示し、ロケットの上下アニメーションを追加。
- タイトルとメニュー画面も Axmol API に寄せつつ、そのまま触れる状態へ整理した。
- `SplashScene` / `HelloWorldScene` の画像参照パスを現在の `Resources` 構成に合わせて修正した。

## ここまでで見えた次の課題
1. Axmol テンプレート側のプロジェクト生成（CMake / platform projects）を新規に用意する。
2. 旧 `proj.android` / `xcodeproj` は cocos2d-x 2.x 前提なので、ビルド設定は別途刷新する。
3. 入力処理や効果音を増やす場合は `EventListenerTouchOneByOne` と `AudioEngine::play2d()` へ寄せる。
4. 画像・フォント・解像度戦略を Axmol の asset search path で再定義する。

## メモ
- 今回は「旧ゲームロジックを Axmol 記法へ寄せる」ことを優先し、ビルドシステムの全面更新までは着手していない。
- ただし `AppDelegate` は Axmol テンプレートで見かける `initGLContextAttrs()` などの雛形も足し、後続の新規プロジェクト移植で流用しやすくした。
- Qiita 記事では「全部一気に直さず、まず `Classes` をコンパイルしやすい形へ寄せる」流れを書くと再現性が高い。
