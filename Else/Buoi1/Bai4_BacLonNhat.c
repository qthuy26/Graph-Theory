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

int degree(Graph *G, int x){
    int deg = 0, i;
    for(i = 1; i <= G->n; i++){
        if(G->A[i][x] == 1){    // Ton tai cung
            deg++;
        }  
    }
    return deg;
}


void max_degree(Graph *G){
	int max_index = 1, max = degree(G, 1), i;
	for(i = 1; i <= G->n; i++){
		if(max < degree(G, i)){
			max = degree(G, i);
			max_index = i;
		}
	}
	printf("%d %d", max_index, max);
}

int main(){
    Graph G;
    int n, m;    // n: so luong dinh     m: so luong cung
    //freopen("dothi.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    int u, v, e;
    for(e = 1; e <= m; e++){
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    max_degree(&G);
}