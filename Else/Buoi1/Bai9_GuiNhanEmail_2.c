#include <stdio.h>
#define MAX_N 100
#define MAX_M 500
typedef struct{
    int A[MAX_N][MAX_M];
    int n,m;
}Graph;

void init_graph(Graph *G,int n,int m){
    G->m=m;
    G->n=n;
    for(int i=1;i<=n;i++){ 
        for(int j=1;j<=m;j++){ 
            G->A[i][j]=0;
        }
    }
}

void add_edge(Graph *G,int e,int x,int y){
    G->A[x][e]=1;
    G->A[y][e]=-1;
}

int degree(Graph *G,int x){
    int deg=0;
    for(int i=1;i<= G->m;i++){
        if(G->A[x][i]==1)
            deg++;
    }
    return deg;
}

int main(){
    Graph G;
    int n,m,v,u,w,e,i,x;
    scanf("%d",&n);
    scanf("%d",&m);
    init_graph(&G,n,m);
    for(e=1;e<=m;e++){ 
        scanf("%d%d",&u,&v); 
        add_edge(&G,e,u,v); 
    } 
    w=0; 
    for(i=1;i<=n;i++){ 
        if(degree(&G,i)>w){
            w=degree(&G,i);
            x=i;
        }
    }
    printf("%d has sent %d email(s).",x,w);
}