#include <cctype>
#include <ctime>
#include <iostream>

using namespace std;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;  //clock per milliseconds

int genRandInt(int low, int high) {
    return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[], int arr3[]) {
    for (int i = 0; i < NUMBERS_SIZE; ++i) {
        arr1[i] = genRandInt(0, NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

int Partition(int numbers[], int i, int k) {
    int l;
    int h;
    int midpoint;
    int pivot;
    int temp;
    bool done;

    /* Pick middle element as pivot */
    midpoint = i + (k - i) / 2;
    pivot = numbers[midpoint];

    done = false;
    l = i;
    h = k;

    while (!done) {
        /* Increment l while numbers[l] < pivot */
        while (numbers[l] < pivot) {
            ++l;
        }

        /* Decrement h while pivot < numbers[h] */
        while (pivot < numbers[h]) {
            --h;
        }

        /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
        if (l >= h) {
            done = true;
        } else {
            /* Swap numbers[l] and numbers[h],
          update l and h */
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;

            ++l;
            --h;
        }
    }

    return h;
}

int median(int a, int b, int c) {
    if ((a > b) ^ (a > c)) {return a;}
    else if ((b < a) ^ (b < c)) {return b;}
    else {return c;}
}

int Partitionforthree(int numbers[], int i, int k) {
    int l;
    int h;
    int midpoint;
    int pivot;
    int temp;
    bool done;

    /* Pick middle element as pivot */
    midpoint = i + (k - i) / 2;
    pivot = numbers[median(i, midpoint, k)];

    done = false;
    l = i;
    h = k;

    while (!done) {
        /* Increment l while numbers[l] < pivot */
        while (numbers[l] < pivot) {
            ++l;
        }

        /* Decrement h while pivot < numbers[h] */
        while (pivot < numbers[h]) {
            --h;
        }

        /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
        if (l >= h) {
            done = true;
        } else {
            /* Swap numbers[l] and numbers[h],
          update l and h */
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;

            ++l;
            --h;
        }
    }

    return h;
}

void printArray(int arr[], int i = NUMBERS_SIZE){
    for (int i = 0; i < NUMBERS_SIZE - 1; i++){
        cout << arr[i] << ", ";
    }
    cout << arr[NUMBERS_SIZE-1] << endl;
}

void Quicksort_midpoint(int numbers[], int i, int k);       // this function sorts the given array in the range from i to k using quicksort method. In this function, pivot is the midpoint element (numbers[(i+k)/2]). (implementation of this function is given in section 21.5)
void Quicksort_medianOfThree(int numbers[], int i, int k);  // this function utilizes different pivot selection technique in quicksort algorithm. The pivot is the median of the following three values: leftmost (numbers[i]), midpoint (numbers[(i+k)/2]) and rightmost (numbers[k]). You should modify the partition function given in section 21.5 to select the pivot using median-of-three technique.
void InsertionSort(int numbers[], int numbersSize);         // this function sorts the given array using InsertionSort method. (implementation of this method is provided in section 21.3).

int main() {
    int first[NUMBERS_SIZE];
    int second[NUMBERS_SIZE];
    int third[NUMBERS_SIZE];

    fillArrays(first, second, third);
    
    clock_t Start = clock();
    Quicksort_midpoint(first, 0, NUMBERS_SIZE - 1);
    clock_t End = clock();
    int elapsedTime = (End - Start) / CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Elapsed Time for the Quicksort Midterm: " << elapsedTime << endl;

    Start = clock();
    Quicksort_medianOfThree(second, 0, NUMBERS_SIZE - 1);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Elapsed Time for the Quicksort Median: " << elapsedTime << endl;

    Start = clock();
    InsertionSort(third, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;  // converts elapsed time from microseconds to milliseconds.
    cout << "Elapsed Time for the Insertion Sort: " << elapsedTime << endl;
    printArray(third);

}


void InsertionSort(int numbers[], int numbersSize) {
    int i, j, temp;
    for (i = 1; i < numbersSize; ++i) {
        j = i;
        while (j > 0 && numbers[j] < numbers[j - 1]) {
            temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
            --j;
        }
    }
}

void Quicksort_midpoint(int numbers[], int i, int k) {
   // Base case: If the partition size is 1 or zero 
   // elements, then the partition is already sorted
   if (i >= k) {
      return;
   }
   
   // Partition the data within the array. Value lowEndIndex 
   // returned from partitioning is the index of the low 
   // partition's last element.
   int lowEndIndex = Partition(numbers, i, k);
   
   // Recursively sort low partition (lowIndex to lowEndIndex) 
   // and high partition (lowEndIndex + 1 to highIndex)
   Quicksort_midpoint(numbers, i, lowEndIndex);
   Quicksort_midpoint(numbers, lowEndIndex + 1, k);
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
   // Base case: If the partition size is 1 or zero 
   // elements, then the partition is already sorted
   if (i >= k) {
      return;
   }
   
   // Partition the data within the array. Value lowEndIndex 
   // returned from partitioning is the index of the low 
   // partition's last element.
   int lowEndIndex = Partitionforthree(numbers, i, k);
   
   // Recursively sort low partition (lowIndex to lowEndIndex) 
   // and high partition (lowEndIndex + 1 to highIndex)
   Quicksort_medianOfThree(numbers, i, lowEndIndex);
   Quicksort_medianOfThree(numbers, lowEndIndex + 1, k);
}