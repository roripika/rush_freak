#ifndef NativeCodeAst_h
#define NativeCodeAst_h

namespace AstExt {
    class NativeCodeAst {
    public:
        // 広告表示開始用と、停止用、そして初期化用の3つのメソッドを定義
        static void initAst();
        static void showAst();
        static void hideAst();

    };
}