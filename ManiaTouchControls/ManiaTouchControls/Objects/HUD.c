#include "HUD.h"
#include "Player.h"
#include "ActClear.h"
#include "ReplayRecorder.h"
#include "TimeAttackGate.h"
#include "../ModConfig.h"

ObjectHUD *HUD;
ModObjectHUD *Mod_HUD;

void (*HUD_DrawNumbersBase16)(Vector2 *drawPos, int32 value) = NULL;

void HUD_DrawTouchControls(void)
{
    RSDK_THIS(HUD);

    int32 playerID       = SceneInfo->currentScreenID;
    EntityPlayer *player = RSDK_GET_ENTITY(playerID, Player);

#if MANIA_USE_PLUS
    if (player->stateInputReplay != StateMachine_None) {
        // Only draw the pause button during time attack replays

        int32 alphaStore   = self->alpha;
        int32 inkStore     = self->inkEffect;
        int32 fxStore      = self->drawFX;
        Vector2 scaleStore = self->scale;

        Mod_HUD->pausePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 76);
        Mod_HUD->pausePos.y = TO_FIXED(16);

        self->inkEffect = INK_ALPHA;
        self->drawFX    = FX_SCALE;

        int32 opacity = (int32)(0x100 * config.vDPadOpacity);
        self->scale.x = (int32)(0x200 * config.vDPadSize);
        self->scale.y = (int32)(0x200 * config.vDPadSize);

        bool32 canPause = !ReplayRecorder->playbackManager->isGhostPlayback;

        if (canPause) {
            if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
                if (Mod_HUD->pauseAlpha[playerID] < opacity)
                    Mod_HUD->pauseAlpha[playerID] += 8;

                self->alpha                        = Mod_HUD->pauseAlpha[playerID];
                Mod_HUD->dpadTouchAnimator.frameID = 5;
                RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->pausePos, true);
            }
            else {
                Mod_HUD->pauseAlpha[playerID] = 0;
            }
        }
        else {
            if (Mod_HUD->pauseAlpha[playerID] > 0)
                Mod_HUD->pauseAlpha[playerID] -= 8;

            self->alpha = Mod_HUD->pauseAlpha[playerID];
            if (self->alpha > 0) {
                Mod_HUD->dpadTouchAnimator.frameID = 5;
                RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->pausePos, true);
            }
        }

        self->alpha     = alphaStore;
        self->inkEffect = inkStore;
        self->drawFX    = fxStore;
        self->scale     = scaleStore;

        return;
    }
#endif

    int32 alphaStore   = self->alpha;
    int32 inkStore     = self->inkEffect;
    int32 fxStore      = self->drawFX;
    Vector2 scaleStore = self->scale;

    Mod_HUD->dpadPos.x = TO_FIXED(config.moveDPadPos.x);
    Mod_HUD->dpadPos.y = TO_FIXED(config.moveDPadPos.y);

    Mod_HUD->actionPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x + config.jumpDPadPos.x);
    Mod_HUD->actionPos.y = TO_FIXED(config.jumpDPadPos.y);

#if GAME_VERSION != VER_100
    Mod_HUD->superPos.x = Mod_HUD->actionPos.x - TO_FIXED(64);
    Mod_HUD->superPos.y = Mod_HUD->actionPos.y;
#endif

    Mod_HUD->swapPos.x = Mod_HUD->actionPos.x;
    Mod_HUD->swapPos.y = Mod_HUD->actionPos.y - TO_FIXED(64);

#if MANIA_USE_PLUS
    if (globals->gameMode == MODE_ENCORE)
        Mod_HUD->pausePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 100);
    else
#endif
        Mod_HUD->pausePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 76);
    Mod_HUD->pausePos.y = TO_FIXED(16);

    self->inkEffect = INK_ALPHA;
    self->drawFX    = FX_SCALE;

    int32 opacity = (int32)(0x100 * config.vDPadOpacity);
    self->scale.x = (int32)(0x200 * config.vDPadSize);
    self->scale.y = (int32)(0x200 * config.vDPadSize);

    bool32 canMove = player->stateInput == Player_Input_P1;
    canMove |= player->stateInput == MegaChopper_Input_GrabbedP1;
    canMove |= player->stateInput == Gachapandora_Player_StateInput_P1Grabbed;
#if MANIA_USE_PLUS
    canMove |= player->stateInput == EncoreIntro_PlayerInput_BuddySel;
#endif
    canMove &= player->state != Player_State_Victory;

    bool32 canJump = player->stateInput == Player_Input_P1;
    canJump |= player->stateInput == MegaChopper_Input_GrabbedP1;
    canJump |= player->stateInput == Gachapandora_Player_StateInput_P1Grabbed;
    canJump &= player->state != Player_State_Victory;

