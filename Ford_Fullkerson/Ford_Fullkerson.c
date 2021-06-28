#include <stdio.h>
#define NO_EDGE 0
#define INF 9999999
#define MAXN 50
typedef struct {
    int C[MAXN][MAXN];  // kha nang thong qua cua cung
    int F[MAXN][MAXN];  // luong tren cung
    int n;
} Graph;

//khoi tao do thi
void init_graph(Graph *G, int n){
    int i, j;
    G->n = n;
    for(i = 1; i <= n; i++){
        for(j = 1; j <= n; j++){
            G->C[i][j] = 0;
        }
    }
}

// them cung vao do thi
void add_edge(Graph *G, int x, int y){
    G->C[x][y] = 1;
    G->C[y][x] = 1;
}

typedef struct {
    int dir;    // >0: +,   <0: -,   0: chua co nhan
    int pre;    // dinh truoc
    int sigma;  // luong tang luong
} Label;

Label labels[MAXN];     // nhan cac dinh


void init_flow(Graph *G){
    int i, j;
    for(i = 1; i <= G->n; i++)
        for(j = 1; j <= G->n; j++)
            G->F[i][j] = 0;
}


typedef struct {
    int front, rear;
    int data[MAXN];
}Queue;


void make_null_queue(Queue *Q){
    Q->front = 0;
    Q->rear = -1;
}

void enqueue(Queue *Q, int x){
    Q->rear++;
    Q->data[Q->rear] = x;
}

int top(Queue *Q){
    return Q->data[Q->front];
}

void dequeue(Queue *Q){
    Q->front++;
}

int empty(Queue *Q){
    return Q->front > Q->rear;
}

int min(int a, int b){
    return a < b ? a : b;
}

int FordFullkerson(Graph *G, int s, int t){
    init_flow(G);
    int u, v, sum_flow = 0;
    Queue Q;
    do {
        for(u = 1; u <= G->n; u++)
            labels[u].dir = 0;

        labels[s].dir = 1;
        labels[s].pre = s;
        labels[s].sigma = INF;

        make_null_queue(&Q);
        enqueue(&Q, s);

        int found = 0;
        while(!empty(&Q)){
            int x = top(&Q);
            dequeue(&Q);
            for(v = 1; v <= G->n; v++){
                if(labels[v].dir == 0 && G->C[x][v] != NO_EDGE && G->F[x][v] < G->C[x][v]){
                    labels[v].dir = 1;
                    labels[v].pre = x;
                    labels[v].sigma = min(labels[x].sigma, G->C[x][v] - G->F[x][v]);
                    enqueue(&Q, v);
                }
                if(labels[v].dir == 0 && G->C[v][x] != NO_EDGE && G->F[v][x] > 0){
                    labels[v].dir = -1;
                    labels[v].pre = x;
                    labels[v].sigma = min(labels[x].sigma, G->F[x][v]);
                    enqueue(&Q, v);
                }
            }
            if(labels[t].dir != 0){
                found = 1;
                break;
            }
        }

        if(found == 1){
            int x = t;
            int sigma = labels[t].sigma;
            sum_flow += sigma;
            
            while(x != s){
                int u = labels[x].pre;
                if(labels[x].dir > 0)
                    G->F[u][x] += sigma;
                else
                    G->F[x][u] -= sigma;
                x = u;
            }
        }
        else   
            break;
    } while(1);
    return sum_flow;
}   


int main(){
    Graph G;
    int n, m, u, v, e, c;
    freopen("dt.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for(e = 0; e < m; e++){
        scanf("%d%d%d", &u, &v, &c);
        G.C[u][v] = c;
    }
    int max_flow = FordFullkerson(&G, 1, n);
    printf("Max flow: %d\n", max_flow);
    
    int i;
    printf("X0: ");
    for(i = 1; i <= n; i++)
        if(labels[i].dir != 0)
            printf("%d ", i);
    printf("\nY0: ");
    for(i = 1; i <= n; i++)
        if(labels[i].dir == 0)
            printf("%d ", i);
    return 0;
}