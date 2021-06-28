#include <stdio.h>
#define MAX_Vertexes 20
#define MAX_Length 20
#define MAX_Element 40

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


// Khai bao cau truc hang doi
typedef struct {
    int data[MAX_Element];
    int front, rear;
} Queue;

void make_null_queue(Queue *Q){
    Q->front = 0;
    Q->rear = -1;
}

void push(Queue *Q, int x){
    Q->rear++;
    Q->data[Q->rear] = x;
}

int top(Queue *Q){
    return Q->data[Q->front];
}

void pop(Queue *Q){
    Q->front++;
}

int empty(Queue *Q){
    return Q->front > Q->rear;
}

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

// Tim lang gieng cua dinh x
List neighbors(Graph *G, int x){
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

int mark[MAX_Vertexes];

void breath_first_search(Graph *G, int x){
    Queue L;
    int mark[MAX_Vertexes];
    make_null_queue(&L);
    int j;
    for(j = 1; j <= G->n; j++){
        mark[j] = 0;
    }
    push(&L, x);
    /* Duyệt 1 */
    printf("Duyet 1\n");
    mark[x] = 1;
    /* Vòng lặp chính dùng để duyệt */
    while (!empty(&L))
    {
        /* Lấy phần tử đầu tiên trong L ra */
        int x = top(&L);
        pop(&L);
        /* Lấy các đỉnh kề của nó */
        List list = neighbors(G, x);
        /* Xét các đỉnh kề của nó */
        for (j = 1; j <= list.size; j++)
        {
            int y = element_at(&list, j);
            if (mark[y] == 0)
            { // y chưa duyệt, duyệt nó
                printf("Duyet %d\n", y);
                mark[y] = 1; //Đánh dấu y đã duyệt
                push(&L, y);
            }
        }
    }
}

int main(){
    //freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
    int i;
    breath_first_search(&G, 1);
    for(i = 2; i <= G.n; i++){
        if(mark[i] == 0){
            breath_first_search(&G, i);
        }
    }
}
