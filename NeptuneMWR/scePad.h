#ifndef _SCEPAD_H
#define _SCEPAD_H

typedef uint32_t SceHandle;

class scePadData_s
{
private:
	ScePadData data;
	SceHandle handle;
	uint32_t curButton;
	uint32_t prevButton;
public:
	scePadData_s();
	~scePadData_s();

	SceHandle getControllerHandle() const;
	ScePadData getControllerData() const;

	bool isConnected() const;
	uint8_t connectedDeviceCount() const;

	void currentFrameData();

	bool isButtonDown(uint32_t button) const;
	bool isButtonPressed(uint32_t button) const;

	vec2_t analogLocation() const;
	vec2_t touchLocation(int currentTouchCount) const;

	void setControllerVibration(uint8_t speed);
	void setControllerLightColor(ScePadLightBarParam color);
};

extern scePadData_s* scePad;

#endif