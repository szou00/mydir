#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {

  DIR *direct = opendir(".");
  struct dirent *d;
  long size;

  struct stat *buf;
  buf = malloc(sizeof(struct stat));

  if (direct == NULL) {
    printf("Could not open current directory" );
    return 0;
  }

  printf("Statistics for directory: .\n");

  //size
  while ((d = readdir(direct)) != NULL) {
    stat(d->d_name, buf);
    size += buf->st_size;
  }
  printf("Total Directory Size: %ld Bytes\n", size);

  char buffer[50];
  sprintf(buffer, "File size: %ld KB\n", size);
  if (size >= 1024) {
    size = size/ 1024;
    sprintf(buffer, "File size: %ld MB\n", size);
  }
  if (size >= 1024) {
    size = size / 1024;
    sprintf(buffer, "File size: %ld GB\n", size);
  }
  printf("%s", buffer);

  //printing directories
  direct = opendir(".");
  printf("Directories: \n");
  while ((d = readdir(direct)) != NULL) {
    if (d->d_type == 4) {
      printf("\t%s\n", d->d_name);
    }
  }

  //printing reg files
  direct = opendir(".");
  printf("Regular Files: \n");
  while ((d = readdir(direct)) != NULL) {
    if (d->d_type == 8) {
      printf("\t%s\n", d->d_name);
    }
  }

  closedir(direct);
  return 0;


}
