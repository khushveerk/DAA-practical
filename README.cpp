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
----------------------------------------------------------------------------------------------------

 // Practical 7: Breadth-First Search (BFS)
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 
void bfs(const vector<vector<int>>& adj, int start, int V) {
    vector<bool> visited(V, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);
 
    cout << "BFS traversal from vertex " << start << ": ";
    while (!q.empty()) {
        int v = q.front(); q.pop();
        cout << v << " ";
        for (int u : adj[v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }
    cout << endl;
}
 
int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;
 
    vector<vector<int>> adj(V);
    cout << "Enter " << E << " edges (u v):\n";
    for (int i=0; i<E; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    int start;
    cout << "Enter starting vertex: ";
    cin >> start;
 
    bfs(adj, start, V);
    return 0;
}
/* edges come in pairs. 
Enter number of vertices and edges: 5 4
Enter 4 edges (u v):
0 1
1 2
2 3
3 4
Enter starting vertex: 0
 */
-------------------------------------------------------------------------------------------------------------

 // Practical 8: Depth-First Search (DFS)
#include <iostream>
#include <vector>
using namespace std;
 
void dfsUtil(const vector<vector<int>>& adj, int v, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";
    for (int u : adj[v])
        if (!visited[u]) dfsUtil(adj, u, visited);
}
 
void dfs(const vector<vector<int>>& adj, int start, int V) {
    vector<bool> visited(V, false);
    cout << "DFS traversal from vertex " << start << ": ";
    dfsUtil(adj, start, visited);
    cout << endl;
}
 
int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;
 
    vector<vector<int>> adj(V);
    cout << "Enter " << E << " edges (u v):\n";
    for (int i=0; i<E; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    int start;
    cout << "Enter starting vertex: ";
    cin >> start;
 
    dfs(adj, start, V);
    return 0;
}
----------------------------------------------------------------------------------------------------------
// Practical 9: Prim's Algorithm - Minimum Spanning Tree
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
 
void primMST(const vector<vector<pair<int,int>>>& adj, int V) {
    vector<int> key(V, INT_MAX), parent(V, -1);
    vector<bool> inMST(V, false);
    key[0] = 0;
 
    for (int count=0; count<V-1; count++) {
        // Pick min key vertex not yet in MST
        int u = -1;
        for (int v=0; v<V; v++)
            if (!inMST[v] && (u==-1 || key[v] < key[u])) u = v;
 
        inMST[u] = true;
 
        for (auto [v, w] : adj[u]) {
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
            }
        }
    }
 
    cout << "\nMinimum Spanning Tree edges:\n";
    cout << "Edge\t\tWeight\n";
    int total = 0;
    for (int v=1; v<V; v++) {
        cout << parent[v] << " - " << v << "\t\t" << key[v] << "\n";
        total += key[v];
    }
    cout << "Total MST weight: " << total << endl;
}
 
int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;
 
    vector<vector<pair<int,int>>> adj(V);
    cout << "Enter " << E << " edges (u v weight):\n";
    for (int i=0; i<E; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
 
    primMST(adj, V);
    return 0;
}
/* Enter number of vertices and edges: 4 5
Enter 5 edges (u v weight):
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4
Enter starting vertex: 0
 */

------------------------------------------------------------------------------------------------------------------

 // Practical 10: Dijkstra's Algorithm - Shortest Path
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
 
void dijkstra(const vector<vector<pair<int,int>>>& adj, int src, int V) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});
 
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
 
    cout << "\nShortest distances from vertex " << src << ":\n";
    cout << "Vertex\tDistance\n";
    for (int i=0; i<V; i++) {
        if (dist[i] == INT_MAX) cout << i << "\tUnreachable\n";
        else cout << i << "\t" << dist[i] << "\n";
    }
}
 
int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;
 
    vector<vector<pair<int,int>>> adj(V);
    cout << "Enter " << E << " edges (u v weight):\n";
    for (int i=0; i<E; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // remove this line for directed graph
    }
 
    int src;
    cout << "Enter source vertex: ";
    cin >> src;
 
    dijkstra(adj, src, V);
    return 0;
}
/* Enter number of vertices and edges: 5 6
Enter 6 edges (u v weight):
0 1 4
0 2 2
1 2 1
1 3 5
2 4 3
3 4 1
Enter source vertex: 0
 */ 

