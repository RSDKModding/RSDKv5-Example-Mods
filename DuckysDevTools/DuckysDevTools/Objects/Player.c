#include "Player.h"
#include "Announcer.h"
#include "LottoMachine.h"

void Player_Input_P1_Hook(void)
{
    RSDK_THIS(Player);

    void (*Player_ChangeCharacter)(EntityPlayer * player, int32 character) = Mod.GetPublicFunction(NULL, "Player_ChangeCharacter");
    if (!Player_ChangeCharacter)
        return;

    ObjectAnnouncer *announcer       = Mod.FindObject("Announcer");
    ObjectLottoMachine *lottoMachine = Mod.FindObject("LottoMachine");
    if (!announcer)
        return;


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
}