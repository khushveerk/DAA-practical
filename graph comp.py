// Practical 1-3: Comparison Graph
// Tests Insertion, Merge, Heap Sort on 100 input sizes (30 to 1000)
// Averages comparisons over 10 random instances each
// Outputs CSV data and plots ASCII graph; save CSV and plot in Python/Excel
 
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
using namespace std;
 
// -------- Insertion Sort --------
long long insertionSort(vector<int> arr) {
    long long comps = 0;
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && (++comps, arr[j] > key)) { arr[j+1] = arr[j]; j--; }
        if (j >= 0) comps++;
        arr[j+1] = key;
    }
    return comps;
}
 
// -------- Merge Sort --------
long long mergeComps;
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> L(arr.begin()+l, arr.begin()+m+1);
    vector<int> R(arr.begin()+m+1, arr.begin()+r+1);
    int i=0, j=0, k=l;
    while (i<(int)L.size() && j<(int)R.size()) {
        mergeComps++;
        arr[k++] = (L[i]<=R[j]) ? L[i++] : R[j++];
    }
    while (i<(int)L.size()) arr[k++]=L[i++];
    while (j<(int)R.size()) arr[k++]=R[j++];
}
void mergeSort(vector<int>& arr, int l, int r) {
    if (l>=r) return;
    int m=(l+r)/2;
    mergeSort(arr,l,m); mergeSort(arr,m+1,r); merge(arr,l,m,r);
}
long long mergeSortCount(vector<int> arr) {
    mergeComps = 0;
    mergeSort(arr, 0, arr.size()-1);
    return mergeComps;
}
 
// -------- Heap Sort --------
long long heapComps;
void heapify(vector<int>& arr, int n, int i) {
    int largest=i, l=2*i+1, r=2*i+2;
    if (l<n){heapComps++; if(arr[l]>arr[largest]) largest=l;}
    if (r<n){heapComps++; if(arr[r]>arr[largest]) largest=r;}
    if (largest!=i){swap(arr[i],arr[largest]); heapify(arr,n,largest);}
}
long long heapSortCount(vector<int> arr) {
    heapComps = 0;
    int n = arr.size();
    for (int i=n/2-1; i>=0; i--) heapify(arr,n,i);
    for (int i=n-1; i>0; i--){swap(arr[0],arr[i]); heapify(arr,i,0);}
    return heapComps;
}
 
// -------- Generate random array --------
vector<int> randArray(int n) {
    vector<int> arr(n);
    for (int& x : arr) x = rand() % 10000;
    return arr;
}
 
int main() {
    srand(time(0));
    const int SIZES = 100, TRIALS = 10;
    ofstream csv("comparison_data.csv");
    csv << "n,n_log_n,insertion_avg,merge_avg,heap_avg\n";
 
    cout << setw(6) << "n"
         << setw(12) << "n*log(n)"
         << setw(14) << "Insertion"
         << setw(12) << "Merge"
         << setw(12) << "Heap" << "\n";
    cout << string(56, '-') << "\n";
 
    for (int s = 0; s < SIZES; s++) {
        int n = 30 + (int)((1000.0 - 30.0) * s / (SIZES - 1));
        double nlogn = n * log2(n);
        double ins=0, mer=0, hea=0;
 
        for (int t = 0; t < TRIALS; t++) {
            vector<int> arr = randArray(n);
            ins += insertionSort(arr);
            mer += mergeSortCount(arr);
            hea += heapSortCount(arr);
        }
        ins /= TRIALS; mer /= TRIALS; hea /= TRIALS;
 
        csv << n << "," << nlogn << "," << ins << "," << mer << "," << hea << "\n";
 
        if (s % 10 == 0)
            cout << setw(6) << n
                 << setw(12) << (long long)nlogn
                 << setw(14) << (long long)ins
                 << setw(12) << (long long)mer
                 << setw(12) << (long long)hea << "\n";
    }
    csv.close();
    cout << "\nFull data saved to comparison_data.csv\n";
    cout << "Use Python/Excel to plot: n vs n*log(n), Insertion, Merge, Heap\n";
 
    // -------- Python plot script --------
    ofstream py("plot_comparisons.py");
    py << "import csv, math\n"
       << "import matplotlib.pyplot as plt\n\n"
       << "ns,nlogn,ins,mer,hea = [],[],[],[],[]\n"
       << "with open('comparison_data.csv') as f:\n"
       << "    next(f)\n"
       << "    for row in csv.reader(f):\n"
       << "        ns.append(int(row[0]))\n"
       << "        nlogn.append(float(row[1]))\n"
       << "        ins.append(float(row[2]))\n"
       << "        mer.append(float(row[3]))\n"
       << "        hea.append(float(row[4]))\n\n"
       << "plt.figure(figsize=(10,6))\n"
       << "plt.plot(ns, ins,   label='Insertion Sort', color='red')\n"
       << "plt.plot(ns, mer,   label='Merge Sort',     color='blue')\n"
       << "plt.plot(ns, hea,   label='Heap Sort',      color='green')\n"
       << "plt.plot(ns, nlogn, label='n log n',        color='black', linestyle='--')\n"
       << "plt.xlabel('Input Size (n)')\n"
       << "plt.ylabel('Average Comparisons')\n"
       << "plt.title('Sorting Algorithm Comparisons vs n log n')\n"
       << "plt.legend()\n"
       << "plt.grid(True)\n"
       << "plt.tight_layout()\n"
       << "plt.savefig('comparison_graph.png', dpi=150)\n"
       << "plt.show()\n"
       << "print('Graph saved as comparison_graph.png')\n";
    py.close();
    cout << "Python plot script saved as plot_comparisons.py\n";
    cout << "Run: python3 plot_comparisons.py  (requires matplotlib)\n";
    return 0;
}
