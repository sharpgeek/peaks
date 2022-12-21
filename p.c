#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define __SIZE_OF(x) (sizeof(x) / sizeof(typeof(x[0])))

#define MINIMAL (3)

typedef enum {
    RISING,
    FALLING,
    PLATEAU,
} condition_t;

condition_t goingTo(int a, int b, int c) {
    if ( a == b || b == c ) return PLATEAU;
    if ( a < b  && b < c ) return RISING;
    if ( a > b  && b > c ) return FALLING;
}

int simData[] = { 47,47,48,50,55,57,57,55,53,50,47,45,45,45,46,47,
                  48,49,50,53,55,55,55,53,52,50,50,50,52,54,56,58,
                  60,60,59,58,57,56,55,55,55,56,56,57,57,55,52,50,
                  49,47,45,43,44,45,46,47,46,45,44,44,43,43};

int peak_hi[__SIZE_OF(simData)];
int peak_lo[__SIZE_OF(simData)];


int main() {

    if ( simData[1] > simData[0] ) peak_lo[0] = simData[0]; else peak_hi[0] = simData[0];

    printf("simData[]:\n{ ");
    for(size_t i = 0U; i < __SIZE_OF(simData); i++)
    {
        printf("%02d, ", simData[i]);
    }
    printf(" }\n");

    printf("Condition:\n{     ");
    static condition_t previous = PLATEAU;
    condition_t current;
    for(size_t i = 1U; i < __SIZE_OF(simData)-1; i++)
    {
        current = goingTo(simData[i-1],simData[i],simData[i+1]);
        if (current != previous)
        {
            switch(current) {
                case RISING:
                    printf("R+, ");
                    if ( previous == FALLING ) peak_lo[i-1] = simData[i-1]; 
                    break;
                case FALLING:
                    printf("F-, ");
                    if ( previous == RISING ) peak_hi[i-1] = simData[i-1]; 
                    break;
                case PLATEAU:
                    printf("P=, ");
                    if ( previous == FALLING ) peak_lo[i] = simData[i]; 
                    if ( previous == RISING  ) peak_hi[i] = simData[i]; 
                    break;
            }
        } else {
            printf("    ");
        }
        previous = current;
    }
    printf("     }\n");

    printf("peak_hi[]:\n{ ");
    for(size_t i = 0U; i < __SIZE_OF(simData); i++)
    {
        printf("%02d, ", peak_hi[i]);
    }
    printf(" }\n");

    printf("peak_lo[]:\n{ ");
    for(size_t i = 0U; i < __SIZE_OF(simData); i++)
    {
        printf("%02d, ", peak_lo[i]);
    }
    printf(" }\n");

    return 0;
}
