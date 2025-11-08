#include "console_impl.h"

void WindowsConsole::write(const tjs_char *text) {
    int mbsize = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)text, -1, NULL, 0, NULL, NULL);
    auto mbstr = new char[mbsize];
    WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)text, -1, mbstr, mbsize, NULL, NULL);
    std::cout << mbstr;
}

void WindowsConsole::error(const tjs_char *text) {
    int mbsize = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)text, -1, nullptr, 0, NULL, NULL);
    auto mbstr = new char[mbsize];
    WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)text, -1, mbstr, mbsize, NULL, NULL);
    std::cerr << mbstr;
}

size_t WindowsConsole::readline(ttstr &result) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    std::wstring readresult;
    const size_t CHUNK_SIZE = 1024;
    wchar_t buffer[CHUNK_SIZE];
    DWORD charsRead;
    bool hasMore = true;
    
    // バッファサイズを超える入力に対応するため、チャンク単位で読み込む
    while (hasMore) {
        if (ReadConsoleW(hStdin, buffer, CHUNK_SIZE, &charsRead, nullptr)) {
            // 改行文字を探し，見つかれば読み取り終了
            for (size_t i = 0; i < charsRead; i++) {
                if (buffer[i] == L'\r' && i + 1 < charsRead && buffer[i + 1] == L'\n') {
                    readresult.append(buffer, i);
                    hasMore = false;
                    break;
                }
            }
            
            // 改行文字が見つからない場合はバッファの内容を追加
            if (hasMore) readresult.append(buffer, charsRead);
        } else {
            // 読み込みに失敗した場合は仕方ないので，読み取り終了
            hasMore = false;
            break;
        }
    }

#ifdef _MSC_VER
    result = readresult;
    return result.length();
#else
    std::u16string res((const char16_t*)readresult.c_str());
    result = res;
    return result.length();
#endif
}

