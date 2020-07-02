#include <net_init.h>
#include <poll.h>
#include <sys/lv2errno.h>

int poll(struct pollfd fds[], nfds_t nfds, int timeout)
{
    if(!LIBNET_INITIALZED)
    {
        errno = ENOSYS;
        return -1;
    }
    return netErrno(netPoll(fds, nfds, timeout));
}