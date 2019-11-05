/*Matt Begbie
    each sort has a time  attached to it for the 10000000000000 size file
    most sorts only require the size and the actual array, however the recursive ones require a high and low to know where to start/stop in the current call of the function  ex. 'bubblesort(array[], size);' & 'QuickSort(unsorted, 0, n -1);'
*/

#include <iostream>
#include <ctime>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <algorithm>
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
void PFlip(int* unsorted, int *f, int *j){

}
int Partition(int arr[], int low, int high, int *comparisons){
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        *comparisons =  *comparisons + 1;
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
int nextGap(int gap){
    gap = (gap*10)/13;

    if (gap < 1){
        gap = 1;
    }

    return gap;
}
int MattGap(int gap){
    gap = gap-1;

    if (gap < 1){
        gap = 1;
    }
    return gap;
}


void SelectionSort(int* unsorted, int n, int *comparisons){
    //int min = unsorted[0];
    int minIndex;
    for (int i = 0; i < n-1; i++){
        minIndex = i;
        for (int j = i+1; j < n; j++){
            *comparisons =  *comparisons + 1;
            if (unsorted[j] < unsorted[minIndex]){
                minIndex = j;
            }
        }
          changeP(&unsorted[minIndex], &unsorted[i]);
    }
}
void BubbleSort(int* unsorted, int n, int *comparisons){
    for (int i = 0; i <n-1; i++){
        for (int j = 0; j < n-i-1; j++){
            *comparisons =  *comparisons + 1;
            if (unsorted[j] > unsorted[j+1]){
                changeP(&unsorted[j], &unsorted[j+1]);
            }
        }
    }
}
void  MergeSort(int* unsorted, int left, int right, int *comparisons){
    if (left < right) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int middle = left+(right-left)/2;

        // Sort first and second halves
        MergeSort(unsorted, left, middle, *&comparisons);
        MergeSort(unsorted, middle+1, right, *&comparisons);

        MergeIt(unsorted, left, middle, right);
    }
}
void QuickSort(int* unsorted, int low, int high, int *comparisons){
    if (low < high){
        int pi = Partition(unsorted, low, high, comparisons);
        QuickSort(unsorted, low, pi - 1, comparisons);
        QuickSort(unsorted, pi + 1, high, comparisons);
    }
}
void CombSort(int* unsorted, int n, int *comparisons){
    int gap = n;
    bool swapped = true;

    // Keep running while gap is more than 1 and last
    // iteration caused a swap
    while (gap != 1 || swapped == true) {
        gap = nextGap(gap);
         swapped = false;

        // Compare all elements with current gap
        for (int i=0; i<n-gap; i++) {
            if (unsorted[i] > unsorted[i+gap]) {
                changeP(&unsorted[i], &unsorted[i+gap]);
                swapped = true;
            }
        }
    }
}
void MattSort(int* unsorted, int n, int *comparisons){
    int gap = n;
    bool swapped = true;

    // Keep running while gap is more than 1 and last
    // iteration caused a swap
    while (gap != 1 || swapped == true) {
        gap = MattGap(gap);
         swapped = false;

        // Compare all elements with current gap
        for (int i=0; i<n-gap; i++) {
            if (unsorted[i] > unsorted[i+gap]) {
                changeP(&unsorted[i], &unsorted[i+gap]);
                swapped = true;
            }
        }
    }
}
void shellSort(int* unsorted, int n, int *comparisons){
  for (int gap = n / 2; gap > 0; gap /= 2){
    for (int i = gap; i < n; i += 1){
      int temp = unsorted[i];
      int j;
      for (j = i; j >= gap && unsorted[j - gap] > temp; j -= gap){
        unsorted[j] = unsorted[j - gap];
      }
      unsorted[j] = temp;
    }
  }
}
void PancakeSort(int* unsorted, int n, int *comparisons){
    int bigIndex = 0;

    for (int i = 0; i < n-1; i++){
        bigIndex = 0;
        for (int j = 0; j < n - i; j++){
            if (unsorted[bigIndex] < unsorted[j]){
                bigIndex = j;
            }
        }
        for (int low = 0, high = bigIndex; low < high ; low++, high--){
            changeP(&unsorted[high], &unsorted[low]);
        }

        for (int l = 0; l <n; l++){
        }
        for (int low = 0, high = n-i-1; low < high; low++, high--){
            changeP(&unsorted[high], &unsorted[low]);
        }
        for (int l = 0; l <n; l++){
        }
    }
}


