#include "stdafx.h"

Material* Material_RegisterHandle(const char* material)
{
	return DB_FindXAssetHeader(XAssetType::ASSET_TYPE_MATERIAL, material, false).material;
}

void* R_RenderFxFlags(int style)
{
	void* temp = (void*)0x1071FD8;

	if (style & 4)
		temp = (void*)0x1071FA0;
	if (style & 2)
		temp = (void*)0x1071FD8;
	if (style & 0x2000)
		temp = (void*)0x1072010;
	if (style & 0x10)
		temp = (void*)0x1072048;
	if (style & 8)
		temp = (void*)0x1072080;
	if (style & 0x400)
		temp = (void*)0x10720B8;
	if (style & 0x800)
		temp = (void*)0x10720F0;
	if (style & 0x1000)
		temp = (void*)0x1071F68;

	return temp;
}

void drawString(const std::string& text, float x, float y, float scale, std::vector<float> color, alignment al, const char* fontStr)
{
	color[0] = color[0] > 1.f ? color[0] / 255 : color[0];
	color[1] = color[1] > 1.f ? color[1] / 255 : color[1];
	color[2] = color[2] > 1.f ? color[2] / 255 : color[2];
	color[3] = color[3] > 1.f ? color[3] / 255 : color[3];

	auto font = R_RegisterFont(fontStr, 18, 0);
	float fontScale = (R_TextWidth(text.c_str(), text.size(), font) * scale);

	if (al == LEFT)
		x = x;

	if (al == CENTER)
		x = x - (fontScale / 2);

	if (al == RIGHT)
		x = x - fontScale;

	if (font)
		AddBaseDrawTextCmd(text.c_str(), text.size(), font, font->pixelHeight, x, y, scale, scale, 0, &color[0], 0, -1, 0, R_RenderFxFlags(0));
}

void drawRectangle(float x, float y, float w, float h, float rot, std::vector<float> color, Material* material)
{
	color[0] = color[0] > 1.f ? color[0] / 255.f : color[0];
	color[1] = color[1] > 1.f ? color[1] / 255.f : color[1];
	color[2] = color[2] > 1.f ? color[2] / 255.f : color[2];
	color[3] = color[3] > 1.f ? color[3] / 255.f : color[3];

	CG_DrawRotatedPicPhysical(scrPlace, x, y, w, h, rot, &color[0], material);
}

void iPrintln(const char* msg)
{
	SV_GameSendServerCommand(0, 0, (const char*)snprintf_s("%c \"%s\"", 102, msg));
}
void Cbuf_AddText(LocalClientNum_t localClientNum, const char* text) {
	int stringLength = strlen(text);
	strcpy((char*)(*(uint64_t*)0x2DBF390), text);
	*(char*)(*(uint64_t*)0x2DBF390 + stringLength + 1) = 0;
	*(int*)(0x2DBF390 + 0x0C) = stringLength + 1;
}
bool softL = false;
void softlands() {
	if (!softL) {
		iPrintln("^7Softlands: ^2Enabled");
		*(int8_t*)0x893D66 = 0x86;
		softL = true;
	}
	else if (softL) {
		*(int8_t*)0x893D66 = 0x87;
		softL = false;
		iPrintln("^7Softlands: ^1Disabled");
	}
}