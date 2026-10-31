#include "host_shared_calls.h"

extern char Aoss_HandleRecvPacket[];
extern char BarberMachine_Start[];
extern char BuildingList_FindByItem[];
extern char CatalogMenu_SetupBgLayers[];
extern char CreatureBook_ActivateFocus[];
extern char CreatureBook_DrawRows[];
extern char CreatureBook_EndScrollTouch[];
extern char CreatureBook_GetFocusX[];
extern char CreatureBook_GetFocusY[];
extern char CreatureBook_GetFocusedTab[];
extern char CreatureBook_IsFocusOnPageArrow[];
extern char CreatureBook_RefreshRowIcons[];
extern char CreatureBook_WaitScrollHoldStart[];
extern char DateTimePicker_AngleAt[];
extern char DateTimePicker_BeginFrame[];
extern char DateTimePicker_CancelList[];
extern char DateTimePicker_DecideList[];
extern char DateTimePicker_EndHandDrag[];
extern char DateTimePicker_GrabHand[];
extern char DateTimePicker_HitTestList[];
extern char DateTimePicker_UpdateHandAnim[];
extern char DateTimePicker_UpdateListClose[];
extern char DateTimePicker_UpdateListOpen[];
extern char DwcFriend_GetProfileId[];
extern char DwcFriend_IsIdle[];
extern char FieldInsect_GetPosAndKind[];
extern char FieldObj_FreeCedarFileBufs[];
extern char FieldObj_LoadIconModels[];
extern char FieldObj_LoadStones[];
extern char FieldObjectManager_Create[];
extern char Field_GetStructureTexSuffix[];
extern char FishCatch_Reset[];
extern char FishCatch_StateStart[];
extern char FishShadow_EnterSpawn[];
extern char FishShadow_RunAi[];
extern char FtrActor_ReleaseCollider[];
extern char GeneralMenuHeader_GetStyle[];
extern char InvItem_IsDeliveryItem[];
extern char InvItem_IsNonTransferable[];
extern char InvItem_IsNotFishInsectOrFlower[];
extern char InvItem_IsTurnipFishOrInsect[];
extern char InventoryBg_ClearDirty[];
extern char InventoryBg_DrawSprite[];
extern char InventoryBg_Init[];
extern char InventoryBg_LoadBg[];
extern char InventoryBg_LoadPictureForHeldItem[];
extern char InventoryBg_PreUpdate[];
extern char InventoryBg_ResetHighlight[];
extern char InventoryBg_SetBellsPanelMode[];
extern char InventoryBg_StartBlink[];
extern char InventoryBg_UploadPalette[];
extern char InventoryItemGrid_AllocUpload[];
extern char InventoryItemGrid_ClearMarks[];
extern char InventoryItemGrid_ClearSlot[];
extern char InventoryItemGrid_DisableSlotRange[];
extern char InventoryItemGrid_DrawExtraMarks[];
extern char InventoryItemGrid_Exit[];
extern char InventoryItemGrid_FindBoxSlotAt[];
extern char InventoryItemGrid_GetSlotItem[];
extern char InventoryItemGrid_HitTestSlot21[];
extern char InventoryItemGrid_IsSlotDisabled[];
extern char InventoryItemGrid_LoadPockets[];
extern char InventoryItemGrid_SetCursorSlot[];
extern char InventoryItemGrid_SetHeldItem[];
extern char InventoryItemGrid_ShowSlotName[];
extern char InventoryItemGrid_StartPresentAnim[];
extern char InventoryItemGrid_UpdatePresentAnim[];
extern char Inventory_PlayPickUpSe[];
extern char Keyboard_ClearFlags[];
extern char Keyboard_ClearHighlight[];
extern char Keyboard_DeleteRange[];
extern char Keyboard_DisableModifierKeys[];
extern char Keyboard_DrawCopyPasteKeys[];
extern char Keyboard_DrawCopyPasteKeysChat[];
extern char Keyboard_EnableKey[];
extern char Keyboard_EnterTabRowAtX[];
extern char Keyboard_EnterTabRowAtX2[];
extern char Keyboard_GetKeyCodePage0A[];
extern char Keyboard_GetSelectedEmotion[];
extern char Keyboard_GetTypedRunLength[];
extern char Keyboard_HandleModeKey[];
extern char Keyboard_HighlightKey[];
extern char Keyboard_InsertCharMultiline[];
extern char Keyboard_IsOnButtonKey[];
extern char Keyboard_LoadEmotionIcons[];
extern char Keyboard_LoadLetterChars[];
extern char Keyboard_MarkScreenDirty[];
extern char Keyboard_ModifyCharKey104[];
extern char Keyboard_PlayCharSe[];
extern char Keyboard_PlayCopySe[];
extern char Keyboard_PressCursorKey[];
extern char Keyboard_Reload[];
extern char Keyboard_ReplaceCharBeforeCursor[];
extern char Keyboard_ResetTypedRun[];
extern char Keyboard_RestoreLastPage[];
extern char Keyboard_SelectEmotionByCode[];
extern char Keyboard_SelectSendKey[];
extern char Keyboard_SetTextFieldPos[];
extern char Keyboard_TickKeyRepeat[];
extern char Keyboard_TouchKey[];
extern char Keyboard_TouchSendKey[];
extern char Keyboard_UpdateShiftKey[];
extern char LetterGrid_GetSlotY[];
extern char LetterGrid_LoadPocketLetters[];
extern char LetterGrid_SetLetters0A[];
extern char LetterGrid_SetLetters2D[];
extern char LetterGrid_TestBit[];
extern char LetterGrid_UpdatePopAnim[];
extern char LocalWl_OnSetGameInfo[];
extern char LocalWl_SetEventCallback[];
extern char NumberPad_AllocLabel[];
extern char NumberPad_ClearFlags[];
extern char NumberPad_Draw[];
extern char NumberPad_DrawKeypadFrame[];
extern char NumberPad_GetCursorX[];
extern char NumberPad_GetValue[];
extern char NumberPad_HitTestKey[];
extern char NumberPad_IsCursorOnButton[];
extern char NumberPad_PlayCancelSe[];
extern char NumberPad_PressCursorKey[];
extern char NumberPad_RedrawValues[];
extern char NumberPad_ReleaseLabels[];
extern char NumberPad_SetAmounts[];
extern char PlayerActor_EndAct3C[];
extern char PlayerActor_EndFillHole[];
extern char PlayerActor_EndFishWait[];
extern char PlayerActor_EndShovelStrike[];
extern char PlayerActor_EndTreeShake[];
extern char PlayerActor_EndUmbrellaSpin[];
extern char PlayerActor_GetTrackTarget[];
extern char PlayerActor_LocalEndWatch[];
extern char PlayerActor_LocalRequestDoorApproach[];
extern char PlayerActor_MainAct5C[];
extern char PlayerActor_MainDoorWalkIn[];
extern char PlayerActor_MainFtrPullMove[];
extern char PlayerActor_MainFtrPush[];
extern char PlayerActor_MainHaircutStart[];
extern char PlayerActor_MainMailboxWait[];
extern char PlayerActor_MainReleaseCreature[];
extern char PlayerActor_MainShovelStrike[];
extern char PlayerActor_MainStandUpSide1[];
extern char PlayerActor_MainThrowBottle[];
extern char PlayerActor_NetAct12[];
extern char PlayerActor_NetAct44[];
extern char PlayerActor_NetAct82[];
extern char PlayerActor_NetAxeBreak[];
extern char PlayerActor_NetAxeFollowThrough[];
extern char PlayerActor_NetFishWait[];
extern char PlayerActor_NetFtrPushMove[];
extern char PlayerActor_RequestAct3C[];
extern char PlayerActor_RequestLieInBed[];
extern char PlayerActor_RoomInteractAt[];
extern char PlayerActor_SetupAct3C[];
extern char PlayerActor_SetupAxeFollowThrough[];
extern char PlayerActor_SetupFirework[];
extern char PlayerActor_SetupFishEscape[];
extern char PlayerActor_SetupHaircutCut[];
extern char PlayerActor_SetupStorageClose[];
extern char PlayerActor_SetupTreeShakeRelease[];
extern char PocketMenuUnk_HasTouchMoved[];
extern char PocketMenu_CanEditRoom[];
extern char PocketMenu_GetPlayerSlot[];
extern char PocketMenu_SetSlotItem[];
extern char PocketMenu_StartRemoveBlink[];
extern char PopupChoice_Update[];
extern char PostOfficeMenu_CloseLetterView[];
extern char PostOfficeMenu_MoveCursorToTarget[];
extern char RoomObjTex_Construct[];
extern char Room_PickRandomWalkTarget[];
extern char SockCore_IsLinkUp[];
extern char Sock_AllocHook[];
extern char Sock_Bind[];
extern char Sock_Startup[];
extern char SpNpcKappn_GetAnimState[];
extern char StarSky_CancelUpload[];
extern char StarSky_DrawArrows[];
extern char StarSky_FindConstellationByLine[];
extern char StarSky_HitArrow[];
extern char StarSky_IsConstellationFree[];
extern char StarSky_RebuildScreen[];
extern char StarSky_ScreenToCell[];
extern char StarSky_ScreenToCellInScope[];
extern char StarSky_ScrollInDir[];
extern char StarSky_ScrollX[];
extern char StarSky_SetScroll[];
extern char StarSky_SetScrollTarget[];
extern char TownMapImage_AllocGlobal[];
extern char TownMapImage_BuildMarkersGlobal[];
extern char TownMapImage_CopyPixels[];
extern char TownMapImage_FinishGlobal[];
extern char TownMapMarkers_AddVillagerHouses[];
extern char TownMapMarkers_Clear[];
extern char TownMapMarkers_Get[];
extern char VillagerTalkTopics_CopyTables[];
extern char WfcApList_Exit[];
extern char WfcButtonBar_InputTask[];
extern char WfcButtonBar_IsClosed[];
extern char WfcErased_HandleInput[];
extern char WfcErased_WaitButtonBar[];
extern char WfcMoveMb_GetChildState[];
extern char WfcMoveWh_StateInReset[];
extern char WfcMove_StepMeasureChannel[];
extern char WfcPool_Destroy[];
extern char WfcSimpleStartRecv_HandleResult[];
extern char WfcSimpleStartRecv_IsLidClosed[];
extern char WfcSound_SetVolume[];
extern char WfcTextKb_SetInsertEnabled[];
extern char WfcText_DrawMonospace[];
extern char WfcTransferDone_Update[];
extern char WfcTransferFailed_Enter[];
extern char WfcTransferFailed_LoadBg[];
extern char WlxWm_NextAllowedChannel[];
extern char Wlx_StartExchange[];
extern char Wlx_Stop[];
extern char _ZN10BarberPoleC2Ev[];
extern char _ZN10FtrStorage13enterFtrAct01Ev[];
extern char _ZN10FtrStorage13execTalkAct06Ev[];
extern char _ZN10FtrTopItem4drawEP8FtrActor[];
extern char _ZN10LetterGrid15clearCursorSlotEv[];
extern char _ZN10LetterGrid8drawMarkEii[];
extern char _ZN10MelodyMenu10execClosedEv[];
extern char _ZN10MelodyMenu10hideCursorEv[];
extern char _ZN10MelodyMenu10showCursorEv[];
extern char _ZN10MelodyMenu11endPlaybackEv[];
extern char _ZN10MelodyMenu14beginDialogDimEv[];
extern char _ZN10MelodyMenu15resetTextLabelsEv[];
extern char _ZN10MelodyMenu17startConfirmTouchEv[];
extern char _ZN10MelodyMenu8onCreateEv[];
extern char _ZN10MelodyMenuD2Ev[];
extern char _ZN10PocketMenu17isHoldingMoneyBagEi[];
extern char _ZN10PocketMenu9mainAct39Ev[];
extern char _ZN11BbsReadMenu10showCursorEv[];
extern char _ZN11BbsReadMenu17setupButtonLabelsEv[];
extern char _ZN11BbsReadMenu8onDeleteEv[];
extern char _ZN11BbsReadMenuD2Ev[];
extern char _ZN11CatalogMenu10selectItemEji[];
extern char _ZN11CatalogMenu10stateCloseEv[];
extern char _ZN11CatalogMenu16syncKnobToScrollEv[];
extern char _ZN11CatalogMenuD2Ev[];
extern char _ZN11FtrComputer10execFtrActEv[];
extern char _ZN11FtrComputerD0Ev[];
extern char _ZN11SpNpcBlanca8onDeleteEv[];
extern char _ZN11SpNpcCopper12canStartSaveEv[];
extern char _ZN11TitleScreen15updateEraseTownEv[];
extern char _ZN11TitleScreen15updateWaitStartEv[];
extern char _ZN11TitleScreen17updateBackToTitleEv[];
extern char _ZN12DonationMenu10stateCloseEv[];
extern char _ZN12DonationMenu18updateKnobPositionEv[];
extern char _ZN12DonationMenu19updateBarTransitionEv[];
extern char _ZN12DonationMenuD2Ev[];
extern char _ZN12FtrStackLinkD2Ev[];
extern char _ZN12SongPickMenu18moveCursorToTargetEv[];
extern char _ZN12SpNpcCeleste21tryStartTelescopeTalkEv[];
extern char _ZN12SpNpcHarriet13isSessionPaidEv[];
extern char _ZN13FieldVillagerD2Ev[];
extern char _ZN13FtrStackedSet5clearEv[];
extern char _ZN13MapViewerMenu11updateTouchEv[];
extern char _ZN13MapViewerMenu12requestCloseEv[];
extern char _ZN13MapViewerMenu14allocTextLabelEv[];
extern char _ZN13MapViewerMenu19setListScrollTargetEj[];
extern char _ZN13PocketMenuUnk6pickUpEj[];
extern char _ZN13PocketMenuUnk9mainAct0DEv[];
extern char _ZN13SpNpcGulliver10setupAct01Ev[];
extern char _ZN13SpNpcNookShop14getRunDistanceEv[];
extern char _ZN14DateTimePicker10clearFlagsEj[];
extern char _ZN14DateTimePicker13moveKnobByPadEv[];
extern char _ZN14DateTimePicker14getListCursorXEv[];
extern char _ZN14DateTimePicker9placeKnobEv[];
extern char _ZN14FriendCodeMenu12notifyParentEj[];
extern char _ZN14FriendCodeMenu13releaseCursorEv[];
extern char _ZN14FriendCodeMenu14pressCursorKeyEv[];
extern char _ZN14FriendCodeMenu8setCaretEh[];
extern char _ZN14LetterGiveMenu16cursorToPopupTopEv[];
extern char _ZN14LetterGiveMenu16showCursorAtSlotEv[];
extern char _ZN14LetterGiveMenu17setupLetterPanelsEv[];
extern char _ZN14LetterGiveMenu8getSlotYEj[];
extern char _ZN14TitleBlinkText4showEv[];
extern char _ZN14TownMapMarkersC2Ev[];
extern char _ZN15AmountEntryMenu10showCursorEv[];
extern char _ZN15AmountEntryMenu12stateOpeningEv[];
extern char _ZN15AmountEntryMenu13refreshCursorEv[];
extern char _ZN15AmountEntryMenu16stateTouchRepeatEv[];
extern char _ZN15AmountEntryMenu9stateOpenEv[];
extern char _ZN15FriendRosterTab10blendColorEiiii[];
extern char _ZN15FriendRosterTab10execClosedEv[];
extern char _ZN15FriendRosterTab12removeFriendEv[];
extern char _ZN15FriendRosterTab16openFriendEditorEi[];
extern char _ZN15FriendRosterTab18updateRowMarkBlinkEv[];
extern char _ZN15FriendRosterTab9mainAct01Ev[];
extern char _ZN15LetterWriteMenu9mainAct0BEv[];
extern char _ZN15NearbyTownsMenu15postStateUpdateEv[];
extern char _ZN15NearbyTownsMenu16findRowByAddressEPh[];
extern char _ZN15PocketsFullMenu12onChoiceDropEv[];
extern char _ZN15PocketsFullMenu13putItemInSlotEiii[];
extern char _ZN15PocketsFullMenu16endNewItemActionEi[];
extern char _ZN15PocketsFullMenu23sendInsectReleasePacketEhh[];
extern char _ZN16DistantTownsMenu11refreshPageEv[];
extern char _ZN16DistantTownsMenu14preStateUpdateEv[];
extern char _ZN16DistantTownsMenu15resetTextLabelsEv[];
extern char _ZN16DistantTownsMenu17updateCursorPressEv[];
extern char _ZN16DistantTownsMenu19refreshFriendStatusEv[];
extern char _ZN16DistantTownsMenu6onDrawEv[];
extern char _ZN16SpNpcWendellTalk16setResultHandlerEi[];
extern char _ZN17LetterStorageMenu15onChoiceDiscardEv[];
extern char _ZN17LetterStorageMenu9pressTab4Ev[];
extern char _ZN17MenuTownListPanel10clearFlagsEj[];
extern char _ZN17MenuTownListPanel9loadBgGfxEv[];
extern char _ZN17PatternEditorMenu13findSpanStartEiii[];
extern char _ZN17PatternEditorMenu13stateWaitWearEv[];
extern char _ZN17PatternEditorMenu15useToolAtCursorEv[];
extern char _ZN17PatternEditorMenu17endShapeAndResumeEv[];
extern char _ZN17PatternEditorMenu19saveToPlayerPatternEv[];
extern char _ZN17PatternEditorMenuD2Ev[];
extern char _ZN17PatternSelectMenu10execClosedEv[];
extern char _ZN17PocketLettersMenu16cursorToPopupTopEv[];
extern char _ZN17SpNpcPellyPhyllis8isOnlineEv[];
extern char _ZN17WfcFriendListMenu14loadBgGraphicsEv[];
extern char _ZN17WfcFriendListMenu8onDeleteEv[];
extern char _ZN17WfcFriendListMenu9allocTextEv[];
extern char _ZN17WfcFriendListMenu9placeKnobEv[];
extern char _ZN17WfcFriendListMenuD2Ev[];
extern char _ZN20LostFoundRecycleMenu9testFlagsEj[];
extern char _ZN20PocketItemSelectMenu16cursorToPopupTopEv[];
extern char _ZN20PocketItemSelectMenu16getSlotItemFlagsEj[];
extern char _ZN22FieldVillagerAiPutAway16enterPutAwayItemEP13FieldVillager[];
extern char _ZN22KatrinaEncodedString164dataEv[];
extern char _ZN23ConstellationEditorMenu16enterDialogTouchEv[];
extern char _ZN23ConstellationEditorMenu25touchesOtherConstellationEjj[];
extern char _ZN23ConstellationEditorMenu9mainAct0DEv[];
extern char _ZN29FieldVillagerAiBirthdayInvite19birthdayInviteStep2EP13FieldVillager[];
extern char _ZN6FtrBed12execFtrAct03Ev[];
extern char _ZN6MapTab14allocTextLabelEv[];
extern char _ZN6MapTab15jumpToSelectionEv[];
extern char _ZN6MapTab16highlightListRowEj[];
extern char _ZN6MapTab19setListScrollTargetEj[];
extern char _ZN7Mailbox10execNoMailEv[];
extern char _ZN8BankMenu13selectDepositEv[];
extern char _ZN8FtrActor11onMoveStartEi[];
extern char _ZN9DesignTab10abortPopupEv[];
extern char _ZN9DesignTab13releaseCursorEv[];
extern char _ZN9DesignTab14updateWearWaitEv[];
extern char _ZN9DesignTab16refreshNameLabelEv[];
extern char _ZN9DesignTab16startButtonInputEv[];
extern char _ZN9DesignTab16updateCursorMoveEv[];
extern char _ZN9DesignTab20moveCursorToPopupRowEv[];
extern char _ZN9DesignTabD2Ev[];
extern char _ZN9FtrGyroidD0Ev[];
extern char _ZN9FtrKind0413enterFtrAct02Ev[];
extern char _ZN9FtrKind05D2Ev[];
extern char _ZN9FtrKind0613enterFtrAct02Ev[];
extern char _ZN9FtrStereo13execTalkAct02Ev[];
extern char _ZN9MusicMenu12paintListRowEij[];
extern char _ZN9MusicMenu13updateMessageEv[];
extern char _ZN9MusicMenu14activateTargetEj[];
extern char _ZN9MusicMenu14refreshButtonsEv[];
extern char _ZN9MusicMenu14updateKnobKeysEv[];
extern char _ZN9MusicMenu18moveCursorToTargetEv[];
extern char _ZN9MusicMenu20targetButtonAtCursorEv[];
extern char _ZN9MusicMenu8onCreateEv[];
extern char _ZN9MusicMenu9testFlagsEj[];
extern char _ZN9MusicMenuD2Ev[];

