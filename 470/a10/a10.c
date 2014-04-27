/*   	Name: Jeff Brandon	Class: cps470
	Section: 2014		Assignment: 10
	Due: APR 30, 2014	Started: APR 21, 2014
	Credit: 10 points
*/

#define SIZE 200

#include <stdio.h>
#include <stdlib.h>
#include <synch.h>
#include <pthread.h>

/* Struct used to sumulate a counting semaphore.
   mtx is used to enforce mutual exclusion on
   the struct when it is having its count manipulated.
   lst is used to maintain a list of waiting processes.
   count is the number of processes on the waitlist when
   negative and the number of available resources otherwise.
*/

struct countsema{
   sema_t mtx;
   sema_t lst;
   int count;
};

typedef struct countsema countsema;

/*   Global semaphores  */
countsema full;
countsema empty;
sema_t mtx;

/* Global buffer */
char buf[SIZE];
int head = 0;
int tail = 0;

/* Problem: Want to simulate a solution to the bounded buffer problem
   using only binary semaphores. 
   Solution: To simulate the bounded buffer problem the global char 
   array buf is used as the buffer and it is maintained as a circular 
   queue. The global ints head and tail point to the head and tail of 
   the queue respectively. First, the semaphores are allocated and 
   initialized to their starting values. Five binary semaphores are 
   necessary: one for mutual exclusion on the buffer and two for each
   counting semaphore used for keeping track of the number of full and 
   empty slots. Next producers and consumers are created to write 
   to and read from the buffer. It is imperitive that a consumer does 
   not attempt to consume and item when the buffer is empty and likewise 
   a producer should not place an item when the buffer is full. Four 
   arguments are passed, each integers corresponding to nprods, proditers, 
   ncons, and consiters respectively. Using these values  ncons consumer 
   threads are created that each iterate consiters times. Similarly after 
   the consumers are created nprods producer threads are created that 
   iterate proditers times. After all producer and consumer threads are 
   finished being created the main thread waits for all of the threads to 
   complete. When all threads are complete the semaphores are released 
   to conserve system resources. If an error is encountered a message is
   printed to stderr and the function exits with error status 1.
*/

int main(int argc, char** argv)
{
   int semainit(void);
   int semarel(void);
   int toint(char*);
   void *consumer(void*);
   void *producer(void*);

   pthread_t tid;
   int consiters, i, ncons, nprods, proditers, tidindex;

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

   if(nprods * proditers != ncons * consiters){
      fprintf(stderr,"nprods * proditers must equal ncons * consiters!!\n");
      exit(1);
   }

   pthread_t tids[nprods + ncons];
   
   if(semainit()!=0){
      fprintf(stderr,"semainit failed\n");
      exit(1);
   }

   tidindex = 0;

   for(i=0; i < ncons; i++){
      if(pthread_create(&tid, NULL, consumer, (void*) &consiters) != 0){
         fprintf(stderr,"Failed to create consumers!!\n");
         exit(1);
      }
      tids[tidindex++] = tid;
   }
   
   for(i=0; i < nprods; i++){
      if(pthread_create(&tid, NULL, producer, (void*) &proditers) !=0){
         fprintf(stderr,"Failed to create producers!!\n");
         exit(1);
      }
      tids[tidindex++] = tid;
   }

   for(i=0; i < tidindex; i++)
      if(pthread_join(tids[i], NULL) != 0)
         fprintf(stderr,"Join failed on thread %d!!\n", tids[i]);


   if(semarel()!= 0){
      fprintf(stderr,"semaclose failed\n");
      exit(1);
   }

   exit(0);
}

/* Problem: Initialize the semaphores for the bounded buffer solution
   Solution: Call sema_init on each binary semaphore, semaphores that
   enforce mutual exclusion are intialized to 1 and waitlist semaphores
   are initialized to 0. After the semaphores have been created, the
   count of full slots is set to 0 and the count of empty slots is 
   set to SIZE. If an error is encountered then -1 is returned. On 
   successful completion 0 is returned.
*/

int semainit()
{
   if(sema_init(&mtx, 1, NULL, NULL) != 0){
      fprintf(stderr,"sema_init failed\n");
      return -1;
   }
   if(sema_init(&full.mtx, 1, NULL, NULL) != 0){
      fprintf(stderr,"sema_init failed\n");
      return -1;
   }
   if(sema_init(&full.lst, 0, NULL, NULL) != 0){
      fprintf(stderr,"sema_init failed\n");
      return -1;
   }
   if(sema_init(&empty.mtx, 1, NULL, NULL) != 0){
      fprintf(stderr,"sema_init failed\n");
      return -1;
   }
   if(sema_init(&empty.lst, 0, NULL, NULL) != 0){
      fprintf(stderr,"sema_init failed\n");
      return -1;
   }
   full.count = 0;
   empty.count = SIZE;
   return 0;
}

