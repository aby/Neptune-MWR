#ifndef STRUCTS_H
#define STRUCTS_H


enum XAssetType
{
	ASSET_TYPE_PHYSPRESET,
	ASSET_TYPE_PHYS_COLLMAP,
	ASSET_TYPE_PHYSWATERPRESET,
	ASSET_TYPE_PHYS_WORLDMAP,
	ASSET_TYPE_PHYSCONSTRAINT,
	ASSET_TYPE_XANIM,
	ASSET_TYPE_XMODELSURFS,
	ASSET_TYPE_XMODEL,
	ASSET_TYPE_MATERIAL,
	ASSET_TYPE_COMPUTESHADER,
	ASSET_TYPE_VERTEXSHADER,
	ASSET_TYPE_DOMAINSHADER,
	ASSET_TYPE_PIXELSHADER,
	ASSET_TYPE_VERTEXDECL,
	ASSET_TYPE_TECHSET,
	ASSET_TYPE_IMAGE,
	ASSET_TYPE_SOUND,
	ASSET_TYPE_SOUNDSUBMIX,
	ASSET_TYPE_SNDCURVE,
	ASSET_TYPE_LPFCURVE,
	ASSET_TYPE_REVERBSENDCURVE,
	ASSET_TYPE_SNDCONTEXT,
	ASSET_TYPE_LOADED_SOUND,
	ASSET_TYPE_COL_MAP_SP,
	ASSET_TYPE_COM_MAP,
	ASSET_TYPE_GLASS_MAP,
	ASSET_TYPE_AIPATHS,
	ASSET_TYPE_VEHICLE_TRACK,
	ASSET_TYPE_MAP_ENTS,
	ASSET_TYPE_FX_MAP,
	ASSET_TYPE_GFX_MAP,
	ASSET_TYPE_LIGHTDEF,
	ASSET_TYPE_UI_MAP,
	ASSET_TYPE_MENUFILE,
	ASSET_TYPE_MENU,
	ASSET_TYPE_ANIMCLASS,
	ASSET_TYPE_LOCALIZE,
	ASSET_TYPE_ATTACHMENT,
	ASSET_TYPE_WEAPON,
	ASSET_TYPE_SNDDRIVERGLOBALS,
	ASSET_TYPE_FX,
	ASSET_TYPE_IMPACTFX,
	ASSET_TYPE_SURFACEFX,
	ASSET_TYPE_AITYPE,
	ASSET_TYPE_MPTYPE,
	ASSET_TYPE_CHARACTER,
	ASSET_TYPE_XMODELALIAS,
	ASSET_TYPE_RAWFILE,
	ASSET_TYPE_SCRIPTFILE,
	ASSET_TYPE_STRINGTABLE,
	ASSET_TYPE_LEADERBOARDDEF,
	ASSET_TYPE_VIRTUALLEADERBOARDDEF,
	ASSET_TYPE_STRUCTUREDDATADEF,
	ASSET_TYPE_DDL,
	ASSET_TYPE_PROTO,
	ASSET_TYPE_TRACER,
	ASSET_TYPE_VEHICLE,
	ASSET_TYPE_ADDON_MAP_ENTS,
	ASSET_TYPE_NETCONSTSTRINGS,
	ASSET_TYPE_REVERBPRESET,
	ASSET_TYPE_LUAFILE,
	ASSET_TYPE_SCRIPTABLE,
	ASSET_TYPE_EQUIPSNDTABLE,
	ASSET_TYPE_VECTORFIELD,
	ASSET_TYPE_DOPPLERPRESET,
	ASSET_TYPE_PARTICLESIMANIMATION,
	ASSET_TYPE_LASER,
	ASSET_TYPE_SKELETONSCRIPT,
	ASSET_TYPE_CLUT,
	ASSET_TYPE_TTF,
	ASSET_TYPE_COUNT,
};

struct ScreenPlacement
{
	float scaleVirtualToReal[2];
	float scaleVirtualToFull[2];
	float scaleRealToVirtual[2];
	float realViewportPosition[2];
	float realViewportSize[2];
	float virtualViewableMin[2];
	float virtualViewableMax[2];
	float realViewableMin[2];
	float realViewableMax[2];
	float virtualAdjustableMin[2];
	float virtualAdjustableMax[2];
	float realAdjustableMin[2];
	float realAdjustableMax[2];
	float subScreenLeft;
};

struct Material
{
	const char* name;
};

struct Font
{
	const char* name;
	int pixelHeight;
};

struct UiContext
{
	char pad_0000[32]; //0x0000
	int32_t scrWidth; //0x0020
	int32_t scrHeight; //0x0024
	char pad_0028[4]; //0x0028
	float FPS; //0x002C
};
enum LocalClientNum_t : int {
	INVALID_LOCAL_CLIENT = -1,
	LOCAL_CLIENT_0 = 0,
	LOCAL_CLIENT_FIRST = 0,
	LOCAL_CLIENT_1 = 1,
	LOCAL_CLIENT_2 = 2,
	LOCAL_CLIENT_3 = 3,
	LOCAL_CLIENT_COUNT = 5
};
union XAssetHeader
{
	Material* material;
	Font* font;
};

union Weapon {
	int data;
};
struct gclient_s { //0x5000
	char _pad0[0x02];		//0x00
	char mFlag0[4];			//0x02
	char _pad1[0x46];		//0x06
	int serverTime;			//0x4C
	char _pad2[0x0C];		//0x50
	int fofFlag;			//0x5C
	char _pad3[0x18];		//0x60
	float origin[3];		//0x78
	char _pad4[0x0C];		//0x84
	float deltaAngles[3];	//0x90
	char _pad5[0x90];		//0x9C
	float angles[3];		//0x12C
	char _pad6[0x250];		//0x138
	Weapon currentOffhand;	//0x388
	Weapon lethalWeapon;	//0x38C
	Weapon tacticalWeapon;	//0x390
	Weapon weapon;			//0x394
	char _pad7[0x4588];		//0x398
	char name0[0x20];		//0x4920
	char _pad8[0x42];		//0x4940
	char name1[0x20];		//0x4982
	char _pad9[0x62];		//0x49A2
	int team;				//0x4A04
	char _pad10[0x1F8];		//0x4A08
	int mflag;				//0x4C00
	char _pad11[0x3FC];		//0x4C04
	//usercmd_s *ucmd;		//0x4F9C //NOT UPDATED
	//usercmd_s *olducmd;	//0x4FE0 //NOT UPDATED
};
struct gentity_s
{
   //mwr:
   //0x3C viewmodel
	short number;			//0x00
	short type;				//0x02
	char _pad0[0x8C];		//0x04
	float angles[3];		//0x90
	char _pad1[0x9C];		//0x9C
	float origin[3];		//0x138
	char _pad2[0x14];		//0x144
	gclient_s* client;		//0x158
	char _pad3[0x28];		//0x160
	short modelIndex;		//0x188
	char _pad4[0x0A];		//0x18A
	int classname;			//0x194
	int script_classname;	//0x198
	int script_linkName;	//0x19C
	int target;				//0x1A0
	int targetname;			//0x1A4
	int u1;					//0x1A8
	int spawnflags;			//0x1AC
	char _pad5[0x20];		//0x1B0
	int health;				//0x1D0
	int maxHealth;			//0x1D4
	char _pad6[0x108];		//0x1D8
}; //Size: 0x02E0

#define cgDC ((UiContext*)(0x2DD80E0))
#define scrPlace ((ScreenPlacement*)(0x6ECBBB0))
#define g_entities ((gentity_s*)(0xBAFD3A0))

#endif