static const HostSharedCandidate sCands_BarberMachine_Start[] = {
    {4, BarberMachine_Start},
    {1, WfcText_DrawMonospace},
};
const HostSharedCall gSharedCall_BarberMachine_Start = {2, sCands_BarberMachine_Start};

static const HostSharedCandidate sCands_BuildingList_FindByItem[] = {
    {3, BuildingList_FindByItem},
    {1, WfcSimpleStartRecv_HandleResult},
};
const HostSharedCall gSharedCall_BuildingList_FindByItem = {2, sCands_BuildingList_FindByItem};

static const HostSharedCandidate sCands_CreatureBook_ActivateFocus[] = {
    {114, CreatureBook_ActivateFocus},
    {107, _ZN15PocketsFullMenu16endNewItemActionEi},
    {110, _ZN20LostFoundRecycleMenu9testFlagsEj},
    {133, _ZN14FriendCodeMenu12notifyParentEj},
};
const HostSharedCall gSharedCall_CreatureBook_ActivateFocus = {4, sCands_CreatureBook_ActivateFocus};

static const HostSharedCandidate sCands_CreatureBook_DrawRows[] = {
    {114, CreatureBook_DrawRows},
    {108, _ZN14LetterGiveMenu8getSlotYEj},
};
const HostSharedCall gSharedCall_CreatureBook_DrawRows = {2, sCands_CreatureBook_DrawRows};

