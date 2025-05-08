#include "GameAPI/Game.hpp"

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
#endif

void InitModAPI(void);