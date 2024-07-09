#ifndef SPIDERMOBILE_H
#define SPIDERMOBILE_H

struct EntitySpiderMobile {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    Vector2 origin;
    EntitySpiderMobile *parent;
    int32 timer;
    int32 invincibilityTimer;
    int32 health;
    int32 bounceCount;
    int32 bounceDelay;
    int32 knockbackCooldown;
    int32 armMoveAmplitude;
    int32 offsetY;
    int32 angleVel;
    int32 headRotation;
    int32 pincerRotation;
    int32 webCurveAngle;
    int32 moveAmplitude;
    int32 webCurveDirection;
    int32 legAngles[12];
    int32 unused[12];
    Vector2 headPos;
    Vector2 legJointPos[2];
    Vector2 pincer1StartPos;
    Vector2 pincer1EndPos;
    Vector2 pincer2StartPos;
    Vector2 pincer2EndPos;
    Vector2 legPositions[12];
    bool32 groundedStore;
    Animator partAnimator;
    Animator bumperAnimator;
    Animator starAnimator;
    Animator headAnimator;
    Animator orbAnimator;
    Animator legsAnimator;
    Animator pincerAnimator;
    Animator webAnimator;
    Animator eggmanAnimator;
    Animator electricAnimator;
};

struct ObjectSpiderMobile {
    RSDK_OBJECT
    Hitbox hitboxBumper;
    Hitbox hitboxSpikes;
    Hitbox hitboxUnused;
    Hitbox hitboxOrb;
    Hitbox hitboxPlatform;
    int32 boundsL;
    int32 boundsR;
    int32 boundsM;
    int32 boundsT;
    int32 boundsB;
    uint16 sfxHit;
    uint16 sfxExplosion;
    uint16 sfxBumper;
    uint16 sfxCharge;
    uint16 sfxElecBall;
    uint16 sfxFall;
    uint16 sfxFlailing;
    uint16 sfxHitGround;
    uint16 sfxRecovery;
    uint16 sfxElevator;
    uint16 sfxHullClose;
    uint16 aniFrames;
    int32 unused3;
};

extern ObjectSpiderMobile *SpiderMobile;

extern StateMachine(SpiderMobile_StateBody_AwaitPlayer);

bool32 SpiderMobile_StateBody_AwaitPlayer_Hook(bool32);
#endif