static const HostSharedCandidate sCands_CreatureBook_EndScrollTouch[] = {
    {114, CreatureBook_EndScrollTouch},
    {99, _ZN13PocketMenuUnk9mainAct0DEv},
};
const HostSharedCall gSharedCall_CreatureBook_EndScrollTouch = {2, sCands_CreatureBook_EndScrollTouch};

static const HostSharedCandidate sCands_CreatureBook_GetFocusX[] = {
    {114, CreatureBook_GetFocusX},
    {95, Keyboard_UpdateShiftKey},
    {105, _ZN17LetterStorageMenu15onChoiceDiscardEv},
};
const HostSharedCall gSharedCall_CreatureBook_GetFocusX = {3, sCands_CreatureBook_GetFocusX};

static const HostSharedCandidate sCands_CreatureBook_GetFocusY[] = {
    {114, CreatureBook_GetFocusY},
    {107, _ZN15PocketsFullMenu23sendInsectReleasePacketEhh},
    {108, _ZN14LetterGiveMenu16cursorToPopupTopEv},
};
const HostSharedCall gSharedCall_CreatureBook_GetFocusY = {3, sCands_CreatureBook_GetFocusY};

static const HostSharedCandidate sCands_CreatureBook_GetFocusedTab[] = {
    {114, CreatureBook_GetFocusedTab},
    {119, _ZN15FriendRosterTab10execClosedEv},
};
const HostSharedCall gSharedCall_CreatureBook_GetFocusedTab = {2, sCands_CreatureBook_GetFocusedTab};

static const HostSharedCandidate sCands_CreatureBook_IsFocusOnPageArrow[] = {
    {114, CreatureBook_IsFocusOnPageArrow},
    {105, _ZN17LetterStorageMenu9pressTab4Ev},
    {108, _ZN14LetterGiveMenu16showCursorAtSlotEv},
};
const HostSharedCall gSharedCall_CreatureBook_IsFocusOnPageArrow = {3, sCands_CreatureBook_IsFocusOnPageArrow};

static const HostSharedCandidate sCands_CreatureBook_RefreshRowIcons[] = {
    {114, CreatureBook_RefreshRowIcons},
    {99, PocketMenuUnk_HasTouchMoved},
};
const HostSharedCall gSharedCall_CreatureBook_RefreshRowIcons = {2, sCands_CreatureBook_RefreshRowIcons};

static const HostSharedCandidate sCands_CreatureBook_WaitScrollHoldStart[] = {
    {114, CreatureBook_WaitScrollHoldStart},
    {104, PostOfficeMenu_MoveCursorToTarget},
    {107, _ZN15PocketsFullMenu13putItemInSlotEiii},
    {129, _ZN23ConstellationEditorMenu16enterDialogTouchEv},
};
const HostSharedCall gSharedCall_CreatureBook_WaitScrollHoldStart = {4, sCands_CreatureBook_WaitScrollHoldStart};

static const HostSharedCandidate sCands_DateTimePicker_BeginFrame[] = {
    {134, DateTimePicker_BeginFrame},
    {95, Keyboard_GetKeyCodePage0A},
    {120, _ZN13MapViewerMenu12requestCloseEv},
};
const HostSharedCall gSharedCall_DateTimePicker_BeginFrame = {3, sCands_DateTimePicker_BeginFrame};

static const HostSharedCandidate sCands_DateTimePicker_CancelList[] = {
    {134, DateTimePicker_CancelList},
    {119, _ZN15FriendRosterTab18updateRowMarkBlinkEv},
    {123, _ZN17PatternEditorMenu15useToolAtCursorEv},
};
const HostSharedCall gSharedCall_DateTimePicker_CancelList = {3, sCands_DateTimePicker_CancelList};

static const HostSharedCandidate sCands_DateTimePicker_DecideList[] = {
    {134, DateTimePicker_DecideList},
    {121, _ZN9DesignTab16refreshNameLabelEv},
};
const HostSharedCall gSharedCall_DateTimePicker_DecideList = {2, sCands_DateTimePicker_DecideList};

static const HostSharedCandidate sCands_DateTimePicker_EndHandDrag[] = {
    {134, DateTimePicker_EndHandDrag},
    {121, _ZN9DesignTab14updateWearWaitEv},
};
const HostSharedCall gSharedCall_DateTimePicker_EndHandDrag = {2, sCands_DateTimePicker_EndHandDrag};

static const HostSharedCandidate sCands_DateTimePicker_GrabHand[] = {
    {134, DateTimePicker_GrabHand},
    {94, LetterGrid_TestBit},
};
const HostSharedCall gSharedCall_DateTimePicker_GrabHand = {2, sCands_DateTimePicker_GrabHand};

static const HostSharedCandidate sCands_DateTimePicker_HitTestList[] = {
    {134, DateTimePicker_HitTestList},
    {121, _ZN9DesignTab20moveCursorToPopupRowEv},
};
const HostSharedCall gSharedCall_DateTimePicker_HitTestList = {2, sCands_DateTimePicker_HitTestList};

static const HostSharedCandidate sCands_DateTimePicker_UpdateHandAnim[] = {
    {134, DateTimePicker_UpdateHandAnim},
    {140, _ZN16DistantTownsMenu6onDrawEv},
};
const HostSharedCall gSharedCall_DateTimePicker_UpdateHandAnim = {2, sCands_DateTimePicker_UpdateHandAnim};

static const HostSharedCandidate sCands_DateTimePicker_UpdateListClose[] = {
    {134, DateTimePicker_UpdateListClose},
    {117, _ZN14TownMapMarkersC2Ev},
};
const HostSharedCall gSharedCall_DateTimePicker_UpdateListClose = {2, sCands_DateTimePicker_UpdateListClose};

static const HostSharedCandidate sCands_DateTimePicker_UpdateListOpen[] = {
    {134, DateTimePicker_UpdateListOpen},
    {94, InventoryItemGrid_AllocUpload},
};
const HostSharedCall gSharedCall_DateTimePicker_UpdateListOpen = {2, sCands_DateTimePicker_UpdateListOpen};

static const HostSharedCandidate sCands_DwcFriend_GetProfileId[] = {
    {65, DwcFriend_GetProfileId},
    {72, _ZN13SpNpcGulliver10setupAct01Ev},
    {79, _ZN16SpNpcWendellTalk16setResultHandlerEi},
};
const HostSharedCall gSharedCall_DwcFriend_GetProfileId = {3, sCands_DwcFriend_GetProfileId};

static const HostSharedCandidate sCands_DwcFriend_IsIdle[] = {
    {65, DwcFriend_IsIdle},
    {74, _ZN11SpNpcBlanca8onDeleteEv},
};
const HostSharedCall gSharedCall_DwcFriend_IsIdle = {2, sCands_DwcFriend_IsIdle};

static const HostSharedCandidate sCands_FieldInsect_GetPosAndKind[] = {
    {3, FieldInsect_GetPosAndKind},
    {4, _ZN10BarberPoleC2Ev},
};
const HostSharedCall gSharedCall_FieldInsect_GetPosAndKind = {2, sCands_FieldInsect_GetPosAndKind};

static const HostSharedCandidate sCands_FieldObj_FreeCedarFileBufs[] = {
    {3, FieldObj_FreeCedarFileBufs},
    {4, PlayerActor_MainDoorWalkIn},
};
const HostSharedCall gSharedCall_FieldObj_FreeCedarFileBufs = {2, sCands_FieldObj_FreeCedarFileBufs};

