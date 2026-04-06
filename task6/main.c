#include "main.h"


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Use %s <file_path>\n", argv[0]);
        return 1;
    }

    struct stat stats;

    if (stat(argv[1], &stats) == 0)
        output_properties(argv, stats);
    else
    {
        fprintf(stderr, "Error in stat()! Check file existance");
        return 1;
    }

    return 0;
}

void output_properties(char *argv[], struct stat stats)
{
    int width = 6;


    // File name
    printf("%*s: %s\n", width, "File", argv[1]);


    // Size
    printf("%*s: %lld\t", width, "Size", (long long)stats.st_size);
    printf("\tBlocks: %lld", (long long)stats.st_blocks);
    printf(
        "\tIO Block: %ld\t%s", (long)stats.st_blksize, file_type(stats.st_mode)
        );
    printf("\n");


    // Location
    printf(
        "%*s: %lxh/%lud", width, "Device",
        (unsigned long)stats.st_dev, (unsigned long)stats.st_dev
        );
    printf("\tInode: %lld", (long long)stats.st_ino);
    printf("\tLinks: %lld", (long long)stats.st_nlink);
    printf("\n");


    // File's permissions
    char perms[11];
    struct passwd *pw = getpwuid(stats.st_uid);
    struct group *gr = getgrgid(stats.st_gid);
    mode_to_letters(stats.st_mode, perms);
    printf("%*s: (%04o/%s)", width, "Access",
        stats.st_mode & 07777, perms);
    printf("\tUid: ( %d / %s)",
        stats.st_uid, pw ? pw->pw_name : "unknown"
        );
    printf("\tGid: ( %d / %s)",
        stats.st_gid, gr ? gr->gr_name : "unknown");
    printf("\n");


    struct tm dt;
    // File's modification time
    dt = *(gmtime(&stats.st_mtime));
    printf
    (
        "%*s:\t%04d-%02d-%02d\t%02d:%02d:%02d\n", width, "Modify",
        dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday,
        dt.tm_hour, dt.tm_min, dt.tm_sec
        );


    // File's creation time
    dt = *(gmtime(&stats.st_ctime));
    printf
    (
        "%*s:\t%04d-%02d-%02d\t%02d:%02d:%02d\n", width, "Birth",
        dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday,
        dt.tm_hour, dt.tm_min, dt.tm_sec
        );
}

const char *file_type(mode_t mode)
{
    if (S_ISREG(mode)) return "regular file";
    if (S_ISDIR(mode)) return "directory";
    if (S_ISLNK(mode)) return "symbolic link";
    if (S_ISCHR(mode)) return "character device";
    if (S_ISBLK(mode)) return "block device";
    if (S_ISSOCK(mode)) return "socket";
    if (S_ISFIFO(mode)) return "fifo";

    return "unknown";
}

void mode_to_letters(mode_t mode, char *str)
{
    str[0] =    S_ISDIR(mode)   ? 'd' :
                S_ISLNK(mode)   ? 'l' :
                S_ISCHR(mode)   ? 'c' :
                S_ISBLK(mode)   ? 'b' :
                S_ISFIFO(mode)  ? 'p' :
                S_ISSOCK(mode)  ? 's' : '-';

    str[1] = (mode & S_IRUSR)   ? 'r' : '-';
    str[2] = (mode & S_IWUSR)   ? 'w' : '-';
    str[3] = (mode & S_IXUSR)   ? 'x' : '-';

    str[4] = (mode & S_IRGRP)   ? 'r' : '-';
    str[5] = (mode & S_IWGRP)   ? 'w' : '-';
    str[6] = (mode & S_IXGRP)   ? 'x' : '-';

    str[7] = (mode & S_IROTH)   ? 'r' : '-';
    str[8] = (mode & S_IWOTH)   ? 'w' : '-';
    str[9] = (mode & S_IXOTH)   ? 'x' : '-';

    str[10] = '\0';
}
