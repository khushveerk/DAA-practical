// Practical 1: Insertion Sort with Comparison Count
#include <iostream>
using namespace std;
 
int comparisons = 0;
 
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            comparisons++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        comparisons++; // failed while condition
        arr[j + 1] = key;
    }
}
 
int main() {
    int arr[] = {31, 41, 59, 26, 41, 58};
    int n = sizeof(arr) / sizeof(arr[0]);
 
    cout << "Before: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
 
    insertionSort(arr, n);
 
    cout << "After:  ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
 
    cout << "Number of comparisons: " << comparisons << endl;
 
    return 0;
}

// Practical 2: Merge Sort with Comparison Count
#include <iostream>
using namespace std;
 
int comparisons = 0;
 
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
 
    int L[10], R[10]; // temp arrays
 
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
 
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }
}
 
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
 
int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
 
    cout << "Before: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
 
    mergeSort(arr, 0, n - 1);
 
    cout << "After:  ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
 
    cout << "Number of comparisons: " << comparisons << endl;
 
    return 0;
}

// Practical 3: Heap Sort with Comparison Count
#include <iostream>
using namespace std;
 
int comparisons = 0;
 
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
 
    if (l < n) {
        comparisons++;
        if (arr[l] > arr[largest]) largest = l;
    }
    if (r < n) {
        comparisons++;
        if (arr[r] > arr[largest]) largest = r;
    }
 
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
 
void heapSort(int arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    // Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
 
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
 
    cout << "Before: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
 
    heapSort(arr, n);
 
    cout << "After:  ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
 
    cout << "Number of comparisons: " << comparisons << endl;
 
    return 0;
}

// Practical 4: Quick Sort with Comparison Count
#include <iostream>
using namespace std;
 
int comparisons = 0;
 
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // last element as pivot
    int i = low - 1;
 
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
 
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
 
int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
 
    cout << "Before: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
 
    quickSort(arr, 0, n - 1);
 
    cout << "After:  ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
 
    cout << "Number of comparisons: " << comparisons << endl;
 
    return 0;
}

// Practical 5: Strassen's Matrix Multiplication
// Works for 2x2 matrices (simplest case to demonstrate Strassen)
#include <iostream>
using namespace std;
 
void strassen(int A[2][2], int B[2][2], int C[2][2]) {
    // 7 Strassen products
    int M1 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
    int M2 = (A[1][0] + A[1][1]) *  B[0][0];
    int M3 =  A[0][0] * (B[0][1] - B[1][1]);
    int M4 =  A[1][1] * (B[1][0] - B[0][0]);
    int M5 = (A[0][0] + A[0][1]) *  B[1][1];
    int M6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);
    int M7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);
 
    // Result matrix
    C[0][0] = M1 + M4 - M5 + M7;
    C[0][1] = M3 + M5;
    C[1][0] = M2 + M4;
    C[1][1] = M1 - M2 + M3 + M6;
}
 
void printMatrix(int M[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            cout << M[i][j] << " ";
        cout << endl;
    }
}
 
int main() {
    int A[2][2] = {{1, 2}, {3, 4}};
    int B[2][2] = {{5, 6}, {7, 8}};
    int C[2][2] = {{0, 0}, {0, 0}};
 
    cout << "Matrix A:" << endl;
    printMatrix(A);
 
    cout << "Matrix B:" << endl;
    printMatrix(B);
 
    strassen(A, B, C);
 
    cout << "Result C = A x B (Strassen):" << endl;
    printMatrix(C);
 
    // Verify with normal multiplication
    cout << "Verification (normal multiply):" << endl;
    int V[2][2] = {{0,0},{0,0}};
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                V[i][j] += A[i][k] * B[k][j];
    printMatrix(V);
 
    return 0;
}

// Practical 6: Count Sort
#include <iostream>
using namespace std;
 
void countSort(int arr[], int n) {
    // Find max element
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];
 
    // Create count array
    int count[100] = {0};
 
    // Count occurrences
    for (int i = 0; i < n; i++)
        count[arr[i]]++;
 
    // Modify count to store actual positions
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];
 
    // Build output array
    int output[10];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
 
    // Copy back to arr
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}
 
int main() {
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
 
    cout << "Before: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
 
    countSort(arr, n);
 
    cout << "After:  ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
 
    return 0;
}

// Practical 7: Breadth First Search (BFS)
#include <iostream>
using namespace std;
 
int adj[10][10]; // adjacency matrix
bool visited[10];
int queue[10];
int front = 0, rear = 0;
 
