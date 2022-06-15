#include "../GameAPI/C/GameAPI/Game.h"

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
    config.vDPadSize     = Mod.GetSettingsFloat("", "Config:vDPadSize", -1);
    config.vDPadOpacity  = Mod.GetSettingsFloat("", "Config:vDPadOpacity", -1);
    config.moveDPadPos.x = Mod.GetSettingsInteger("", "Config:moveDPadPosX", 0x7FFFFFFF);
    config.moveDPadPos.y = Mod.GetSettingsInteger("", "Config:moveDPadPosY", 0x7FFFFFFF);
    config.jumpDPadPos.x = Mod.GetSettingsInteger("", "Config:jumpDPadPosX", 0x7FFFFFFF);
    config.jumpDPadPos.y = Mod.GetSettingsInteger("", "Config:jumpDPadPosY", 0x7FFFFFFF);

    if (config.vDPadSize <= -1) {
        config.vDPadSize = 1.0;
        Mod.SetSettingsFloat("Config:vDPadSize", config.vDPadSize);
        Mod.SaveSettings();
    }

    if (config.vDPadOpacity <= -1) {
        config.vDPadOpacity = 0.625;
        Mod.SetSettingsFloat("Config:vDPadOpacity", config.vDPadOpacity);
        Mod.SaveSettings();
    }

    if (config.moveDPadPos.x == 0x7FFFFFFF) {
        config.moveDPadPos.x = 56;
        Mod.SetSettingsInteger("Config:moveDPadPosX", config.moveDPadPos.x);
        Mod.SaveSettings();
    }

    if (config.moveDPadPos.y == 0x7FFFFFFF) {
        config.moveDPadPos.y = 184;
        Mod.SetSettingsInteger("Config:moveDPadPosY", config.moveDPadPos.y);
        Mod.SaveSettings();
    }

    if (config.jumpDPadPos.x == 0x7FFFFFFF) {
        config.jumpDPadPos.x = -56;
        Mod.SetSettingsInteger("Config:jumpDPadPosX", config.jumpDPadPos.x);
        Mod.SaveSettings();
    }

    if (config.jumpDPadPos.y == 0x7FFFFFFF) {
        config.jumpDPadPos.y = 188;
        Mod.SetSettingsInteger("Config:jumpDPadPosY", config.jumpDPadPos.y);
        Mod.SaveSettings();
    }

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