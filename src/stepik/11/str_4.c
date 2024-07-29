#include <assert.h>
#include <stdio.h>
#include <string.h>
char * my_strcat (char *dest, const char *src);

int main(){
  char *src = strdup("lo");
  char *dst = strdup("hel");

  char* new_str = my_strcat(dst, src);

  assert(new_str != strcat(dst, src));
}

char * my_strcat (char *dest, const char *src){
  stpcpy(dest + strlen(dest), src);
  return dest;
}