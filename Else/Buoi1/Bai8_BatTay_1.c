#include <stdio.h>
#define MAX_Verticles 20
#define MAX_Length 20
#define MAX_Element 40

// Khai bao cau truc do thi
typedef struct{
    int A[MAX_Verticles][MAX_Length];
    int n; //so luong dinh
}Graph;


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

int main(){
    Graph G;
    //freopen("HeSinhThaiRung.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m); 
    init_Graph(&G, n);
    int i, j;
    for(i = 1; i <= m; i++){
    		int a, b;
    		scanf("%d%d", &a, &b);
    		G.A[a][b]++;
    		G.A[b][a]++;
    }
	for(i = 1; i <= n; i++){
		int total = 0;
		for(j = 1; j <= n; j++){
			total += G.A[i][j];
		}
		printf("%d\n", total);
	}
    return 0;
}