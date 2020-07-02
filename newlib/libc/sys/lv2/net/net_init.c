#include <net_init.h>

#ifndef __LINUX_ERRNO_EXTENSIONS__
#define __LINUX_ERRNO_EXTENSIONS__
#endif

#include <errno.h>
#include <string.h>
#include <sysmodule/sysmodule.h>
#include <sys/lv2errno.h>

extern void *__netMemory = NULL;

int32_t netInitialize()
{
	if(__netMemory) return 0;

	int32_t ret;
	struct netInitParam params;
	
	ret = sysModuleLoad(SYSMODULE_NET);
	if(ret<0) return lv2errno(ret);

	memset(&params, 0, sizeof(struct netInitParam));
	__netMemory = malloc(LIBNET_MEMORY_SIZE);
	
	params.memory = (u32)((u64)__netMemory);
	params.memory_size = LIBNET_MEMORY_SIZE;
	params.flags = 0;
	ret = netInitializeNetworkEx(&params);
	if(ret) {
		free(__netMemory);
		__netMemory = NULL;
	}
	return ret;
}

int32_t netDeinitialize()
{
	netFinalizeNetwork();

	if(__netMemory) free(__netMemory);
	__netMemory = NULL;

	sysModuleUnload(SYSMODULE_NET);
	return 0;
}

const static int neterrno2errno[] = {
	[NET_EPERM]				= EPERM,
	[NET_ENOENT]			= ENOENT,
	[NET_ESRCH]				= ESRCH,
	[NET_EINTR]				= EINTR,
	[NET_EIO]				= EIO,
	[NET_ENXIO]				= ENXIO,
	[NET_E2BIG]				= E2BIG,
	[NET_ENOEXEC]			= ENOEXEC,
	[NET_EBADF]				= EBADF,
	[NET_ECHILD]			= ECHILD,
	[NET_EDEADLK]			= EDEADLK,
	[NET_ENOMEM]			= ENOMEM,
	[NET_EACCES]			= EACCES,
	[NET_EFAULT]			= EFAULT,
	[NET_ENOTBLK]			= ENOTBLK,
	[NET_EBUSY]				= EBUSY,
	[NET_EEXIST]			= EEXIST,
	[NET_EXDEV]				= EXDEV,
	[NET_ENODEV]			= ENODEV,
	[NET_ENOTDIR]			= ENOTDIR,
	[NET_EISDIR]			= EISDIR,
	[NET_EINVAL]			= EINVAL,
	[NET_ENFILE]			= ENFILE,
	[NET_EMFILE]			= EMFILE,
	[NET_ENOTTY]			= ENOTTY,
	[NET_ETXTBSY]			= ETXTBSY,
	[NET_EFBIG]				= EFBIG,
	[NET_ENOSPC]			= ENOSPC,
	[NET_ESPIPE]			= ESPIPE,
	[NET_EROFS]				= EROFS,
	[NET_EMLINK]			= EMLINK,
	[NET_EPIPE]				= EPIPE,
	[NET_EDOM]				= EDOM,
	[NET_ERANGE]			= ERANGE,
	[NET_EAGAIN]			= EAGAIN,
	[NET_EWOULDBLOCK]		= EWOULDBLOCK,
	[NET_EINPROGRESS]		= EINPROGRESS,
	[NET_EALREADY]			= EALREADY,
	[NET_ENOTSOCK]			= ENOTSOCK,
	[NET_EDESTADDRREQ]		= EDESTADDRREQ,
	[NET_EMSGSIZE]			= EMSGSIZE,
	[NET_EPROTOTYPE]		= EPROTOTYPE,
	[NET_ENOPROTOOPT]		= ENOPROTOOPT,
	[NET_EPROTONOSUPPORT]	= EPROTONOSUPPORT,
	[NET_ESOCKTNOSUPPORT]	= ESOCKTNOSUPPORT,
	[NET_EOPNOTSUPP]		= EOPNOTSUPP,
	[NET_EPFNOSUPPORT]		= EPFNOSUPPORT,
	[NET_EAFNOSUPPORT]		= EAFNOSUPPORT,
	[NET_EADDRINUSE]		= EADDRINUSE,
	[NET_EADDRNOTAVAIL]		= EADDRNOTAVAIL,
	[NET_ENETDOWN]			= ENETDOWN,
	[NET_ENETUNREACH]		= ENETUNREACH,
	[NET_ENETRESET]			= ENETRESET,
	[NET_ECONNABORTED]		= ECONNABORTED,
	[NET_ECONNRESET]		= ECONNRESET,
	[NET_ENOBUFS]			= ENOBUFS,
	[NET_EISCONN]			= EISCONN,
	[NET_ENOTCONN]			= ENOTCONN,
	[NET_ESHUTDOWN]			= ESHUTDOWN,
	[NET_ETOOMANYREFS]		= ETOOMANYREFS,
	[NET_ETIMEDOUT]			= ETIMEDOUT,
	[NET_ECONNREFUSED]		= ECONNREFUSED,
	[NET_ELOOP]				= ELOOP,
	[NET_ENAMETOOLONG]		= ENAMETOOLONG,
	[NET_EHOSTDOWN]			= EHOSTDOWN,
	[NET_EHOSTUNREACH]		= EHOSTUNREACH,
	[NET_ENOTEMPTY]			= ENOTEMPTY,
	[NET_EPROCLIM]			= EPROCLIM,
	[NET_EUSERS]			= EUSERS,
	[NET_EDQUOT]			= EDQUOT,
	[NET_ESTALE]			= ESTALE,
	[NET_EREMOTE]			= EREMOTE,
	[NET_EBADRPC]			= ENOTSUP, // no match
	[NET_ERPCMISMATCH]		= ENOTSUP, // no match
	[NET_EPROGUNAVAIL]		= ENOTSUP, // no match
	[NET_EPROGMISMATCH]		= ENOTSUP, // no match
	[NET_EPROCUNAVAIL]		= ENOTSUP, // no match
	[NET_ENOLCK]			= ENOLCK,
	[NET_ENOSYS]			= ENOSYS,
	[NET_EFTYPE]			= EFTYPE,
	[NET_EAUTH]				= EPERM, // no match
	[NET_ENEEDAUTH]			= EPERM, // no match
	[NET_EIDRM]				= EIDRM,
	[NET_ENOMSG]			= ENOMSG,
	[NET_EOVERFLOW]			= EOVERFLOW,
	[NET_EILSEQ]			= EILSEQ,
	[NET_ENOTSUP]			= ENOTSUP,
	[NET_ECANCELED]			= ECANCELED,
	[NET_EBADMSG]			= EBADMSG,
	[NET_ENODATA]			= ENODATA,
	[NET_ENOSR]				= ENOSR,
	[NET_ENOSTR]			= ENOSTR,
	[NET_ETIME]				= ETIME
};

int32_t netErrno(int ret)
{
	if(ret>=0) return ret;

	if(net_errno<(sizeof(neterrno2errno)/sizeof(neterrno2errno[0])))
		errno = neterrno2errno[net_errno] ?: ENOTSUP;
	else
		errno = ENOTSUP;

	return -1;
}