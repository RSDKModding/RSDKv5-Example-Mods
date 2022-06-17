#include "ModConfig.h"

#include "Objects/Player.h"
#include "Objects/BSS_Player.h"
#include "Objects/UFO_Player.h"
#include "Objects/HUD.h"
#include "Objects/BSS_HUD.h"
#include "Objects/CreditsSetup.h"
#include "Objects/CutsceneSeq.h"

ModConfig config;

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
    // Setup Config
    config.vDPadSize     = Mod.GetSettingsFloat("", "Config:vDPadSize", 1.0);
    config.vDPadOpacity  = Mod.GetSettingsFloat("", "Config:vDPadOpacity", .625);
    config.moveDPadPos.x = Mod.GetSettingsInteger("", "Config:moveDPadPosX", 56);
    config.moveDPadPos.y = Mod.GetSettingsInteger("", "Config:moveDPadPosY", 184);
    config.jumpDPadPos.x = Mod.GetSettingsInteger("", "Config:jumpDPadPosX", -56);
    config.jumpDPadPos.y = Mod.GetSettingsInteger("", "Config:jumpDPadPosY", 188);

    Mod.SetSettingsFloat("Config:vDPadSize", config.vDPadSize);
    Mod.SetSettingsFloat("Config:vDPadOpacity", config.vDPadOpacity);
    Mod.SetSettingsInteger("Config:moveDPadPosX", config.moveDPadPos.x);
    Mod.SetSettingsInteger("Config:moveDPadPosY", config.moveDPadPos.y);
    Mod.SetSettingsInteger("Config:jumpDPadPosX", config.jumpDPadPos.x);
    Mod.SetSettingsInteger("Config:jumpDPadPosY", config.jumpDPadPos.y);
    Mod.SaveSettings();

    // Register State Hooks
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_Input_P1"), Player_Input_P1_Hook, false);
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "BSS_Player_Input_P1"), BSS_Player_Input_P1_Hook, false);
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "UFO_Player_Input_P1"), UFO_Player_Input_P1_Hook, false);

    // Register Modded Objects
    // Mod.RegisterObject((Object **)&BSS_HUD, "BSS_HUD", sizeof(EntityBSS_HUD), sizeof(ObjectBSS_HUD), NULL, NULL, NULL, BSS_HUD_Draw, NULL, NULL, NULL,
    //                    NULL, NULL, "BSS_HUD");
    // Mod.RegisterObject((Object **)&HUD, "HUD", sizeof(EntityHUD), sizeof(ObjectHUD), NULL, NULL, NULL, HUD_Draw, NULL, NULL, NULL, NULL, NULL, "HUD");
    
    Mod.RegisterObject((Object **)&CreditsSetup, "CreditsSetup", sizeof(EntityCreditsSetup), sizeof(ObjectCreditsSetup), NULL, NULL,
                       CreditsSetup_StaticUpdate, NULL, NULL, NULL, NULL, NULL, NULL, "CreditsSetup");

#if MANIA_USE_PLUS
    Mod.RegisterObject(NULL, "CutsceneSeq", sizeof(EntityCutsceneSeq), 0, CutsceneSeq_Update, NULL, NULL, NULL,
                       CutsceneSeq_Create, NULL, NULL, NULL, NULL, "CutsceneSeq");
#endif
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