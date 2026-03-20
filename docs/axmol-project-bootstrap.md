# Axmol プロジェクト起こし手順

## なぜ必要か
このリポジトリにある `rendaPower.xcodeproj` / `proj.android` は cocos2d-x 2.x 前提のプロジェクトです。
`Classes` のソースを Axmol 記法へ寄せても、**そのまま旧プロジェクト設定では Axmol ヘッダやライブラリを見つけられません**。

そのため、Axmol 側の公式フローに合わせて、**新しい Axmol プロジェクトを生成してから `Classes` と `Resources` を移植する**前提で進めます。

## 前提
- Axmol をインストール済みで、`axmol` コマンドが使えること。
- Axmol 公式ドキュメントでも、まず `axmol new` でプロジェクトを作り、`CMakeLists.txt` を中心に構成する流れが案内されています。

## 最短手順
### 1. スクリプトを使う
```bash
./scripts/bootstrap_axmol_project.sh
```

デフォルトでは `build/axmol_port/rush_freak_axmol` に新規プロジェクトを作成します。

### 2. 直接コマンドを打つ
```bash
axmol new -p dev.roripika.rushfreak -d build/axmol_port -l cpp rush_freak_axmol
```

### 3. 生成後に移すもの
- `rendaPower/Classes/*.h`, `rendaPower/Classes/*.cpp` → `Source/`
- `rendaPower/Resources/*` → `Content/`

### 4. ビルドファイルを生成する
```bash
axmol build -p win32 -c
```

`win32` は一例です。必要に応じて `ios` や `android` などへ読み替えてください。

## 補足
- 現在のブランチで行っているのは、**旧 `Classes` を Axmol で再利用しやすい記法へ寄せる作業**です。
- 実際のビルド入口は、旧 `xcodeproj` を延命するよりも、Axmol が生成する新しいプロジェクトへ移す方が安全です。
- Qiita 記事では「まず source-level migration を済ませ、その後 `axmol new` プロジェクトへ入れ替える」という二段階構成で書くと伝わりやすいです。
