#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_VAL 100  //Max count array size

// The two arrays I am using for swap counting
int bubbleCount[MAX_VAL];
int selectionCount[MAX_VAL];

void resetSwapCounts() { //Reset so I can reuse the swap counters for both arrays
    for (int i = 0; i < MAX_VAL; i++) {
        bubbleCount[i] = 0;
        selectionCount[i] = 0;
    }
}

void swap(int* aPtr, int* bPtr, int swapCounts[MAX_VAL], int aVal, int bVal) {
    int temp = *aPtr; //pointer to first num swaps with second num
    *aPtr = *bPtr;
    *bPtr = temp;
    swapCounts[aVal]++; //incrementing the swap count to the value's position
    swapCounts[bVal]++; //This records a swap for each value
}

//Bubble sort using the swap function that records swaps
void bubbleSort(int arr[], int n, int swapCounts[MAX_VAL]) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1], swapCounts, arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; //Breaks the loop when no swap occurs at all
    }
}

//Selection sort using the swap function that records swaps
void selectionSort(int arr[], int n, int swapCounts[MAX_VAL]) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(&arr[i], &arr[min_idx], swapCounts, arr[i], arr[min_idx]);
        }
    }
}

// This function prints the amount of swaps for each value once the sort finishes
void printSwapCounts(int swapCounts[MAX_VAL], int arr[], int n) {
    int ttlSwaps = 0;
    for (int i = 0; i < n; i++) {
        printf("%d: %d\n", arr[i], swapCounts[arr[i]]);
        ttlSwaps += swapCounts[arr[i]];
    }
    printf("%d\n", ttlSwaps / 2);
}

int main() {
    //Init the array1 and copy to a new array so I don't permanently change the starting one
    int array1[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int array1Cpy[sizeof(array1) / sizeof(array1[0])];
    for (int i = 0; i < sizeof(array1) / sizeof(array1[0]); i++) {
        array1Cpy[i] = array1[i];
    }
    int n1 = sizeof(array1) / sizeof(array1[0]);
    //Init the array2 and copy to a new array so I don't permanently change the starting one
    int array2[] = {90, 80, 70, 60, 50, 40, 30, 20, 10};
    int array2Cpy[sizeof(array2) / sizeof(array2[0])];
    for (int i = 0; i < sizeof(array2) / sizeof(array2[0]); i++) {
        array2Cpy[i] = array2[i];
    }
    int n2 = sizeof(array2) / sizeof(array2[0]);

    //Each of these blocks is sorting an array and printing the amount of swaps
    resetSwapCounts();
    bubbleSort(array1, n1, bubbleCount);
    printf("array1 bubble sort:\n");
    printSwapCounts(bubbleCount, array1, n1);

    resetSwapCounts();
    bubbleSort(array2, n2, bubbleCount);
    printf("array2 bubble sort:\n");
    printSwapCounts(bubbleCount, array2, n2);

    resetSwapCounts();
    selectionSort(array1Cpy, n1, selectionCount);
    printf("array1 selection sort:\n");
    printSwapCounts(selectionCount, array1Cpy, n1);

    resetSwapCounts();
    selectionSort(array2Cpy, n2, selectionCount);
    printf("array2 selection sort:\n");
    printSwapCounts(selectionCount, array2Cpy, n2);

    return 0;
}