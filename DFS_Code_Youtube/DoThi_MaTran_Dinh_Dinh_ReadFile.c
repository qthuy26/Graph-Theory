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

// Kiem tra tinh lien ke
int adjacent(Graph *G, int x, int y){ 
    return (G->A[x][y] != 0);
}

// Tinh bac cua dinh trong do thi
int degree(Graph *G, int x){
    int deg = 0, i;
    for(i = 1; i <= G->n; i++){
        if(G->A[i][x] == 1){    // Ton tai cung
            deg++;
        }  
    }
    return deg;
}

int main(){
    Graph G;
    int i, n, m;    // n: so luong dinh     m: so luong cung
    FILE* file = fopen("dothi.txt", "r");
    fscanf(file, "%d%d", &n, &m);
    init_Graph(&G, n);
    int u, v, e;
    for(e = 1; e <= m; e++){
        fscanf(file, "%d%d", &u, &v);
        // printf("%d %d\n", u, v);
        add_edge(&G, u, v);
    }
    fclose(file);
    // add_edge(&G, 2, 6);
    // add_edge(&G, 6, 4);
    // add_edge(&G, 5, 6);
    // add_edge(&G, 1, 4);
    // add_edge(&G, 1, 5);
    // add_edge(&G, 2, 3);
    // add_edge(&G, 2, 4);
    // add_edge(&G, 4, 5);
    for(i = 1; i <= G.n; i++){
        printf("degree(%d) = %d\n", i, degree(&G, i));
    }
}
