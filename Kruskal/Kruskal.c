#include <stdio.h>
#define MAX_M 500
typedef struct{
    int u, v;
    int w;
}Edge;

typedef struct{
    int n, m; // n dinh, m cung
    Edge edge[MAX_M];
}Graph;

void init_graph(Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
}

void add_edge(Graph *pG, int x, int y, int w){
    pG->edge[pG->m].u = x;
    pG->edge[pG->m].v = y;
    pG->edge[pG->m].w = w;
    pG->m++;
}

int parent[100];    
int find_root(int u){
    while(parent[u] != u)
        u = parent[u];
    return u;
}

int Kruskal(Graph *G, Graph *T){
    int i, j;
    for(i = 0; i < G->m-1; i++)
        for(j = i+1; j < G->m; j++)
            if(G->edge[i].w > G->edge[j].w){
                Edge temp = G->edge[i];
                G->edge[i] = G->edge[j];
                G->edge[j] = temp;
            }
    init_graph(T, G->n);
    for(i = 1; i <= G->m; i++)
        parent[i] = i;
    int sum_w = 0;
    int e;
    for(e = 0; e < G->n-1; e++){
        int u = G->edge[e].u;
        int v = G->edge[e].v;
        int w = G->edge[e].w;  
        int root_u = find_root(u);
        int root_v = find_root(v);
        if(root_u != root_v){
            if(u > v)
                add_edge(T, v, u, w);
            else
                add_edge(T, u, v, w);
            parent[root_v] = root_u;
            sum_w += w;
        }
    }
    return sum_w;
}

int main(){
    Graph G, T;
    int n, m, u, v, w, e;
    freopen("dothi.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for(e = 1; e <= m; e++){
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    int sum_w = Kruskal(&G, &T);
    printf("%d\n", sum_w);
    for(e = 0; e < T.m; e++)
        printf("%d %d %d\n", T.edge[e].u, T.edge[e].v, T.edge[e].w);
}