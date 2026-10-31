#include "types.h"
#include "sys/ProcProfile.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_02038474.h"
#include "proto/main/unk_020407fc.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_020571f4.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02082d74.h"
#include "proto/main/unk_02089fbc.h"
#include "proto/main/unk_0208e6d8.h"
#include "proto/main/unk_0208f268.h"
#include "proto/main/unk_02095794.h"
#include "proto/main/unk_02095b1c.h"
#include "proto/main/unk_02096c10.h"
#include "proto/main/unk_0209c9f8.h"
#include "proto/main/unk_0209e394.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020b4174.h"
#include "proto/main/unk_020b45e0.h"
#include "proto/main/unk_020b478c.h"
#include "proto/main/unk_020b5da0.h"
#include "proto/main/unk_020b7d10.h"
#include "proto/main/unk_020e1e2c.h"
#include "proto/ov004/unk_ov004_0223db88.h"
#include "proto/ov004/unk_ov004_0223e014.h"
#include "proto/ov004/unk_ov004_0223e9bc.h"

extern ProcProfile sFieldSceneProfile;
extern ProcProfile sSceneLightsProfile;
extern ProcProfile sPlayerActorProfile;
extern ProcProfile sCameraProfile;
extern ProcProfile data_020da3c4;
extern ProcProfile sFieldGroundProfile;
extern ProcProfile sRoomShellProfile;
extern ProcProfile sSnowballSpawnerProfile;
extern ProcProfile sRoostCafeSetProfile;
extern ProcProfile sCheckInGateProfile;
extern ProcProfile sRecycleBoxProfile;
extern ProcProfile sTaxiInteriorProfile;
extern ProcProfile sMuseumDisplayProfile;
extern ProcProfile sBarberMachineProfile;
extern ProcProfile sBarberPoleProfile;
extern ProcProfile sRoomBoardSignProfile;
extern ProcProfile sVillagerBoardProfile;
extern ProcProfile sMuseumExhibitInfoProfile;
extern ProcProfile sBuildingActorProfile;
extern ProcProfile sReddTentProfile;
extern ProcProfile sGateHouseProfile;
extern ProcProfile sVillagerHouseProfile;
extern ProcProfile sTownHallProfile;
extern ProcProfile sPlayerHouseProfile;
extern ProcProfile sTownSignProfile;
extern ProcProfile sShopBuildingProfile;
extern ProcProfile sBulletinBoardProfile;
extern ProcProfile sKappnTaxiProfile;
extern ProcProfile sMailboxProfile;
extern ProcProfile sCountdownSignProfile;
extern ProcProfile sCountdownDigitProfile;
extern ProcProfile sGulliverShipProfile;
extern ProcProfile sKatrinaTentProfile;
extern ProcProfile sGracieCarProfile;
extern ProcProfile sNewYearCountdownProfile;
extern ProcProfile sPlayerBedSetterProfile;
extern ProcProfile sAtmProfile;
extern ProcProfile sRoomTelephoneProfile;
extern ProcProfile sFtrActorProfile;
extern ProcProfile sFtrBasicProfile;
extern ProcProfile sFtrKind02Profile;
extern ProcProfile sFtrKind03Profile;
extern ProcProfile sFtrKind04Profile;
extern ProcProfile sFtrKind05Profile;
extern ProcProfile sFtrKind06Profile;
extern ProcProfile sFtrKind07Profile;
extern ProcProfile sFtrSeatProfile;
extern ProcProfile sFtrBedProfile;
extern ProcProfile sFtrStorageProfile;
extern ProcProfile sFtrClockProfile;
extern ProcProfile sFtrStereoProfile;
extern ProcProfile sFtrTvProfile;
extern ProcProfile sFtrTvVcrProfile;
extern ProcProfile sFtrCartProfile;
extern ProcProfile sFtrGyroidProfile;
extern ProcProfile sFtrKind19Profile;
extern ProcProfile sFtrCannonProfile;
extern ProcProfile sFtrShirtProfile;
extern ProcProfile sFtrMyDesignProfile;
extern ProcProfile sFtrDesignDisplayProfile;
extern ProcProfile sFtrCompassProfile;
extern ProcProfile sFtrVillagerPicProfile;
extern ProcProfile sFtrInstrumentProfile;
extern ProcProfile sFtrPiggyBankProfile;
extern ProcProfile sFtrMetronomeProfile;
extern ProcProfile sFtrWallpaperSampleProfile;
extern ProcProfile sFtrCarpetSampleProfile;
extern ProcProfile sFtrKind25Profile;
extern ProcProfile sFtrHeadwearProfile;
extern ProcProfile sFtrComputerProfile;
extern ProcProfile sFtrSingingInsectProfile;
extern ProcProfile sFtrPhoneProfile;
extern ProcProfile sFtrNookwayProfile;
extern ProcProfile sSpNpcPeteProfile;
extern ProcProfile sSpNpcReddProfile;
extern ProcProfile sSpNpcTortimerProfile;
extern ProcProfile sSpNpcTortimerFishingTourneyProfile;
extern ProcProfile sSpNpcTortimerBugOffProfile;
extern ProcProfile sSpNpcTortimerFlowerFestProfile;
extern ProcProfile sSpNpcTortimerFireworksProfile;
extern ProcProfile sSpNpcTortimerBrightNightsProfile;
extern ProcProfile sSpNpcTortimerCountdownProfile;
extern ProcProfile sSpNpcTortimer2Profile;
extern ProcProfile sSpNpcRoverProfile;
extern ProcProfile sSpNpcCornimerProfile;
extern ProcProfile sSpNpcGulliverProfile;
extern ProcProfile sSpNpcHarrietProfile;
extern ProcProfile sSpNpcShrunkProfile;
extern ProcProfile sSpNpcBrewsterProfile;
extern ProcProfile sCafeCoffeeSetProfile;
extern ProcProfile sSpNpcResettiProfile;
extern ProcProfile sSpNpcRoostGuestProfile;
extern ProcProfile sSpNpcBlancaProfile;
extern ProcProfile sSpNpcPascalProfile;
extern ProcProfile sSpNpcLyleProfile;
extern ProcProfile sSpNpcSaharahProfile;
extern ProcProfile sSpNpcWendellProfile;
extern ProcProfile sSpNpcGracieProfile;
extern ProcProfile sSpNpcCelesteProfile;
extern ProcProfile sSpNpcBlathersProfile;
extern ProcProfile sSpNpcJoanProfile;
extern ProcProfile sSpNpcKatrinaProfile;
extern ProcProfile sTarotPropsProfile;
extern ProcProfile sSpNpcCopperProfile;
extern ProcProfile sSpNpcBookerProfile;
extern ProcProfile sSpNpcTommyProfile;
extern ProcProfile sSpNpcTimmyProfile;
extern ProcProfile sSpNpcNookShopProfile;
extern ProcProfile sSpNpcSableProfile;
extern ProcProfile sSewingMachineProfile;
extern ProcProfile sSpNpcMabelProfile;
extern ProcProfile sSpNpcPellyPhyllisProfile;
extern ProcProfile sSpNpcKappnProfile;
extern ProcProfile sSpNpcTestProfile;
extern ProcProfile sSpNpcNookIntroProfile;
extern ProcProfile sSpNpcKatieProfile;
extern ProcProfile sSpNpcKaitlinProfile;
extern ProcProfile sBirthdayHostVillagerProfile;
extern ProcProfile sBirthdayGuestVillagerProfile;
extern ProcProfile sHouseVisitVillagerProfile;
extern ProcProfile sSickVillagerProfile;
extern ProcProfile sFieldVillagerProfile;
extern ProcProfile sHouseOwnerVillagerProfile;
extern ProcProfile sFleaMarketSellerVillagerProfile;
extern ProcProfile sFleaMarketBuyerVillagerProfile;
extern ProcProfile sCafeVillagerProfile;
extern ProcProfile sSkyProcProfile;
extern ProcProfile sFieldObjectManagerProfile;
extern ProcProfile sRoomItemIconsProfile;
extern ProcProfile data_020d96ec;
extern ProcProfile sMenuTabBarProfile;
extern ProcProfile sMenuLauncherProfile;
extern ProcProfile sPocketMenuProfile;
extern ProcProfile sPocketMenuUnkProfile;
extern ProcProfile sShopSellMenuProfile;
extern ProcProfile sPocketItemSelectMenuProfile;
extern ProcProfile sChestMenuProfile;
extern ProcProfile sPocketLettersMenuProfile;
extern ProcProfile sPostOfficeMenuProfile;
extern ProcProfile sLetterStorageMenuProfile;
extern ProcProfile sMailboxMenuProfile;
extern ProcProfile sPocketsFullMenuProfile;
extern ProcProfile sLetterGiveMenuProfile;
extern ProcProfile sSongPickMenuProfile;
extern ProcProfile sLostFoundRecycleMenuProfile;
extern ProcProfile data_ov111_02298920;
extern ProcProfile sFishBookTabProfile;
extern ProcProfile sInsectBookTabProfile;
extern ProcProfile sMapTabProfile;
extern ProcProfile sFriendRosterTabProfile;
extern ProcProfile sMapViewerMenuProfile;
extern ProcProfile sDesignTabProfile;
extern ProcProfile data_ov122_0229a130;
extern ProcProfile data_ov112_022999b8;
extern ProcProfile data_ov113_022935c8;
extern ProcProfile sLetterViewMenuProfile;
extern ProcProfile sPatternEditorMenuProfile;
extern ProcProfile sPatternSelectMenuProfile;
extern ProcProfile data_ov126_022999e0;
extern ProcProfile sStargazingMenuProfile;
extern ProcProfile sConstellationEditorMenuProfile;
extern ProcProfile sClockAdjustMenuProfile;
extern ProcProfile sTimeSelectMenuProfile;
extern ProcProfile sBirthdayMenuProfile;
extern ProcProfile sDateSelectMenuProfile;
extern ProcProfile sAmountEntryMenuProfile;
extern ProcProfile sBankMenuProfile;
extern ProcProfile sFriendCodeMenuProfile;
extern ProcProfile sDistantTownsMenuProfile;
extern ProcProfile sNearbyTownsMenuProfile;
extern ProcProfile sCatalogMenuProfile;
extern ProcProfile sMelodyMenuProfile;
extern ProcProfile sMusicMenuProfile;
extern ProcProfile sDonationMenuProfile;
extern ProcProfile sWfcFriendListMenuProfile;
extern ProcProfile sInsectManagerProfile;
extern ProcProfile sSnowballProfile;
extern ProcProfile sMuseumInsectRoomProfile;
extern ProcProfile sHouseRoachManagerProfile;
extern ProcProfile sHouseRoachProfile;
extern ProcProfile sFieldFishManagerProfile;
extern ProcProfile sFishDisplayProfile;
extern ProcProfile sMuseumAquariumProfile;
extern ProcProfile sFieldStructureMgrProfile;
extern ProcProfile sFurnitureManagerProfile;
extern ProcProfile sMsgUiProcProfile;
extern ProcProfile sDummyProcCDProfile;
extern ProcProfile data_020e1178;
static ProcProfile sEffectSplProcProfileHost = {(void *(*)())EffectSplProc_Create, 0xd2, 0xd5};
#define data_020e1178 sEffectSplProcProfileHost
extern ProcProfile sTitleScreenProfile;
extern ProcProfile data_020d9520;


