#include "GameAPI/Game.h"

#define extraWidth ((ScreenInfo->size.x - WIDE_SCR_XSIZE) / 2)

#if MANIA_USE_PLUS
typedef struct ObjectUIControl ObjectUIControl;
typedef struct EntityUIControl EntityUIControl;
typedef struct ObjectMainMenu ObjectMainMenu;
typedef struct EntityMainMenu EntityMainMenu;
typedef struct ObjectUIDiorama ObjectUIDiorama;
typedef struct EntityUIDiorama EntityUIDiorama;
#endif

typedef struct ObjectSpiderMobile ObjectSpiderMobile;
typedef struct EntitySpiderMobile EntitySpiderMobile;
typedef struct ObjectHeavyShinobi ObjectHeavyShinobi;
typedef struct EntityHeavyShinobi EntityHeavyShinobi;
typedef struct ObjectCrimsonEye ObjectCrimsonEye;
typedef struct EntityCrimsonEye EntityCrimsonEye;

typedef struct ObjectCutsceneSeq ObjectCutsceneSeq;
typedef struct EntityCutsceneSeq EntityCutsceneSeq;

typedef struct ObjectZone ObjectZone;
typedef struct ObjectPlayer ObjectPlayer;
typedef struct EntityPlayer EntityPlayer;

#if MANIA_USE_PLUS
#include "Menu/UIControl.h"
#include "Menu/MainMenu.h"
#include "Menu/UIDiorama.h"
#endif

#include "Bosses/SpiderMobile.h"
#include "Bosses/HeavyShinobi.h"
#include "Bosses/CrimsonEye.h"

#include "Cutscenes/CutsceneSeq.h"

#include "Zone.h"
#include "Player.h"