/* Problem: need to release resources used in creating semaphores
   after they have been used.
   Solution: Destroy the semaphores. If an error occurs return -1.
   On success return 0.
*/

int semarel(){
   if(sema_destroy(&mtx)!=0){
      fprintf(stderr,"sema_destroy failed\n");
      return -1;
   }
   if(sema_destroy(&full.mtx) != 0){
      fprintf(stderr,"sema_destroy failed\n");
      return -1;
   }
   if(sema_destroy(&full.lst) !=0 ){
      fprintf(stderr,"sema_destroy failed\n");
      return -1;
   }
   if(sema_destroy(&empty.mtx) != 0){
      fprintf(stderr,"sema_destroy failed\n");
      return -1;
   }
   if(sema_destroy(&empty.lst) != 0){
      fprintf(stderr,"sema_destroy failed\n");
      return -1;
   }
   return 0;
}

/* Problem: convert a string of characters into an int
   Solution: parse the string and add the digits one
   at a time to an int. return the resulting int.
   Note: I wrote this and then learned about the strtol()
   family of functions. I left this in because I already 
   had it written.
*/

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

/* Problem: Need to simulate a consumer process
   Solution: The passed pointer contains an int which specifies
   the number of items to consume. After that many items have been
   consumed by consumeitem() the thread returns with successful
   exit status. If an error is encountered when consuming an item
   a message is printed to stderr and the thread returns with 
   error status -1.
*/

void *consumer(void *arg){
   int consumeitem(void);
   int i, n; 

   n = *((int *) arg);
   for(i = 0; i < n; i++)
      if(consumeitem() != 0){
         fprintf(stderr, "Error consuming item in thread %d\n", (int) pthread_self());
         pthread_exit((void*)-1);
      }
   pthread_exit(NULL);
}

/* Problem: Need to consume an item from the global buffer
   Solution: First it is important to make sure there is an 
   available full space. This is accomplished by calling pmf().
   After access is granted it is necessary to request mutual 
   exclusion on the buffer by making a P() request on mtx.
   After mutual exclusion is ensured, a message is printed
   denoting that the current value of buf[tale] is being consumed.
   The the value at tale is set to null and the queue's tail 
   pointer is advanced. After this mutual exclusion on the buffer 
   is released and then vme() is called to increase the number
   of empty cells in the buffer. Returns 0 on success -1 on failure.
*/

int consumeitem(){
   int pmf(void);
   int vme(void);
   
   if(pmf() != 0) return -1;
      if(sema_wait(&mtx) != 0) return -1;
         fprintf(stderr, "Thread %d consuming\t%c\n", (int) pthread_self(), buf[tail]);
         buf[tail] = NULL;
         tail == (SIZE - 1) ? tail = 0 : tail++;
      if(sema_post(&mtx) != 0) return -1;
   if(vme() != 0) return -1;
   
   return 0;
}

/* Problem: Need a producer thread that will produce n items
   Solution: arg points to an int that dictates the number
   of times to iterate through a loop that produces an 
   item and places it in the buffer using produceitem.
   After the item are produced successfully the thread
   exits with success status. If an error occurs while 
   producing and item an error message is printed to
   stderr and the thread exits with an error status.
*/

void *producer(void *arg){
   int produceitem(void);
   int i, n;

   n = *((int *) arg);
   for(i = 0; i < n; i++)
      if(produceitem() != 0){
         fprintf(stderr,"Error producing item in thread:%d\n", (int) pthread_self());
         pthread_exit((void*)-1);
      }
   pthread_exit(NULL);
}

