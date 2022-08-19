#include "../GameAPI/C/GameAPI/Game.h"
#include "ModConfig.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

ModConfig config;

void MaxControlHook(void *data)
{
    UNUSED(data);

    globals->medalMods &= ~MEDAL_PEELOUT;
    globals->medalMods &= ~MEDAL_INSTASHIELD;
    globals->medalMods |= MEDAL_NODROPDASH;

    if (config.peeloutEnabled)
        globals->medalMods |= MEDAL_PEELOUT;

    if (config.instaShieldEnabled)
        globals->medalMods |= MEDAL_INSTASHIELD;

    if (config.dropdashEnabled)
        globals->medalMods &= ~MEDAL_NODROPDASH;
}

void InitModAPI(void)
{
    // Register State Hooks
    Mod.AddModCallback(MODCB_ONSTAGELOAD, MaxControlHook);

    // Setup Config
    config.peeloutEnabled     = Mod.GetSettingsBool("", "Config:peeloutEnabled", false);
    config.instaShieldEnabled = Mod.GetSettingsBool("", "Config:instaShieldEnabled", false);
    config.dropdashEnabled    = Mod.GetSettingsBool("", "Config:dropdashEnabled", true);

    Mod.SetSettingsBool("Config:peeloutEnabled", config.peeloutEnabled);
    Mod.SetSettingsBool("Config:instaShieldEnabled", config.instaShieldEnabled);
    Mod.SetSettingsBool("Config:dropdashEnabled", config.dropdashEnabled);
    Mod.SaveSettings();
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