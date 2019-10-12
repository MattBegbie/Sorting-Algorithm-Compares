/*Matt Begbie

*/

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
void CombSort(int* unsorted, int n){
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

void MattSort(int* unsorted, int n){
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

void shellSort(int* unsorted, int n){
  for (int gap = n / 2; gap > 0; gap /= 2)
  {
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



void ReadTheTextFile(int* unsorted, int *n){
    cout << "unsorted" << endl;
    stringstream doc;
    doc << "data" << *n << ".txt";
    ifstream infile(doc.str());
    for (int x = 0; x < *n; x++){//do for the size of array
        infile >> unsorted[x];
        cout << unsorted[x] << "\t";
    }
    infile.close();
}
int main(){

    //array with the data
    int n = 0;
    int sizeindex = 0;
    int fsize[] = {10, 100, 1000, 10000, 100000};
    int sortSel = 0;
    //ask user for size
    cout << "1. data10.txt \n2. data100.txt\n3. data1000.txt \n4. data10000.txt\n5. data100000.txt" << endl;
    cout << "Please choose the text file to use (1-5): ";
    cin >> sizeindex;
    n = fsize[sizeindex - 1];
    int unsorted[n];
    //select sort
    cout << "1. BubbleSort \n2. QuickSort \n3. MergeSort \n4. SelectionSort \n5. CombSort \n6. MattSort" << endl;
    cout << "Please select a sort to use (1-6)";
    cin >> sortSel;
    //read the file;
    ReadTheTextFile(unsorted, &n);

    clock_t begin = clock(); //start of clock
    if (sortSel == 1){
        BubbleSort(unsorted, n); //31.087000000 seconds
    }
    else if (sortSel == 2) {
        QuickSort(unsorted, 0, n -1); //0.018000000 seconds
    }
    else if (sortSel == 3) {
        MergeSort(unsorted, 0, n -1); // 0.063 seconds
    }
    else if (sortSel == 4) {
        SelectionSort(unsorted, n);//23 seconds
    }
    else if (sortSel == 5) {
        CombSort(unsorted, n); // 0.029000000 seconds
    }
    else if (sortSel == 6) {
        MattSort(unsorted, n); //12.019000000 seconds, this is just a bad combsort where instead of making the gap smaller by a factor, it shrinks by 1 each time
    }
    else if (sortSel == 8) {
        shellSort(unsorted, n);
    }
    else if (sortSel == 9) {

    }
    else if (sortSel == 10) {

    }
    else if (sortSel == 11) {

    }
    else if (sortSel == 12) {

    }
    else if (sortSel == 13) {

    }

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