#if GAME_VERSION != VER_100
    bool32 canSuper = canJump && Player_CanTransform(player);
#endif

    ObjectTimeAttackGate *TimeAttackGate = Mod.FindObject("TimeAttackGate");

    bool32 canSwap = globals->gameMode == MODE_TIMEATTACK && TimeAttackGate->started;
#if MANIA_USE_PLUS
    if (globals->gameMode == MODE_ENCORE)
        canSwap = canJump && !HUD->swapCooldown && Player_CheckValidState(player) && Player_CanSwap(player, false);
#endif

    bool32 canPause = canMove;

#if GAME_VERSION != VER_100
    Vector2 superPos = Mod_HUD->superPos;
#endif
    Vector2 swapPos = Mod_HUD->swapPos;

    RSDKControllerState *controller = &ControllerInfo[player->controllerID];

    if (canMove) {
        if (Mod_HUD->dpadAlpha[playerID] < opacity)
            Mod_HUD->dpadAlpha[playerID] += 4;

        // Draw DPad
        self->alpha                   = Mod_HUD->dpadAlpha[playerID];
        Mod_HUD->dpadAnimator.frameID = 10;
        RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->dpadPos, true);

        if (player->classID == Player->classID ? player->left : controller->keyLeft.down) {
            self->alpha                        = opacity;
            Mod_HUD->dpadTouchAnimator.frameID = 6;
            RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->dpadPos, true);
        }
        else {
            self->alpha                   = Mod_HUD->dpadAlpha[playerID];
            Mod_HUD->dpadAnimator.frameID = 6;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->dpadPos, true);
        }

        if (player->classID == Player->classID ? player->down : controller->keyDown.down) {
            self->alpha                        = opacity;
            Mod_HUD->dpadTouchAnimator.frameID = 9;
            RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->dpadPos, true);

            if (player->classID == Player->classID ? player->left : controller->keyLeft.down) {
                Mod_HUD->dpadTouchAnimator.frameID = 14;
                RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->dpadPos, true);
            }
            else if (player->classID == Player->classID ? player->right : controller->keyRight.down) {
                Mod_HUD->dpadTouchAnimator.frameID = 15;
                RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->dpadPos, true);
            }
        }
        else {
            self->alpha                   = Mod_HUD->dpadAlpha[playerID];
            Mod_HUD->dpadAnimator.frameID = 9;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->dpadPos, true);
        }

        if (player->classID == Player->classID ? player->right : controller->keyRight.down) {
            self->alpha                        = opacity;
            Mod_HUD->dpadTouchAnimator.frameID = 7;
            RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->dpadPos, true);
        }
        else {
            self->alpha                   = Mod_HUD->dpadAlpha[playerID];
            Mod_HUD->dpadAnimator.frameID = 7;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->dpadPos, true);
        }

        if (player->classID == Player->classID ? player->up : controller->keyUp.down) {
            self->alpha                        = opacity;
            Mod_HUD->dpadTouchAnimator.frameID = 8;
            RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->dpadPos, true);

            if (player->classID == Player->classID ? player->left : controller->keyLeft.down) {
                Mod_HUD->dpadTouchAnimator.frameID = 12;
                RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->dpadPos, true);
            }
            else if (player->classID == Player->classID ? player->right : controller->keyRight.down) {
                Mod_HUD->dpadTouchAnimator.frameID = 13;
                RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->dpadPos, true);
            }
        }
        else {
            self->alpha                   = Mod_HUD->dpadAlpha[playerID];
            Mod_HUD->dpadAnimator.frameID = 8;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->dpadPos, true);
        }

        if (player->classID == Player->classID
                ? (!player->up && !player->down && !player->left && !player->right)
                : (!controller->keyUp.down && !controller->keyDown.down && !controller->keyLeft.down && !controller->keyRight.down)) {
            self->alpha                   = Mod_HUD->dpadAlpha[playerID];
            Mod_HUD->dpadAnimator.frameID = 11;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->dpadPos, true);
        }
    }
    else {
        if (Mod_HUD->dpadAlpha[playerID] > 0) {
            Mod_HUD->dpadAlpha[playerID] -= 4;
        }

        self->alpha = Mod_HUD->dpadAlpha[playerID];
        if (self->alpha > 0) {
            Mod_HUD->dpadAnimator.frameID = 0;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->dpadPos, true);
        }
    }

    if (canJump) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_HUD->jumpAlpha[playerID] < opacity)
                Mod_HUD->jumpAlpha[playerID] += 4;

            if (player->classID == Player->classID ? player->jumpHold : controller->keyC.down) {
                self->alpha                        = opacity;
                Mod_HUD->dpadTouchAnimator.frameID = 1;
                RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->actionPos, true);
            }
            else {
                self->alpha                   = Mod_HUD->jumpAlpha[playerID];
                Mod_HUD->dpadAnimator.frameID = 1;
                RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->actionPos, true);
            }
        }
        else {
            Mod_HUD->jumpAlpha[playerID] = 0;
        }
    }
    else {
        if (Mod_HUD->jumpAlpha[playerID] > 0)
            Mod_HUD->jumpAlpha[playerID] -= 4;

        self->alpha = Mod_HUD->jumpAlpha[playerID];
        if (self->alpha > 0) {
            Mod_HUD->dpadAnimator.frameID = 1;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &Mod_HUD->actionPos, true);
        }
    }

