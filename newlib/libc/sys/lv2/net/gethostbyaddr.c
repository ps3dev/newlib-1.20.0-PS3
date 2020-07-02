#include <netdb.h>
#include <net_init.h>
#include <sys/lv2errno.h>

struct hostent * gethostbyaddr(const char *addr, socklen_t len, int type)
{
    if(!LIBNET_INITIALZED)
    {
        errno = ENOSYS;
        return NULL;
    }
    return netErrno(netGetHostByAddr(addr, len, type));
}