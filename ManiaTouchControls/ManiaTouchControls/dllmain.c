#include "ModConfig.h"

#include "Objects/Player.h"
#include "Objects/BSS_Player.h"
#include "Objects/UFO_Player.h"
#include "Objects/PBL_Player.h"
#include "Objects/HUD.h"
#include "Objects/ActClear.h"
#include "Objects/DebugMode.h"
#include "Objects/BSS_HUD.h"
#include "Objects/PBL_Crane.h"
#include "Objects/PBL_Flipper.h"
#include "Objects/PBL_Setup.h"
#include "Objects/DASetup.h"
#include "Objects/PuyoLevelSelect.h"
#include "Objects/PuyoBean.h"
#include "Objects/PuyoGame.h"
#include "Objects/CPZBoss.h"
#include "Objects/CreditsSetup.h"
#include "Objects/CutsceneSeq.h"
#include "Objects/Summary.h"
#include "Objects/TryAgain.h"
#include "Objects/TryAgainE.h"
#include "Objects/TitleSetup.h"
#include "Objects/UIVideo.h"
#include "Objects/UIControl.h"

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
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_Input_P1"), Player_Input_P1_Hook, true);

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "BSS_Player_Input_P1"), BSS_Player_Input_P1_Hook, true);

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "UFO_Player_Input_P1"), UFO_Player_Input_P1_Hook, true);

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "ActClear_State_TallyScore"), ActClear_State_TallyScore_Hook, true);

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "PuyoBean_Input_Player"), PuyoBean_Input_Player_Hook, true);

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "PuyoGame_State_ShowMatchResults"), PuyoGame_State_ShowMatchResults_Hook, true);
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "PuyoGame_State_ShowRoundResults"), PuyoGame_State_ShowRoundResults_Hook, true);

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "CPZBoss_State_HandleMatch_Player"), CPZBoss_State_HandleMatch_Player_Hook, true);

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "TryAgain_State_Stinger"), TryAgain_State_Stinger_Hook, true);

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "DASetup_State_ManageControl"), DASetup_State_ManageControl_Hook, true);

#if MANIA_USE_PLUS
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "PBL_Player_Input_P1"), PBL_Player_Input_P1_Hook, true);

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "ActClear_State_ShowResultsTA"), ActClear_State_ShowResultsTA_Hook, true);

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "TryAgainE_State_Stinger"), TryAgainE_State_Stinger_Hook, true);

    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Summary_State_Wait"), Summary_State_Wait_Hook, true);
#endif

    // Register Object Hooks
    MOD_REGISTER_OBJECT_HOOK(UIControl);


    // Register Modded Objects
    MOD_REGISTER_OBJ_OVERLOAD(PuyoGame, PuyoGame_Update, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(PuyoLevelSelect, PuyoLevelSelect_Update, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(CreditsSetup, NULL, NULL, CreditsSetup_StaticUpdate, NULL, NULL, NULL, NULL, NULL, NULL);

    MOD_REGISTER_OBJ_OVERLOAD_MSV(BSS_Player, Mod_BSS_Player, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD_MSV(DASetup, Mod_DASetup, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(DebugMode, DebugMode_Update, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD_MSV(Player, Mod_Player, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD_MSV(PuyoBean, Mod_PuyoBean, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD_MSV(PuyoLevelSelect, Mod_PuyoLevelSelect, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD_MSV(UFO_Player, Mod_UFO_Player, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    
#if MANIA_USE_PLUS
    MOD_REGISTER_OBJ_OVERLOAD_MSV(PBL_Player, Mod_PBL_Player, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD_MSV(PBL_Crane, Mod_PBL_Crane, PBL_Crane_Update, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD_MSV(PBL_Flipper, Mod_PBL_Flipper, NULL, NULL, PBL_Flipper_StaticUpdate, NULL, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD_MSV(PBL_Setup, Mod_PBL_Setup, NULL, NULL, PBL_Setup_StaticUpdate, NULL, NULL, NULL, NULL, NULL, NULL);
#endif

#if MANIA_USE_PLUS
    MOD_REGISTER_OBJ_OVERLOAD_NOCLASS(CutsceneSeq, CutsceneSeq_Update, NULL, NULL, NULL, CutsceneSeq_Create, NULL, NULL, NULL, NULL);
#endif

    // Register Mod Callbacks
    Mod.AddModCallback(MODCB_ONVIDEOSKIPCB, TitleSetup_ModCB_VideoSkip);
    Mod.AddModCallback(MODCB_ONVIDEOSKIPCB, UIVideo_ModCB_VideoSkip);

    // Get Public Functions
    CutsceneSeq_CheckSkip  = Mod.GetPublicFunction(NULL, "CutsceneSeq_CheckSkip");
    TitleSetup_VideoSkipCB = Mod.GetPublicFunction(NULL, "TitleSetup_VideoSkipCB");
    UIVideo_SkipCB         = Mod.GetPublicFunction(NULL, "UIVideo_SkipCB");
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

#ifdef __vita__
void main() __attribute__ ((weak, alias ("module_start")));
int module_start(int argc, const void *args) {};
int module_stop(int argc, const void *args) {};
#endif
