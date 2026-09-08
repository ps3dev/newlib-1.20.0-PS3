#ifndef __SYS_DIRENT_H__
#define __SYS_DIRENT_H__

#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>

/* d_type from sysLv2FsReadDir (syscall 806) / CellFsDirent:
   UNKNOWN=0, DIRECTORY=1, REGULAR=2, SYMLINK=3.
   Not CELL_FS_S_IF* from CellFsStat.mode.
   DT_BLK/CHR/FIFO/SOCK are unique sentinels so libstdc++'s
   get_file_type switch has no duplicate case labels; readdir never yields them. */
#define DT_INVALID			0xff
#define DT_UNKNOWN			0
#define DT_FIFO				0xf8
#define DT_CHR				0xf9
#define DT_DIR				1
#define DT_BLK				0xfa
#define DT_REG				2
#define DT_LNK				3
#define DT_SOCK				0xfb
#define DT_WHT				DT_INVALID

#define dirfd(dp)			((dp)->dd_fd)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _dirdesc
{
	int32_t	dd_fd;
	int32_t	dd_loc;
	int32_t	dd_size;
	void *dd_buf;
	size_t	dd_len;
	int32_t	dd_seek;
	int32_t	dd_rewind;
	int32_t	dd_flags;
} DIR;

struct dirent
{
	union {
		ino_t		d_ino;
		ino_t		d_fileno;
	};
	uint8_t		d_type;
	uint16_t	d_seekoff;
	uint16_t	d_reclen;
	uint16_t	d_namlen;
	char		d_name[MAXPATHLEN + 1];
};

int closedir(DIR *dirp);
DIR *opendir(const char *dirname);
struct dirent *readdir(DIR *dirp);
int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);
void rewinddir(DIR *dirp);
void seekdir(DIR *dirp, long int loc);
long int telldir(DIR *dirp);

#ifdef __cplusplus
}
#endif

#endif //__DIRENT_H__
