#include "Player.h"
#include "Announcer.h"
#include "LottoMachine.h"

ObjectPlayer *Player;

void (*Player_ChangeCharacter)(EntityPlayer *player, int32 character) = NULL;

void Player_StageLoad(void)
{
    Mod.Super(Player->classID, SUPER_STAGELOAD, NULL);

    SceneInfo->debugMode = true;
}

bool32 Player_Input_P1_Hook(bool32 skippedState)
{
    RSDK_THIS(Player);

    if (!Player_ChangeCharacter)
        return false;

    ObjectAnnouncer *announcer       = Mod.FindObject("Announcer");
    ObjectLottoMachine *lottoMachine = Mod.FindObject("LottoMachine");
    if (!announcer)
        return false;

    if (self->controllerID < PLAYER_COUNT) {
        if (globals->gameMode != MODE_COMPETITION || announcer->finishedCountdown) {
            RSDKControllerState *controller = &ControllerInfo[self->controllerID];

            if (!lottoMachine || !((1 << self->playerID) & lottoMachine->activePlayers)) {
#if MANIA_USE_PLUS
                if (SKU->platform == PLATFORM_DEV && controller->keySelect.press) {
                    self->characterID <<= 1;
                    if (self->characterID > ID_RAY)
                        self->characterID = 1;

                    Player_ChangeCharacter(self, self->characterID);
                }
#else
                if (GameInfo->platform == PLATFORM_DEV && controller->keySelect.press) {
                    self->characterID <<= 1;
                    if (self->characterID > ID_KNUCKLES)
                        self->characterID = 1;

                    Player_ChangeCharacter(self, self->characterID);
                }
#endif
            }
        }
    }

    return false;
}