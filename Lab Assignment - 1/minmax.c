#include<stdio.h>
#include<omp.h>
void get_min(int* array, int n, int gmin){
  int min=gmin;
  int i;
  for(i=0; i<n; i++){
    if(array[i]<min){
      min=array[i];
    }
  }
  #pragma omp critical
  if(min<gmin){
    gmin=min;
  }
  printf("Min element is %d\n",gmin);
}
void get_max(int* array, int n, int gmax){
  int max=gmax;
  int i;
  for(i=0; i<n; i++){
    if(array[i]>max){
      max=array[i];
    }
  }
  #pragma omp critical
  if(max>gmax){
    gmax=max;
  }
  printf("Max element is %d\n",gmax);
}

int main(){
  int n;
  printf("Enter the number of elements: ");
  scanf("%d",&n);
  int array[n];
  printf("Enter the elements:\n");
  for (int i=0; i<n; i++){
    scanf("%d",&array[i]);
  }
  printf("20BCE0959\n");
  omp_set_num_threads(4);
  int gmax=__WINT_MIN__, gmin=__INT_MAX__;
  double t1,t2,t3,t4;
  #pragma omp parallel shared(array,n, gmax, gmin)
  {
    #pragma omp sections
    {
      #pragma omp section
      {
        t1=omp_get_wtime();
        get_min(array, n, gmin);
        t2=omp_get_wtime();
      }
      #pragma omp section
      {
        t3=omp_get_wtime();
        get_max(array, n, gmax);
        t4=omp_get_wtime();
      }
    }
    #pragma omp master
    {
      printf("Time taken for max calculation is %lf\n",t4-t3);
      printf("Time taken for min calculation is %lf\n",t2-t1);
    }
  }
  return 0;
}