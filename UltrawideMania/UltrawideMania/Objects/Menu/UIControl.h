#if MANIA_USE_PLUS
#ifndef UICONTROL_H
#define UICONTROL_H

#define UICONTROL_BUTTON_COUNT (64)
#if MANIA_USE_PLUS
#define UICONTROL_PROMPT_COUNT (4)
#endif

struct ObjectUIControl {
    RSDK_OBJECT
    bool32 isProcessingInput;
    bool32 inputLocked;
    bool32 lockInput;
    bool32 upPress[PLAYER_COUNT];
    bool32 downPress[PLAYER_COUNT];
    bool32 leftPress[PLAYER_COUNT];
    bool32 rightPress[PLAYER_COUNT];
    bool32 backPress[PLAYER_COUNT];
    bool32 confirmPress[PLAYER_COUNT];
    bool32 yPress[PLAYER_COUNT];
    bool32 xPress[PLAYER_COUNT];
#if MANIA_USE_PLUS
    bool32 startPress[PLAYER_COUNT];
#endif
    bool32 anyUpPress;
    bool32 anyDownPress;
    bool32 anyLeftPress;
    bool32 anyRightPress;
    bool32 anyConfirmPress;
    bool32 anyBackPress;
    bool32 anyYPress;
    bool32 anyXPress;
#if MANIA_USE_PLUS
    bool32 anyStartPress;
#endif
    bool32 forceBackPress;
    bool32 hasTouchInput;
    int32 timer;
    int32 unused1;
    uint16 aniFrames;
};

// Entity Class
struct EntityUIControl {
    RSDK_ENTITY
    StateMachine(state);
    int32 unused1;
    int32 buttonID;
    String tag;
    String parentTag;
    bool32 activeOnLoad;
    bool32 noWidgets;
    bool32 resetSelection;
    uint8 buttonCount;
#if MANIA_USE_PLUS
    uint8 promptCount;
#endif
    uint8 rowCount;
    uint8 columnCount;
    uint8 startingID;
    Vector2 size;
    Vector2 cameraOffset;
    Vector2 scrollSpeed;
#if MANIA_USE_PLUS
    bool32 noClamp;
    bool32 noWrap;
#endif
    Vector2 startPos;
    Vector2 targetPos;
    bool32 childHasFocus;
    bool32 dialogHasFocus;
#if MANIA_USE_PLUS
    bool32 popoverHasFocus;
#endif
    bool32 hasStoredButton;
    bool32 selectionDisabled;
#if MANIA_USE_PLUS
    bool32 menuWasSetup;
#endif
    int32 backoutTimer;
    int32 storedButtonID;
    int32 lastButtonID;
    void *heading; // EntityUIHeading
    void *shifter; // EntityUIShifter
#if MANIA_USE_PLUS
    void *carousel;                        // EntityUICarousel
    void *prompts[UICONTROL_PROMPT_COUNT]; // EntityUIButtonPrompt
#endif
    void *buttons[UICONTROL_BUTTON_COUNT]; // EntityUIButton
    bool32 (*backPressCB)(void);
    void (*processButtonInputCB)(void);
    void (*menuSetupCB)(void);
    void (*menuUpdateCB)(void);
    void (*yPressCB)(void);
    void (*xPressCB)(void);
    int32 unused2;
    int32 unused3;
    int32 unused4;
    int32 unused5;
    int32 unused6;
    int32 unused7;
};
#endif
#endif
