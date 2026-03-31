#include "stdafx.h"

scePadData_s* scePad;

struct PadDataHande_s
{
	char pad_0000[0x1C]; //0x0000
	uint32_t handle; //0x1C
};
PadDataHande_s* PadDataHande = (PadDataHande_s*)0xF5E1568; //Needs to be changed per-game 

scePadData_s::scePadData_s()
{
	this->handle = -1;
	this->curButton = 0;
	this->prevButton = 0;

	ZeroMemoy(this->data);
	
	this->handle = scePadGetHandle(PadDataHande->handle, SCE_PAD_PORT_TYPE_STANDARD, 0);
}

scePadData_s::~scePadData_s()
{
	this->handle = -1;
	this->curButton = 0;
	this->prevButton = 0;
	ZeroMemoy(this->data);
}

SceHandle scePadData_s::getControllerHandle() const
{
	return this->handle;
}

ScePadData scePadData_s::getControllerData() const
{
	return this->data;
}

bool scePadData_s::isConnected() const
{
	return this->data.connected;
}

uint8_t scePadData_s::connectedDeviceCount() const
{
	return this->data.connectedCount;
}

void scePadData_s::currentFrameData()
{
	scePadReadState(this->handle, &this->data);
	this->prevButton = this->curButton;
	this->curButton = this->data.buttons;
}

bool scePadData_s::isButtonDown(uint32_t button) const
{
	return (this->curButton & button) != 0;
}

bool scePadData_s::isButtonPressed(uint32_t button) const
{
	uint32_t pressed = this->curButton & ~this->prevButton;
	return (pressed & button) != 0;
}

vec2_t scePadData_s::analogLocation() const
{
	return vec2_t(this->data.analogButtons.l2 / 255.f, this->data.analogButtons.r2 / 255.f);
}

vec2_t scePadData_s::touchLocation(int currentTouchCount) const
{
	return vec2_t(this->data.touchData.touch[currentTouchCount].x, this->data.touchData.touch[currentTouchCount].y);
}

void scePadData_s::setControllerVibration(uint8_t speed)
{
	ScePadVibrationParam vib;

	vib.smallMotor = speed;
	vib.largeMotor = speed;

	scePadSetVibration(this->handle, &vib);
}

void scePadData_s::setControllerLightColor(ScePadLightBarParam color)
{
	scePadSetLightBar(this->handle, &color);
}
