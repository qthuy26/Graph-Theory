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

// Khoi tao ngan xep rong
void make_null_stack(Stack *stack){
    stack->size = 0;
}

// Kiem tra stack rong
int empty_stack(Stack *stack){
    return stack->size == 0;   
}

// Them mot phan tu vao trong ngan xep
void push_stack(Stack *stack, int x){
    stack->data[stack->size] = x;
    stack->size++;
}

// Lay mot phan tu nam trong stack
int top(Stack *stack){
    return stack->data[stack->size - 1];
}

// Xoa mot phan tu nam trong stack
void pop(Stack *stack){
    stack->size--;
}

// Duyet do thi theo chieu sau
List depth_first_search(Graph *G, int x, int parent[]){
    Stack S;
    make_null_stack(&S);
    push_stack(&S, x);
    parent[x] = 0;
    List list_dfs;
    make_null(&list_dfs);
    int mark[MAX_Verticles];    // Khoi tao cac dinh chua duoc duyet
    int i, j;
    for(i = 1; i <= G->n; i++)
        mark[i] = 0;
    while(!empty_stack(&S)){
        int u = top(&S);
        pop(&S);
        if(mark[u] == 1)
            continue;
        push_back(&list_dfs, u);
        mark[u] = 1;
        List list = neighbor(G, u);
        for(i = 1; i <= list.size; i++){
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
    int n, m, e, u, v, i, j;   // n: so luong dinh     m: so luong cung
    freopen("DFS.txt", "r", stdin);
    scanf("%d%d", &n, &m);  // doc dinh va cung
    init_Graph(&G, n);
    for(e = 1; e <= m; e++){
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    int parent[MAX_Verticles];
    for(i = 1; i <= G.n; i++){
        parent[i] = -1;
    }
    int mark_dfs[MAX_Verticles];
    for(i = 1; i <= G.n; i++){
        mark_dfs[i] = 0;
    }
    for(i = 1; i <= G.n; i++){
        if(mark_dfs[i] == 0){
            List dfs = depth_first_search(&G, i, parent);
            for(j = 1; j <= dfs.size; j++){
                printf("Duyet: %d\n", element_at(&dfs, j));
                mark_dfs[element_at(&dfs, j)] = 1;
            }
        }
    }
    for(i = 1; i <= G.n; i++){
        printf("%d %d\n", i, parent[i]);
    }
    return 0;
}
