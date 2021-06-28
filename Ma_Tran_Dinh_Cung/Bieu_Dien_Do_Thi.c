#include <stdio.h>
#define MAX_N 100
#define MAX_M 500

typedef struct {
    int A[MAX_N][MAX_M];
    int n, m;
} Graph;

void init_graph(Graph* pG, int n, int m){
    int i, j;
    pG->n = n;
    pG->m = m;
    for(i = 1; i <= n; i++){
        for(j = 1; i <= m; i++){
            pG->A[i][j] = 0;
        }
    }
}

void add_edge(Graph *pG, int e, int x, int y){
    pG->A[x][e] = 1;
    pG->A[y][e] = 1;
}

int degree(Graph *pG, int x){
    int deg = 0, i;
    for(i = 1; i <= pG->m; i++){
        if(pG->A[x][i] == 1){
            deg++;
        }
    }
    return deg;
}

int adjacent(Graph *pG, int x, int y){
    int e;
    for(e = 1; e <= pG->m; e++){
        if(pG->A[x][e] == 1 && pG->A[y][e] == 1){
            return 1;
        }
    }   
    return 0;
}

void neighbours(Graph *pG, int x){
    int i;
    for(i = 1; i <= pG->n; i++){
        if(i == x){
            continue;
        }
        if(adjacent(pG, x, i) == 1){
            printf("%d ", i);
        }
    }
}


int main(){
    Graph G;
    int i, n, m, u, v;
    freopen("dothi.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n, m);
    for(i = 1; i <= m; i++){
        scanf("%d%d", &u, &v);
        printf("%d %d\n", u, v);
        add_edge(&G, i, u, v);
    }
    for(i = 1; i <= n; i++){
        printf("Degree(%d) = %d\n", i, degree(&G, i));
    }
    neighbours(&G, 4);
}