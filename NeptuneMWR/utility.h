#ifndef _UTILITY_H
#define _UTILITY_H

#define HTONS(n) (((((unsigned short)(n)&0xFF)) << 8) | (((unsigned short)(n)&0xFF00) >> 8))
#define IP(a, b, c, d) (((a) << 0) + ((b) << 8) + ((c) << 16) + ((d) << 24))

#define ZeroMemoy(dest) memset(&dest, 0, sizeof(dest))
#define ZeroRegion(dest, len) memset(&dest, 0, len)

void kLog(const char* fmt, ...);

#endif