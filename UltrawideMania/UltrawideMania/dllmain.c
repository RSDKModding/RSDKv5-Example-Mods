#include "Objects/All.h"

ObjectZone *Zone;
ObjectPlayer *Player;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
    MOD_REGISTER_OBJ_OVERLOAD(CutsceneSeq, NULL, CutsceneSeq_LateUpdate, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
#if MANIA_USE_PLUS
    MOD_REGISTER_OBJ_OVERLOAD(UIDiorama, NULL, NULL, NULL, NULL, UIDiorama_Create, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(MainMenu, NULL, NULL, MainMenu_StaticUpdate, NULL, NULL, NULL, NULL, NULL, NULL);

    MathHelpers_PointInHitbox = Mod.GetPublicFunction(NULL, "MathHelpers_PointInHitbox");
#endif

    SpiderMobile_StateBody_AwaitPlayer = Mod.GetPublicFunction(NULL, "SpiderMobile_StateBody_AwaitPlayer");
    Mod.RegisterStateHook(SpiderMobile_StateBody_AwaitPlayer, SpiderMobile_StateBody_AwaitPlayer_Hook, false);

    HeavyShinobi_State_Init = Mod.GetPublicFunction(NULL, "HeavyShinobi_State_Init");
    Mod.RegisterStateHook(HeavyShinobi_State_Init, HeavyShinobi_State_Init_Hook, false);

    CrimsonEye_StateContainer_SetupArena  = Mod.GetPublicFunction(NULL, "CrimsonEye_StateContainer_SetupArena");
    CrimsonEye_StateContainer_AwaitPlayer = Mod.GetPublicFunction(NULL, "CrimsonEye_StateContainer_AwaitPlayer");
    Mod.RegisterStateHook(CrimsonEye_StateContainer_SetupArena, CrimsonEye_StateContainer_SetupArena_Hook, false);
    Mod.RegisterStateHook(CrimsonEye_StateContainer_AwaitPlayer, CrimsonEye_StateContainer_AwaitPlayer_Hook, false);

    BigSqueeze_StateManager_SetupIntro = Mod.GetPublicFunction(NULL, "BigSqueeze_StateManager_SetupIntro");
    BigSqueeze_StateManager_SetupArena = Mod.GetPublicFunction(NULL, "BigSqueeze_StateManager_SetupArena");
    Mod.RegisterStateHook(BigSqueeze_StateManager_SetupIntro, BigSqueeze_StateManager_SetupIntro_Hook, false);
    Mod.RegisterStateHook(BigSqueeze_StateManager_SetupArena, BigSqueeze_StateManager_SetupArena_Hook, false);

    FBZ1Outro_Cutscene_PrepareFBZ2 = Mod.GetPublicFunction(NULL, "FBZ1Outro_Cutscene_PrepareFBZ2");

    MOD_REGISTER_OBJECT_HOOK(SpiderMobile);
    MOD_REGISTER_OBJECT_HOOK(CrimsonEye);
    MOD_REGISTER_OBJECT_HOOK(BigSqueeze);

    MOD_REGISTER_OBJECT_HOOK(Zone);
    MOD_REGISTER_OBJECT_HOOK(Player);
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
