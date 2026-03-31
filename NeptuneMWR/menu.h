#ifndef MENU_H
#define MENU_H

enum menuIds
{
	HOME,

	MENU1,
	GAMESETTINGS,
	MENU2,
	BOTMENU,
	LANMENU,
	CREDITS,
	MENU6,

	COUNT
};

struct Options
{
	int optIndex;
	const char* text;

	std::function<void()> callback;

	Options(const char* text, int optIndex, std::function<void()> callback) : text(text), optIndex(optIndex), callback(callback) {};

};

extern std::vector<uint8_t> controllerColor;
extern bool isMenuOpen;
extern bool firstopen;
void buttonMonitoring();
void renderMenu();

#endif