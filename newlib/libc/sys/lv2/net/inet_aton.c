#include <arpa/inet.h>
#include <net_init.h>
#include <sys/lv2errno.h>

int inet_aton(const char* cp, struct in_addr* inp)
{
    if(!LIBNET_INITIALZED)
    {
        errno = ENOSYS;
        return -1;
    }
    return netErrno(netInetAton(cp, inp));
}