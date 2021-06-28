#include <stdio.h>
#define MAX_Verticles 20
#define MAX_Length 20
typedef struct{
    int A[MAX_Verticles][MAX_Length];
    int n; //so luong dinh
}Graph;

//khoi tao do thi
void init_Graph(Graph *G, int n){
    int i, j;
    G->n = n;
    for(i = 1; i <= n; i++){
        for(j = 1; j <= n; j++){
            G->A[i][j] = 0;
        }
    }
}

// them cung vao do thi
void add_edge(Graph *G, int x, int y){
    G->A[x][y] = 1;
    G->A[y][x] = 1;
}

// in do thi
void print_Graph(Graph G){
    int i, j;
    for(i = 1; i <= G.n; i++){
         for(j = 1; j <= G.n; j++){
            printf("%d ", G.A[i][j]);
        }
        printf("\n");
    }
}

int main(){
    Graph G;
    int n, m;    // n: so luong dinh     m: so luong cung
    freopen("dt1.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    int u, v, e;
    for(e = 1; e <= m; e++){
        scanf("%d%d", &u, &v);
        //printf("%d %d\n", u, v);
        add_edge(&G, u, v);
    }
    print_Graph(G);
}