#include "stdafx.h"

void kLog(const char* fmt, ...)
{
	char buffer[0x400] = { 0 };

	va_list args;
	va_start(args, fmt);
	vsprintf(buffer, fmt, args);

	int sock = sceNetSocket("PS4 Output", AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in sockAddr = { 0 };
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = HTONS(9023);
	sockAddr.sin_addr.s_addr = IP(192, 168, 1, 216);

	sceNetConnect(sock, (struct SceNetSockaddr*)&sockAddr, sizeof(struct sockaddr_in));
	sceNetSend(sock, buffer, 0x400, 0);
	sceNetSocketClose(sock);
	va_end(args);
}