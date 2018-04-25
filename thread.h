

// thread.h
#indef _THREAD_H
#define thread_H

typedef void *(*f_WithArgs)(void *);
enum THREAD_STATES{DED, RUN, RED, SLP, SUS, NEW};
enum TYPE {ARG, NOARG};

//Statistics block of thread 
//contain basic information of thread
struct statistics{
	
	//thread id
	int ID;

	//thread state
	enum THREAD_STATES state;
	
	//thread burst time
	int burst;

	//thread total execution time
	int totalExecTime;

	//thread sleep time
	int totalSleepTime;

	//thread average time quantum
	float avgerageTimeQuantum;
 	
	//thread average waiting time
 	float avgWaitTime;

 	//thread actual execution time/running time
 	int RedTimeTotal;

 	//clock to read time when thread start executing
 	clock_t RunTimeStart;

 	//clock to read time when thread in ready state
 	clock_t RedTimeStart;
};

//the thread control block
typedef struct tcb{
	jmp_buf env;

	//thread stack
	char stack[4096]; 
	struct statistics stat;

	//thread type determining arg/noarg
	enum TYPE threadType;

	//thread routine no arg type
	void (*f1)(void);

	//thread routine arg type
	f_WithArgs f2;

	//thread args
	void* args;
	void* retVal;
	
}TCB; 

class thread{

	//Create thread of function.
	int create(void (*f)(void));
	
	// Create thread of function which takes arguments.
	int createWithArgs(void *(*f)(void *), void *arg);

	//return RThreadID
	int getID(void);

	//the scheduler func, sig == signalID?
	void dispatch(int);

	//start executing the threads - possibly a master thread
	void start(void);

	//put thread status = RED
	void run(int threadID);

	//put thread status = SUS
	void suspend(int threadID);

	//put thread status = RED
	void resume(int threadID);


	void yield(void);
	

	void initStatistics(struct statistics* stat,int id);
	
	//delete thread with given thread id
	void deleteThread(int threadID);
	
	// put thread status = SLP
	void sleep1(int sec);
	
	//stops the master thread
	void clean(void);	
	
	//print the fields of statistics
	struct statistics* getStatus(int threadID);

}

#endif