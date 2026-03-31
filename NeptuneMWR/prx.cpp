
#include "stdafx.h"
#include "structs.h"
#include "detour.h"
 
int(*sceKernelDebugOutText)(int dbg_channel, const char* text);

//void kprintf(const char* fmt, ...)
//{
//	if (sceKernelDebugOutText)
//	{
//		char buffer[0x400] = { 0 };
//		va_list args;
//		va_start(args, fmt);
//		vsprintf(buffer, fmt, args);
//		va_end(args);
//
//
//
//		sceKernelDebugOutText(0, va("[%s] %s", PROJECT_NAME, buffer));
//	}
//
//}


typedef void(*Menu_PaintAll_t)(uint64_t a, uint64_t b);
Menu_PaintAll_t Menu_PaintAll = Menu_PaintAll_t(0x682D10);
detour* Menu_PaintAll_d;
void Menu_PaintAll_f(uint64_t a, uint64_t b) {

	colorCycle<uint8_t>(controllerColor);
	scePad->setControllerLightColor({ controllerColor[0], controllerColor[1], controllerColor[2]});

	buttonMonitoring();
	if (isMenuOpen)
		renderMenu();
	

	Menu_PaintAll_d->invoke(a, b);
	//Menu_PaintAll(a, b);
}

detour* GPad_UpdateAllInternal_d;
void GPad_UpdateAllInternal_f() //Lock buttons for game when menu is open
{
	if (!isMenuOpen)
		GPad_UpdateAllInternal_d->invoke();
}

SceKernelModule handle;
extern "C" {
	int module_start(size_t args, const void* argp) {

		scePad = new scePadData_s();

		Menu_PaintAll_d = new detour(0x682D10, Menu_PaintAll_f);
		GPad_UpdateAllInternal_d = new detour(0xB86300, GPad_UpdateAllInternal_f);

		//SceKernelModule handle = sceKernelLoadStartModule("libkernel.sprx", 0, NULL, 0, 0, 0);
		//sceKernelDlsym(handle, "sceKernelDebugOutText", (void**)&sceKernelDebugOutText);

		return SCE_OK;
	}
	int module_stop(size_t args, const void* argp) {

		delete scePad;
		delete Menu_PaintAll_d;
		delete GPad_UpdateAllInternal_d;

		return SCE_OK;
	}
}