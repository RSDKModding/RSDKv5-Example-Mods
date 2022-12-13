#include "ModConfig.h"
#include "Objects/All.h"

ModConfig config;

ObjectZone *Zone;

bool32 (*MathHelpers_PointInHitbox)(int32 thisX1, int32 thisY1, int32 otherX1, int32 otherY1, int32 direction, Hitbox *hitbox);

int32 extraWidth;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void SetExtraWidth(void *d)
{
    UNUSED(d);
    extraWidth = (ScreenInfo->size.x - 424) / 2;
}

void InitModAPI(void)
{
    // Setup Config
    Mod.SaveSettings();

    MOD_REGISTER_OBJ_OVERLOAD(UIDiorama, NULL, NULL, NULL, NULL, UIDiorama_Create, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(MainMenu, NULL, NULL, MainMenu_StaticUpdate, NULL, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(CutsceneSeq, NULL, CutsceneSeq_LateUpdate, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    MathHelpers_PointInHitbox = Mod.GetPublicFunction(NULL, "MathHelpers_PointInHitbox");

    SpiderMobile_StateBody_AwaitPlayer = Mod.GetPublicFunction(NULL, "SpiderMobile_StateBody_AwaitPlayer");
    Mod.RegisterStateHook(SpiderMobile_StateBody_AwaitPlayer, SpiderMobile_StateBody_AwaitPlayer_Pre, true);
    Mod.RegisterStateHook(SpiderMobile_StateBody_AwaitPlayer, SpiderMobile_StateBody_AwaitPlayer_Hook, false);

    HeavyShinobi_State_Init = Mod.GetPublicFunction(NULL, "HeavyShinobi_State_Init");
    Mod.RegisterStateHook(HeavyShinobi_State_Init, HeavyShinobi_State_Init_Hook, false);

    FBZ1Outro_Cutscene_PrepareFBZ2 = Mod.GetPublicFunction(NULL, "FBZ1Outro_Cutscene_PrepareFBZ2");

    MOD_REGISTER_OBJECT_HOOK(SpiderMobile);
    MOD_REGISTER_OBJECT_HOOK(Zone);

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