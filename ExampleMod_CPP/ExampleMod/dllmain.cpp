#include "../GameAPI/CPP/GameAPI/Game.hpp"

using namespace RSDK;

ManiaGlobalVariables *maniaGlobals = nullptr;

#if RETRO_USE_MOD_LOADER
extern "C" {
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
}
#endif

void InitModAPI(void) { Dev::Print(Dev::PRINT_NORMAL, "Hello From Example Mod (C++)!\n"); }

#if RETRO_USE_MOD_LOADER
#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id)
{
#if !RETRO_REV01
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

    maniaGlobals = (ManiaGlobalVariables *)Mod::GetGlobals();

    InitModAPI();

    return true;
}
#endif