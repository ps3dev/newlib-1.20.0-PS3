#include <arpa/inet.h>
#include <net_init.h>
#include <sys/lv2errno.h>

int inet_pton(int af, const char* src, void* dst)
{
    if(!LIBNET_INITIALZED)
    {
        errno = ENOSYS;
        return -1;
    }
    switch(af)
    {
        case AF_INET:
            return netErrno(netInetPton(af, src, dst));
        case AF_INET6:
            /* TODO: Implement support for IPV6 */
            errno = EAFNOSUPPORT;
            return NULL;
        default:
            errno = EAFNOSUPPORT;
            return NULL;
    }
}