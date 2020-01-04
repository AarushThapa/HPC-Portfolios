#include <stdio.h>
#include <cuda_runtime_api.h>
#include <time.h>
/****************************************************************************

  nvcc -o cudaaz99 az99.cu 


     To Run:
     ./cudaaz99 > cudares.txt

 
*****************************************************************************/
__device__ int match(char *attempt) {
  char pw1[] = "CV78";
  char pw2[] = "FT81";
  char pw3[] = "HS21";
  char pw4[] = "SC63";

  char *a = attempt;
  char *b = attempt;
  char *c = attempt;
  char *d = attempt;

  char *p1 = pw1;
  char *p2 = pw2;
  char *p3 = pw3;
  char *p4 = pw4;

  while(*a == *p1) {
   if(*a == '\0')
    {
    printf("Password: %s\n",pw1);
      break;
    }

    a++;
    p1++;
  }
    
  while(*b == *p2) {
   if(*b == '\0')
    {
    printf("Password: %s\n",pw2);
      break;
}

    b++;
    p2++;
  }

  while(*c == *p3) {
   if(*c == '\0')
    {
    printf("Password: %s\n",pw3);
      break;
    }

    c++;
    p3++;
  }

  while(*d == *p4) {
   if(*d == '\0')
    {
    printf("Password: %s\n",pw4);
      break;
    }

    d++;
    p4++;
  }
  return 0;

	}
/****************************************************************************
  The kernel function assume that there will be only one thread and uses
  nested loops to generate all possible passwords and test whether they match
  the hidden password.
*****************************************************************************/

__global__ void  kernel() {
char k1,k2;
 
  char pass[5];
  pass[4] = '\0';

int i = blockIdx.x+65;
int j = threadIdx.x+65;
char matchone = i;
char matchtwo = j;
    
pass[0] = matchone;
pass[1] = matchtwo;

    for(k1='0'; k1<='9'; k1++){
      for(k2='0'; k2<='9'; k2++){
            pass[2] = k1;
            pass[3] = k2;
          if(match(pass)) {
        	//printf("Password Cracked");
          }
             else {
        	 //printf("tried: %s\n", pass);          
       	     }
          }
        } 
      
}
int time_difference(struct timespec *start,
                    struct timespec *finish,
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec;
  long long int dn =  finish->tv_nsec - start->tv_nsec;

  if(dn < 0 ) {
    ds--;
    dn += 1000000000;
  }
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}


int main() {

  struct  timespec start, finish;
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

kernel <<<26,26>>>();
  cudaThreadSynchronize();

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed/1.0e9));
  return 0;
}




