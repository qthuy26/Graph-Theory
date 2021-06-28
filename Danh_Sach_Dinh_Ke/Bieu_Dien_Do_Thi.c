#include <stdio.h>
#define MAX_N 100
#define MAX_M 500

typedef struct {
    int data[MAX_N];
    int size;
} List;

typedef struct {
    List adj[MAX_N]; //mảng các danh sách
    int n, m;
} Graph;

void make_null(List *pL){
    pL->size = 0;
}

void push_back(List *pL, int x){
    pL->data[pL->size] = x;
    pL->size++;
}

int element_at(List *pL, int p){
    return pL->data[p];
}

int size(List *pL){
    return pL->size;
}

void init_graph(Graph *pG, int n, int m){
    int i;
    for(i = 1; i <= n; i++){
        make_null(&pG->adj[i]);
    }
}

void add_edge(Graph *pG, int x, int y){
    pG->adj[x].data[x] = y;
    pG->adj[y].data[y] = x;
}

int degree(Graph *pG, int x){
    return pG->adj[x].size;
}

int adjacent(Graph *pG, int x, int y){
    int i;
    for(i = 1; i <= pG->n; i++){
        if(element_at(&pG->adj[x], i) == y)
            return 1;
    }
    return 0;
}

void neighbours(Graph *pG, int x){
    int i;
    for(i = 1; i <= pG->n; i++){
        printf("%d ", pG->adj[x].data[i]);
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
        //printf("%d %d\n", u, v);
        add_edge(&G, u, v);
    }
    // for(i = 1; i <= n; i++){
    //     printf("Degree(%d) = %d\n", i, degree(&G, i));
    // }
    printf("%d ", degree(&G, 4));
    //neighbours(&G, 2);
}