static const HostSharedCandidate sCands_FieldObj_LoadIconModels[] = {
    {3, FieldObj_LoadIconModels},
    {4, PlayerActor_MainHaircutStart},
};
const HostSharedCall gSharedCall_FieldObj_LoadIconModels = {2, sCands_FieldObj_LoadIconModels};

static const HostSharedCandidate sCands_FieldObj_LoadStones[] = {
    {3, FieldObj_LoadStones},
    {4, PlayerActor_SetupHaircutCut},
};
const HostSharedCall gSharedCall_FieldObj_LoadStones = {2, sCands_FieldObj_LoadStones};

static const HostSharedCandidate sCands_FieldObjectManager_Create[] = {
    {3, FieldObjectManager_Create},
    {4, PlayerActor_NetAct44},
};
const HostSharedCall gSharedCall_FieldObjectManager_Create = {2, sCands_FieldObjectManager_Create};

static const HostSharedCandidate sCands_Field_GetStructureTexSuffix[] = {
    {3, Field_GetStructureTexSuffix},
    {1, WfcSimpleStartRecv_IsLidClosed},
};
const HostSharedCall gSharedCall_Field_GetStructureTexSuffix = {2, sCands_Field_GetStructureTexSuffix};

static const HostSharedCandidate sCands_FishCatch_Reset[] = {
    {3, FishCatch_Reset},
    {4, PlayerActor_MainFtrPullMove},
};
const HostSharedCall gSharedCall_FishCatch_Reset = {2, sCands_FishCatch_Reset};

static const HostSharedCandidate sCands_FishCatch_StateStart[] = {
    {3, FishCatch_StateStart},
    {4, PlayerActor_MainFtrPush},
};
const HostSharedCall gSharedCall_FishCatch_StateStart = {2, sCands_FishCatch_StateStart};

static const HostSharedCandidate sCands_FishShadow_EnterSpawn[] = {
    {3, FishShadow_EnterSpawn},
    {4, PlayerActor_MainStandUpSide1},
};
const HostSharedCall gSharedCall_FishShadow_EnterSpawn = {2, sCands_FishShadow_EnterSpawn};

static const HostSharedCandidate sCands_FishShadow_RunAi[] = {
    {3, FishShadow_RunAi},
    {4, PlayerActor_RequestLieInBed},
};
const HostSharedCall gSharedCall_FishShadow_RunAi = {2, sCands_FishShadow_RunAi};

static const HostSharedCandidate sCands_GeneralMenuHeader_GetStyle[] = {
    {124, GeneralMenuHeader_GetStyle},
    {96, _ZN10PocketMenu17isHoldingMoneyBagEi},
};
const HostSharedCall gSharedCall_GeneralMenuHeader_GetStyle = {2, sCands_GeneralMenuHeader_GetStyle};

static const HostSharedCandidate sCands_InvItem_IsDeliveryItem[] = {
    {94, InvItem_IsDeliveryItem},
    {134, _ZN14DateTimePicker13moveKnobByPadEv},
};
const HostSharedCall gSharedCall_InvItem_IsDeliveryItem = {2, sCands_InvItem_IsDeliveryItem};

static const HostSharedCandidate sCands_InvItem_IsNonTransferable[] = {
    {94, InvItem_IsNonTransferable},
    {142, _ZN11CatalogMenu16syncKnobToScrollEv},
};
const HostSharedCall gSharedCall_InvItem_IsNonTransferable = {2, sCands_InvItem_IsNonTransferable};

static const HostSharedCandidate sCands_InvItem_IsNotFishInsectOrFlower[] = {
    {94, InvItem_IsNotFishInsectOrFlower},
    {130, NumberPad_ReleaseLabels},
};
const HostSharedCall gSharedCall_InvItem_IsNotFishInsectOrFlower = {2, sCands_InvItem_IsNotFishInsectOrFlower};

static const HostSharedCandidate sCands_InvItem_IsTurnipFishOrInsect[] = {
    {94, InvItem_IsTurnipFishOrInsect},
    {143, _ZN10MelodyMenu11endPlaybackEv},
};
const HostSharedCall gSharedCall_InvItem_IsTurnipFishOrInsect = {2, sCands_InvItem_IsTurnipFishOrInsect};

static const HostSharedCandidate sCands_InventoryBg_DrawSprite[] = {
    {94, InventoryBg_DrawSprite},
    {130, NumberPad_PlayCancelSe},
};
const HostSharedCall gSharedCall_InventoryBg_DrawSprite = {2, sCands_InventoryBg_DrawSprite};

static const HostSharedCandidate sCands_InventoryBg_Init[] = {
    {94, InventoryBg_Init},
    {145, _ZN12DonationMenu19updateBarTransitionEv},
};
const HostSharedCall gSharedCall_InventoryBg_Init = {2, sCands_InventoryBg_Init};

static const HostSharedCandidate sCands_InventoryBg_LoadBg[] = {
    {94, InventoryBg_LoadBg},
    {140, _ZN16DistantTownsMenu11refreshPageEv},
};
const HostSharedCall gSharedCall_InventoryBg_LoadBg = {2, sCands_InventoryBg_LoadBg};

static const HostSharedCandidate sCands_InventoryBg_LoadPictureForHeldItem[] = {
    {94, InventoryBg_LoadPictureForHeldItem},
    {123, _ZN17PatternEditorMenu17endShapeAndResumeEv},
};
const HostSharedCall gSharedCall_InventoryBg_LoadPictureForHeldItem = {2, sCands_InventoryBg_LoadPictureForHeldItem};

static const HostSharedCandidate sCands_InventoryBg_PreUpdate[] = {
    {94, InventoryBg_PreUpdate},
    {95, Keyboard_SelectSendKey},
    {117, TownMapMarkers_AddVillagerHouses},
};
const HostSharedCall gSharedCall_InventoryBg_PreUpdate = {3, sCands_InventoryBg_PreUpdate};

static const HostSharedCandidate sCands_InventoryBg_ResetHighlight[] = {
    {94, InventoryBg_ResetHighlight},
    {144, _ZN9MusicMenu14activateTargetEj},
};
const HostSharedCall gSharedCall_InventoryBg_ResetHighlight = {2, sCands_InventoryBg_ResetHighlight};

static const HostSharedCandidate sCands_InventoryBg_SetBellsPanelMode[] = {
    {94, InventoryBg_SetBellsPanelMode},
    {147, _ZN11TitleScreen15updateEraseTownEv},
};
const HostSharedCall gSharedCall_InventoryBg_SetBellsPanelMode = {2, sCands_InventoryBg_SetBellsPanelMode};

static const HostSharedCandidate sCands_InventoryBg_StartBlink[] = {
    {94, InventoryBg_StartBlink},
    {144, _ZN9MusicMenu12paintListRowEij},
};
const HostSharedCall gSharedCall_InventoryBg_StartBlink = {2, sCands_InventoryBg_StartBlink};

static const HostSharedCandidate sCands_InventoryItemGrid_ClearMarks[] = {
    {94, InventoryItemGrid_ClearMarks},
    {143, _ZN10MelodyMenu10execClosedEv},
};
const HostSharedCall gSharedCall_InventoryItemGrid_ClearMarks = {2, sCands_InventoryItemGrid_ClearMarks};

static const HostSharedCandidate sCands_InventoryItemGrid_ClearSlot[] = {
    {94, InventoryItemGrid_ClearSlot},
    {113, _ZN11BbsReadMenu8onDeleteEv},
};
const HostSharedCall gSharedCall_InventoryItemGrid_ClearSlot = {2, sCands_InventoryItemGrid_ClearSlot};

static const HostSharedCandidate sCands_InventoryItemGrid_DisableSlotRange[] = {
    {94, InventoryItemGrid_DisableSlotRange},
    {140, _ZN16DistantTownsMenu17updateCursorPressEv},
    {145, _ZN12DonationMenu10stateCloseEv},
};
const HostSharedCall gSharedCall_InventoryItemGrid_DisableSlotRange = {3, sCands_InventoryItemGrid_DisableSlotRange};

static const HostSharedCandidate sCands_InventoryItemGrid_DrawExtraMarks[] = {
    {94, InventoryItemGrid_DrawExtraMarks},
    {123, _ZN17PatternEditorMenu13findSpanStartEiii},
    {144, _ZN9MusicMenu13updateMessageEv},
};
const HostSharedCall gSharedCall_InventoryItemGrid_DrawExtraMarks = {3, sCands_InventoryItemGrid_DrawExtraMarks};

static const HostSharedCandidate sCands_InventoryItemGrid_Exit[] = {
    {94, InventoryItemGrid_Exit},
    {121, _ZN9DesignTab16startButtonInputEv},
};
const HostSharedCall gSharedCall_InventoryItemGrid_Exit = {2, sCands_InventoryItemGrid_Exit};

static const HostSharedCandidate sCands_InventoryItemGrid_FindBoxSlotAt[] = {
    {94, InventoryItemGrid_FindBoxSlotAt},
    {95, Keyboard_SelectEmotionByCode},
};
const HostSharedCall gSharedCall_InventoryItemGrid_FindBoxSlotAt = {2, sCands_InventoryItemGrid_FindBoxSlotAt};

static const HostSharedCandidate sCands_InventoryItemGrid_GetSlotItem[] = {
    {94, InventoryItemGrid_GetSlotItem},
    {140, _ZN16DistantTownsMenu19refreshFriendStatusEv},
    {146, _ZN17WfcFriendListMenu14loadBgGraphicsEv},
};
const HostSharedCall gSharedCall_InventoryItemGrid_GetSlotItem = {3, sCands_InventoryItemGrid_GetSlotItem};

