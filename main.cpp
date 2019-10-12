#include <iostream>
#include <ctime>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

void FunctionToTime() {
    int a;
    for (int i=0;i<100;i++){
            a=i*i*i;
            cout <<a<<endl;
    }
}

void changeP(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;

}

int Partition(int arr[], int low, int high){
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            changeP(&arr[i], &arr[j]);
        }
    }
    changeP(&arr[i + 1], &arr[high]);
    return (i + 1);

}

void MergeIt(int* unsorted, int left, int middle, int right){
    int i, j, k = 0;
    int n1 = middle - left + 1;
    int n2 =  right - middle;

    /* create temp arrays */
    int L[n1], R[n2];

    for (i = 0; i < n1; i++) {
        L[i] = unsorted[left + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = unsorted[middle + 1+ j];
    }

    /* Merge the temp arrays back into unsorted[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray

     while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            unsorted[k] = L[i];
            i++;
        }
        else{
            unsorted[k] = R[j];
            j++;
        }
        k++;
    }

    // copy the remaining elements of the temp arrays
       while (i < n1)
    {
        unsorted[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        unsorted[k] = R[j];
        j++;
        k++;
    }
}


void SelectionSort(int* unsorted, int n){
    //int min = unsorted[0];
    int minIndex;
    for (int i = 0; i < n-1; i++){
        minIndex = i;
        for (int j = i+1; j < n; j++){
            if (unsorted[j] < unsorted[minIndex]){
                minIndex = j;
            }
        }
          changeP(&unsorted[minIndex], &unsorted[i]);
    }
}

void BubbleSort(int* unsorted, int n){
    for (int i = 0; i <n-1; i++){
        for (int j = 0; j < n-i-1; j++){
            if (unsorted[j] > unsorted[j+1]){
                changeP(&unsorted[j], &unsorted[j+1]);
            }
        }
    }
}

void  MergeSort(int* unsorted, int left, int right){
    if (left < right) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int middle = left+(right-left)/2;

        // Sort first and second halves
        MergeSort(unsorted, left, middle);
        MergeSort(unsorted, middle+1, right);

        MergeIt(unsorted, left, middle, right);
    }
}

void QuickSort(int* unsorted, int low, int high){
    if (low < high){
        int pi = Partition(unsorted, low, high);

        QuickSort(unsorted, low, pi - 1);
        QuickSort(unsorted, pi + 1, high);
    }
}

void ReadTheTextFile(int* unsorted, int *n){
    cout << "unsorted" << endl;
    //ifstream infile("data10.txt");  *n = 10;
    //ifstream infile("data100.txt");  *n = 100;
    //ifstream infile("data1000.txt");  *n = 1000;
    //ifstream infile("data10000.txt");  *n = 10000;
    ifstream infile("data100000.txt");  *n = 100000;
    for (int x = 0; x < *n; x++){//do for the size of array
        infile >> unsorted[x];
        cout << unsorted[x] << "\t";
    }
    infile.close();
}
int main(){

    //array with the data
    int n = 0;
    int unsorted[100000];
    //read the file;
    ReadTheTextFile(unsorted, &n);

    clock_t begin = clock(); //start of clock

    //BubbleSort(unsorted, n);
    //QuickSort(unsorted, 0, n -1);
    MergeSort(unsorted, 0, n -1);

//    SelectionSort(unsorted, n);
    clock_t end = clock(); //end of clock
    cout << endl << "sorted" << endl ;
    for (int x = 0; x < n; x++){
        cout << unsorted[x] << "\t";

    }
    cout << endl;

    //timiming stuff
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    printf ("Elapsed time is %.9f seconds.", elapsed_secs );


    return 0;

}



