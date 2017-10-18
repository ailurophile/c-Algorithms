
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>



/**
 * Sorts array of n values.
 */
void sort(int *values, int n)
{
    //  implement a counting sort algorithm

    int max_value = 0;
    for (int i = 0; i < n; i++) // find maximum value
    {
        if (values[i] > max_value)
        {
          max_value = values[i];
        }
    }
    //create array as long as the maximum value in values array +1
    int counts[max_value + 1];
    memset(counts, 0, sizeof(counts)); //clear count values in array
    // count each value in values
    for (int i = 0; i < n; i++)
    {
        counts[values[i]] += 1;
    }
    //copy values into values array in order
    int *ptr = values;
    for (int i = 0; i < max_value + 1; i++)
    {
        for  (int j = 0; j < counts[i]; j++)
        {
            *ptr++ = i;
        }
    }
    return;
}

bool search(int value, int values[], int n)
{
    // Only positive values allowed
    if (n < 2)
    {
        return false;
    }
    int bottom = 0; //lower bound for searching
    int top = n-1; //highest value in search
    int try;
    sort(values,n); //sort values array from lowest to highest
    while (values[bottom] < values[top])
    {
        int next = (bottom + top)/2;
        if (next == try)
        {
          if ((values[bottom] == value) || (values[top] == value))
          {
            return true; //value found
          }
          return false;  // value not found
        }
        try = next; //pick middle value
        if (values[try] == value)
        {
            return true; // found value so return true
        }
        if (values[try] > value)
        {
            top = try;  // eliminate larger values from search
        }
        else
        {
            bottom = try; //eliminate smaller values from search
        }
    }
    return false; // value not found

}

int main(void)
{
  int array[] = {5,3,6,2,7,8,5};
  int array2[] = {26,27,28};
  int len = sizeof(array)/sizeof(int);
  printf("%d\n", (search(2,array,len)));
  printf("%d\n", (search(1,array,len)));
  printf("%d\n", (search(4,array,len)));
  printf("%d\n", (search(8,array,len)));
  printf("%d\n", (search(28,array2,3)));
  /*
  sort(array, len);
  for (int i = 0; i < len; i++)
  {
    printf("%i ",array[i]);
  }
  printf("\n");
  */

}
