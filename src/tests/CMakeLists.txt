# ===========================================
# KirikiriX テストスイート
# ===========================================

# === テストの有効化 ===
enable_testing()

# === テストソースの収集 ===
set(TEST_SOURCES
    main.cc
    core/native_instances/rect.cc
)

# === テスト実行ファイルの作成 ===
add_executable(krkrx_test ${TEST_SOURCES})

# エイリアスの作成
add_executable(krkrx::test ALIAS krkrx_test)

# === インクルードディレクトリ ===
target_include_directories(krkrx_test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# === 依存ライブラリ ===
target_link_libraries(krkrx_test
    PRIVATE
        GTest::gtest_main   # Google Testメインエントリーポイント
        runtime             # KirikiriXランタイム
)

# === ターゲットのプロパティ ===
set_target_properties(krkrx_test PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# === テストの登録 ===
include(GoogleTest)
gtest_discover_tests(krkrx_test
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# テスト実行ターゲットの追加
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS krkrx_test
    COMMENT "全テストを実行中..."
)