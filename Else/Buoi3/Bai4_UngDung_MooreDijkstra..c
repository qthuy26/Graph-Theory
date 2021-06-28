#include <stdio.h>
#define MAX_Vertexes 20
#define MAX_Length 20
#define MAX_Element 40
#define MAXN 50
#define INFINITY 999999
#define NO_EDGE 0

// Khai bao cau truc do thi
typedef struct{
    int A[MAX_Vertexes][MAX_Length];
    int n; //so luong dinh
}Graph;

// Khai bao cau truc danh sach List
typedef struct{
    int data[MAX_Length];
    int size;
}List;

// Khoi tao danh sach rong
void make_null(List *list){
    list->size = 0;
}

// Them mot phan tu (dinh) vao cuoi danh sach
void push_back(List *list, int x){
    list->data[list->size] = x;
    list->size++;
}


// Lay mot phan tu (dinh) trong danh sach tai vi tri i
int element_at(List *list, int i){
    return list->data[i-1];
}


//khoi tao do thi
void init_graph(Graph *G, int n){
    int i, j;
    G->n = n;
    for(i = 1; i <= n; i++){
        for(j = 1; j <= n; j++){
            G->A[i][j] = NO_EDGE;
        }
    }
}

// them cung vao do thi
void add_edge(Graph *G, int u, int v, int w){
    G->A[u][v] = w;
    G->A[v][u] = w;
}


// Tim lang gieng cua dinh x
List neighbor(Graph *G, int x){
    List L;
    int i;
    make_null(&L);
    for(i = 1; i <= G->n; i++){
        if(G->A[x][i] == 1){
            push_back(&L, i);
        }
    }
    return L;
}

int mark[MAXN];
int pi[MAXN];
int p[MAXN];

void Dijkstra(Graph *G, int s){
    int u, v, it;
    for(u = 1; u <= G->n; u++){
        pi[u] = INFINITY;
        mark[u] = 0;
    }
    pi[s] = 0;
    p[s] = -1;

    for(it = 1; it < G->n; it++){
        int j, min_pi = INFINITY;
        for(j = 1; j <= G->n; j++){
            if(mark[j] == 0 && pi[j] < min_pi){
                min_pi = pi[j];
                u = j;
            }
        }
        mark[u] = 1;
        for(v = 1; v <= G->n; v++){
            if(G->A[u][v] != NO_EDGE && mark[v] == 0){
                if(pi[u] + G->A[u][v] < pi[v]){
                    pi[v] = pi[u] + G->A[u][v];
                    p[v] = u;
                }
            }
        }
    }
}

int main(){
    //freopen("dt.txt", "r", stdin);
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);

	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	int s, t;
	scanf("%d%d", &s, &t);
    Dijkstra(&G, s);
    printf("%d", pi[t]);
}