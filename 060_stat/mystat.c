#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

//This function is abstrated out from step1
//select file type in step1
const char * output_type(struct stat sb) {
  const char * type;
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      type = "block special file";
      break;
    case S_IFCHR:
      type = "character special file";
      break;
    case S_IFDIR:
      type = "directory";
      break;
    case S_IFIFO:
      type = "fifo";
      break;
    case S_IFLNK:
      type = "symbolic link";
      break;
    case S_IFREG:
      type = "regular file";
      break;
    case S_IFSOCK:
      type = "socket";
      break;
    default:
      type = "unknown?";
      break;
  }
  return type;
}

//This function is abstrated out from step2
//select first character in step2
char output_first(struct stat sb) {
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      return 'b';
    case S_IFCHR:
      return 'c';
    case S_IFDIR:
      return 'd';
    case S_IFIFO:
      return 'p';
    case S_IFLNK:
      return 'l';
    case S_IFREG:
      return '-';
    case S_IFSOCK:
      return 's';
    default:
      return ' ';
  }
}

int main(int argc, char * argv[]) {
  struct stat sb[argc];

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; i++) {
    if (lstat(argv[i], &sb[i]) == -1) {
      perror("lstat");
      exit(EXIT_FAILURE);
    }
  }

  //Using the for loop to take any number of command line arguments
  for (int j = 1; j < argc; j++) {
    //Use type to store the string of file type
    const char * type;
    type = output_type(sb[j]);

    //step1
    //print the first three lines that "stat" would print
    //print the first line
    char linktarget[256];
    ssize_t len = readlink(argv[j], linktarget, 256);
    linktarget[len] = '\0';
    if (S_ISLNK(sb[j].st_mode)) {
      printf("  File: %s -> %s\n", argv[j], linktarget);
    }
    else {
      printf("  File: %s\n", argv[j]);
    }

    //print the second line
    printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
           (unsigned long)sb[j].st_size,
           (unsigned long)sb[j].st_blocks,
           (unsigned long)sb[j].st_blksize,
           type);

    //print the third line
    if ((S_ISCHR(sb[j].st_mode)) || (S_ISBLK(sb[j].st_mode))) {
      printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
             sb[j].st_dev,
             sb[j].st_dev,
             (unsigned long)sb[j].st_ino,
             (unsigned long)sb[j].st_nlink,
             major(sb[j].st_rdev),
             minor(sb[j].st_rdev));
    }
    else {
      printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
             sb[j].st_dev,
             sb[j].st_dev,
             (unsigned long)sb[j].st_ino,
             (unsigned long)sb[j].st_nlink);
    }

    //step2
    //add part of the fourth line
    //calculate the output of the second percent sign
    char permission[11];
    permission[0] = output_first(sb[j]);
    if ((sb[j].st_mode & S_IRUSR) != 0) {
      permission[1] = 'r';
    }
    else {
      permission[1] = '-';
    }

    if ((sb[j].st_mode & S_IWUSR) != 0) {
      permission[2] = 'w';
    }
    else {
      permission[2] = '-';
    }

    if ((sb[j].st_mode & S_IXUSR) != 0) {
      permission[3] = 'x';
    }
    else {
      permission[3] = '-';
    }

    if ((sb[j].st_mode & S_IRGRP) != 0) {
      permission[4] = 'r';
    }
    else {
      permission[4] = '-';
    }

    if ((sb[j].st_mode & S_IWGRP) != 0) {
      permission[5] = 'w';
    }
    else {
      permission[5] = '-';
    }

    if ((sb[j].st_mode & S_IXGRP) != 0) {
      permission[6] = 'x';
    }
    else {
      permission[6] = '-';
    }

    if ((sb[j].st_mode & S_IROTH) != 0) {
      permission[7] = 'r';
    }
    else {
      permission[7] = '-';
    }

    if ((sb[j].st_mode & S_IWOTH) != 0) {
      permission[8] = 'w';
    }
    else {
      permission[8] = '-';
    }

    if ((sb[j].st_mode & S_IXOTH) != 0) {
      permission[9] = 'x';
    }
    else {
      permission[9] = '-';
    }
    permission[10] = '\0';
    //step3
    //get username
    struct passwd * name = getpwuid(sb[j].st_uid);
    //get group name
    struct group * groupname = getgrgid(sb[j].st_gid);

    //print the fourth line
    printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
           sb[j].st_mode & ~S_IFMT,
           permission,
           sb[j].st_uid,
           name->pw_name,
           sb[j].st_gid,
           groupname->gr_name);

    //step4
    //print access time
    char * timestr = time2str(&sb[j].st_atime, sb[j].st_atim.tv_nsec);
    printf("Access: %s\n", timestr);
    free(timestr);

    //print Modify time
    timestr = time2str(&sb[j].st_mtime, sb[j].st_mtim.tv_nsec);
    printf("Modify: %s\n", timestr);
    free(timestr);

    //print Change time
    timestr = time2str(&sb[j].st_ctime, sb[j].st_ctim.tv_nsec);
    printf("Change: %s\n", timestr);
    free(timestr);

    printf(" Birth: -\n");
  }

  exit(EXIT_SUCCESS);
}
