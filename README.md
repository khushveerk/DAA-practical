# DAA-practical

// Practical 1: Insertion Sort with comparison count
#include <iostream>
#include <vector>
using namespace std;
 
long long insertionSort(vector<int>& arr) {
    long long comparisons = 0;
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && (++comparisons, arr[j] > key)) {
            arr[j + 1] = arr[j];
            j--;
        }
        if (j >= 0) comparisons++; // count the failed comparison
        arr[j + 1] = key;
    }
    return comparisons;
}
 
int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int& x : arr) cin >> x;
 
    long long comps = insertionSort(arr);
 
    cout << "Sorted array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nNumber of comparisons: " << comps << endl;
    return 0;
}
----------------------------------------------------------------------------------------------------
// Practical 2: Merge Sort with comparison count
#include <iostream>
#include <vector>
using namespace std;
 
long long mergeCount = 0;
 
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < (int)left.size() && j < (int)right.size()) {
        mergeCount++;
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < (int)left.size()) arr[k++] = left[i++];
    while (j < (int)right.size()) arr[k++] = right[j++];
}
 
void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}
 
int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int& x : arr) cin >> x;
 
    mergeCount = 0;
    mergeSort(arr, 0, n - 1);
 
    cout << "Sorted array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nNumber of comparisons: " << mergeCount << endl;
    return 0;
}

-----------------------------------------------------------------------------------------------
// Practical 3: Heap Sort with comparison count
#include <iostream>
#include <vector>
using namespace std;
 
long long heapComps = 0;
 
void heapify(vector<int>& arr, int n, int i) {
    int largest = i, l = 2*i+1, r = 2*i+2;
    if (l < n) { heapComps++; if (arr[l] > arr[largest]) largest = l; }
    if (r < n) { heapComps++; if (arr[r] > arr[largest]) largest = r; }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
 
void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n/2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n-1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
 
int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int& x : arr) cin >> x;
 
    heapComps = 0;
    heapSort(arr);
 
    cout << "Sorted array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nNumber of comparisons: " << heapComps << endl;
    return 0;
}

----------------------------------------------------------------------------------------------------