static const HostSharedCandidate sCands_InventoryItemGrid_HitTestSlot21[] = {
    {94, InventoryItemGrid_HitTestSlot21},
    {134, DateTimePicker_AngleAt},
};
const HostSharedCall gSharedCall_InventoryItemGrid_HitTestSlot21 = {2, sCands_InventoryItemGrid_HitTestSlot21};

static const HostSharedCandidate sCands_InventoryItemGrid_IsSlotDisabled[] = {
    {94, InventoryItemGrid_IsSlotDisabled},
    {141, _ZN15NearbyTownsMenu15postStateUpdateEv},
};
const HostSharedCall gSharedCall_InventoryItemGrid_IsSlotDisabled = {2, sCands_InventoryItemGrid_IsSlotDisabled};

static const HostSharedCandidate sCands_InventoryItemGrid_LoadPockets[] = {
    {94, InventoryItemGrid_LoadPockets},
    {118, _ZN6MapTab19setListScrollTargetEj},
};
const HostSharedCall gSharedCall_InventoryItemGrid_LoadPockets = {2, sCands_InventoryItemGrid_LoadPockets};

static const HostSharedCandidate sCands_InventoryItemGrid_SetCursorSlot[] = {
    {94, InventoryItemGrid_SetCursorSlot},
    {120, _ZN13MapViewerMenu19setListScrollTargetEj},
};
const HostSharedCall gSharedCall_InventoryItemGrid_SetCursorSlot = {2, sCands_InventoryItemGrid_SetCursorSlot};

static const HostSharedCandidate sCands_InventoryItemGrid_SetHeldItem[] = {
    {94, InventoryItemGrid_SetHeldItem},
    {144, _ZN9MusicMenu14updateKnobKeysEv},
};
const HostSharedCall gSharedCall_InventoryItemGrid_SetHeldItem = {2, sCands_InventoryItemGrid_SetHeldItem};

static const HostSharedCandidate sCands_InventoryItemGrid_ShowSlotName[] = {
    {94, InventoryItemGrid_ShowSlotName},
    {140, _ZN16DistantTownsMenu14preStateUpdateEv},
};
const HostSharedCall gSharedCall_InventoryItemGrid_ShowSlotName = {2, sCands_InventoryItemGrid_ShowSlotName};

static const HostSharedCandidate sCands_InventoryItemGrid_StartPresentAnim[] = {
    {94, InventoryItemGrid_StartPresentAnim},
    {121, _ZN9DesignTab10abortPopupEv},
};
const HostSharedCall gSharedCall_InventoryItemGrid_StartPresentAnim = {2, sCands_InventoryItemGrid_StartPresentAnim};

static const HostSharedCandidate sCands_InventoryItemGrid_UpdatePresentAnim[] = {
    {94, InventoryItemGrid_UpdatePresentAnim},
    {146, _ZN17WfcFriendListMenu9allocTextEv},
};
const HostSharedCall gSharedCall_InventoryItemGrid_UpdatePresentAnim = {2, sCands_InventoryItemGrid_UpdatePresentAnim};

static const HostSharedCandidate sCands_Inventory_PlayPickUpSe[] = {
    {94, Inventory_PlayPickUpSe},
    {95, Keyboard_PlayCharSe},
    {127, StarSky_SetScrollTarget},
    {130, NumberPad_AllocLabel},
};
const HostSharedCall gSharedCall_Inventory_PlayPickUpSe = {4, sCands_Inventory_PlayPickUpSe};

static const HostSharedCandidate sCands_Keyboard_ClearHighlight[] = {
    {95, Keyboard_ClearHighlight},
    {101, _ZN20PocketItemSelectMenu16cursorToPopupTopEv},
    {103, _ZN17PocketLettersMenu16cursorToPopupTopEv},
};
const HostSharedCall gSharedCall_Keyboard_ClearHighlight = {3, sCands_Keyboard_ClearHighlight};

static const HostSharedCandidate sCands_Keyboard_DeleteRange[] = {
    {95, Keyboard_DeleteRange},
    {131, _ZN15AmountEntryMenu9stateOpenEv},
};
const HostSharedCall gSharedCall_Keyboard_DeleteRange = {2, sCands_Keyboard_DeleteRange};

static const HostSharedCandidate sCands_Keyboard_DisableModifierKeys[] = {
    {95, Keyboard_DisableModifierKeys},
    {120, _ZN13MapViewerMenu11updateTouchEv},
};
const HostSharedCall gSharedCall_Keyboard_DisableModifierKeys = {2, sCands_Keyboard_DisableModifierKeys};

static const HostSharedCandidate sCands_Keyboard_DrawCopyPasteKeys[] = {
    {95, Keyboard_DrawCopyPasteKeys},
    {118, _ZN6MapTab15jumpToSelectionEv},
    {143, _ZN10MelodyMenu8onCreateEv},
};
const HostSharedCall gSharedCall_Keyboard_DrawCopyPasteKeys = {3, sCands_Keyboard_DrawCopyPasteKeys};

static const HostSharedCandidate sCands_Keyboard_DrawCopyPasteKeysChat[] = {
    {95, Keyboard_DrawCopyPasteKeysChat},
    {133, _ZN14FriendCodeMenu14pressCursorKeyEv},
};
const HostSharedCall gSharedCall_Keyboard_DrawCopyPasteKeysChat = {2, sCands_Keyboard_DrawCopyPasteKeysChat};

static const HostSharedCandidate sCands_Keyboard_EnableKey[] = {
    {95, Keyboard_EnableKey},
    {99, _ZN13PocketMenuUnk6pickUpEj},
};
const HostSharedCall gSharedCall_Keyboard_EnableKey = {2, sCands_Keyboard_EnableKey};

static const HostSharedCandidate sCands_Keyboard_EnterTabRowAtX[] = {
    {95, Keyboard_EnterTabRowAtX},
    {142, _ZN11CatalogMenu10selectItemEji},
};
const HostSharedCall gSharedCall_Keyboard_EnterTabRowAtX = {2, sCands_Keyboard_EnterTabRowAtX};

static const HostSharedCandidate sCands_Keyboard_EnterTabRowAtX2[] = {
    {95, Keyboard_EnterTabRowAtX2},
    {143, _ZN10MelodyMenu10showCursorEv},
    {145, _ZN12DonationMenu18updateKnobPositionEv},
};
const HostSharedCall gSharedCall_Keyboard_EnterTabRowAtX2 = {3, sCands_Keyboard_EnterTabRowAtX2};

static const HostSharedCandidate sCands_Keyboard_GetSelectedEmotion[] = {
    {95, Keyboard_GetSelectedEmotion},
    {118, _ZN6MapTab16highlightListRowEj},
    {119, _ZN15FriendRosterTab10blendColorEiiii},
    {131, _ZN15AmountEntryMenu13refreshCursorEv},
};
const HostSharedCall gSharedCall_Keyboard_GetSelectedEmotion = {4, sCands_Keyboard_GetSelectedEmotion};

static const HostSharedCandidate sCands_Keyboard_GetTypedRunLength[] = {
    {95, Keyboard_GetTypedRunLength},
    {121, _ZN9DesignTab16updateCursorMoveEv},
};
const HostSharedCall gSharedCall_Keyboard_GetTypedRunLength = {2, sCands_Keyboard_GetTypedRunLength};

static const HostSharedCandidate sCands_Keyboard_HandleModeKey[] = {
    {95, Keyboard_HandleModeKey},
    {119, _ZN15FriendRosterTab12removeFriendEv},
};
const HostSharedCall gSharedCall_Keyboard_HandleModeKey = {2, sCands_Keyboard_HandleModeKey};

static const HostSharedCandidate sCands_Keyboard_HighlightKey[] = {
    {95, Keyboard_HighlightKey},
    {123, _ZN17PatternEditorMenu13stateWaitWearEv},
};
const HostSharedCall gSharedCall_Keyboard_HighlightKey = {2, sCands_Keyboard_HighlightKey};

static const HostSharedCandidate sCands_Keyboard_InsertCharMultiline[] = {
    {95, Keyboard_InsertCharMultiline},
    {118, _ZN6MapTab14allocTextLabelEv},
};
const HostSharedCall gSharedCall_Keyboard_InsertCharMultiline = {2, sCands_Keyboard_InsertCharMultiline};

static const HostSharedCandidate sCands_Keyboard_IsOnButtonKey[] = {
    {95, Keyboard_IsOnButtonKey},
    {107, _ZN15PocketsFullMenu12onChoiceDropEv},
    {109, _ZN12SongPickMenu18moveCursorToTargetEv},
    {129, _ZN23ConstellationEditorMenu9mainAct0DEv},
};
const HostSharedCall gSharedCall_Keyboard_IsOnButtonKey = {4, sCands_Keyboard_IsOnButtonKey};

static const HostSharedCandidate sCands_Keyboard_LoadEmotionIcons[] = {
    {95, Keyboard_LoadEmotionIcons},
    {94, LetterGrid_UpdatePopAnim},
    {144, _ZN9MusicMenu8onCreateEv},
};
const HostSharedCall gSharedCall_Keyboard_LoadEmotionIcons = {3, sCands_Keyboard_LoadEmotionIcons};

static const HostSharedCandidate sCands_Keyboard_LoadLetterChars[] = {
    {95, Keyboard_LoadLetterChars},
    {94, _ZN10LetterGrid15clearCursorSlotEv},
};
const HostSharedCall gSharedCall_Keyboard_LoadLetterChars = {2, sCands_Keyboard_LoadLetterChars};

static const HostSharedCandidate sCands_Keyboard_MarkScreenDirty[] = {
    {95, Keyboard_MarkScreenDirty},
    {133, _ZN14FriendCodeMenu13releaseCursorEv},
};
const HostSharedCall gSharedCall_Keyboard_MarkScreenDirty = {2, sCands_Keyboard_MarkScreenDirty};

