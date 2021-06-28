#include <stdio.h>
#include <stdio.h>
#define MAX_VERTICES 100

typedef struct {
    int n;
    int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

/* Khoi tao do thi G co n dinh */
void init_graph(Graph* G, int n) {
    int i, j;
    G->n = n;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->A[i][j] = 0;
}

/* Them cung e = (x, y) vao do thi G */
void add_edge(Graph* G, int x, int y) {
    G->A[x][y] = 1; //y ke voi x
}

/* Kiem tra y co ke voi x khong */
int adjacent(Graph* G, int x, int y) {
    return G->A[x][y] != 0;
}

/* Tinh bac cua dinh x: deg(x) */
int degree(Graph* G, int x) {
    int y, deg = 0;
    for (y = 1; y <= G->n; y++)
        if (G->A[x][y] > 0)
            deg+=G->A[x][y];
    return deg;
}

/* KHAI BAO VA DINH NGHIA CTDL DANH SACH */
#define MAX_ELEMENTS 100
typedef struct {
    int data[MAX_ELEMENTS];
    int size;
} List;

/* Tao danh sach rong */
void make_null_list(List* L) {
    L->size = 0;
}

/* Them mot phan tu vao cuoi danh sach */
void push_back(List* L, int x) {
    L->data[L->size] = x;
    L->size++;
}

/* Lay phan tu tai vi tri i, phan tu bat dau o vi tri 1*/
int element_at(List* L, int i) {
    return L->data[i-1];
}

/* Tra ve so phan tu cua danh sach */
int count_list(List* L) {
    return L->size;
}

/* Tim cac dinh ke cua dinh x */
List neighbors(Graph* G, int x) {
    int y;
    List list;
    make_null_list(&list);
    for (y = 1; y <= G->n; y++)
        if (adjacent(G, x, y))
            push_back(&list, y);
    return list;
}

void copy_list(List *L1, List *L2){
    make_null_list(L1);
    int i;
    for(i=1;i<=L2->size;i++)
        push_back(L1,element_at(L2,i));
}

#define oo 9999999
// Ham min
int min(int a,int b){
    return a < b ? a : b;
}

// Ham max
int max(int a , int b){
    return a > b ? a : b;
}

/* Khai bao Queue */
#define MAX_ELEMENTS 100
typedef struct {
    int data[MAX_ELEMENTS];
    int front, rear;
} Queue;

void make_null_queue(Queue* Q) {
    Q->front = 0;
    Q->rear = -1;
}

void push(Queue* Q, int x) {
    Q->rear++;
    Q->data[Q->rear] = x;
}

int top(Queue* Q) {
    return Q->data[Q->front];
}
void pop(Queue* Q) {
    Q->front++;
}

int empty_queue(Queue* Q) {
    return Q->front > Q->rear;
}

int d[MAX_VERTICES];
void topo_sort(Graph *G,List *L){
    //Tinh d[u]
    int d[MAX_VERTICES];
    int x, u;
    for (u = 1; u <= G->n; u++)
        d[u] = 0;
    for (x = 1; x <= G->n; x++)
        for (u = 1; u <= G->n; u++)
            if (G->A[x][u] != 0)
                d[u]++;
    Queue Q;
    make_null_queue(&Q);
    for(u=1;u<=G->n;u++)
        if(d[u]==0)
            push(&Q,u);
    make_null_list(L);
    while(!empty_queue(&Q)){
        int u = top(&Q);
        pop(&Q);
        push_back(L,u);
        List list = neighbors(G,u);
        for(x=1;x<=list.size;x++){
            int v = element_at(&list,x);
            d[v]--;
            if(d[v]==0)
                push(&Q,v);
        }
    }
}

int main() {
    Graph G;
    int n, u, x, v, j ;
    List L;
    // FILE* file = fopen("duanphanmem1.txt", "r");
    scanf("%d", &n);
    init_graph(&G, n+2);
    d[n+1] = 0;
    for (u = 1; u <= n; u++) {
        scanf("%d",&d[u]);
        do {
            scanf("%d", &x);
            if (x > 0) 
                add_edge(&G, x, u);
        }while (x > 0);
    }
    for (u = 1; u <= n; u++) {
        int deg_neg = 0;
        for (x = 1; x <= n; x++)
            if (G.A[x][u] > 0)
                deg_neg++;
        if (deg_neg == 0)
            add_edge(&G, n+1, u);
    }
    for (u = 1; u <= n; u++) {
        int deg_pos = 0;
        for (v = 1; v <= n; v++)
            if (G.A[u][v] > 0)
                deg_pos++;
        if (deg_pos == 0)
            add_edge(&G, u, n+2);
    }
    topo_sort(&G,&L);
    int t[MAX_VERTICES];
    t[n+1] = 0;
    for (j = 2; j <= L.size; j++) {
        int u = element_at(&L, j);
        t[u] = -1;
        for (x = 1; x <= G.n; x++)
            if (G.A[x][u] > 0)
                t[u] = max(t[u], t[x] + d[x]);
    }
    int T[MAX_VERTICES];
    T[n+2] = t[n+2];
    for (j = L.size-1 ; j >= 1; j --) {
        int u = element_at(&L, j);
        T[u] = oo;
        for (v = 1; v <= G.n; v++)
            if (G.A[u][v] > 0)
                T[u] = min(T[u], T[v] - d[u]);
    }
    //printf("%d\n",t[G.n]);
    int a,b;
    scanf("%d %d",&a,&b);
    /* for(u =1; u<=G.n;u++){
        if (t[u]==T[u])
            printf("%d\n",u);
        printf("%d-%d\n",t[u],T[u]);*/
    // }
    if(b >= t[a] && b <= T[a])
        printf("YES");
    else printf("NO");
    return 0;
}