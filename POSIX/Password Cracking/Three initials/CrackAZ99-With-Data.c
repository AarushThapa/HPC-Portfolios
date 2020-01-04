#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>

/******************************************************************************


  Compile with:
    cc -o CrackAZ99-With-Data CrackAZ99-With-Data.c -lcrypt

  

    ./CrackAZ99-With-Data > results.txt


******************************************************************************/
int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$FZsX/uCiZrKGm/puMtEzBbWlE/ILLhOwj9jl6xXAxvnzSIQq6YICQKXQ9Ivb/vwmcLu1bTW0UHLZIATiDGQ1b.",
  "$6$KB$U4mUDlg46lki6OOKFeDiacfn/KY0cWCU9jqzR5iN/yPQxUUl/Fxuo1Osku.mqFecUy1H2MwYVz6lYMiGz6X5B/",
  "$6$KB$OEWX1wsXmGMLIH0/CVKL88tiGB3KgIbN2d9cJZg6iNzKEortO9CvHL5LZ1Lv7WK6RFMOGw4D8exA2Wti/QU/e/",
  "$6$KB$nBThLi9bgDpSwmC7gc82m03gbjScVGLZq6U8EGd9yGYWmu16mIeQ.ybOYniXvAXfc6w9eyALnTBCN.M.JvRNw/"
};



void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}


void crack(char *salt_and_encrypted){
  int x, y, z,q;    
  char salt[7];    
  char plain[7];  
  char *enc;       
  int count = 0;  

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
	for(q='A'; q<='Z'; q++){
	      for(z=0; z<=99; z++){
		sprintf(plain, "%c%c%c%02d", x, y, q, z); 
		enc = (char *) crypt(plain, salt);
		count++;
		if(strcmp(salt_and_encrypted, enc) == 0){
		  printf("#%-8d%s %s\n", count, plain, enc);
		} else {
		  printf(" %-8d%s %s\n", count, plain, enc);
		}
	}
      }
    }
  }
  printf("%d solutions explored\n", count);
}


int time_difference(struct timespec *start, struct timespec *finish,
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

int main(int argc, char *argv[]){
  int i;
  struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
  for(i=0;i<n_passwords;i<i++) {
    crack(encrypted_passwords[i]);
  }

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9)); 

  return 0;
}
