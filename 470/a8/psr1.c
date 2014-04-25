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

/* global variables for holding pipe read and write file descriptors */
int readdes, writedes;

/* Problem: simulate a race condition scenario and prevent the race 
   condition from corrupting data using a binary semaphore.
   Solution: Use a pipe to simulate a binary semaphore. Initialize
   the pipe to 1 to represent that the resource is available. Create
   10 threads that perform a task, in this case the function term.
   wait for the threads to complete. Then close the pipe. If any
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
   Solution: Create a pipe, set the readdes global
   variable as the read file descriptor and set the
   writedes global variable as the write file descriptor.
   write "1" to the write end of the pipe to show that the
   resource is available. If errors are encountered return 
   -1. On successful completion return 0.
*/

int semainit()
{
   int filedes[2];
   if(pipe(filedes) != 0)return -1;
   readdes = filedes[0];
   writedes = filedes[1];
   if(write(writedes,"1",1) != 1)return -1;
   return 0;
}

/* Problem: need to release resources used in creating a binary
   semaphore after it has been used.
   Solution: close the file descriptors specified by the global
   vaiables readdes and writedes. If an error occurs return -1.
   On success return 0.
*/

int semarel(){
   if(close(readdes)!=0) return -1;
   if(close(writedes) !=0) return -1;
   return 0;
}

/* Problem: simulate a binary semaphore p() operation.
   Solution: In the context of using a pipe for a 
   semaphore, the read operation on the pipe is a blocking call.
   Because of this we read from the pipe, when the read completes
   the resource is available. To complete the read, memory is allocated
   to a character pointer that can be passed to the read operation.
   if the read character is not a 1 an error has occured. Before returning,
   the memory allocated for the read must be freed. Returns 0 on success
   -1 if an error has occured.
*/

int semap(){
   char *c;
   c = malloc(sizeof(char));
   if(c==NULL){
      fprintf(stderr,"failed to allocate memory\n");
      return -1;
   }
   if(read(readdes,c,1)<1){      
      fprintf(stderr,"read failed\n");
      free(c);
      return -1;
   }
   if(*c != '1'){
      free(c);
      return -1;
   }
   free(c);
   return 0;
}

/* Problem: Simulate a binary semaphore v() operation
   Solution: In context of pipe to simulate a binary
   semaphore "1" is written to the pipe. If an error
   occurs during the write -1 is returned otherwise
   0 is returned on success.
*/

int semav(){
   if(write(writedes,"1",1) < 1){
      fprintf(stderr,"semav: Write failed\n");
      return -1;
   }
   return 0;
}
