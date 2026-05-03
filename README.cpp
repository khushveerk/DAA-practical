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

// Practical 4: Strassen's Algorithm for Matrix Multiplication
#include <iostream>
#include <vector>
using namespace std;
 
typedef vector<vector<int>> Matrix;
 
Matrix add(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i=0; i<n; i++) for (int j=0; j<n; j++) C[i][j] = A[i][j]+B[i][j];
    return C;
}
 
Matrix sub(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i=0; i<n; i++) for (int j=0; j<n; j++) C[i][j] = A[i][j]-B[i][j];
    return C;
}
 
Matrix strassen(const Matrix& A, const Matrix& B) {
    int n = A.size();
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }
    int half = n / 2;
 
    // Split into submatrices
    Matrix A11(half, vector<int>(half)), A12(half, vector<int>(half)),
           A21(half, vector<int>(half)), A22(half, vector<int>(half));
    Matrix B11(half, vector<int>(half)), B12(half, vector<int>(half)),
           B21(half, vector<int>(half)), B22(half, vector<int>(half));
 
    for (int i=0; i<half; i++)
        for (int j=0; j<half; j++) {
            A11[i][j]=A[i][j];       A12[i][j]=A[i][j+half];
            A21[i][j]=A[i+half][j];  A22[i][j]=A[i+half][j+half];
            B11[i][j]=B[i][j];       B12[i][j]=B[i][j+half];
            B21[i][j]=B[i+half][j];  B22[i][j]=B[i+half][j+half];
        }
 
    // 7 Strassen products
    Matrix M1 = strassen(add(A11,A22), add(B11,B22));
    Matrix M2 = strassen(add(A21,A22), B11);
    Matrix M3 = strassen(A11, sub(B12,B22));
    Matrix M4 = strassen(A22, sub(B21,B11));
    Matrix M5 = strassen(add(A11,A12), B22);
    Matrix M6 = strassen(sub(A21,A11), add(B11,B12));
    Matrix M7 = strassen(sub(A12,A22), add(B21,B22));
 
    // Combine
    Matrix C(n, vector<int>(n));
    for (int i=0; i<half; i++)
        for (int j=0; j<half; j++) {
            C[i][j]           = M1[i][j]+M4[i][j]-M5[i][j]+M7[i][j];
            C[i][j+half]      = M3[i][j]+M5[i][j];
            C[i+half][j]      = M2[i][j]+M4[i][j];
            C[i+half][j+half] = M1[i][j]-M2[i][j]+M3[i][j]+M6[i][j];
        }
    return C;
}
 
void printMatrix(const Matrix& M) {
    for (auto& row : M) {
        for (int x : row) cout << x << "\t";
        cout << "\n";
    }
}
 
int main() {
    int n;
    cout << "Enter matrix size (must be power of 2, e.g. 2,4,8): ";
    cin >> n;
 
    Matrix A(n, vector<int>(n)), B(n, vector<int>(n));
    cout << "Enter matrix A (" << n << "x" << n << "):\n";
    for (auto& row : A) for (int& x : row) cin >> x;
    cout << "Enter matrix B (" << n << "x" << n << "):\n";
    for (auto& row : B) for (int& x : row) cin >> x;
 
    Matrix C = strassen(A, B);
    cout << "\nResult (A x B):\n";
    printMatrix(C);
    return 0;
}

--------------------------------------------------------------------------------------------------------

 // Practical 5: Radix Sort
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
void countSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n), count(10, 0);
    for (int i=0; i<n; i++) count[(arr[i]/exp)%10]++;
    for (int i=1; i<10; i++) count[i] += count[i-1];
    for (int i=n-1; i>=0; i--) {
        output[count[(arr[i]/exp)%10]-1] = arr[i];
        count[(arr[i]/exp)%10]--;
    }
    arr = output;
}
 
void radixSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    for (int exp=1; maxVal/exp > 0; exp*=10)
        countSort(arr, exp);
}
 
int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter non-negative elements: ";
    for (int& x : arr) cin >> x;
 
    radixSort(arr);
 
    cout << "Sorted array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    return 0;
}

------------------------------------------------------------------------------------------------

 // Practical 6: Bucket Sort
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
void bucketSort(vector<float>& arr) {
    int n = arr.size();
    vector<vector<float>> buckets(n);
 
    for (int i=0; i<n; i++) {
        int idx = (int)(n * arr[i]);
        if (idx == n) idx = n - 1;
        buckets[idx].push_back(arr[i]);
    }
 
    for (auto& b : buckets) sort(b.begin(), b.end());
 
    int k = 0;
    for (auto& b : buckets)
        for (float x : b) arr[k++] = x;
}
 
int main() {
    int n;
    cout << "Enter number of elements (values between 0 and 1): ";
    cin >> n;
    vector<float> arr(n);
    cout << "Enter elements (e.g. 0.3 0.7 0.1): ";
    for (float& x : arr) cin >> x;
 
    bucketSort(arr);
 
    cout << "Sorted array: ";
    for (float x : arr) cout << x << " ";
    cout << endl;
    return 0;
}
