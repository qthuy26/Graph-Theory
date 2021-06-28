#include <stdio.h>
#define MAX_N 100
typedef struct{
    int n,m;
    int A[MAX_N][MAX_N];
}Graph;

void init_graph(Graph*G,int n){
    int i,j;
    G->n=n;
    for(i=1;i<=n;i++){ 
        for(j=1;j<=n;j++){ 
            G->A[i][j]=0;
        }
    }
}

int main(){
    Graph G;
    int n,i,j,maxt,max,a[100];
    scanf("%d",&n);
    init_graph(&G,n);
    for(i=1;i<=n;i++){ 
        for(j=1;j<=n;j++){ 
            scanf("%d",&G.A[i][j]); 
        } 
    } 
    for(i=1;i<=n;i++){ 
        for(j=1;j<=n;j++){ 
            a[i]=a[i]+G.A[j][i]; 
        } 
    } 
    max=1; 
    maxt=a[1]; 
    for(i=2;i<=n;i++){ 
        if(a[i] > maxt) {
            maxt = a[i] ;
            max = i ;
        }
    }
    printf("%d has received %d email(s).",max,maxt);
}