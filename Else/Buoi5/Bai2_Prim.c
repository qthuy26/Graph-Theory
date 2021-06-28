#include <stdio.h>
#define MAX_M 500
typedef struct{
    int n, m; // n dinh, m cung
    int A[MAX_M][MAX_M];
}Graph;

void init_graph(Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
}

void add_edge(Graph *G, int x, int y, int w){
    G->A[x][y] = w;
}

typedef struct {
	int data[100];
	int size;
}List;

void make_null_list(List *list){
	list->size = 0;
}

int element_at(List *list, int x){
	return list->data[x-1];
}

void push_back(List *list, int x){
	list->data[list->size] = x;
	list->size++;
}

int pi[100];
int p[100];
int mark[100];
int Prim(Graph *G, Graph *T){
	init_graph(T, G->n);
	int i, u, v;
	for(u = 1; u <= G->n; u++)
		pi[u] = 999999;
	pi[1] = 0;
	for(v = 1; v <= G->n; v++)
		if(G->A[1][v] != 0){
			pi[v] = G->A[1][v];
			p[v] = 1;
		}
	for(i = 1; i <= G->n; i++)
		mark[i] = 0;
	mark[1] = 1;
	int sum_w = 0;
	for(i = 1; i < G->n; i++){
		int min_dist = 999999, min_u;
		for(u = 1; u <= G->n; u++)
			if(mark[u] == 0){
				if(min_dist > pi[u]){
					min_dist = pi[u];
					min_u = u;					
				}
			}
		u = min_u;
		mark[min_u] = 1;
		add_edge(T, u, p[u], min_dist);
		sum_w += min_dist;
		for(v = 1; v <= G->n; v++)
			if(G->A[u][v] != 0 && mark[v] == 0)
				if(pi[v] > G->A[u][v]){
					pi[v] = G->A[u][v];
					p[v] = u;
				}	
	}
	return sum_w;
}


int main(){
    Graph G, T;
    int n, m, u, v, w, e;
    //freopen("dt.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for(e = 1; e <= m; e++){
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    int sum_w = Prim(&G, &T);
    printf("%d\n", sum_w);
    int i, j;
	for(i = 1; i <= T.n; i++)
    	for(j = 1; j <= T.n; j++)
    		if(T.A[i][j] > 0){
				if(i < j)
    				printf("%d %d %d\n", i, j, T.A[i][j]);
    			else
    				printf("%d %d %d\n", j, i, T.A[i][j]);
    		}
}