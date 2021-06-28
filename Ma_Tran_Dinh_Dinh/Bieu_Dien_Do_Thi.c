#include <stdio.h>
#define MAX_N 100
typedef struct{
    int A[MAX_N][MAX_N];
    int n, m;
}Graph;

void init_graph(Graph *pG, int n){
    int i, j;
    pG->n = n;
    for(i = 1; i <= n; i++){
        for(j = 1; j <= n; j++){
            pG->A[i][j] = 0;
        }
    }
}

void add_edge(Graph *pG, int x, int y){
    pG->A[x][y] = 1;
    pG->A[y][x] = 1;
}

int degree(Graph *pG, int x){
    int i, deg = 0;
    for(i = 1; i <= pG->n; i++){
        if(pG->A[x][i] == 1){
            deg++;
        }
    }
    return deg;
}

int adjacent(Graph *pG, int x, int y){
    return (pG->A[x][y] != 0);
}

void neighbours(Graph *pG, int x){
    int i;
    for(i = 1; i <= pG->n; i++){
        if(adjacent(pG, i, x) == 1){
            printf("%d ", i);
        }
    }
}

int main(){
    Graph G;
    int i, n, m, u, v;
    freopen("dothi.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for(i = 1; i <= m; i++){
        scanf("%d%d", &u, &v);
        printf("%d %d\n", u, v);
        add_edge(&G, u, v);
    }
    for(i = 1; i <= n; i++){
        printf("Degree(%d) = %d\n", i, degree(&G, i));
    }
    neighbours(&G, 4);
}