#if GAME_VERSION != VER_100
    bool32 canTransform = player->state == Player_State_Air && player->jumpAbilityState == 1;

    if (canSuper) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_HUD->superAlpha[playerID] < opacity)
                Mod_HUD->superAlpha[playerID] += 4;

            if (ControllerInfo[player->controllerID].keyY.down) {
                self->alpha                        = opacity / (2 - canTransform);
                Mod_HUD->dpadTouchAnimator.frameID = 3;
                RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &superPos, true);
            }
            else {
                self->alpha                   = Mod_HUD->superAlpha[playerID] / (2 - canTransform);
                Mod_HUD->dpadAnimator.frameID = 3;
                RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &superPos, true);
            }
        }
        else {
            Mod_HUD->superAlpha[playerID] = 0;
        }
    }
    else {
        if (Mod_HUD->superAlpha[playerID] > 0)
            Mod_HUD->superAlpha[playerID] -= 4;

        self->alpha = Mod_HUD->superAlpha[playerID] / (2 - canTransform);
        if (self->alpha > 0) {
            Mod_HUD->dpadAnimator.frameID = 3;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &superPos, true);
        }
    }
#endif

    bool32 canPressSwap = true;
#if MANIA_USE_PLUS
    if (globals->gameMode == MODE_ENCORE)
        canPressSwap = Player_CanSwap(player, true);
#endif

    if (canSwap) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_HUD->swapAlpha[playerID] < opacity)
                Mod_HUD->swapAlpha[playerID] += 4;

            if (ControllerInfo[player->controllerID].keyY.down) {
                self->alpha                        = opacity / (2 - canPressSwap);
                Mod_HUD->dpadTouchAnimator.frameID = 4;
                RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &swapPos, true);
            }
            else {
                self->alpha                   = Mod_HUD->swapAlpha[playerID] / (2 - canPressSwap);
                Mod_HUD->dpadAnimator.frameID = 4;
                RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &swapPos, true);
            }
        }
        else {
            Mod_HUD->swapAlpha[playerID] = 0;
        }
    }
    else {
        if (Mod_HUD->swapAlpha[playerID] > 0)
            Mod_HUD->swapAlpha[playerID] -= 4;

        self->alpha = Mod_HUD->swapAlpha[playerID] / (2 - canPressSwap);
        if (self->alpha > 0) {
            Mod_HUD->dpadAnimator.frameID = 4;
            RSDK.DrawSprite(&Mod_HUD->dpadAnimator, &swapPos, true);
        }
    }

    if (canPause) {
        if ((SceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (Mod_HUD->pauseAlpha[playerID] < opacity)
                Mod_HUD->pauseAlpha[playerID] += 8;

            self->alpha                        = Mod_HUD->pauseAlpha[playerID];
            Mod_HUD->dpadTouchAnimator.frameID = 5;
            RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->pausePos, true);
        }
        else {
            Mod_HUD->pauseAlpha[playerID] = 0;
        }
    }
    else {
        if (Mod_HUD->pauseAlpha[playerID] > 0)
            Mod_HUD->pauseAlpha[playerID] -= 8;

        self->alpha = Mod_HUD->pauseAlpha[playerID];
        if (self->alpha > 0) {
            Mod_HUD->dpadTouchAnimator.frameID = 5;
            RSDK.DrawSprite(&Mod_HUD->dpadTouchAnimator, &Mod_HUD->pausePos, true);
        }
    }

    self->alpha     = alphaStore;
    self->inkEffect = inkStore;
    self->drawFX    = fxStore;
    self->scale     = scaleStore;
}

