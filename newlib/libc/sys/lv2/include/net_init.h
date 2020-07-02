#ifndef __LV2_NET_INIT_H__
#define __LV2_NET_INIT_H__

#include <net/net.h>

void * __netMemory;

#define LIBNET_MEMORY_SIZE			0x20000 // 128KB
#define LIBNET_INITIALZED	(__netMemory)

#ifdef __cplusplus
extern "C" {
#endif

int32_t netInitialize();
int32_t netDeinitialize();
int32_t netErrno(int ret);

#ifdef __cplusplus
	}
#endif

#endif