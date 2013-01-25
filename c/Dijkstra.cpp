#include <cstdio>
#define INFINITY 10001

int G[6][6] = {
    { INFINITY, INFINITY, 10,       INFINITY, 30,       100 },
    { INFINITY, INFINITY, 5,        INFINITY, INFINITY, INFINITY },
    { INFINITY, INFINITY, INFINITY, 50,       INFINITY, INFINITY },
    { INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 10 },
    { INFINITY, INFINITY, INFINITY, 20,       INFINITY, 60 },
    { INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY }
};

void Showpath(int path[], int n) {
    if (n == 0) {
        printf("A%d", n);
    } else {
        Showpath(path, path[n]);
        printf(" -> A%d", n);
    }
}

void Dijkstra() {
    int dist[6], s[6] = {0}, path[6], i, w;   

    for (i = 0; i < 6; ++i)  {  
        dist[i] =  G[0][i];
        path[i] = 0;
    }   
    dist[0] = 0; 
    s[0] = 1;    

    for (i = 1; i < 6; ++i) {
        int v, min = INFINITY;    

        for (w = 0; w < 6; ++w) { 
            if (!s[w] && (dist[w] < min)) { v = w; min = dist[w]; }
        }
        s[v] = 1; 
        
        for (w = 0; w < 6; ++w) { 
            if (!s[w] && (min + G[v][w] < dist[w])) {
                dist[w] = min + G[v][w];
                path[w] = v;
            } 
        } 
    } 
    
    Showpath(path, 5);
    printf("\nThe shorest path %d ", dist[5]);
}

int main() {
    Dijkstra();

    return 0;
}
