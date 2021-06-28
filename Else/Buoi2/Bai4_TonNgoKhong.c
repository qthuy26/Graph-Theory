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

int num[MAX_Verticles];
int min_num[MAX_Verticles];
int on_stack[MAX_Verticles];
int k=0, count = 0;
// Duyet do thi bat dau tu dinh x
void strong_connect(Graph *G, int x){
    Stack S;
    make_null_stack(&S);
    int j;
    num[x] = min_num[x] = ++k;
    push_stack(&S, x);
    on_stack[x] = 1;

    List list = neighbor(G, x);
    for(j = 1; j <= list.size; j++){
        int y = element_at(&list, j);
        if(num[y] < 0){
            strong_connect(G, y);
            min_num[x] = min(min_num[x], min_num[y]);
        }
        else if(on_stack[y]){
            min_num[x] = min(min_num[x], num[y]);
        }
    }
    if(num[x] == min_num[x]){
        int w;
        do{
            w = top(&S);
            pop(&S);
            on_stack[w] = 0;
        } while(w != x);
    }
}

int main(){
    Graph G;
    int n, m;
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    int u, v, i;
    for(i = 1; i <= m; i++){
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    for(i = 1; i <= n; i++){
        num[i] = -1;
        on_stack[i] = 0;
    }
    for(i = 1; i <= n; i++){
        if(num[i] == -1){
            count++;
            strong_connect(&G, i);
        }
    }
    if(count == 1)
        printf("DUOC");
    else printf("KHONG");
    return 0;
}
