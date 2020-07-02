#include <arpa/inet.h>
#include <net_init.h>
#include <sys/lv2errno.h>

in_addr_t inet_network(const char* cp)
{
    if(!LIBNET_INITIALZED)
    {
        errno = ENOSYS;
        return (in_addr_t) -1;
    }
    return (in_addr_t) netErrno(netInetNetwork(cp));
}