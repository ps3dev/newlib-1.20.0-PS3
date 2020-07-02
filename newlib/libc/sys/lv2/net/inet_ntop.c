#include <arpa/inet.h>
#include <net_init.h>
#include <sys/lv2errno.h>

const char * inet_ntop(int af, const void* src, char* dst, socklen_t size)
{
    if(!LIBNET_INITIALZED)
    {
        errno = ENOSYS;
        return (in_addr_t) -1;
    }
    switch(af)
    {
        case AF_INET:
            return netInetNtop(af, src, dst, size);
        case AF_INET6:
            /* TODO: Implement support for IPV6 */
            errno = EAFNOSUPPORT;
            return NULL;
        default:
            errno = EAFNOSUPPORT;
            return NULL;
    }
}