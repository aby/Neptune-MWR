#include "stdafx.h"

std::vector< Options* > Option;
std::vector<uint8_t> controllerColor = { 1,0,0,1 };

bool isMenuOpen;
int currentMenu, currentScroll = 1, maxOptions = 10;
int prevMenu, prevScroll;
bool firstopen; 
void backMenu() {
	if (currentMenu == HOME) {
		isMenuOpen = false;
	}
	if (currentMenu > HOME) {
		currentMenu = prevMenu;
		currentScroll = prevScroll;
		Option.clear();
	}
}

void updateCurrentMenu(int menu)
{
	prevMenu = currentMenu;
	prevScroll = currentScroll;

	currentMenu = menu;
	currentScroll = 1;
	Option.clear();
}


void buttonMonitoring() {

	scePad->currentFrameData();
	drawString(isMenuOpen ? "Scroll: \x14   \x15 | Select:  \x03" : "Press \x11 + \x15 to open Neptune", 25, 25, 1, { 255,255,255,255 }, LEFT);
	if (!isMenuOpen && (scePad->isButtonDown(SCE_PAD_BUTTON_DOWN) && scePad->isButtonDown(SCE_PAD_BUTTON_R3))) {
		sceKernelUsleep(5000);
		isMenuOpen = true;
	}

	if (!isMenuOpen)
		return;

	if (scePad->isButtonPressed(SCE_PAD_BUTTON_CIRCLE)) {
		backMenu();
	}

	if (scePad->isButtonPressed(SCE_PAD_BUTTON_SQUARE)) {
		Option[currentScroll]->callback();
	}

	if (scePad->isButtonPressed(SCE_PAD_BUTTON_UP)) {
		currentScroll--;
		if (currentScroll < 1)
			currentScroll = Option.size() - 1;
	}

	if (scePad->isButtonPressed(SCE_PAD_BUTTON_DOWN)) {
		currentScroll++;
		if (currentScroll > Option.size() - 1)
			currentScroll = 1;
	}
}

char keyBuffer[0x400];//will store what you type into the SceImeKeyboard 
void createMenu()
{
	if (Option.size() > 0)
		return;
	if (!firstopen) { currentScroll = 1, firstopen = true; }
	int optIndex = 0;
	Option.emplace_back(new Options("", optIndex++, []() {})); //Add in null opt for unlimited scrolling shit
	
	switch (currentMenu) {
		case HOME: {
			Option.emplace_back(new Options("Game Settings", optIndex++, []() { updateCurrentMenu(GAMESETTINGS); }));
			Option.emplace_back(new Options("Bot Menu", optIndex++, []() { updateCurrentMenu(BOTMENU); }));
			Option.emplace_back(new Options("LOCAL/LAN Menu", optIndex++, []() { updateCurrentMenu(LANMENU); }));
			Option.emplace_back(new Options("Sub Menu", optIndex++, []() { updateCurrentMenu(MENU1); }));
			Option.emplace_back(new Options("Sub Menu", optIndex++, []() { updateCurrentMenu(MENU1); }));
			Option.emplace_back(new Options("Sub Menu", optIndex++, []() { updateCurrentMenu(MENU1); }));
			Option.emplace_back(new Options("Sub Menu", optIndex++, []() { updateCurrentMenu(MENU1); }));
			Option.emplace_back(new Options("Sub Menu", optIndex++, []() { updateCurrentMenu(MENU1); }));
			Option.emplace_back(new Options("Sub Menu", optIndex++, []() { updateCurrentMenu(MENU1); }));
			Option.emplace_back(new Options("Sub Menu", optIndex++, []() { updateCurrentMenu(MENU1); }));
			Option.emplace_back(new Options("Sub Menu", optIndex++, []() { updateCurrentMenu(MENU1); }));
			Option.emplace_back(new Options("Credits", optIndex++, []() { updateCurrentMenu(CREDITS); }));
		} break;
		case MENU1: {
			Option.emplace_back(new Options("ScePad LightBar Red", optIndex++, []() { scePad->setControllerLightColor({ controllerColor[0], controllerColor[1], controllerColor[2] }); }));
			Option.emplace_back(new Options("SceNotify Test", optIndex++, []() {}));
			Option.emplace_back(new Options("SceMessageDialog Test", optIndex++, []() {}));
			Option.emplace_back(new Options("SceImeKeyboard Test", optIndex++, []() {}));
		} break;
		case GAMESETTINGS: {
			Option.emplace_back(new Options("Soft Lands", optIndex++, []() { softlands(); }));
		} break;
		case BOTMENU: {
			Option.emplace_back(new Options("Teleport to Self", optIndex++, []() { iPrintln("Do a ting here 3"); }));
			Option.emplace_back(new Options("Freeze All Bots", optIndex++, []() { iPrintln("Do a ting here 3"); }));
			Option.emplace_back(new Options("Unfreeze All Bots", optIndex++, []() { iPrintln("Do a ting here 3"); }));
			Option.emplace_back(new Options("Bots Crouch", optIndex++, []() { iPrintln("Do a ting here 3"); }));
			Option.emplace_back(new Options("Bots Prone", optIndex++, []() { iPrintln("Do a ting here 3"); }));
		} break;
		case LANMENU: {
			Option.emplace_back(new Options("Name Changer", optIndex++, []() { iPrintln("Do a ting here 1"); }));
			Option.emplace_back(new Options("Unlock Emblems/Calling Cards", optIndex++, []() { iPrintln("Do a ting here 2"); }));
			Option.emplace_back(new Options("Unlock Character Patch", optIndex++, []() { iPrintln("Do a ting here 3"); }));
			Option.emplace_back(new Options("Unlock Weapon Sticker", optIndex++, []() { iPrintln("Do a ting here 3"); }));
			Option.emplace_back(new Options("Unlock DLC Items(^1Requires DLC Installed^7)", optIndex++, []() { iPrintln("Do a ting here 3"); }));
		} break;
		case CREDITS: {
			Option.emplace_back(new Options("^3shield", optIndex++, []() { iPrintln("^6twitter.com/shieldlol"); }));
		} break;
		case MENU6: {
			for (int i = 0; i < 2; i++)//Every menu has unlimited scrolling this just so i dont have to make a bunch of options by hand
				Option.emplace_back(new Options("Option", optIndex++, []() { iPrintln("ting"); }));
		} break;
	}

}

