# 吉里吉里X (Kirikiri X)

> ⚠️ **開発中**: 現在開発中のプロジェクトです。動作は不安定な可能性があります。

マルチプラットフォーム対応を目的とした吉里吉里Zベースのランタイムエンジン

## ビルド方法

詳細なビルド手順は **[BUILD.md](BUILD.md)** をご覧ください。

### クイックスタート

```bash
# Windows (MSVC)
cmake --preset windows-msvc-release
cmake --build --preset windows-msvc-release

# Linux
cmake --preset linux-release
cmake --build --preset linux-release
```

## 対応予定プラットフォーム

- ✅ Windows (MSVC / MinGW)
- ✅ Linux (GCC / Clang)
- 🚧 macOS (未着手)

## 主な機能

- TJS2スクリプトエンジン
- マルチメディア機能
- プラットフォーム抽象化レイヤー
- モダンなC++20実装

## ライセンス

詳細は [LICENSE.txt](LICENSE.txt) をご覧ください。