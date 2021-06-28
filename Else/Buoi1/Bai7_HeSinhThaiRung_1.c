#include <stdio.h>
#define MAX_Verticles 20
#define MAX_Length 20
#define MAX_Element 40

// Khai bao cau truc do thi
typedef struct{
    int A[MAX_Verticles][MAX_Length];
    int n; //so luong dinh
}Graph;

// Khai bao cau truc danh sach List
typedef struct{
    int data[MAX_Length];
    int size;
}List;

// Khai bao cau truc ngan xep
typedef struct{
    int data[MAX_Element];
    int size;
}Stack;

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

// in do thi
void print_Graph(Graph G){
    int i, j;
    for(i = 1; i <= G.n; i++){
         for(j = 1; j <= G.n; j++){
            printf("%d ", G.A[i][j]);
        }
        printf("\n");
    }
}

// Kiem tra tinh lien ke
int adjacent(Graph *G, int x, int y){ 
    return (G->A[x][y] != 0);
}

// Tinh bac cua dinh trong do thi
int degree(Graph *G, int x){
    int deg = 0, i;
    for(i = 1; i <= G->n; i++){
        if(G->A[i][x] == 1){    // Ton tai cung
            deg++;
        }  
    }
    return deg;
}

// Tim lang gieng cua dinh x
List neighbor(Graph *G, int x){
    List L;
    int i;
    make_null(&L);
    for(i = 1; i <= G->n; i++){
        if(G->A[i][x] == 1){
            push_back(&L, i);
        }
    }
    return L;   
}

List chung_doi_thu(Graph *G, int x, int y){
	List neighborX;
	make_null(&neighborX);
	neighborX = neighbor(G, x);
	List neighborY;
	make_null(&neighborY);
	neighborY = neighbor(G, y);
	List list;
	make_null(&list);
	int i, j;
	for(i = 0; i < neighborX.size; i++){
		for(j = 0; j < neighborY.size; j++){
			if(neighborX.data[i] == neighborY.data[j]){
				push_back(&list, neighborX.data[i]);
			}
		}
	}
	return list;
}

int main(){
    Graph G;
    List list;
    make_null(&list);
    int n, m, e, u, v, j, x, y;   // n: so luong dinh     m: so luong cung
    //freopen("HeSinhThaiRung.txt", "r", stdin);
    scanf("%d%d", &n, &m);  // doc dinh va cung
    init_Graph(&G, n);
    for(e = 1; e <= m; e++){
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    //Doc 2 loai x và y
	scanf("%d%d", &x, &y);

	list = chung_doi_thu(&G, x, y);
	
	if(list.size != 0)
		for(j = 0; j < list.size; j++){
			printf("%d ", list.data[j]);
		}
	else
		printf("KHONG CHUNG DOI THU");
    return 0;
}