void renderMenu()
{
	();

	auto font = R_RegisterFont("fonts/default.otf", 18, 0);

	drawRectangle((cgDC->scrWidth / 2) - 200, 100, 400, 60, 0, { 63, 91, 239, 255 });
	drawRectangle((cgDC->scrWidth / 2) - 200, 160, 400, 4 + ((maxOptions) * (font->pixelHeight * 1.2)), 0, { 0,0,0,55 }); //Menu_PaintAll kinda like mw2 where alpha is weird needs to be really low
	drawRectangle((cgDC->scrWidth / 2) - 200, 164 + ((maxOptions) * (font->pixelHeight * 1.2)), 400, (font->pixelHeight * 1.2), 0, { 63, 91, 239, 55 });

	drawString("Neptune", (cgDC->scrWidth / 2), 150, 2, { 255,255,255,255 }, CENTER);
	drawString("by shield", (cgDC->scrWidth / 2) - 195, 182 + ((maxOptions) * (font->pixelHeight * 1.2)), .85f, { 1,1,1,1 });
	drawString(va("%d/%d", currentScroll, Option.size() - 1), (cgDC->scrWidth / 2) + 195, 182 + ((maxOptions) * (font->pixelHeight * 1.2)), .85f, { 1,1,1,1 }, RIGHT);

	for (auto opt : Option) {
		if (currentScroll <= maxOptions && opt->optIndex <= maxOptions) {
			if (currentScroll == opt->optIndex)
				drawRectangle((cgDC->scrWidth / 2) - 200, 144 + (opt->optIndex * (font->pixelHeight * 1.2)), 400, (font->pixelHeight * 1), 0, { 63, 91, 239, 55 });
			drawString(opt->text, (cgDC->scrWidth / 2), 164 + (opt->optIndex * (font->pixelHeight * 1.2)), 1, { 1,1,1,1 }, CENTER);
		}
		else if ((opt->optIndex > (currentScroll - maxOptions)) && opt->optIndex <= currentScroll) {
			if (currentScroll == opt->optIndex)
				drawRectangle((cgDC->scrWidth / 2) - 200, 144 + (((opt->optIndex - (currentScroll - maxOptions))) * (font->pixelHeight * 1.2)), 400, (font->pixelHeight * 1), 0, { 63, 91, 239, 55 });
			drawString(opt->text, (cgDC->scrWidth / 2), 164 + (((opt->optIndex - (currentScroll - maxOptions))) * (font->pixelHeight * 1.2)), 1, { 1,1,1,1 }, CENTER);
		}
	}
}