void ReadTheTextFile(int* unsorted, unsigned long *n){
    cout << "unsorted" << endl;
    stringstream doc;
    doc << "data" << *n << ".txt";
    ifstream infile(doc.str());
    cout<<doc.str()<<endl;
    for (unsigned long x = 0; x < *n; x++){//do for the size of array
        infile >> unsorted[x];
        //cout <<x<<"="<< unsorted[x] << "\t";
    }
    infile.close();
}
int main(){

    //array with the data
    unsigned long n = 0;
    int sizeindex = 0;
    int fsize[] = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
    int sortSel = 0;
    int comparisons = 0;
    //ask user for size
    cout << "1. data10.txt \n2. data100.txt\n3. data1000.txt \n4. data10000.txt\n5. data100000.txt\n6. data1000000.txt\n7. data10000000.txt" << endl;
    cout << "Please choose the text file to use (1-5): ";
    cin >> sizeindex;
    n = fsize[sizeindex - 1];



    int* unsorted= new int [n];
    //select sort
    cout << "1. BubbleSort \n2. QuickSort \n3. MergeSort \n4. SelectionSort \n5. CombSort \n6. MattSort \n7. ShellSort \n8. PancakeSort" << endl;
    cout << "Please select a sort to use (1-8)";
    cin >> sortSel;
    //read the file;
    ReadTheTextFile(unsorted, &n);

    clock_t begin = clock(); //start of clock
    if (sortSel == 1){
        BubbleSort(unsorted, n, &comparisons); //31.087000000 seconds
        //comparisons = n(n - 1)/2
    }
    else if (sortSel == 2) {
        QuickSort(unsorted, 0, n -1, &comparisons); //0.01.8000000 seconds
    }
    else if (sortSel == 3) {
        MergeSort(unsorted, 0, n -1, &comparisons); // 0.063 seconds
    }
    else if (sortSel == 4) {
        SelectionSort(unsorted, n, &comparisons);//23 seconds
    }
    else if (sortSel == 5) {
        CombSort(unsorted, n, &comparisons); // 0.029000000 seconds
    }
    else if (sortSel == 6) {
        MattSort(unsorted, n, &comparisons); //12.019000000 seconds, this is just a bad combsort where instead of making the gap smaller by a factor, it shrinks by 1 each time
    }
    else if (sortSel == 7) {
        shellSort(unsorted, n, &comparisons); // 0.023000000 seconds
    }
    else if (sortSel == 8) {
        PancakeSort(unsorted, n, &comparisons); // 67.481000000 seconds with home pc, 83.644000000 with school
    }
    else if (sortSel == 9) {
        //if pancake sort uses selection sort to find the highest number, can a new sort be used as a base with the same permutations?
        //this is an attempt with quicksort0.663000000
    }
    else if (sortSel == 10) {

    }
    else if (sortSel == 11) {

    }
    else if (sortSel == 12) { //placeholder so it is fast to copy/paste a new sort because i am lazy

    }

    clock_t end = clock(); //end of clock
    cout << endl << "sorted" << endl ;
    for (int x = 0; x < n; x++){
        //cout << unsorted[x] << "\t";
    }
    cout << endl;

    //timiming stuff
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    printf ("Elapsed time is %.9f seconds.", elapsed_secs );
    cout << endl << endl << "Comparisons:" << comparisons;
    return 0;
}



