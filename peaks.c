#include <stdio.h>
#include <stdbool.h>

bool getMountains(const int TempBuffer[], int *PeakArr, int size)
{
    int next, previous, k = 0;
    int min = 0;
    int min_index = 0;
    bool result = false;
    
    // check current element against next & previous
    for(int i = 0; i < size; i++)
    {
        // Store next element if not at the end
        next = (i + 1 == size) ? 0 : TempBuffer[i + 1];
        
        // keep the track of min value & min peak index
        if(TempBuffer[i] < min)
        {
            min = TempBuffer[i];
            min_index = i;
        }
        
        // max peak: if current element > next & previous
        if(TempBuffer[i] > next && TempBuffer[i] >= previous)
        {
            // validate max peak
            if(TempBuffer[i]>(min+2))
            {
                // min index
                PeakArr[k++]= min_index;
                
                // max index
                PeakArr[k++]= i;
                
                // Reset min
                min = TempBuffer[i];
                
                result = (k>2) ? true : result;
            }
        }
        // Store previous element
        previous = TempBuffer[i];
    }
    return result;
}

void LeftShiftArr(int* arr, int Size)
{
    int i, temp;
    temp = arr[0];
    for (i = 0; i < Size-1; i++)
    {
        arr[i] = arr[i+1];
    }
    arr[i] = 0;
}

void reset_buffer(int* arr, int ResetUpToIndex, int Size)
{
    for (int i = 0; i < ResetUpToIndex; i++)
    {
        LeftShiftArr(arr, Size);
    }
}

int main()
{
    // to simulate: data from the image above 
    int TempBuffer[] = {47,47,48,50,55,57,57,55,53,50,47,45,45,45,46,47,
                        48,49,50,53,55,55,55,53,52,50,50,50,52,54,56,58,
                        60,60,59,58,57,56,55,55,55,56,56,57,57,55,52,50,
                        49,47,45,43,44,45,46,47,46,45,44,44,43,43};
    int size = sizeof(TempBuffer) / sizeof(TempBuffer[0]);
    int PeakArr[4]={0};
    int buffer[1000]= {0};
    int index =0;
    bool x = false;
    
    for(int y =0; y<size; y++)
    {
        printf("->:%d ",TempBuffer[y]);
        buffer[index++] = TempBuffer[y];
        x = getMountains(buffer,PeakArr,1000);
        if(x)
        {
            printf("\nBreak at index:%d -> ",y);
            for(int j =0; j<4;j++)
            {
                printf("%d-%d, ",PeakArr[j],buffer[PeakArr[j]]);
            }
            
            int ResetUpToIndex = PeakArr[2]+1;
            reset_buffer(buffer, ResetUpToIndex, 1000);
            index = PeakArr[3]-PeakArr[2];
            printf("\n------------------------------------------------------\n");
            
            for(int j =0; j<4;j++)
            {
                PeakArr[j] =0;
            }
        }
    }
    return 0;
}