void HUD_DrawMobileHUD(void)
{
    RSDK_THIS(HUD);

    EntityPlayer *player = RSDK_GET_ENTITY(SceneInfo->currentScreenID, Player);
    Vector2 drawPos;

    Object *debugModeSVars = Mod.FindObject("DebugMode");
    if (debugModeSVars && RSDK_GET_ENTITY(SLOT_PLAYER1, Player)->classID == debugModeSVars->classID) {
        if (player->camera) {
            // Draw Camera YPos
            drawPos.x = TO_FIXED(ScreenInfo[player->camera->screenID].size.x - 16);
            drawPos.y = TO_FIXED(42);
            HUD_DrawNumbersBase16(&drawPos, ScreenInfo[player->camera->screenID].position.y);

            // Draw Camera XPos
            drawPos.x -= TO_FIXED(9);
            HUD_DrawNumbersBase16(&drawPos, ScreenInfo[player->camera->screenID].position.x);

            // Draw Player YPos
            drawPos.x = TO_FIXED(ScreenInfo[player->camera->screenID].size.x - 16);
            drawPos.y += TO_FIXED(16);
            HUD_DrawNumbersBase16(&drawPos, FROM_FIXED(player->position.y));

            // Draw Player XPos
            drawPos.x -= TO_FIXED(9);
            HUD_DrawNumbersBase16(&drawPos, FROM_FIXED(player->position.x));
        }
    }
#if MANIA_USE_PLUS
    else if (self->actionPromptPos > -TO_FIXED(64) && globals->gameMode == MODE_TIMEATTACK) {
        drawPos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x) - self->actionPromptPos;
        drawPos.y = TO_FIXED(48);

        if (API.CheckDLC(DLC_PLUS)) {
            // Draw Replay Save Icon
            ObjectActClear *ActClear = Mod.FindObject("ActClear");
            if (HUD->replaySaveEnabled || ActClear->hasSavedReplay)
                RSDK.DrawSprite(&self->replayClapAnimator, &drawPos, true);
            else {
                self->inkEffect = INK_BLEND;
                RSDK.DrawSprite(&self->replayClapAnimator, &drawPos, true);
                self->inkEffect = INK_NONE;
            }
            drawPos.y += TO_FIXED(28);
        }
        // Draw Thumbs Up Icon
        RSDK.DrawSprite(&self->thumbsUpIconAnimator, &drawPos, true);
    }
#endif
}

void HUD_Draw(void)
{
    RSDK_THIS(HUD);

    EntityPlayer *player = RSDK_GET_ENTITY(SceneInfo->currentScreenID, Player);

    int32 playerClassID = player->classID;
    void *playerCamera  = player->camera;

    // make the game think we should have debug mode enabled
    // however NULL the camera to draw nothing
    Object *debugModeSVars = Mod.FindObject("DebugMode");
    if (debugModeSVars)
        player->classID = debugModeSVars->classID;
    else
        player->classID = TYPE_DEFAULTOBJECT;
    player->camera = NULL;

    Vector2 lifePos = self->lifePos;
#if MANIA_USE_PLUS
    if (globals->gameMode == MODE_COMPETITION) {
        lifePos = self->vsLifePos[SceneInfo->currentScreenID];

        self->vsLifePos[SceneInfo->currentScreenID].x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 48) - lifePos.x;
        self->vsLifePos[SceneInfo->currentScreenID].y = TO_FIXED(25);
    }
    else if (globals->gameMode == MODE_ENCORE) {
        self->lifePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 72) - lifePos.x;
        self->lifePos.y = TO_FIXED(25);
    }
    else {
#endif
        self->lifePos.x = TO_FIXED(ScreenInfo[SceneInfo->currentScreenID].size.x - 48) - lifePos.x;
        self->lifePos.y = TO_FIXED(25);
#if MANIA_USE_PLUS
    }
#endif

    // Draw HUD stuff
    Mod.Super(HUD->classID, SUPER_DRAW, NULL);

    player->classID = playerClassID;
    player->camera  = playerCamera;

    // Draw Mobile HUD bits
    HUD_DrawMobileHUD();

#if MANIA_USE_PLUS
    if (globals->gameMode == MODE_COMPETITION)
        self->vsLifePos[SceneInfo->currentScreenID] = lifePos;
    else
#endif
        self->lifePos = lifePos;

    HUD_DrawTouchControls();
}

void HUD_StageLoad(void)
{
    Mod.Super(HUD->classID, SUPER_STAGELOAD, NULL);

    Mod_HUD->dpadFrames = RSDK.LoadSpriteAnimation("Global/TouchControls.bin", SCOPE_STAGE);

    for (uint8 p = 0; p < PLAYER_COUNT; p++) {
        if (globals->gameMode != MODE_TIMEATTACK) {
            Mod_HUD->dpadAlpha[p] = 0;
            Mod_HUD->jumpAlpha[p] = 0;
#if GAME_VERSION != VER_100
            Mod_HUD->superAlpha[p] = 0;
#endif
            Mod_HUD->swapAlpha[p]  = 0;
            Mod_HUD->pauseAlpha[p] = 0;
        }
        else
            Mod_HUD->swapAlpha[p] = 0;
    }

    RSDK.SetSpriteAnimation(Mod_HUD->dpadFrames, 0, &Mod_HUD->dpadAnimator, true, 0);
    RSDK.SetSpriteAnimation(Mod_HUD->dpadFrames, 1, &Mod_HUD->dpadTouchAnimator, true, 0);
}