void bfs(int start, int V) {
    visited[start] = true;
    queue[rear++] = start;
 
    cout << "BFS Traversal: ";
    while (front < rear) {
        int node = queue[front++];
        cout << node << " ";
 
        for (int i = 0; i < V; i++) {
            if (adj[node][i] == 1 && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }
    cout << endl;
}
 
int main() {
    int V = 6; // number of vertices (0 to 5)
 
    // Define edges (undirected graph)
    // Edge list: {u, v}
    int edges[][2] = {
        {0, 1}, {0, 2},
        {1, 3}, {1, 4},
        {2, 5}
    };
    int E = sizeof(edges) / sizeof(edges[0]);
 
    // Build adjacency matrix
    for (int i = 0; i < E; i++) {
        int u = edges[i][0], v = edges[i][1];
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
 
    // Print adjacency matrix
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            cout << adj[i][j] << " ";
        cout << endl;
    }
    cout << endl;
 
    bfs(0, V); // start BFS from vertex 0
 
    return 0;
}

// Practical 8: Depth First Search (DFS)
#include <iostream>
using namespace std;
 
int adj[10][10]; // adjacency matrix
bool visited[10];
 
void dfs(int node, int V) {
    visited[node] = true;
    cout << node << " ";
 
    for (int i = 0; i < V; i++) {
        if (adj[node][i] == 1 && !visited[i])
            dfs(i, V);
    }
}
 
int main() {
    int V = 6; // number of vertices (0 to 5)
 
    // Define edges (undirected graph)
    int edges[][2] = {
        {0, 1}, {0, 2},
        {1, 3}, {1, 4},
        {2, 5}
    };
    int E = sizeof(edges) / sizeof(edges[0]);
 
    // Build adjacency matrix
    for (int i = 0; i < E; i++) {
        int u = edges[i][0], v = edges[i][1];
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
 
    // Print adjacency matrix
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            cout << adj[i][j] << " ";
        cout << endl;
    }
    cout << endl;
 
    cout << "DFS Traversal: ";
    dfs(0, V); // start DFS from vertex 0
    cout << endl;
 
    return 0;
}

// Practical 9: Prim's Algorithm - Minimum Spanning Tree
#include <iostream>
using namespace std;
 
#define INF 9999
#define V 5  // number of vertices
 
int graph[V][V] = {
    {0,   2,   0,   6,   0},
    {2,   0,   3,   8,   5},
    {0,   3,   0,   0,   7},
    {6,   8,   0,   0,   9},
    {0,   5,   7,   9,   0}
};
 
void primMST() {
    int parent[V];   // stores MST
    int key[V];      // min weight to include vertex
    bool inMST[V];   // whether vertex is in MST
 
    // Initialize
    for (int i = 0; i < V; i++) {
        key[i] = INF;
        inMST[i] = false;
    }
 
    key[0] = 0;
    parent[0] = -1; // root has no parent
 
    for (int count = 0; count < V - 1; count++) {
        // Pick vertex with minimum key not yet in MST
        int u = -1;
        for (int v = 0; v < V; v++)
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;
 
        inMST[u] = true;
 
        // Update key values of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }
 
    // Print MST
    int totalWeight = 0;
    cout << "Edge\tWeight" << endl;
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << "\t" << graph[parent[i]][i] << endl;
        totalWeight += graph[parent[i]][i];
    }
    cout << "Total MST Weight: " << totalWeight << endl;
}
 
int main() {
    cout << "Graph (Adjacency Matrix):" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            cout << graph[i][j] << " ";
        cout << endl;
    }
    cout << endl;
 
    cout << "Minimum Spanning Tree (Prim's):" << endl;
    primMST();
 
    return 0;
}


// Practical 10: Dijkstra's Shortest Path Algorithm
#include <iostream>
using namespace std;
 
#define INF 9999
#define V 5  // number of vertices
 
int graph[V][V] = {
    {0,  10,  0,   0,   5},
    {0,   0,  1,   0,   2},
    {0,   0,  0,   4,   0},
    {7,   0,  6,   0,   0},
    {0,   3,  9,   2,   0}
};
 
void dijkstra(int src) {
    int dist[V];     // shortest distance from src
    bool visited[V]; // whether vertex is finalized
 
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = false;
    }
 
    dist[src] = 0;
 
    for (int count = 0; count < V - 1; count++) {
        // Pick unvisited vertex with min distance
        int u = -1;
        for (int v = 0; v < V; v++)
            if (!visited[v] && (u == -1 || dist[v] < dist[u]))
                u = v;
 
        visited[u] = true;
 
        // Update distances of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !visited[v] && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }
 
    // Print result
    cout << "Shortest distances from vertex " << src << ":" << endl;
    cout << "Vertex\tDistance" << endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) cout << i << "\tUnreachable" << endl;
        else cout << i << "\t" << dist[i] << endl;
    }
}
 
int main() {
    cout << "Graph (Adjacency Matrix):" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            cout << graph[i][j] << " ";
        cout << endl;
    }
    cout << endl;
 
    dijkstra(0); // find shortest path from vertex 0
 
    return 0;
}

// Practical 11: 0-1 Knapsack Problem (Dynamic Programming)
#include <iostream>
using namespace std;
 
int main() {
    int weight[] = {2, 3, 4, 5};   // weights of items
    int value[]  = {3, 4, 5, 6};   // values of items
    int n = 4;                      // number of items
    int W = 8;                      // knapsack capacity
 
    // dp[i][w] = max value using first i items with capacity w
    int dp[10][10] = {0};
 
    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            // Don't include item i
            dp[i][w] = dp[i-1][w];
            // Include item i (if it fits)
            if (weight[i-1] <= w) {
                int include = dp[i-1][w - weight[i-1]] + value[i-1];
                if (include > dp[i][w])
                    dp[i][w] = include;
            }
        }
    }
 
    // Print DP table
    cout << "DP Table:" << endl;
    cout << "     ";
    for (int w = 0; w <= W; w++) cout << w << "  ";
    cout << endl;
    for (int i = 0; i <= n; i++) {
        cout << "i=" << i << ": ";
        for (int w = 0; w <= W; w++)
            cout << dp[i][w] << "  ";
        cout << endl;
    }
 
    cout << "\nMaximum Value: " << dp[n][W] << endl;
 
    // Traceback to find selected items
    cout << "Items Selected:" << endl;
    int w = W;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            cout << "  Item " << i
                 << " (weight=" << weight[i-1]
                 << ", value=" << value[i-1] << ")" << endl;
            w -= weight[i-1];
        }
    }
 
    return 0;
}
--------------------------------------------------------------------------------------------------
  