static const HostSharedCandidate sCands_Keyboard_ModifyCharKey104[] = {
    {95, Keyboard_ModifyCharKey104},
    {131, _ZN15AmountEntryMenu12stateOpeningEv},
};
const HostSharedCall gSharedCall_Keyboard_ModifyCharKey104 = {2, sCands_Keyboard_ModifyCharKey104};

static const HostSharedCandidate sCands_Keyboard_PlayCopySe[] = {
    {95, Keyboard_PlayCopySe},
    {143, _ZN10MelodyMenu15resetTextLabelsEv},
};
const HostSharedCall gSharedCall_Keyboard_PlayCopySe = {2, sCands_Keyboard_PlayCopySe};

static const HostSharedCandidate sCands_Keyboard_PressCursorKey[] = {
    {95, Keyboard_PressCursorKey},
    {113, _ZN11BbsReadMenu10showCursorEv},
};
const HostSharedCall gSharedCall_Keyboard_PressCursorKey = {2, sCands_Keyboard_PressCursorKey};

static const HostSharedCandidate sCands_Keyboard_Reload[] = {
    {95, Keyboard_Reload},
    {142, _ZN11CatalogMenu10stateCloseEv},
};
const HostSharedCall gSharedCall_Keyboard_Reload = {2, sCands_Keyboard_Reload};

static const HostSharedCandidate sCands_Keyboard_ReplaceCharBeforeCursor[] = {
    {95, Keyboard_ReplaceCharBeforeCursor},
    {94, _ZN10LetterGrid8drawMarkEii},
};
const HostSharedCall gSharedCall_Keyboard_ReplaceCharBeforeCursor = {2, sCands_Keyboard_ReplaceCharBeforeCursor};

static const HostSharedCandidate sCands_Keyboard_ResetTypedRun[] = {
    {95, Keyboard_ResetTypedRun},
    {120, _ZN13MapViewerMenu14allocTextLabelEv},
    {123, _ZN17PatternEditorMenu19saveToPlayerPatternEv},
};
const HostSharedCall gSharedCall_Keyboard_ResetTypedRun = {3, sCands_Keyboard_ResetTypedRun};

static const HostSharedCandidate sCands_Keyboard_RestoreLastPage[] = {
    {95, Keyboard_RestoreLastPage},
    {129, _ZN23ConstellationEditorMenu25touchesOtherConstellationEjj},
};
const HostSharedCall gSharedCall_Keyboard_RestoreLastPage = {2, sCands_Keyboard_RestoreLastPage};

static const HostSharedCandidate sCands_Keyboard_SelectEmotionByCode[] = {
    {95, Keyboard_SelectEmotionByCode},
    {94, InventoryItemGrid_FindBoxSlotAt},
};
const HostSharedCall gSharedCall_Keyboard_SelectEmotionByCode = {2, sCands_Keyboard_SelectEmotionByCode};

static const HostSharedCandidate sCands_Keyboard_SelectSendKey[] = {
    {95, Keyboard_SelectSendKey},
    {94, InventoryBg_PreUpdate},
    {117, TownMapMarkers_AddVillagerHouses},
};
const HostSharedCall gSharedCall_Keyboard_SelectSendKey = {3, sCands_Keyboard_SelectSendKey};

static const HostSharedCandidate sCands_Keyboard_SetTextFieldPos[] = {
    {95, Keyboard_SetTextFieldPos},
    {144, _ZN9MusicMenu14refreshButtonsEv},
};
const HostSharedCall gSharedCall_Keyboard_SetTextFieldPos = {2, sCands_Keyboard_SetTextFieldPos};

static const HostSharedCandidate sCands_Keyboard_TickKeyRepeat[] = {
    {95, Keyboard_TickKeyRepeat},
    {142, CatalogMenu_SetupBgLayers},
};
const HostSharedCall gSharedCall_Keyboard_TickKeyRepeat = {2, sCands_Keyboard_TickKeyRepeat};

static const HostSharedCandidate sCands_Keyboard_TouchKey[] = {
    {95, Keyboard_TouchKey},
    {119, _ZN15FriendRosterTab9mainAct01Ev},
};
const HostSharedCall gSharedCall_Keyboard_TouchKey = {2, sCands_Keyboard_TouchKey};

static const HostSharedCandidate sCands_Keyboard_TouchSendKey[] = {
    {95, Keyboard_TouchSendKey},
    {131, _ZN15AmountEntryMenu10showCursorEv},
    {132, _ZN8BankMenu13selectDepositEv},
};
const HostSharedCall gSharedCall_Keyboard_TouchSendKey = {3, sCands_Keyboard_TouchSendKey};

static const HostSharedCandidate sCands_LetterGrid_GetSlotY[] = {
    {94, LetterGrid_GetSlotY},
    {119, _ZN15FriendRosterTab16openFriendEditorEi},
};
const HostSharedCall gSharedCall_LetterGrid_GetSlotY = {2, sCands_LetterGrid_GetSlotY};

static const HostSharedCandidate sCands_LetterGrid_LoadPocketLetters[] = {
    {94, LetterGrid_LoadPocketLetters},
    {146, _ZN17WfcFriendListMenu8onDeleteEv},
};
const HostSharedCall gSharedCall_LetterGrid_LoadPocketLetters = {2, sCands_LetterGrid_LoadPocketLetters};

static const HostSharedCandidate sCands_LetterGrid_SetLetters0A[] = {
    {94, LetterGrid_SetLetters0A},
    {131, _ZN15AmountEntryMenu16stateTouchRepeatEv},
};
const HostSharedCall gSharedCall_LetterGrid_SetLetters0A = {2, sCands_LetterGrid_SetLetters0A};

static const HostSharedCandidate sCands_LetterGrid_SetLetters2D[] = {
    {94, LetterGrid_SetLetters2D},
    {133, _ZN14FriendCodeMenu8setCaretEh},
};
const HostSharedCall gSharedCall_LetterGrid_SetLetters2D = {2, sCands_LetterGrid_SetLetters2D};

static const HostSharedCandidate sCands_LetterGrid_UpdatePopAnim[] = {
    {94, LetterGrid_UpdatePopAnim},
    {95, Keyboard_LoadEmotionIcons},
    {144, _ZN9MusicMenu8onCreateEv},
};
const HostSharedCall gSharedCall_LetterGrid_UpdatePopAnim = {3, sCands_LetterGrid_UpdatePopAnim};

static const HostSharedCandidate sCands_LocalWl_SetEventCallback[] = {
    {66, LocalWl_SetEventCallback},
    {65, SockCore_IsLinkUp},
    {67, WlxWm_NextAllowedChannel},
    {68, _ZN13FieldVillagerD2Ev},
    {69, VillagerTalkTopics_CopyTables},
};
const HostSharedCall gSharedCall_LocalWl_SetEventCallback = {5, sCands_LocalWl_SetEventCallback};

static const HostSharedCandidate sCands_NumberPad_Draw[] = {
    {130, NumberPad_Draw},
    {113, _ZN11BbsReadMenu17setupButtonLabelsEv},
};
const HostSharedCall gSharedCall_NumberPad_Draw = {2, sCands_NumberPad_Draw};

static const HostSharedCandidate sCands_NumberPad_DrawKeypadFrame[] = {
    {130, NumberPad_DrawKeypadFrame},
    {143, _ZN10MelodyMenu10hideCursorEv},
};
const HostSharedCall gSharedCall_NumberPad_DrawKeypadFrame = {2, sCands_NumberPad_DrawKeypadFrame};

static const HostSharedCandidate sCands_NumberPad_GetCursorX[] = {
    {130, NumberPad_GetCursorX},
    {121, _ZN9DesignTab13releaseCursorEv},
    {140, _ZN16DistantTownsMenu15resetTextLabelsEv},
};
const HostSharedCall gSharedCall_NumberPad_GetCursorX = {3, sCands_NumberPad_GetCursorX};

static const HostSharedCandidate sCands_NumberPad_GetValue[] = {
    {130, NumberPad_GetValue},
    {94, InventoryBg_UploadPalette},
};
const HostSharedCall gSharedCall_NumberPad_GetValue = {2, sCands_NumberPad_GetValue};

static const HostSharedCandidate sCands_NumberPad_HitTestKey[] = {
    {130, NumberPad_HitTestKey},
    {117, TownMapMarkers_Get},
    {147, _ZN14TitleBlinkText4showEv},
};
const HostSharedCall gSharedCall_NumberPad_HitTestKey = {3, sCands_NumberPad_HitTestKey};

static const HostSharedCandidate sCands_NumberPad_IsCursorOnButton[] = {
    {130, NumberPad_IsCursorOnButton},
    {144, _ZN9MusicMenu18moveCursorToTargetEv},
};
const HostSharedCall gSharedCall_NumberPad_IsCursorOnButton = {2, sCands_NumberPad_IsCursorOnButton};

static const HostSharedCandidate sCands_NumberPad_PlayCancelSe[] = {
    {130, NumberPad_PlayCancelSe},
    {94, InventoryBg_DrawSprite},
};
const HostSharedCall gSharedCall_NumberPad_PlayCancelSe = {2, sCands_NumberPad_PlayCancelSe};

static const HostSharedCandidate sCands_NumberPad_PressCursorKey[] = {
    {130, NumberPad_PressCursorKey},
    {141, _ZN15NearbyTownsMenu16findRowByAddressEPh},
};
const HostSharedCall gSharedCall_NumberPad_PressCursorKey = {2, sCands_NumberPad_PressCursorKey};

static const HostSharedCandidate sCands_NumberPad_SetAmounts[] = {
    {130, NumberPad_SetAmounts},
    {127, StarSky_DrawArrows},
};
const HostSharedCall gSharedCall_NumberPad_SetAmounts = {2, sCands_NumberPad_SetAmounts};

static const HostSharedCandidate sCands_PlayerActor_EndAct3C[] = {
    {3, PlayerActor_EndAct3C},
    {1, WfcTransferFailed_LoadBg},
};
const HostSharedCall gSharedCall_PlayerActor_EndAct3C = {2, sCands_PlayerActor_EndAct3C};

