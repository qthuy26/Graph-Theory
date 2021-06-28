#include <stdio.h>
#define MAX_Length 100
#define MAX_VERTICES 100

typedef struct{
	int n;
	int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

//khoi tao do thi
void init_graph(Graph *G, int n){
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
}

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

void copy_list(List *S1, List *S2){
	make_null(S1);
	S1->size = S2->size;
	int i;
	for(i = 0; i < S1->size; i++){
		S1->data[i] = S2->data[i];
	}
}

int rank[MAX_VERTICES];
void ranking(Graph *G){
	int d[MAX_VERTICES];
	int x, u;
	for(u = 1; u <= G->n; u++)
		d[u] = 0;
	for(x = 1; x <= G->n; x++)
		for(u = 1; u <= G->n; u++)
			if(G->A[x][u] != 0)
				d[u]++;
	List S1, S2;
	make_null(&S1);

	for(u = 1; u <= G->n; u++)
		if(d[u] == 0)
			push_back(&S1, u);

	int k=0, i;
	while(S1.size > 0){
		make_null(&S2);
		for(i = 1; i <= S1.size; i++){
			int p = element_at(&S1, i);
			rank[p] = k;
			int v;
			for(v = 1; v <= G->n; v++)
				if(G->A[p][v] != 0){
					d[v]--;
					if(d[v] == 0)
						push_back(&S2, v);
				}
		}
		copy_list(&S1, &S2);
		k++;
	}
}

int main(){
	//freopen("dt.txt", "r", stdin); //Khi n?p bài nh? b? dòng này.
	Graph G;
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);

	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	int i;
	ranking(&G);
	for(i = 1; i <= n; i++){
		printf("%d\n", rank[i]);
	}
}