-----------------------------------------------------------------------------------------------------------------------
// Practical 11: Weighted Interval Scheduling (Dynamic Programming)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
struct Interval {
    int start, end, weight;
};
 
// Binary search: latest interval that ends <= start of interval i
int latestCompatible(const vector<Interval>& jobs, int i) {
    int lo=0, hi=i-1;
    while (lo <= hi) {
        int mid = (lo+hi)/2;
        if (jobs[mid].end <= jobs[i].start) {
            if (jobs[mid+1].end <= jobs[i].start) lo = mid+1;
            else return mid;
        } else hi = mid-1;
    }
    return -1;
}
 
int main() {
    int n;
    cout << "Enter number of intervals: ";
    cin >> n;
 
    vector<Interval> jobs(n);
    cout << "Enter each interval as: start end weight\n";
    for (auto& j : jobs) cin >> j.start >> j.end >> j.weight;
 
    // Sort by finish time
    sort(jobs.begin(), jobs.end(), [](const Interval& a, const Interval& b){
        return a.end < b.end;
    });
 
    vector<int> dp(n+1, 0);
    for (int i=1; i<=n; i++) {
        int p = latestCompatible(jobs, i-1);
        int include = jobs[i-1].weight + (p >= 0 ? dp[p+1] : 0);
        dp[i] = max(dp[i-1], include);
    }
 
    cout << "\nMaximum weight from scheduled intervals: " << dp[n] << endl;
 
    // Traceback selected intervals
    cout << "Selected intervals (start, end, weight):\n";
    int i = n;
    while (i > 0) {
        int p = latestCompatible(jobs, i-1);
        int include = jobs[i-1].weight + (p >= 0 ? dp[p+1] : 0);
        if (include >= dp[i-1]) {
            cout << "  [" << jobs[i-1].start << ", " << jobs[i-1].end
                 << "] weight=" << jobs[i-1].weight << "\n";
            i = (p >= 0) ? p+1 : 0;
        } else {
            i--;
        }
    }
    return 0;
}
/* Enter number of intervals: 4
Enter each interval as: start end weight
1 3 5
2 5 6
4 7 5
6 8 4

 What these intervals look like on a timeline:
Time:  1  2  3  4  5  6  7  8
Job1:  [-----]              w=5
Job2:     [---------]       w=6
Job3:          [-----]      w=5
Job4:                [---]  w=4

*/
------------------------------------------------------------------------------------------------------------

 // Practical 12: 0-1 Knapsack Problem (Dynamic Programming)
#include <iostream>
#include <vector>
using namespace std;
 
int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter knapsack capacity: ";
    cin >> W;
 
    vector<int> weight(n), value(n);
    cout << "Enter weight and value of each item:\n";
    for (int i=0; i<n; i++) {
        cout << "Item " << i+1 << " (weight value): ";
        cin >> weight[i] >> value[i];
    }
 
    // DP table
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));
    for (int i=1; i<=n; i++) {
        for (int w=0; w<=W; w++) {
            dp[i][w] = dp[i-1][w]; // don't include item i
            if (weight[i-1] <= w)
                dp[i][w] = max(dp[i][w], dp[i-1][w-weight[i-1]] + value[i-1]);
        }
    }
 
    cout << "\nMaximum value: " << dp[n][W] << endl;
 
    // Traceback selected items
    cout << "Items selected:\n";
    int w = W;
    for (int i=n; i>0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            cout << "  Item " << i << " (weight=" << weight[i-1]
                 << ", value=" << value[i-1] << ")\n";
            w -= weight[i-1];
        }
    }
 
    // Print DP table (for small inputs)
    if (n <= 8 && W <= 15) {
        cout << "\nDP Table:\n   ";
        for (int j=0; j<=W; j++) cout << j << "\t";
        cout << "\n";
        for (int i=0; i<=n; i++) {
            cout << i << ": ";
            for (int j=0; j<=W; j++) cout << dp[i][j] << "\t";
            cout << "\n";
        }
    }
    return 0;
}
/* Enter number of items: 4
Enter knapsack capacity: 10
Enter weight and value of each item:
Item 1 (weight value): 2 6
Item 2 (weight value): 2 10
Item 3 (weight value): 3 12
Item 4 (weight value): 5 13
*/
 
