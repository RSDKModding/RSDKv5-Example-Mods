#include "ModConfig.h"
#include "Objects/All.h"

ModConfig config;

bool32 (*MathHelpers_PointInHitbox)(int32 thisX1, int32 thisY1, int32 otherX1, int32 otherY1, int32 direction, Hitbox *hitbox);

int32 extraWidth;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void SetExtraWidth(void *d)
{
    (void)d;
    extraWidth = (ScreenInfo->width - 424) / 2;
}

void InitModAPI(void)
{
    // Setup Config
    Mod.SaveSettings();

    MOD_REGISTER_OBJ_OVERLOAD(UIDiorama, UIDiorama_Update, NULL, NULL, NULL, UIDiorama_Create, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(MainMenu, NULL, NULL, MainMenu_StaticUpdate, NULL, NULL, NULL, NULL, NULL, NULL);

    MathHelpers_PointInHitbox = Mod.GetPublicFunction(NULL, "MathHelpers_PointInHitbox");

    // be extra sure
    Mod.AddModCallback(MODCB_ONSTATICUPDATE, SetExtraWidth);
}

#if RETRO_USE_MOD_LOADER
#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id)
{
#if MANIA_USE_PLUS
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

    globals = Mod.GetGlobals();

    modID = id;

    InitModAPI();

    return true;
}
#endif