static const HostSharedCandidate sCands_PlayerActor_EndFillHole[] = {
    {3, PlayerActor_EndFillHole},
    {4, _ZN8FtrActor11onMoveStartEi},
};
const HostSharedCall gSharedCall_PlayerActor_EndFillHole = {2, sCands_PlayerActor_EndFillHole};

static const HostSharedCandidate sCands_PlayerActor_EndFishWait[] = {
    {3, PlayerActor_EndFishWait},
    {1, WfcErased_HandleInput},
};
const HostSharedCall gSharedCall_PlayerActor_EndFishWait = {2, sCands_PlayerActor_EndFishWait};

static const HostSharedCandidate sCands_PlayerActor_EndShovelStrike[] = {
    {3, PlayerActor_EndShovelStrike},
    {4, _ZN11FtrComputer10execFtrActEv},
};
const HostSharedCall gSharedCall_PlayerActor_EndShovelStrike = {2, sCands_PlayerActor_EndShovelStrike};

static const HostSharedCandidate sCands_PlayerActor_EndTreeShake[] = {
    {3, PlayerActor_EndTreeShake},
    {4, FtrActor_ReleaseCollider},
};
const HostSharedCall gSharedCall_PlayerActor_EndTreeShake = {2, sCands_PlayerActor_EndTreeShake};

static const HostSharedCandidate sCands_PlayerActor_EndUmbrellaSpin[] = {
    {3, PlayerActor_EndUmbrellaSpin},
    {4, _ZN10FtrStorage13enterFtrAct01Ev},
};
const HostSharedCall gSharedCall_PlayerActor_EndUmbrellaSpin = {2, sCands_PlayerActor_EndUmbrellaSpin};

static const HostSharedCandidate sCands_PlayerActor_GetTrackTarget[] = {
    {3, PlayerActor_GetTrackTarget},
    {4, _ZN9FtrKind05D2Ev},
};
const HostSharedCall gSharedCall_PlayerActor_GetTrackTarget = {2, sCands_PlayerActor_GetTrackTarget};

static const HostSharedCandidate sCands_PlayerActor_LocalEndWatch[] = {
    {3, PlayerActor_LocalEndWatch},
    {4, _ZN9FtrKind0413enterFtrAct02Ev},
};
const HostSharedCall gSharedCall_PlayerActor_LocalEndWatch = {2, sCands_PlayerActor_LocalEndWatch};

static const HostSharedCandidate sCands_PlayerActor_LocalRequestDoorApproach[] = {
    {3, PlayerActor_LocalRequestDoorApproach},
    {1, WfcApList_Exit},
};
const HostSharedCall gSharedCall_PlayerActor_LocalRequestDoorApproach = {2, sCands_PlayerActor_LocalRequestDoorApproach};

static const HostSharedCandidate sCands_PlayerActor_MainAct5C[] = {
    {3, PlayerActor_MainAct5C},
    {4, _ZN11FtrComputerD0Ev},
};
const HostSharedCall gSharedCall_PlayerActor_MainAct5C = {2, sCands_PlayerActor_MainAct5C};

static const HostSharedCandidate sCands_PlayerActor_MainMailboxWait[] = {
    {3, PlayerActor_MainMailboxWait},
    {1, WfcButtonBar_InputTask},
};
const HostSharedCall gSharedCall_PlayerActor_MainMailboxWait = {2, sCands_PlayerActor_MainMailboxWait};

static const HostSharedCandidate sCands_PlayerActor_MainReleaseCreature[] = {
    {3, PlayerActor_MainReleaseCreature},
    {4, _ZN9FtrKind0613enterFtrAct02Ev},
};
const HostSharedCall gSharedCall_PlayerActor_MainReleaseCreature = {2, sCands_PlayerActor_MainReleaseCreature};

static const HostSharedCandidate sCands_PlayerActor_MainShovelStrike[] = {
    {3, PlayerActor_MainShovelStrike},
    {1, WfcTextKb_SetInsertEnabled},
};
const HostSharedCall gSharedCall_PlayerActor_MainShovelStrike = {2, sCands_PlayerActor_MainShovelStrike};

static const HostSharedCandidate sCands_PlayerActor_MainThrowBottle[] = {
    {3, PlayerActor_MainThrowBottle},
    {4, _ZN12FtrStackLinkD2Ev},
};
const HostSharedCall gSharedCall_PlayerActor_MainThrowBottle = {2, sCands_PlayerActor_MainThrowBottle};

static const HostSharedCandidate sCands_PlayerActor_NetAct12[] = {
    {4, PlayerActor_NetAct12},
    {1, WfcMove_StepMeasureChannel},
};
const HostSharedCall gSharedCall_PlayerActor_NetAct12 = {2, sCands_PlayerActor_NetAct12};

static const HostSharedCandidate sCands_PlayerActor_NetAct82[] = {
    {3, PlayerActor_NetAct82},
    {4, _ZN10FtrTopItem4drawEP8FtrActor},
};
const HostSharedCall gSharedCall_PlayerActor_NetAct82 = {2, sCands_PlayerActor_NetAct82};

static const HostSharedCandidate sCands_PlayerActor_NetAxeBreak[] = {
    {3, PlayerActor_NetAxeBreak},
    {4, _ZN9FtrStereo13execTalkAct02Ev},
};
const HostSharedCall gSharedCall_PlayerActor_NetAxeBreak = {2, sCands_PlayerActor_NetAxeBreak};

static const HostSharedCandidate sCands_PlayerActor_NetAxeFollowThrough[] = {
    {3, PlayerActor_NetAxeFollowThrough},
    {1, WfcTransferDone_Update},
};
const HostSharedCall gSharedCall_PlayerActor_NetAxeFollowThrough = {2, sCands_PlayerActor_NetAxeFollowThrough};

static const HostSharedCandidate sCands_PlayerActor_NetFishWait[] = {
    {3, PlayerActor_NetFishWait},
    {1, WfcErased_WaitButtonBar},
};
const HostSharedCall gSharedCall_PlayerActor_NetFishWait = {2, sCands_PlayerActor_NetFishWait};

static const HostSharedCandidate sCands_PlayerActor_NetFtrPushMove[] = {
    {4, PlayerActor_NetFtrPushMove},
    {1, WfcMoveWh_StateInReset},
};
const HostSharedCall gSharedCall_PlayerActor_NetFtrPushMove = {2, sCands_PlayerActor_NetFtrPushMove};

static const HostSharedCandidate sCands_PlayerActor_RequestAct3C[] = {
    {3, PlayerActor_RequestAct3C},
    {1, WfcTransferFailed_Enter},
};
const HostSharedCall gSharedCall_PlayerActor_RequestAct3C = {2, sCands_PlayerActor_RequestAct3C};

static const HostSharedCandidate sCands_PlayerActor_RoomInteractAt[] = {
    {4, PlayerActor_RoomInteractAt},
    {1, WfcSound_SetVolume},
};
const HostSharedCall gSharedCall_PlayerActor_RoomInteractAt = {2, sCands_PlayerActor_RoomInteractAt};

static const HostSharedCandidate sCands_PlayerActor_SetupAct3C[] = {
    {3, PlayerActor_SetupAct3C},
    {4, _ZN6FtrBed12execFtrAct03Ev},
};
const HostSharedCall gSharedCall_PlayerActor_SetupAct3C = {2, sCands_PlayerActor_SetupAct3C};

static const HostSharedCandidate sCands_PlayerActor_SetupAxeFollowThrough[] = {
    {3, PlayerActor_SetupAxeFollowThrough},
    {4, _ZN10FtrStorage13execTalkAct06Ev},
};
const HostSharedCall gSharedCall_PlayerActor_SetupAxeFollowThrough = {2, sCands_PlayerActor_SetupAxeFollowThrough};

static const HostSharedCandidate sCands_PlayerActor_SetupFirework[] = {
    {3, PlayerActor_SetupFirework},
    {4, _ZN13FtrStackedSet5clearEv},
};
const HostSharedCall gSharedCall_PlayerActor_SetupFirework = {2, sCands_PlayerActor_SetupFirework};

static const HostSharedCandidate sCands_PlayerActor_SetupFishEscape[] = {
    {3, PlayerActor_SetupFishEscape},
    {4, _ZN9FtrGyroidD0Ev},
};
const HostSharedCall gSharedCall_PlayerActor_SetupFishEscape = {2, sCands_PlayerActor_SetupFishEscape};

static const HostSharedCandidate sCands_PlayerActor_SetupStorageClose[] = {
    {4, PlayerActor_SetupStorageClose},
    {1, WfcMoveMb_GetChildState},
};
const HostSharedCall gSharedCall_PlayerActor_SetupStorageClose = {2, sCands_PlayerActor_SetupStorageClose};

static const HostSharedCandidate sCands_PlayerActor_SetupTreeShakeRelease[] = {
    {3, PlayerActor_SetupTreeShakeRelease},
    {1, WfcButtonBar_IsClosed},
};
const HostSharedCall gSharedCall_PlayerActor_SetupTreeShakeRelease = {2, sCands_PlayerActor_SetupTreeShakeRelease};

static const HostSharedCandidate sCands_PocketMenu_CanEditRoom[] = {
    {97, PocketMenu_CanEditRoom},
    {98, _ZN10PocketMenu9mainAct39Ev},
};
const HostSharedCall gSharedCall_PocketMenu_CanEditRoom = {2, sCands_PocketMenu_CanEditRoom};

static const HostSharedCandidate sCands_PocketMenu_GetPlayerSlot[] = {
    {96, PocketMenu_GetPlayerSlot},
    {101, _ZN20PocketItemSelectMenu16getSlotItemFlagsEj},
    {104, PostOfficeMenu_CloseLetterView},
    {108, _ZN14LetterGiveMenu17setupLetterPanelsEv},
};
const HostSharedCall gSharedCall_PocketMenu_GetPlayerSlot = {4, sCands_PocketMenu_GetPlayerSlot};