/* Problem: Create an item and place it in the global buffer
   at the head of the queue.
   Solution: Use the rand function modulo 26 to generate a random
   letter A-Z. Request access to an empty space in the buffer by
   making a P() request on the "empty" semaphore the counts the
   number of remaining empty spaces in the buffer using the pme()
   function. Next it is important to have mutual exclusion on the 
   buffer when it is modified so a P request is made on mtx.
   Once mutual exclusion is granted, the item is placed at head
   in the global buffer, a message is printed to stderr to inform
   the user which thread placed what item, and head is moved to the
   next index. Once this is accomplished, mutual exclusion on the
   buffer must be released, and then vmf is called to sumulate the
   V operation on the simulated counting semaphore full. Returns 0
   on success and -1 on failure.
*/
int produceitem(){
   int pme(void);
   int vmf(void);

   char item;

   item = (rand() % 26) + 'A';

   if(pme() != 0) return -1;
      if(sema_wait(&mtx) != 0) return -1;
         buf[head] = item;
         fprintf(stderr,"Thread %d placing\t%c\n", (int)pthread_self(),item);
         head == (SIZE-1) ? head = 0 : head++; 
      if(sema_post(&mtx) != 0) return -1;
   if(vmf() != 0) return -1;
   
   return 0;   
}

/* Problem: need to simulate the P operation on the simulated
   counting semaphore that keeps track of the number of empty
   spaces in the global buffer.
   
   Note on counting semaphores: A counting semaphore ensures two things: 
   its operations are garunteed to be atomic, and it keeps a count of the 
   number of available resources. The count can be negative when there are
   more processes requesting access to the resource than there are
   resources available. Because each request for access decrements
   the counter regardless of weather or not there is a resource 
   available when the count is negative it keeps track of the
   number of processes waiting to access the resource. 

   Solution: First to enforce atomic operations a binary semaphore mtx is 
   used to enforce mutual exclusion by making a P operation on it before
   proceding. Once exclusive access is obtained, the count of
   empty spaces is decremented. After that a check is done to see
   if the count has become negative. If it is negative then there
   are currently no empty slots available and the calling process
   needs to wait for one. This is accomplished by making a P request
   on the empty semaphores lst (list) binary semaphore which simulates
   a waitlist of processes that need to be granted access. lst is
   initialized to 0 so it will block until a V operation is done on
   the semaphore when an empty space is made available. Because
   waiting on lst is a blocking call it is imperitive that exclusive
   access to empty is released before waiting, otherwise 
   the waiting process will block other processes from accessing the
   empty semaphore. Also if the count remains positive or 0, 
   exclusive access must be released before returning successfully.
   Returns 0 on success, and -1 on failure.
*/

int pme(){
   if(sema_wait(&empty.mtx) != 0) return -1;
      empty.count--;
      if(empty.count < 0){
         if(sema_post(&empty.mtx) != 0) return -1;
         if(sema_wait(&empty.lst) != 0) return -1;
      }
      else if(sema_post(&empty.mtx) != 0) return -1;
   return 0;
}

/* Problem: Simulate a V operation on the simulated counting 
   semaphore empty.
   Solution: Enforce mutual exclusion on empty using the mtx
   binary semaphore of empty. Once exclusive access is granted
   increment the count of empty spaces. If the count is 0 or less
   then the waitlist is either negative or just became non negative
   and a waiting process should be given access to an empty space.
   When this is the case a V operation is done on the lst semaphore
   of empty to signal that a space is now empty. After this is 
   accomplished mutual exclusion on empty is released.
   Returns 0 on success and -1 on failure. 
*/

int vme(){
   if(sema_wait(&empty.mtx) != 0) return -1;
      empty.count++;
      if(empty.count <= 0)
         if(sema_post(&empty.lst) != 0) return -1;
      if(sema_post(&empty.mtx) != 0) return -1;
   return 0;
}

/* Problem: Simulate P operation on simulated counting semaphore
   full.
   Solution: same as pme function except it deals with the full
   semaphore that keeps track of the number of full slots currently
   in the buffer.
*/

int pmf(){
   if(sema_wait(&full.mtx) != 0) return -1;
      full.count--;
      if(full.count < 0){
         if(sema_post(&full.mtx) != 0) return -1;
         if(sema_wait(&full.lst) != 0) return -1;
      }
      else if(sema_post(&full.mtx) != 0) return -1;
   return 0;
}

/* Problem: Simulate V operation on the simulated counting semaphore full
   Solution:Request mutual exclusion on the full semaphore. When granted increment 
   the number of full spaces. If the number of full spaces is negative then there are 
   waiting consumers. One of the waiting consumers should be granted access to the 
   buffer to consume the item so a V operation is performed on the full lst, the 
   condition consumers wait on. Mutual exclusion on the full semaphore is released 
   before returning. Returns 0 on success, -1 on failure.
*/

int vmf(){
   if(sema_wait(&full.mtx) != 0) return -1;
      full.count++;
      if(full.count <= 0)
         if(sema_post(&full.lst) != 0) return -1;
      if(sema_post(&full.mtx) != 0) return -1;
   return 0;
}
