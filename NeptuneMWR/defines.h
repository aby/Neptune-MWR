#ifndef DEFINES_H
#define DEFINES_H

typedef XAssetHeader(*DB_FindXAssetHeader_t)(XAssetType type, const char* name, bool err);
typedef void(*AddBaseDrawTextCmd_t)(char const*, int, Font*, int, float, float, float, float, float, float const*, int, int, char, void*);
typedef Font* (*R_RegisterFont_t)(const char* fontName, int fontSize, int img);
typedef void(*CG_DrawRotatedPicPhysical_t)(ScreenPlacement const*, float, float, float, float, float, float const*, Material*);
typedef int(*R_TextWidth_t)(const char* text, int charSize, Font* font);
typedef void(*SV_GameSendServerCommand_t)(int ent, int type, char const* cmd);

extern DB_FindXAssetHeader_t DB_FindXAssetHeader;
extern AddBaseDrawTextCmd_t AddBaseDrawTextCmd;
extern R_RegisterFont_t R_RegisterFont;
extern CG_DrawRotatedPicPhysical_t CG_DrawRotatedPicPhysical;
extern R_TextWidth_t R_TextWidth;
extern SV_GameSendServerCommand_t SV_GameSendServerCommand;








#endif