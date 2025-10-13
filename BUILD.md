# 吉里吉里X ビルドガイド

このドキュメントでは、吉里吉里Xのビルド方法について説明します。

## 必要な環境

### 共通

- **CMake**: 3.21以降
- **Ninja**: 推奨（高速ビルド）
- **C++20対応コンパイラ**

### Windows

以下のいずれかのコンパイラ環境：

- **MSVC**: Visual Studio 2019以降
- **MinGW-w64**: GCC 11以降

### Linux

- **GCC**: 11以降 または **Clang**: 13以降
- **pkg-config**: libadwaita-1の検索に必要
- **libadwaita-1**: GTK4ベースのUIライブラリ

```bash
# Ubuntu/Debian
sudo apt install build-essential cmake ninja-build pkg-config libadwaita-1-dev

# Fedora
sudo dnf install gcc-c++ cmake ninja-build pkg-config libadwaita-devel

# Arch Linux
sudo pacman -S base-devel cmake ninja pkg-config libadwaita
```

## ビルド方法

### 方法1: CMakeプリセットを使用（推奨）

CMakeプリセットを使うと、プラットフォームとビルドタイプを簡単に選択できます。

#### Windows (MSVC)

```powershell
# デバッグビルド
cmake --preset windows-msvc-debug
cmake --build --preset windows-msvc-debug

# リリースビルド
cmake --preset windows-msvc-release
cmake --build --preset windows-msvc-release
```

#### Windows (MinGW)

```bash
# デバッグビルド
cmake --preset windows-mingw-debug
cmake --build --preset windows-mingw-debug

# リリースビルド
cmake --preset windows-mingw-release
cmake --build --preset windows-mingw-release
```

#### Linux

```bash
# デバッグビルド
cmake --preset linux-debug
cmake --build --preset linux-debug

# リリースビルド
cmake --preset linux-release
cmake --build --preset linux-release
```

### 方法2: 従来の方法

```bash
# ビルドディレクトリの作成
mkdir build
cd build

# 設定
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release

# ビルド
cmake --build .
```

## 実行

ビルドが成功すると、以下の場所に実行ファイルが生成されます：

```
build/<プリセット名>/bin/krkrx
```

例：
```bash
# Windows MSVC Releaseビルドの場合
.\build\windows-msvc-release\bin\krkrx.exe

# Linux Releaseビルドの場合
./build/linux-release/bin/krkrx
```

## テストの実行

### プリセットを使用

```bash
# Windows MSVC
ctest --preset windows-msvc-debug

# Linux
ctest --preset linux-debug
```

### 従来の方法

```bash
cd build
ctest --output-on-failure

# または
cmake --build . --target run_tests
```

## IDE統合

### Visual Studio Code

VS Codeは`CMakePresets.json`を自動認識します。

1. **CMake Tools**拡張機能をインストール
2. Ctrl+Shift+P → "CMake: Select Configure Preset"
3. 目的のプリセットを選択
4. F7でビルド

### Visual Studio 2022

Visual Studio 2022は`CMakePresets.json`をネイティブサポートします。

1. プロジェクトフォルダを開く
2. "プロジェクト" → "CMakeプリセットの管理"
3. 目的のプリセットを選択
4. Ctrl+Shift+Bでビルド

### CLion

CLionもCMakeプリセットに対応しています。

1. プロジェクトを開く
2. Settings → Build, Execution, Deployment → CMake
3. "Enable CMake Presets"を有効化
4. ビルド設定でプリセットを選択

## トラブルシューティング

### SDL2のダウンロードに失敗する

ネットワーク環境によっては、FetchContentでのダウンロードに失敗することがあります。
その場合は再度ビルドを試してください。

### Windows: UTF-8関連のエラー

MSVCでUTF-8関連のエラーが出る場合、`/utf-8`オプションは自動で設定されています。
それでもエラーが出る場合は、ソースファイルがUTF-8 BOM付きで保存されているか確認してください。

### Linux: libadwaita-1が見つからない

```bash
# パッケージがインストールされているか確認
pkg-config --modversion libadwaita-1

# インストールされていない場合
sudo apt install libadwaita-1-dev  # Ubuntu/Debian
```

## 詳細設定

### ビルドオプション

CMakeキャッシュ変数で動作をカスタマイズできます：

```bash
cmake --preset linux-debug \
  -DBUILD_TESTING=OFF        # テストを無効化
```

### クリーンビルド

```bash
# ビルドディレクトリを削除
rm -rf build

# 再度ビルド
cmake --preset <プリセット名>
cmake --build --preset <プリセット名>
```

## 高度な使い方

### コンパイルデータベースの生成

C++のインテリセンスやlinterで使用する`compile_commands.json`は自動生成されます：

```
build/<プリセット名>/compile_commands.json
```

### 並列ビルド

Ninjaは自動で並列ビルドしますが、明示的に指定することも可能です：

```bash
cmake --build --preset <プリセット名> -j 8
```

## プロジェクト構造

```
kirikiri-x/
├── cmake/                    # CMakeモジュール
│   ├── CompilerSettings.cmake  # コンパイラ設定
│   ├── Dependencies.cmake      # 外部依存関係
│   └── Platform.cmake          # プラットフォーム設定
├── src/
│   ├── runtime/              # ランタイムライブラリ
│   ├── platforms/            # プラットフォーム実装
│   │   ├── windows/
│   │   └── linux/
│   ├── tests/                # テスト
│   └── third_party/          # サードパーティライブラリ
├── CMakeLists.txt            # メインCMake設定
├── CMakePresets.json         # ビルドプリセット
└── BUILD.md                  # このファイル
```

## 依存関係

以下のライブラリは自動でダウンロード・ビルドされます：

- **SDL2** 2.32.4: マルチメディア機能
- **Google Test**: テストフレームワーク
- **oniguruma**: 正規表現エンジン（サブディレクトリに含まれる）