static const HostSharedCandidate sCands_PocketMenu_SetSlotItem[] = {
    {96, PocketMenu_SetSlotItem},
    {125, _ZN17PatternSelectMenu10execClosedEv},
};
const HostSharedCall gSharedCall_PocketMenu_SetSlotItem = {2, sCands_PocketMenu_SetSlotItem};

static const HostSharedCandidate sCands_PocketMenu_StartRemoveBlink[] = {
    {96, PocketMenu_StartRemoveBlink},
    {122, _ZN15LetterWriteMenu9mainAct0BEv},
};
const HostSharedCall gSharedCall_PocketMenu_StartRemoveBlink = {2, sCands_PocketMenu_StartRemoveBlink};

static const HostSharedCandidate sCands_PopupChoice_Update[] = {
    {2, PopupChoice_Update},
    {1, Aoss_HandleRecvPacket},
};
const HostSharedCall gSharedCall_PopupChoice_Update = {2, sCands_PopupChoice_Update};

static const HostSharedCandidate sCands_RoomObjTex_Construct[] = {
    {4, RoomObjTex_Construct},
    {1, WfcPool_Destroy},
};
const HostSharedCall gSharedCall_RoomObjTex_Construct = {2, sCands_RoomObjTex_Construct};

static const HostSharedCandidate sCands_Room_PickRandomWalkTarget[] = {
    {4, Room_PickRandomWalkTarget},
    {3, _ZN7Mailbox10execNoMailEv},
};
const HostSharedCall gSharedCall_Room_PickRandomWalkTarget = {2, sCands_Room_PickRandomWalkTarget};

static const HostSharedCandidate sCands_Sock_Bind[] = {
    {65, Sock_Bind},
    {68, _ZN29FieldVillagerAiBirthdayInvite19birthdayInviteStep2EP13FieldVillager},
};
const HostSharedCall gSharedCall_Sock_Bind = {2, sCands_Sock_Bind};

static const HostSharedCandidate sCands_Sock_Startup[] = {
    {65, Sock_Startup},
    {68, _ZN22FieldVillagerAiPutAway16enterPutAwayItemEP13FieldVillager},
};
const HostSharedCall gSharedCall_Sock_Startup = {2, sCands_Sock_Startup};

static const HostSharedCandidate sCands_SpNpcKappn_GetAnimState[] = {
    {51, SpNpcKappn_GetAnimState},
    {45, _ZN22KatrinaEncodedString164dataEv},
    {46, _ZN12SpNpcCeleste21tryStartTelescopeTalkEv},
    {48, _ZN11SpNpcCopper12canStartSaveEv},
    {50, _ZN13SpNpcNookShop14getRunDistanceEv},
    {53, _ZN12SpNpcHarriet13isSessionPaidEv},
    {54, _ZN17SpNpcPellyPhyllis8isOnlineEv},
};
const HostSharedCall gSharedCall_SpNpcKappn_GetAnimState = {7, sCands_SpNpcKappn_GetAnimState};

static const HostSharedCandidate sCands_StarSky_CancelUpload[] = {
    {127, StarSky_CancelUpload},
    {147, _ZN11TitleScreen15updateWaitStartEv},
};
const HostSharedCall gSharedCall_StarSky_CancelUpload = {2, sCands_StarSky_CancelUpload};

static const HostSharedCandidate sCands_StarSky_DrawArrows[] = {
    {127, StarSky_DrawArrows},
    {130, NumberPad_SetAmounts},
};
const HostSharedCall gSharedCall_StarSky_DrawArrows = {2, sCands_StarSky_DrawArrows};

static const HostSharedCandidate sCands_StarSky_FindConstellationByLine[] = {
    {127, StarSky_FindConstellationByLine},
    {143, _ZN10MelodyMenu14beginDialogDimEv},
    {144, _ZN9MusicMenu9testFlagsEj},
};
const HostSharedCall gSharedCall_StarSky_FindConstellationByLine = {3, sCands_StarSky_FindConstellationByLine};

static const HostSharedCandidate sCands_StarSky_HitArrow[] = {
    {127, StarSky_HitArrow},
    {147, _ZN11TitleScreen17updateBackToTitleEv},
};
const HostSharedCall gSharedCall_StarSky_HitArrow = {2, sCands_StarSky_HitArrow};

static const HostSharedCandidate sCands_StarSky_IsConstellationFree[] = {
    {127, StarSky_IsConstellationFree},
    {113, _ZN11BbsReadMenuD2Ev},
    {123, _ZN17PatternEditorMenuD2Ev},
    {134, _ZN14DateTimePicker10clearFlagsEj},
    {139, _ZN17MenuTownListPanel10clearFlagsEj},
    {142, _ZN11CatalogMenuD2Ev},
    {143, _ZN10MelodyMenuD2Ev},
    {144, _ZN9MusicMenuD2Ev},
    {145, _ZN12DonationMenuD2Ev},
    {146, _ZN17WfcFriendListMenuD2Ev},
};
const HostSharedCall gSharedCall_StarSky_IsConstellationFree = {10, sCands_StarSky_IsConstellationFree};

static const HostSharedCandidate sCands_StarSky_RebuildScreen[] = {
    {127, StarSky_RebuildScreen},
    {134, _ZN14DateTimePicker9placeKnobEv},
    {144, _ZN9MusicMenu20targetButtonAtCursorEv},
};
const HostSharedCall gSharedCall_StarSky_RebuildScreen = {3, sCands_StarSky_RebuildScreen};

static const HostSharedCandidate sCands_StarSky_ScreenToCell[] = {
    {127, StarSky_ScreenToCell},
    {139, _ZN17MenuTownListPanel9loadBgGfxEv},
};
const HostSharedCall gSharedCall_StarSky_ScreenToCell = {2, sCands_StarSky_ScreenToCell};

static const HostSharedCandidate sCands_StarSky_ScreenToCellInScope[] = {
    {127, StarSky_ScreenToCellInScope},
    {117, TownMapImage_AllocGlobal},
};
const HostSharedCall gSharedCall_StarSky_ScreenToCellInScope = {2, sCands_StarSky_ScreenToCellInScope};

static const HostSharedCandidate sCands_StarSky_ScrollInDir[] = {
    {127, StarSky_ScrollInDir},
    {130, NumberPad_RedrawValues},
};
const HostSharedCall gSharedCall_StarSky_ScrollInDir = {2, sCands_StarSky_ScrollInDir};

static const HostSharedCandidate sCands_StarSky_ScrollX[] = {
    {127, StarSky_ScrollX},
    {146, _ZN17WfcFriendListMenu9placeKnobEv},
};
const HostSharedCall gSharedCall_StarSky_ScrollX = {2, sCands_StarSky_ScrollX};

static const HostSharedCandidate sCands_StarSky_SetScroll[] = {
    {127, StarSky_SetScroll},
    {117, TownMapImage_CopyPixels},
};
const HostSharedCall gSharedCall_StarSky_SetScroll = {2, sCands_StarSky_SetScroll};

static const HostSharedCandidate sCands_StarSky_SetScrollTarget[] = {
    {127, StarSky_SetScrollTarget},
    {94, Inventory_PlayPickUpSe},
    {95, Keyboard_PlayCharSe},
    {130, NumberPad_AllocLabel},
};
const HostSharedCall gSharedCall_StarSky_SetScrollTarget = {4, sCands_StarSky_SetScrollTarget};

static const HostSharedCandidate sCands_TownMapImage_AllocGlobal[] = {
    {117, TownMapImage_AllocGlobal},
    {127, StarSky_ScreenToCellInScope},
};
const HostSharedCall gSharedCall_TownMapImage_AllocGlobal = {2, sCands_TownMapImage_AllocGlobal};

static const HostSharedCandidate sCands_TownMapImage_BuildMarkersGlobal[] = {
    {117, TownMapImage_BuildMarkersGlobal},
    {134, _ZN14DateTimePicker14getListCursorXEv},
};
const HostSharedCall gSharedCall_TownMapImage_BuildMarkersGlobal = {2, sCands_TownMapImage_BuildMarkersGlobal};

static const HostSharedCandidate sCands_TownMapImage_FinishGlobal[] = {
    {117, TownMapImage_FinishGlobal},
    {94, InventoryBg_ClearDirty},
    {95, Keyboard_ClearFlags},
    {121, _ZN9DesignTabD2Ev},
    {130, NumberPad_ClearFlags},
};
const HostSharedCall gSharedCall_TownMapImage_FinishGlobal = {5, sCands_TownMapImage_FinishGlobal};

static const HostSharedCandidate sCands_TownMapMarkers_Clear[] = {
    {117, TownMapMarkers_Clear},
    {143, _ZN10MelodyMenu17startConfirmTouchEv},
};
const HostSharedCall gSharedCall_TownMapMarkers_Clear = {2, sCands_TownMapMarkers_Clear};

static const HostSharedCandidate sCands_TownMapMarkers_Get[] = {
    {117, TownMapMarkers_Get},
    {130, NumberPad_HitTestKey},
    {147, _ZN14TitleBlinkText4showEv},
};
const HostSharedCall gSharedCall_TownMapMarkers_Get = {3, sCands_TownMapMarkers_Get};

static const HostSharedCandidate sCands_Wlx_StartExchange[] = {
    {67, Wlx_StartExchange},
    {65, Sock_AllocHook},
};
const HostSharedCall gSharedCall_Wlx_StartExchange = {2, sCands_Wlx_StartExchange};

static const HostSharedCandidate sCands_Wlx_Stop[] = {
    {67, Wlx_Stop},
    {66, LocalWl_OnSetGameInfo},
};
const HostSharedCall gSharedCall_Wlx_Stop = {2, sCands_Wlx_Stop};
