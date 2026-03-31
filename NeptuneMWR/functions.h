#ifndef FUNCTIONS_H
#define FUNCTIONS_H

enum alignment
{
	LEFT,
	CENTER,
	RIGHT
};
extern bool softL;

Material* Material_RegisterHandle(const char* material);
void* R_RenderFxFlags(int style);

void drawString(const std::string& text, float x, float y, float scale, std::vector<float> color, alignment al = LEFT, const char* fontStr = "fonts/default.otf");
void drawRectangle(float x, float y, float w, float h, float rot, std::vector<float> color, Material* material = Material_RegisterHandle("white"));
void iPrintln(const char* msg);

template<typename T>
void colorCycle(std::vector<T>& rain)
{
	if (rain[3] <= 0) rain[3] = 0;
	if (rain[0] <= 0 && rain[1] <= 0 && rain[2] <= 0)
		rain[0] = 255;
	if (rain[0] > 0 && rain[2] <= 63)
	{
		rain[0] -= 2;
		rain[1] += 2;
		rain[3] = rain[3];
	}
	if (rain[1] > 0 && rain[0] <= 63)
	{
		rain[1] -= 2;
		rain[2] += 2;
		rain[3] = rain[3];
	}
	if (rain[2] > 0 && rain[1] <= 63)
	{
		rain[0] += 2;
		rain[2] -= 2;
		rain[3] = rain[3];
	}
}
void Cbuf_AddText(LocalClientNum_t localClientNum, const char* text);

void softlands();
#endif