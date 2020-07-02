#include <arpa/inet.h>
#include <net_init.h>
#include <sys/lv2errno.h>

char * inet_ntoa(struct in_addr in)
{
    if(!LIBNET_INITIALZED)
    {
        errno = ENOSYS;
        return NULL;
    }
    return netInetNtoa(in);
}