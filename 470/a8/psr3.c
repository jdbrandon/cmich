/*   	Name: Jeff Brandon	Class: cps470
	Section: 2014		Assignment: 8
	Due: APR 11, 2014	Started: APR 7, 2014
	Credit: 15 points

	Aknowlegements: I worked in tandem with Jeff Pulicifer in
	the computer lab and we helped eachother when we encountered
	issues.
*/

#define SIZE 10

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <synch.h>
#include <pthread.h>
/*   Global semaphore  */
   sema_t s;

/* Problem: simulate a race condition scenario and prevent the race 
   condition from corrupting data using a binary semaphore.
   Solution: Use a binary semaphore to enforce mutual exclusion. 
   Initialize the semaphore with a count of 1 to represent that one 
   resource is available. Create 10 threads that perform a task, in this 
   case the function term. Wait for the threads to complete. Then destroy 
   the semaphore. If any errors occur during system calls an error message 
   should be displayed and the function returns exit status 1.
*/
int main()
{
   pthread_t tid, tids[SIZE];
   int k;
   void *term(void *arg);
   int semainit(void);
   int semarel(void);

   if(semainit()!=0){
      fprintf(stderr,"semainit failed\n");
      exit(1);
   }

   for(k=0; k<SIZE; k++){
      if(pthread_create(&tid, NULL, term, NULL) != 0){
         fprintf(stderr, "pthread_create failed\n");
         exit(1);
      }
      tids[k] = tid;
   }
   for(k=0; k<SIZE; k++)
      if(pthread_join(tids[k], NULL) !=0 )
         fprintf(stderr, "pthread_join failed\n");

   if(semarel()!= 0){
      fprintf(stderr,"semaclose failed\n");
      exit(1);
   }

   exit(0);
}

/* Problem: Need a task that can be carried out by 
   several threads to display a race condition in action
   and a solution for it
   Solution: Use stderr as the shared resource. Print the thread
   id and the id of the parent process to stdout. To prevent the
   race conditon from occursing use a semaphore. Call semap to
   request access to the resource, when access is granted print
   to std out 20 times. After printing to stdout call semav to
   release control of the resource. If errors are encountered
   a message should be printed to stderr describing the problem.
*/

void *term(void *arg)
{
   int semap(void);
   int semav(void);
   int i;

   if(semap() != 0){
      fprintf(stderr,"semap failed\n");
      pthread_exit((void*)-1);
   }

   for(i=0; i<20; i++)
      fprintf(stderr,"Thread: %d of process: %d\n", (int)pthread_self(), 
         (int) getpid());
   
   if(semav() != 0){
      fprintf(stderr,"semav failed\n");
      pthread_exit((void*)-1);
   }

   pthread_exit(NULL);  
}

/* Problem: need to initialize a binary semaphore
   Solution: Create a semaphore with 1 resource. If errors are encountered 
   return -1. On successful completion return 0.
*/

int semainit()
{
   if(sema_init(&s,1,NULL,NULL)!=0){
      fprintf(stderr,"sema_init failed\n");
      return -1;
   }
   return 0;
}

/* Problem: need to release resources used in creating a binary
   semaphore after it has been used.
   Solution: Destroy the semaphore. If an error occurs return -1.
   On success return 0.
*/

int semarel(){
   if(sema_destroy(&s)!=0){
      fprintf(stderr,"sema_destroy failed\n");
      return -1;
   }
   return 0;
}

/* Problem: simulate a binary semaphore p() operation.
   Solution: In the context of using a semaphore, the wait operation on 
   the semaphore is a blocking agent. Because of this we wait on 
   the semaphore, access is granted when the resource is available.  
   Returns 0 on success -1 if an error has occured.
*/

int semap(){
   if(sema_wait(&s)!=0){
      fprintf(stderr,"sema_wait failed\n");
      return -1;
   }
   return 0;
}

/* Problem: Simulate a binary semaphore v() operation
   Solution: In context of a binary semaphore the semaphore
   post function is called on the semaphore. If an error
   occurs -1 is returned otherwise 0 is returned on success.
*/

int semav(){
   if(sema_post(&s)!=0){
      fprintf(stderr,"sema_post failed\n");
      return -1;
   }
   return 0;
}
