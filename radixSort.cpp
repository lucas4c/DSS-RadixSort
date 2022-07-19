#include <cstdio>
#include <string>
#include <bits/stdc++.h>
using std::string;
using namespace std;

size_t getMax(string arr[], int arrSize){
    size_t max = arr[0].size();
    for (int i = 1; i < arrSize; i++){
        if (arr[i].size()>max)
            max = arr[i].size();
    }
    return max;
}

void countSort(string arr[], int size, size_t k){
    string *temp = NULL; int *counter = NULL;
    temp = new string[size];
    counter = new int[257];

    for (int i = 0; i <257; i++){
        counter[i] = 0;
    }
    for (int j = 0; j <size; j++){
        counter[k < arr[j].size() ? (int)(unsigned char)arr[j][k] + 1 : 0]++;
    }

    for (int f = 1; f <257; f++){
        counter[f] += counter[f - 1];
    }

    for (int r = size - 1; r >= 0; r--){
        temp[counter[k < arr[r].size() ? (int)(unsigned char)arr[r][k] + 1 : 0] - 1] = arr[r];
        counter[k < arr[r].size() ? (int)(unsigned char)arr[r][k] + 1 : 0]--;
    }

    for (int l = 0; l < size; l++){

        arr[l] = temp[l];
    }

    delete[] temp;
    delete[] counter;
}


void radixSort(string arr[], int r){
    size_t max = getMax(arr, r);
    for (size_t digit = max; digit > 0; digit--){
        countSort(arr, r, digit - 1);
    }

}

void filterArray(string arr[], int *r) {
    string *temp = new string[1000000];
    int tempIndex = 0;

    for (int i=0; i<=*r; i++) {
        if(arr[i].length()>=4) {
            temp[tempIndex] = arr[i];
            tempIndex++;
        }
    }

    for (int i=0; i<=*r; i++) {
        arr[i]='0';
    }

    for (int i=0; i<=tempIndex; i++) {
        arr[i]=temp[i];
    }

    *r=tempIndex;

}

void countFreq(string filename, string arr[], int r) {

    int freq=1;

    ofstream file(filename);

    for (int i=0; i<=r; i++) {
        if(arr[i]==arr[i+1])
            freq++;
        else {
            file << arr[i] << " " << freq << endl;
            freq=1;
        }
    }

    file.close();

}

int main(void) {
    int wordCounter;

    std::ifstream file1 ("frankenstein_clean.txt");
    std::ifstream file2 ("war_and_peace_clean.txt");
    std::string word;

    string *arr1 = new string[1000000];
    int arr1Size;
    string *arr2 = new string[1000000];
    int arr2Size;

    wordCounter = 0;
    while (file1 >> word) {

        arr1[wordCounter] = word;
        wordCounter++;

    }
    arr1Size = wordCounter;

    wordCounter = 0;
    while (file2 >> word) {

        arr2[wordCounter] = word;
        wordCounter++;

    }
    arr2Size = wordCounter;

    radixSort(arr1, arr1Size);
    radixSort(arr2, arr2Size);
    filterArray(arr1, &arr1Size);
    filterArray(arr2, &arr2Size);

    countFreq("frankenstein_ordenado.txt", arr1, arr1Size);
    countFreq("war_and_peace_ordenado.txt", arr2, arr2Size);

    return 0;
}
