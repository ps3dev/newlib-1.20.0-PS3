#include <arpa/inet.h>
#include <net_init.h>
#include <sys/lv2errno.h>

struct in_addr inet_makeaddr(in_addr_t net, in_addr_t lna)
{
    if(!LIBNET_INITIALZED)
    {
        errno = ENOSYS;
        struct in_addr in;
        in.s_addr = (in_addr_t) -1;
        return in;
    }
    return netInetMakeaddr(net, lna);
}