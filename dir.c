#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {

  //initialization
  DIR *direct;
  struct dirent *d;
  long size;

  struct stat *buf;
  buf = malloc(sizeof(struct stat));

  char *file = malloc(50);

  //if there is a commnd line argument
  if (argc>1) {
    file = argv[1];
  }
  //no command line argument. asks user for a directory to scan
  else {
    printf("Please enter a directory name: ");
    fgets(file, 50, stdin);
    *(strchr(file, '\n')) = '\0'; //get rid of ending
    printf("\n");
  }

  // printf("int: %d\n", argc);
  // printf("directory name: %s\n", argv[1]);
  // printf("directory: %s\n", file);
  direct = opendir(file);

  //check for error
  if (errno || direct == NULL) {
    printf("Error: %s. Could not open directory. \n", strerror(errno));
    return 0;
  }

  printf("Statistics for directory: %s\n", file);

  //size
  while ((d = readdir(direct)) != NULL) {
    stat(d->d_name, buf);
    size += buf->st_size;
  }
  printf("\nTotal Directory Size: %ld Bytes\n\n", size);
  printf("(Size below considers 1 MB = 1024 Bytes, 1 GB = 1024 MB)\n\n");

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
  printf("%s\n", buffer);

  //printing directories
  direct = opendir(file);
  printf("Directories: \n");
  while ((d = readdir(direct)) != NULL) {
    if (d->d_type == 4) {
      printf("\t%s\n", d->d_name);
    }
  }

  //printing reg files
  direct = opendir(file);
  printf("Regular Files: \n");
  while ((d = readdir(direct)) != NULL) {
    if (d->d_type == 8) {
      printf("\t%s\n", d->d_name);
    }
  }

  closedir(direct);
  return 0;


}
