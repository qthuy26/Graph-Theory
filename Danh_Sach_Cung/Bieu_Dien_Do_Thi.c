#include <stdio.h>
#define MAX_M 500
typedef struct{
    int u, v;
}Edge;

typedef struct{
    int n, m; // n dinh, m cung
    Edge edge[MAX_M];
}Graph;

void init_graph(Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
}

void add_edge(Graph *pG, int x, int y){
    pG->edge[pG->m].u = x;
    pG->edge[pG->m].v = y;
    pG->m++;
}

int degree(Graph *pG, int x){
    int deg = 0, i;
    for(i = 0; i <= pG->m; i++){
        if((pG->edge[i].u == x) || (pG->edge[i].v == x)){    // Ton tai cung
            deg++;
        }  
    }
    return deg;
}

int adjacent(Graph *pG, int x, int y){
    int i;
    for(i = 0; i <= pG->m; i++){
        if((pG->edge[i].u == x && pG->edge[i].v == y) || (pG->edge[i].u == y && pG->edge[i].v == x))
            return 1;
    }
    return 0;
}

void neighbours(Graph *pG, int x){
    int i;
    for(i = 1; i <= pG->n; i++){
        if(adjacent(pG, i, x)){
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
    neighbours(&G, 2);
}