ProcProfile *sProfileTableMain[216] = {
    &sGameRootProfile,
    &data_020e3fd4,
    &sSceneBaseProfile,
    &sDummyScene3Profile,
    &sDummyScene4Profile,
    &sFieldEntrySceneProfile,
    &sFieldSceneProfile,
    &sSceneLightsProfile,
    &sRemotePlayerSpawnerProfile,
    &sPlayerActorProfile,
    &sPlayerNetSyncProfile,
    &sCameraProfile,
    &data_020da3c4,
    &sFieldGroundProfile,
    &sRoomShellProfile,
    &sSnowballSpawnerProfile,
    &sRoostCafeSetProfile,
    &sCheckInGateProfile,
    &sRecycleBoxProfile,
    &sTaxiInteriorProfile,
    &sMuseumDisplayProfile,
    &sBarberMachineProfile,
    &sBarberPoleProfile,
    &sRoomBoardSignProfile,
    &sVillagerBoardProfile,
    &sMuseumExhibitInfoProfile,
    &sBuildingActorProfile,
    &sReddTentProfile,
    &sGateHouseProfile,
    &sVillagerHouseProfile,
    &sTownHallProfile,
    &sPlayerHouseProfile,
    &sTownSignProfile,
    &sShopBuildingProfile,
    &sBulletinBoardProfile,
    &sKappnTaxiProfile,
    &sMailboxProfile,
    &sCountdownSignProfile,
    &sCountdownDigitProfile,
    &sGulliverShipProfile,
    &sKatrinaTentProfile,
    &sGracieCarProfile,
    &sNewYearCountdownProfile,
    &sPlayerBedSetterProfile,
    &sAtmProfile,
    &sRoomTelephoneProfile,
    &sFtrActorProfile,
    &sFtrBasicProfile,
    &sFtrKind02Profile,
    &sFtrKind03Profile,
    &sFtrKind04Profile,
    &sFtrKind05Profile,
    &sFtrKind06Profile,
    &sFtrKind07Profile,
    &sFtrSeatProfile,
    &sFtrBedProfile,
    &sFtrStorageProfile,
    &sFtrClockProfile,
    &sFtrStereoProfile,
    &sFtrTvProfile,
    &sFtrTvVcrProfile,
    &sFtrCartProfile,
    &sFtrGyroidProfile,
    &sFtrKind19Profile,
    &sFtrCannonProfile,
    &sFtrShirtProfile,
    &sFtrMyDesignProfile,
    &sFtrDesignDisplayProfile,
    &sFtrCompassProfile,
    &sFtrVillagerPicProfile,
    &sFtrInstrumentProfile,
    &sFtrPiggyBankProfile,
    &sFtrMetronomeProfile,
    &sFtrWallpaperSampleProfile,
    &sFtrCarpetSampleProfile,
    &sFtrKind25Profile,
    &sFtrHeadwearProfile,
    &sFtrComputerProfile,
    &sFtrSingingInsectProfile,
    &sFtrPhoneProfile,
    &sFtrNookwayProfile,
    &sMuseumRoomProfile,
    &sMuseumFossilRoomProfile,
    &sMuseumRoomUnk53Profile,
    &sSpNpcPeteProfile,
    &sSpNpcReddProfile,
    &sSpNpcTortimerProfile,
    &sSpNpcTortimerFishingTourneyProfile,
    &sSpNpcTortimerBugOffProfile,
    &sSpNpcTortimerFlowerFestProfile,
    &sSpNpcTortimerFireworksProfile,
    &sSpNpcTortimerBrightNightsProfile,
    &sSpNpcTortimerCountdownProfile,
    &sSpNpcTortimer2Profile,
    &sSpNpcRoverProfile,
    &sSpNpcCornimerProfile,
    &sSpNpcGulliverProfile,
    &sSpNpcHarrietProfile,
    &sSpNpcShrunkProfile,
    &sSpNpcBrewsterProfile,
    &sCafeCoffeeSetProfile,
    &sSpNpcResettiProfile,
    &sSpNpcRoostGuestProfile,
    &sSpNpcBlancaProfile,
    &sSpNpcPascalProfile,
    &sSpNpcLyleProfile,
    &sSpNpcSaharahProfile,
    &sSpNpcWendellProfile,
    &sSpNpcGracieProfile,
    &sSpNpcCelesteProfile,
    &sSpNpcBlathersProfile,
    &sSpNpcJoanProfile,
    &sSpNpcKatrinaProfile,
    &sTarotPropsProfile,
    &sSpNpcCopperProfile,
    &sSpNpcBookerProfile,
    &sSpNpcTommyProfile,
    &sSpNpcTimmyProfile,
    &sSpNpcNookShopProfile,
    &sSpNpcSableProfile,
    &sSewingMachineProfile,
    &sSpNpcMabelProfile,
    &sSpNpcPellyPhyllisProfile,
    &sSpNpcKappnProfile,
    &sSpNpcTestProfile,
    &sSpNpcNookIntroProfile,
    &sSpNpcKatieProfile,
    &sSpNpcKaitlinProfile,
    &sBirthdayHostVillagerProfile,
    &sBirthdayGuestVillagerProfile,
    &sHouseVisitVillagerProfile,
    &sSickVillagerProfile,
    &sFieldVillagerProfile,
    &sHouseOwnerVillagerProfile,
    &sFleaMarketSellerVillagerProfile,
    &sFleaMarketBuyerVillagerProfile,
    &sCafeVillagerProfile,
    &sSkyProcProfile,
    &sFieldObjectManagerProfile,
    &sRoomItemIconsProfile,
    &data_020d96ec,
    &data_020e1da0,
    &sMenuManagerProfile,
    &sMenuTabBarProfile,
    &sMenuLauncherProfile,
    &sPocketMenuProfile,
    &sPocketMenuUnkProfile,
    &sShopSellMenuProfile,
    &sPocketItemSelectMenuProfile,
    &sChestMenuProfile,
    &sPocketLettersMenuProfile,
    &sPostOfficeMenuProfile,
    &sLetterStorageMenuProfile,
    &sMailboxMenuProfile,
    &sPocketsFullMenuProfile,
    &sLetterGiveMenuProfile,
    &sSongPickMenuProfile,
    &sLostFoundRecycleMenuProfile,
    &data_ov111_02298920,
    &sFishBookTabProfile,
    &sInsectBookTabProfile,
    &sMapTabProfile,
    &sFriendRosterTabProfile,
    &sMapViewerMenuProfile,
    &sDesignTabProfile,
    &data_ov122_0229a130,
    &data_ov112_022999b8,
    &data_ov113_022935c8,
    &sLetterViewMenuProfile,
    &sPatternEditorMenuProfile,
    &sPatternSelectMenuProfile,
    &data_ov126_022999e0,
    &sStargazingMenuProfile,
    &sConstellationEditorMenuProfile,
    &sClockAdjustMenuProfile,
    &sTimeSelectMenuProfile,
    &sBirthdayMenuProfile,
    &sDateSelectMenuProfile,
    &sAmountEntryMenuProfile,
    &sBankMenuProfile,
    &sFriendCodeMenuProfile,
    &sDistantTownsMenuProfile,
    &sNearbyTownsMenuProfile,
    &sCatalogMenuProfile,
    &sMelodyMenuProfile,
    &sMusicMenuProfile,
    &sDonationMenuProfile,
    &sWfcFriendListMenuProfile,
    &sInsectManagerProfile,
    &sSnowballProfile,
    &sMuseumInsectRoomProfile,
    &sHouseRoachManagerProfile,
    &sHouseRoachProfile,
    &sFieldFishManagerProfile,
    &sFishDisplayProfile,
    &sMuseumAquariumProfile,
    &sFieldStructureMgrProfile,
    &sFurnitureManagerProfile,
    &sShopStockPlacerProfile,
    &sSaveManagerProfile,
    &sDummyProcC8Profile,
    &sMsgUiProcProfile,
    &sHudProcProfile,
    &sChatBalloonProcProfile,
    &sTransitionCommIconProfile,
    &sDummyProcCDProfile,
    &sTextSystemModuleProfile,
    &sBgmProcProfile,
    &sNpcSpawnerProfile,
    &sHandOverItemProfile,
    &data_020e1178,
    &sResidentSelectProfile,
    &sTitleScreenProfile,
    &sSaveMenuProfile,
    &sEventAnnouncerProfile,
    &data_020d9520,
};
