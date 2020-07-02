#include <netdb.h>
#include <net_init.h>
#include <sys/lv2errno.h>

struct hostent * gethostbyname(const char *name)
{
    if(!LIBNET_INITIALZED)
    {
        errno = ENOSYS;
        return NULL;
    }
    return netErrno(netGetHostByName(name));
}