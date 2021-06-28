#include<stdio.h> 
#define MAX_Vertices 20
#define Max_Length 20
typedef struct{
	int A[MAX_Vertices][MAX_Vertices]; 
	int n;
}Graph; 

// in ma tran
void init_Graph(Graph *G, int n){
	int i, j;
	G->n = n;
	for(i=1; i<=n; i++)
		for(j=1; j<=n;j++)
			G->A[i][j] = 0;
			
}

// them cung vao do thi 
void add_edge(Graph *G, int x, int y){
	G->A[x][y] = 1;
	G->A[y][x] = 1;
}

// kiem tra x va y co la lang gieng khong
int adjecent(Graph *G, int x, int y){
	return (G->A[x][y] != 0);
}

// tinh bac cua dinh x cua mot do thi
int degree(Graph *G, int x){
	int deg=0, i;
	for(i=1; i<=G->n; i++){
		if(G->A[i][x] == 1)
			deg++;
	}
	return deg;
}

// khai bao cau truc danh sach List
typedef struct{
	int data[Max_Length];
	int size;
}List;

// ham khoi tao danh sach rong
void make_null(List *list){
	list->size = 0;
}

// them mot phan tu (dinh) vao cuoi danh sach
void push_back(List *list, int x){
	list->data[list->size] = x;
	list->size++;
}

// Lay mot phan tu (dinh) trong danh sach tai vi tri i
int element_at(List *list, int i){
	return list->data[i-1];
}

// Tim Lang gieng cua dinh x
List neighbors(Graph *G, int x){
	List L;
	make_null(&L);
	int i;
	for(i=1; i<=G->n; i++)
		if(G->A[i][x] == 1){
			push_back(&L, i);	
		}
	return L;
}

int mark[MAX_Vertices];
int parent[MAX_Vertices];

// Duyet theo chieu sau
void DFS_Recursion(Graph *G, int u, int p){
	if(mark[u] == 1)
		return;
	//printf("Duyet: %d\n", u);
	parent[u] = p;
	mark[u] = 1;
	List list = neighbors(G, u);
	int i;
	for(i=1; i<=list.size; i++){
		int v = element_at(&list, i);
		DFS_Recursion(G, v, u);
	}
}

int main(){
	Graph G;
	//freopen("DFS_Recursion.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	int u, v, i;
	for(i=1; i<=m; i++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u,v);
	}
	for(i=1; i<=n; i++){
		mark[i] = 0;
		parent[i] = -1;
	}
	for(i=1; i<=n; i++){
		if(mark[i] == 0)
			DFS_Recursion(&G, i, 0);
	}		
	for(i=1; i<=n; i++){
		printf("%d %d\n", i, parent[i]);
	}
	return 0;
}
