#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define __SIZE_OF(x) (sizeof(x) / sizeof(typeof(x[0])))

#define max(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

#define IGNORE (2)

bool is_rising(int a, int b) {
  if (b > a) return true;
  return false;
}

bool is_falling(int a, int b) {
  if (b < a) return true;
  return false;
}

int localMinUtil(int arr[], int low, int high, int n)
{
  int mid = low + (high + low) / 2;

  if ( (mid = 0 || arr[mid - 1] < arr[mid]) &&
       (mid == n-1 || arr[mid+1] > arr[mid]) )
    return mid;

  else if ( mid > 0 && arr[mid-1] < arr[mid])
    return localMinUtil(arr, low, (mid-1), n);

  return localMinUtil(arr, (mid+1), high, n);
}

int localMin(int arr[], int n)
{
  return localMinUtil(arr, 0, n-1, n);
}

int main()
{
    int simData[] = { 47,47,48,50,55,57,57,55,53,50,47,45,45,45,46,47,
                      48,49,50,53,55,55,55,53,52,50,50,50,52,54,56,58, };
    //                  60,60,59,58,57,56,55,55,55,56,56,57,57,55,52,50,
    //                  49,47,45,43,44,45,46,47,46,45,44,44,43,43 };
    int peaks[__SIZE_OF(simData)] = { simData[0] };

    printf("simData[]:\n{ ");
    for(size_t i = 0U; i < __SIZE_OF(simData); i++)
    {
        printf("%d, ", simData[i]);
    }
    printf(" }\n");

    for(size_t i = 0U; i < __SIZE_OF(simData); i+=3)
    {
        peaks[i] = localMin(simData, __SIZE_OF(simData)-i);
    }

    printf("peaks_hi[]:\n{ ");
    for(size_t i = 0U; i < __SIZE_OF(simData); i++)
    {
        printf("%02d, ", peaks[i]);
    }
    printf(" }\n");

    return 0;
}
