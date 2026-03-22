#include "axmol.h"
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
#include "NativeCodeAst.h"
#include "NativeCodeAstJni.h"

namespace AstExt
{
    void NativeCodeAst::initAst()
    {
        ::NativeCodeAstJni::initAstJni();
    }
    void NativeCodeAst::showAst()
    {
        ::NativeCodeAstJni::showAstJni();
    }
    void NativeCodeAst::hideAst()
    {
        ::NativeCodeAstJni::hideAstJni();
    }
}
#endif
