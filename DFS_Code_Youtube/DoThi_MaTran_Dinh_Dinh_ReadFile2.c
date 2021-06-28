#include <stdio.h>
#define MAX_Verticles 20
#define MAX_Length 20
typedef struct{
    int A[MAX_Verticles][MAX_Length];
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

// Tim lang gieng cua dinh x
List neighbour(Graph *G, int x){
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

int main(){
    Graph G;
    int i, n, m, j;    // n: so luong dinh     m: so luong cung
    freopen("dothi.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    int u, v, e;
    for(e = 1; e <= m; e++){
        scanf("%d%d", &u, &v);
        // printf("%d %d\n", u, v);
        add_edge(&G, u, v);
    }

    printf("In ra danh sach lang gieng cua cac dinh trong do thi\n");
    for(i = 1; i <= G.n; i++){ // duyet dinh cua do thi
        List list = neighbour(&G, i); // dua danh sach lang gieng cua dinh vao danh sach
        printf("Neighbor(%d) = [", i);
        for(j = 1; j <= list.size; j++){ // in tung phan tu trong danh sach cua moi dinh
            printf("%d ", element_at(&list, j));
        }
        printf("]\n");
    }

    // for(i = 1; i <= G.n; i++){
    //     printf("degree(%d) = %d\n", i, degree(&G, i));
    // }
}
