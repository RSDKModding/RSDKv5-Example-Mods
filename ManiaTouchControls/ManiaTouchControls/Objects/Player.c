#include "Player.h"
#include "SaveGame.h"

#include "../ModConfig.h"
#include "../Helpers.h"

ObjectPlayer *Player;
ModObjectPlayer *Mod_Player;

StateMachine(Player_Input_P1)                          = NULL;
bool32 (*Player_CheckValidState)(EntityPlayer *player) = NULL;

StateMachine(Player_State_Transform) = NULL;
StateMachine(Player_State_Victory)   = NULL;

#if MANIA_USE_PLUS
StateMachine(Player_State_Death)         = NULL;
StateMachine(Player_State_Drown)         = NULL;
StateMachine(Player_State_EncoreRespawn) = NULL;
StateMachine(Player_State_Static)        = NULL;
StateMachine(Player_State_Ground)        = NULL;
StateMachine(Player_State_Roll)          = NULL;
#endif

// Extras (not part of Player but don't wanna to make a new file)
StateMachine(MegaChopper_Input_GrabbedP1)              = NULL;
StateMachine(Gachapandora_Player_StateInput_P1Grabbed) = NULL;
#if MANIA_USE_PLUS
StateMachine(EncoreIntro_PlayerInput_BuddySel) = NULL;
#endif
StateMachine(ERZStart_State_PlayerSuperFly) = NULL;
StateMachine(ERZStart_State_PlayerRebound)  = NULL;

bool32 Player_CanTransform(EntityPlayer *player)
{
    if (!SceneInfo->timeEnabled /*&& !ERZStart && (!PhantomEgg || PhantomEgg->disableSuperForm)*/)
        return false;

    // Support for MegAmi's Super Cancel mod
    bool32 superCancel = false;
    Mod.LoadModInfo("SuperCancel", NULL, NULL, NULL, &superCancel);
    if (superCancel && !RSDK.FindObject("ERZSetup") && (player->state == Player_State_Transform || player->superState == SUPERSTATE_SUPER))
        return true;

    SaveRAM *saveRAM = SaveGame_GetSaveRAM();
    if (!saveRAM)
        return false;

    uint8 emeralds = saveRAM->chaosEmeralds;

#if MANIA_USE_PLUS
    if (Player->canSuperCB && !Player->canSuperCB(false))
        return false;
#endif

    if (player->superState >= SUPERSTATE_SUPER || emeralds != 0x7F || player->rings < 50 || player->sidekick)
        return false;

    return true;
}

#if MANIA_USE_PLUS
bool32 Player_CanSwap(EntityPlayer *player)
{
    EntityPlayer *sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
    if (!sidekick->classID)
        return false;

    if (Player->cantSwap || player->drawGroup == 2 || !SceneInfo->timeEnabled)
        return false;

    if (Player->respawnTimer) {
        Player->respawnTimer = 240;
        return false;
    }

    if (player->state == Player_State_Death || player->state == Player_State_Drown) {
        if (sidekick->state == Player_State_Death || sidekick->state == Player_State_Drown || sidekick->state == Player_State_EncoreRespawn
            || sidekick->state == Player_State_Static) {
            return false;
        }
    }
    else {
        if (player->state != Player_State_Ground && player->state != Player_State_Roll)
            return false;
        if (sidekick->state != Player_State_Ground && sidekick->state != Player_State_Roll)
            return false;
    }

    return true;
}
#endif

bool32 Player_Input_P1_Hook(bool32 skippedState)
{
    RSDK_THIS(Player);

    if (self->controllerID < PLAYER_COUNT) {
        RSDKControllerState *controller = &ControllerInfo[self->controllerID];

        if (self->state != ERZStart_State_PlayerSuperFly && self->state != ERZStart_State_PlayerRebound)
            HandleDPad_4Dir(controller);
        else
            HandleDPad_8Dir(controller);

#if GAME_VERSION != VER_100
        bool32 canSuper = Player_CanTransform(self) && !self->onGround;
#endif
#if MANIA_USE_PLUS
        bool32 canSwap = Player_CanSwap(self) && globals->gameMode == MODE_ENCORE;
#endif

        int32 jumpX = ScreenInfo->center.x;
        int32 jumpY = 96;

#if GAME_VERSION != VER_100
        if (canSuper)
            jumpX = ScreenInfo[self->playerID].size.x + config.jumpDPadPos.x - 48;
#endif
#if MANIA_USE_PLUS
        if (canSwap)
            jumpY = config.jumpDPadPos.y - 48;
#endif

        // fixes a bug with button vs touch
        bool32 touchedJump = false;
        if (CheckTouchRect(jumpX, jumpY, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
            ControllerInfo->keyA.down |= true;
            controller->keyA.down = true;
            touchedJump           = true;
        }

        bool32 touchedPause = false;
        if (CheckTouchRect(ScreenInfo->size.x - 0x80, 0, ScreenInfo->size.x, 0x40, NULL, NULL) >= 0) {
            ControllerInfo->keyStart.down |= true;
            controller->keyStart.down = true;
            touchedPause              = true;
        }

        bool32 touchedDebug = false;
        if (SceneInfo->debugMode) {
            if (CheckTouchRect(0, 0, 112, 56, NULL, NULL) >= 0) {
#if GAME_VERSION != VER_100
                ControllerInfo->keyX.down |= true;
                controller->keyX.down = true;
#else
                ControllerInfo->keyY.down |= true;
                controller->keyY.down = true;
#endif
                touchedDebug = true;
            }
        }

#if GAME_VERSION != VER_100
        bool32 touchedSuper = false;
        if (canSuper) {
            if (CheckTouchRect(jumpX - 64, jumpY, jumpX, ScreenInfo->size.x, NULL, NULL) >= 0) {
                ControllerInfo->keyY.down |= true;
                controller->keyY.down = true;
                touchedSuper          = true;
            }

            if (!Mod_Player->touchSuper && touchedSuper) {
                ControllerInfo->keyY.press |= ControllerInfo->keyY.down;
                controller->keyY.press |= controller->keyY.down;
            }
            Mod_Player->touchSuper = controller->keyY.down;
        }
        else {
            Mod_Player->touchSuper = 0;
        }
#endif

#if MANIA_USE_PLUS
        bool32 touchedSwap = false;
        if (canSwap) {
            if (CheckTouchRect(jumpX, jumpY - 64, ScreenInfo->size.x, jumpY, NULL, NULL) >= 0) {
                ControllerInfo->keyY.down |= true;
                controller->keyY.down = true;
                touchedSwap           = true;
            }

            if (!Mod_Player->touchSwap && touchedSwap) {
                ControllerInfo->keyY.press |= ControllerInfo->keyY.down;
                controller->keyY.press |= controller->keyY.down;
            }
            Mod_Player->touchSwap = controller->keyY.down;
        }
        else {
            Mod_Player->touchSwap = 0;
        }
#endif

        if (!Mod_Player->touchJump && touchedJump) {
            ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }
        Mod_Player->touchJump = controller->keyA.down;

        if (!Mod_Player->touchDebug && touchedDebug) {
            ControllerInfo->keyX.press |= ControllerInfo->keyX.down;
            controller->keyX.press |= controller->keyX.down;
        }
        Mod_Player->touchDebug = controller->keyX.down;

        if (!Mod_Player->touchPause && touchedPause) {
            ControllerInfo->keyStart.press |= ControllerInfo->keyStart.down;
            controller->keyStart.press |= controller->keyStart.down;
        }
        Mod_Player->touchPause = controller->keyStart.down;
    }

    return false;
}