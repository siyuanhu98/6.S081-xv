#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if(argc != 1) {
    fprintf(2, "usage: uptime\n");
    exit(0);
  }
  char *str[];
  str[] = uptime();
  printf(str);
  exit(0);
}
