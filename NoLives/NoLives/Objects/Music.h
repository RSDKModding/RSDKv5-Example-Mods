#ifndef OBJ_MUSIC_H
#define OBJ_MUSIC_H

#include "../../GameAPI/C/GameAPI/Game.h"

typedef enum {
    TRACK_NONE         = -1,
    TRACK_STAGE        = 0,
    TRACK_INVINCIBLE   = 1,
    TRACK_SNEAKERS     = 2,
    TRACK_MINIBOSS     = 3,
    TRACK_HBHBOSS      = 4,
    TRACK_EGGMAN1      = 5,
    TRACK_EGGMAN2      = 6,
    TRACK_RUBYPRESENCE = 5,
    TRACK_BUDDYBEAT    = 6,
    TRACK_ACTCLEAR     = 7,
    TRACK_DROWNING     = 8,
    TRACK_GAMEOVER     = 9,
    TRACK_SUPER        = 10,
    TRACK_ERZBOSS      = 10,
#if MANIA_USE_PLUS
    TRACK_HBHMISCHIEF = 11,
    TRACK_NOLOAD      = 12,
#else
    TRACK_NOLOAD      = 11,
    TRACK_HBHMISCHIEF = 12,
#endif
    TRACK_1UP = 13,
} MusicTracks;

typedef enum {
    TRACK_PRIORITY_NONE    = 0,
    TRACK_PRIORITY_1UP     = 10000,
    TRACK_PRIORITY_ANY     = 10010,
    TRACK_PRIORITY_POWERUP = 10100,
    TRACK_PRIORITY_SUPER   = 11000,
    TRACK_PRIORITY_DROWN   = 11000,
} TrackPriorityValues;

// Object Class
typedef struct {
    RSDK_OBJECT
    char trackNames[16][32];
    uint32 trackLoops[16];
    int32 trackStartPos;
    int32 channelID;
    int32 activeTrack;
#if MANIA_USE_PLUS
    int32 nextTrack;
    int32 restartTrackID;
#else
    int32 prevTrack;
    int32 queuedTrack;
    int32 nextTrack;
    bool32 playingRegularTrack;
    bool32 playingDrownTrack;
    bool32 playing1UPTrack;
#endif
    uint16 aniFrames;
} ObjectMusic;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    String trackFile;
    String soundTestTitle;
    int32 trackID;
    uint32 trackLoop;
    bool32 playOnLoad;
    bool32 restartTrack;
    int32 timer;
    int32 trackPriority;
    int32 trackStartPos;
    float volume;
    float fadeSpeed;
    Animator animator;
} EntityMusic;

// Object Struct
extern ObjectMusic *Music;

// Standard Entity Events
void Music_StaticUpdate(void);

#endif //! OBJ_MUSIC_H
