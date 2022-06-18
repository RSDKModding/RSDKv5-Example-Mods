#include "Player.h"
#include "CompetitionSession.h"

ObjectPlayer *Player;

bool32 Player_State_Die_Hook(bool32 skippedState)
{
    RSDK_THIS(Player);

    EntityCompetitionSession *session = (EntityCompetitionSession *)globals->competitionSession;

    self->lives = 3;
    if (globals->gameMode == MODE_COMPETITION)
        session->lives[self->playerID] = 3;

    return false;
}
bool32 Player_State_Drown_Hook(bool32 skippedState)
{
    RSDK_THIS(Player);

    EntityCompetitionSession *session = (EntityCompetitionSession *)globals->competitionSession;

    self->lives = 3;
    if (globals->gameMode == MODE_COMPETITION)
        session->lives[self->playerID] = 3;

    return false;
}