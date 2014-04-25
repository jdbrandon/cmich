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
#include <pthread.h>
/*   Global mutex variable */
   pthread_mutex_t mutex;

/* Problem: simulate a race condition scenario and prevent the race 
   condition from corrupting data using a binary semaphore.
   Solution: Use pthread_mutex to simulate a binary semaphore. Initialize
   the mutex to represent that the resource is available. Create
   10 threads that perform a task, in this case the function term.
   wait for the threads to complete. Then destroy the mutex. If any
   errors occur during system calls an error message should
   be displayed and the function returns exit status 1.
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
   Solution: Create a pthread_mutex. If errors are encountered return 
   -1. On successful completion return 0.
*/

int semainit()
{
   if(pthread_mutex_init(&mutex,NULL)!=0){
      fprintf(stderr,"pthread_mutex_init failed\n");
      return -1;
   }
   return 0;
}

/* Problem: need to release resources used in creating a binary
   semaphore after it has been used.
   Solution: Destroy the pthread_mutex. If an error occurs return -1.
   On success return 0.
*/

int semarel(){
   if(pthread_mutex_destroy(&mutex)!=0){
      fprintf(stderr,"pthread_mutex_destroy failed\n");
      return -1;
   }
   return 0;
}

/* Problem: simulate a binary semaphore p() operation.
   Solution: In the context of using a pthread_mutex for a 
   semaphore, the lock operation on the mutex is a blocking agent.
   Because of this we request a lock on the mutex, when the lock is 
   granted the resource is available.  Returns 0 on success -1 if an error 
   has occured.
*/

int semap(){
   if(pthread_mutex_lock(&mutex)!=0){
      fprintf(stderr,"pthread_mutex_lock failed\n");
      return -1;
   }
   return 0;
}

/* Problem: Simulate a binary semaphore v() operation
   Solution: In context of pthread_mutex to simulate a binary
   semaphore the mutex is unlocked. If an error
   occurs -1 is returned otherwise 0 is returned on success.
*/

int semav(){
   if(pthread_mutex_unlock(&mutex)!=0){
      fprintf(stderr,"pthread_mutex_unlock failed\n");
      return -1;
   }
   return 0;
}
