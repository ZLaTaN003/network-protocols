#include <stdio.h>

void dvp(){
  int n;
  int cost[20][20];
  int dist[20][20];
  int via[20][20];
  
  printf("Enter number of nodes: \n");
  scanf("%d", &n);

  printf("Enter cost matrix:\n");
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
        scanf("%d", &cost[i][j]);
        dist[i][j] = cost[i][j];
        via[i][j] = j;
        }
    }
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(dist[i][j] > cost[i][k] + dist[k][j]) {
                    dist[i][j] = cost[i][k] + dist[k][j];
                    via[i][j] = k;
                }
            }
        }
    }
    for(int i = 0; i < n; i++) {
        printf("\nRouter %d\n", i + 1);
        for(int j = 0; j < n; j++) {
            printf("To %d via %d distance %d\n",
                   j + 1,
                   via[i][j] + 1,
                   dist[i][j]);
        }
    }
    
}
