#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
bool varyLast(char *ptr, char *lsb, char *letters, int len,char *hash);
/* program to crack passwords created using DES encryption with 1-4 characters
of a-z or A-Z.  execute crack with hash as command line argument. If a match is
found it will be printed. */
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
      printf("Usage: ./crack hash\n");
      return 1; //Error - no argument specified
  }
  char *hash = argv[1];
  char try[5];
  try[4] = '\0';
  char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p',
'q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K',
'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  char *ptr = try;
  int len = sizeof(letters);

  ptr += 3; // start from back of try to get single characters
  char *last = ptr;
  //do all single character passwords first
  if (varyLast(ptr,ptr,letters,len,hash))
    {
      return 0;
    }
  ptr--;
  //do all two character passwords
  for (int i = 0; i < len; i++)
  {
    *ptr = letters[i];
    if (varyLast(ptr,last,letters,len,hash))
    {
      return 0;
    }
  }
  ptr--;
  //do all three character passwords
  for (int i = 0; i < len; i++)
  {
    *ptr = letters[i];
    for (int j = 0; j < len; j++)
    {
      *(ptr+1) = letters[j];
      if (varyLast(ptr,last,letters,len,hash))
      {
        return 0;
      }
    }
  }
  ptr--;
  //do all four character passwords
  for (int i = 0; i < len; i++)
  {
    *ptr = letters[i];
    for (int j = 0; j < len; j++)
    {
      *(ptr+1) = letters[j];
      for (int k = 0; k < len; k++)
      {
        *(ptr+2) = letters[k];
        if (varyLast(ptr,last,letters,len,hash))
        {
          return 0;
        }
      }
    }

  }
  return 0;
}

bool varyLast(char *ptr, char *lsb, char *letters, int len,char *hash)
{

  for (int i = 0; i < len; i++)
  {
    *lsb = letters[i];

    if (!strcmp(hash, crypt(ptr,"50")))
    {
      printf("%s\n",ptr);
      return 1;
    }
  }
  return 0;
}
