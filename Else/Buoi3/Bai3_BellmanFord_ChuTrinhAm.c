#include <stdio.h>
#include <stdio.h>
#define MAX_Vertexes 20
#define MAX_Length 20
#define MAX_Element 40
#define MAXN 50
#define INFINITY 999999

typedef struct{
    int u, v;
    int w;
}Edge;

// Khai bao cau truc do thi
typedef struct{
    int n, m; //so luong dinh
    Edge edges[MAXN];
}Graph;


//khoi tao do thi
void init_graph(Graph *G, int n, int m){
    G->n = n;
    G->m = 0;
}

// them cung vao do thi
void add_edge(Graph *G, int u, int v, int w){
    G->edges[G->m].u = u;
    G->edges[G->m].v = v;
    G->edges[G->m].w = w;
    G->m++;
}


int pi[MAXN];
int p[MAXN];

void BellmanFord(Graph *G, int s){
    int u, v, w, it, k;
    for(u = 1; u <= G->n; u++){
        pi[u] = INFINITY;
    }
    pi[s] = 0;
    p[s] = -1;
    for(it = 1; it < G->n; it++){
        for(k = 0; k < G->m; k++){
            u = G->edges[k].u;
            v = G->edges[k].v;
            w = G->edges[k].w;
            if(pi[u] + w < pi[v]){
                pi[v] = pi[u] + w;
                p[v] = u;
            }
        }
    }
}

int main(){
    //freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n, m);

	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
    BellmanFord(&G, 1);
    if(pi[n] < 0)
        printf("negative cycle");
    else
        printf("ok");
}