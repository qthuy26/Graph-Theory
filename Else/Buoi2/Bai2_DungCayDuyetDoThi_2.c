#include<stdio.h> 
#define MAX_Vertices 20
#define Max_Length 20
#define Max_Element 40
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

// them cung
void add_edge(Graph *G, int x, int y){
	G->A[x][y] = 1;
	G->A[y][x] = 1;
}

// kiem tra co la lang gieng khong
int adjecent(Graph *G, int x, int y){
	return (G->A[x][y] != 0);
}

// tinh bac cau dinh x cua mot do thi
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

// them mot phan tu (dinh) vao danh sach
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

// khai bao cau truc cua ngan xep
typedef struct{
	int data[Max_Element];
	int size;
}Stack;

// khoi tao ngan xep rong
void make_null_stack(Stack *stack){
	stack->size = 0;
}

// Them mot phan tu vao trong ngan xep
void push_stack(Stack *stack, int x){
	stack->data[stack->size] = x;
	stack->size++;
}

// Lay mot phan tu trong stack
int top(Stack *stack){
	return stack->data[stack->size-1];
}

// Xoa mot phan tu thuoc stack
void pop(Stack *stack){
	stack->size--;
}

// Kiem tra stack co rong hay khong
int empty(Stack *stack){
	return stack->size == 0;
}

// Duyet theo chieu sau
List depth_first_search(Graph *G, int x, int parent[]){
	Stack S;
	make_null_stack(&S);
	push_stack(&S, x);
	parent[x] = 0;
	List list_dfs;
	make_null(&list_dfs);
	int mark[MAX_Vertices];
	int i;
	// khoi tao tat ca cac dinh chua duoc duyet
	for(i=1; i<=G->n; i++)
		mark[i]= 0;
	while(!empty(&S)){
		int u = top(&S);
		pop(&S);
		if(mark[u] == 1)
			continue;
	//	printf("Duyet: %d\n", u);
		push_back(&list_dfs, u);
		mark[u] = 1;
		List list = neighbors(G, u);
		for(i=1; i<=list.size; i++){
			int v = element_at(&list, i);
			if(mark[v] == 0){
				push_stack(&S, v);
				parent[v] = u;
			}
		}
	}
	return list_dfs;
}

int main(){
	Graph G;
//	freopen("DFS_Recursion.txt", "r", stdin);
	int n, m, i, j; // n la so luong dinh; m la so luong cung
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	int u, v, e;
	for(e=1; e<=m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	int parent[MAX_Vertices];
	for(i=1; i<=G.n; i++){
		parent[i] = -1;
	}

	int mark_dfs[MAX_Vertices];
	for(i=1; i<=G.n; i++){
		mark_dfs[i] = 0;
	}
	for(i=1; i<=G.n; i++){
		if(mark_dfs[i] == 0){
			List dfs = depth_first_search(&G, i, parent);
			for(j=1; j<=dfs.size; j++){
				int k = element_at(&dfs, j);
				mark_dfs[k] = 1;
			}				
		}			
	}	
	for(u=1; u<=G.n; u++)
		printf("%d %d\n", u, parent[u]);
	return 0;
}
