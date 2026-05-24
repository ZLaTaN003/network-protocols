#include <stdio.h>

void leakybucket(){ // Simulate Leaky Bucket Algorithm for congestion control
  int bsize,n,itemsize,out;
  int currentsize = 0;
  int i = 0;
  
  printf("Enter the size of the bucket,no of inputs and outflow\n");
  scanf("%d %d %d",&bsize,&n,&out);
  while(n > 0){
    printf("Enter the size of item %d item",i);
    scanf("%d",&itemsize);
    
    if (currentsize + itemsize <= bsize){
      currentsize += itemsize;
      printf("item of size %d occupied %d of the bucket of size %d before outflow \n",itemsize,currentsize,bsize);   
    }
    else{
      printf("item don't fit fully discarded excess \n");
      currentsize = bsize;
      printf("item of size %d occupied %d of the bucket of size %d before outflow \n",itemsize,currentsize,bsize);  
    }
    
    if(currentsize  > out){
      currentsize -= out; 
    }
    else{
      currentsize = 0;  
    }
    printf("item of size %d occupied %d of the bucket of size %d after outflow\n",itemsize,currentsize,bsize);
    printf("Bucket size after outflow = %d\n", currentsize);
 
    n--;
    i++;
    
  }
  
  



}
