/*   	Name: Jeff Brandon	Class: cps470
	Section: 2014		Assignment: 10
	Due: APR 30, 2014	Started: APR 21, 2014
	Credit: 10 points
*/

#define SIZE 200

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <synch.h>
#include <pthread.h>

struct full{
   sema_t mf;
   sema_t mflst;
   int count;
};

struct empty{
   sema_t me;
   sema_t melst;
   int count;
};

typedef struct full full;
typedef struct empty empty;

/*   Global semaphores  */
full fcount;
empty ecount;
sema_t mtx;

int main(int argc, char** argv)
{
   int semainit(void);
   int semarel(void);
   int toint(char*);
   int consiters, ncons, nprods, proditers;

   if(argc != 5){
      fprintf(stderr, "Invalid input, expects four arguments!!\n");
      exit(1);
   }

   if((nprods = toint(argv[1])) <= 0 ||
       (proditers = toint(argv[2])) <= 0 ||
        (ncons = toint(argv[3])) <= 0 ||
         (consiters = toint(argv[4])) <= 0){
      fprintf(stderr,"Invalid input: all values must be positive integers!!\n");
      exit(1);
   }
   
   if(semainit()!=0){
      fprintf(stderr,"semainit failed\n");
      exit(1);
   }

   /* create consumers */
   
   /* create producers */

   /* join threads */

   if(semarel()!= 0){
      fprintf(stderr,"semaclose failed\n");
      exit(1);
   }

   exit(0);
}

/* Problem: need to initialize a binary semaphore
   Solution: Create a semaphore with 1 resource. If errors are encountered 
   return -1. On successful completion return 0.
*/

int semainit()
{
   if(sema_init(&mtx,1,NULL,NULL)!=0){
      fprintf(stderr,"sema_init failed\n");
      return -1;
   }
   if(sema_init(&((&fcount)->mf),1,NULL,NULL)!=0){
      fprintf(stderr,"sema_init failed\n");
      return -1;
   }
   if(sema_init(&((&fcount)->mflst),0,NULL,NULL)!=0){
      fprintf(stderr,"sema_init failed\n");
      return -1;
   }
   if(sema_init(&((&ecount)->me),1,NULL,NULL)!=0){
      fprintf(stderr,"sema_init failed\n");
      return -1;
   }
   if(sema_init(&((&ecount)->melst),1,NULL,NULL)!=0){
      fprintf(stderr,"sema_init failed\n");
      return -1;
   }
   (&fcount)->count = 0;
   (&ecount)->count = SIZE;
   return 0;
}

/* Problem: need to release resources used in creating a binary
   semaphore after it has been used.
   Solution: Destroy the semaphore. If an error occurs return -1.
   On success return 0.
*/

int semarel(){
   if(sema_destroy(&mtx)!=0){
      fprintf(stderr,"sema_destroy failed\n");
      return -1;
   }
   if(sema_destroy(&((&fcount)->mf))!=0){
      fprintf(stderr,"sema_destroy failed\n");
      return -1;
   }
   if(sema_destroy(&((&fcount)->mflst))!=0){
      fprintf(stderr,"sema_destroy failed\n");
      return -1;
   }
   if(sema_destroy(&((&ecount)->me))!=0){
      fprintf(stderr,"sema_destroy failed\n");
      return -1;
   }
   if(sema_destroy(&((&ecount)->melst))!=0){
      fprintf(stderr,"sema_destroy failed\n");
      return -1;
   }
   return 0;
}

int toint(char* s){
   int i=0;
   while(*s){
      if(*s > '9' || *s < '0') return -1;
      i+=*s - '0';
      i*=10;
      *s++;
   }
   return i/10;
}
