#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/resource.h>

#include "queue.h"
#include "input_handeler.h"

int run = 1; // tracks if the program should exit or not
int processRunningBg = 0; // tracks if process is running in the bg

struct queue pid_list; // fcfs process queue

// =================== function declaration ==========================

/**
 * 
 * @brief Help gives list of commands supported by the shell
 *
 */
void Help();

/**
 *
 * @brief HelpCmd gives a detailed explanation of 
 * 			commands supported by the shell 
 * 
 * @param a_cmd: command whoses explanation is given
 *
 */
void HelpCmd(char* a_cmd);

/**
 * 
 * @brief Ver shows the current version of the shell
 * 
 */
void Ver();

/**
 * 
 *@brief Shows the living process with the given PID
 *
 */
void Ps();

/**
 * 
 * @brief MakeProcess creates a process suspends it
 * 
 * @param a_input: parameter to be passed to the process.
 * 		 is in the form p(n, qt)
 * 		 where p is the name of the process
 * 		 n is the number of time the promt to be printed
 * 		 qt is the time allocated to the process
 *
*/
void MakeProcess(char* a_input);

/**
 * 
 * @brief KillProcess kills a process given pid
 * 
 * @param a_pid: pid of the process to kill
 *
*/
void KillProcess(pid_t a_pid);

/**
 * 
 * @brief SuspendProcess suspends a process of given pid
 *
 * @param a_pid: pid of the process to suspend
 *
*/
void SuspendProcess(pid_t a_pid);

/**
 * 
 * @brief ContinueProcess continues a suspended process of given pid
 *
 * @param a_pid: pid of the process to continue
 *
*/
void ContinueProcess(pid_t a_pid);

/**
 * 
 * @brief ChildDead waits for fg child process to finish and 
 *	dequeues it from the list
 *
 * @param a_pid: pid of the process to continue
 *
*/
void ChildDead();

/**
 *
 * @brief DeleteProcess deletes the specified process from the list and 
 *	frees up any allocated memory
 *
 * @param a_pid: pid of the process to delete
 *
*/
void DeleteProcess(pid_t a_pid);

/**
 * @brief Exit exits out of the shell
*/
void Exit();

/**
 *
 * @brief ContinueExecuteProcess continue execution of process if 
 * process list are not empty
 *
*/
void ContinueExecuteProcess();

/**
 * @brief CheckBgProcess handels background process if there are any.
 *
 *	CheckBgProcess checks to see if there is any bg process running
 *		and if there are any bg process, it checks for its curr status.
 *		if it has finished its execution, the finished process is cleaned
 *		and the processes in the queue are executed.
 *		else does nothing
 *
*/
void CheckBgProcess();

/**
 * @brief KillRunningProcess kill the specified process from the list and 
 *	frees up any allocated memory if it exists
 *
 * @param a_pid: pid of the process to continue
 *	
*/
void KillRunningProcess(pid_t a_processId);

int main(int argc, char const *argv[])
{
	setpriority(PRIO_PROCESS,0,-20);
	
	pid_list.m_head = NULL;
	pid_list.m_tail = NULL;
	
	char input[15][30];
	
	
	int argnum; // tracks how many words are there in a given input
	
	while (run)
	{
		// checking for bg process 
		CheckBgProcess();
		
		
		// resetting the input array
		for(int i = 0; i < 15; ++i)
		{
			memset(input[i],'\0', 30);
		}
		
		// promt
		printf("\n=>");

		// getiing user input
		for (argnum=0; (scanf("%s",&input[argnum][0]))==1;++argnum)
		{
			if (getchar()=='\n')
			{ 
				break;
			}
		}
		
		// ver cmd
		if (strcmp(input[0],"ver")==0 && argnum==0) 
		{
			Ver();
		}
		// help cmd
		else if (strcmp(input[0],"help")==0 && argnum==0) 
		{
			Help();
		}
		// detail help cmd 
		else if (strcmp(input[0],"help")==0 && argnum==1) 
		{
			HelpCmd(input[argnum]);
		}
		// ps cmd
		else if (strcmp(input[0],"ps")==0 && argnum==0) 
		{
			Ps();
		}
		// kill cmd
		// todo: start here make this a functino
		else if (strcmp(input[0],"kill")==0 && argnum==1) 
		{
			// if the process to kill is head 
			// then processRunningBg no longer running 
			pid_t processToKill = atoi(input[1]);

			KillRunningProcess( processToKill);
		}
		// exec cmd
		else if (strcmp(input[0],"exec")==0 && argnum!=0)
		{
			// queing the process all process are suspended
			for (int i=1; i<=argnum; i++) 
			{
				// making a child process and suspending them
				MakeProcess(input[i]);
			}
			
			// continue the process
			// chekcing if there was a process alreading running
			if(!processRunningBg)
			{
				ContinueExecuteProcess();
			}
		}
		// exit cmd
		else if (strcmp(input[0],"exit")==0 && argnum==0) 
		{			
			Exit();
		}
		// invalid input
		else 
		{
			printf("Nosuch command. Check help for help.\n");
		}
	} // while run closing brackets

	return 0;
}

// =========================== function defination ========================

void Help()
{
	printf("This is manual page\n");
	printf("This shell supports the following commands:\n");
	printf("\tver\n\texec\n\tps\n\tkill\n\thelp\n\texit\n");
	printf("For more details please type 'help command'\n");
}

void HelpCmd(char* a_cmd)
{
	printf("This is manual page\n");

	// checking for command ver
	if (strcmp(a_cmd, "ver") == 0)
	{
		printf("\nver:\tShows details about the shell version\n");
	}
	// checking for command exec
	else if (strcmp(a_cmd, "exec") == 0) 
	{
		printf("\nexec:\texecutes the program for given number of time\n");
		printf("\tand has a given time quantum specified to it\n\n");
		
		printf("\tUsage: exec p1(n1, qt1) p2(n2, qt2)\n");
		printf("\tA valid input should have\n");
		printf("\texactly one '(', ')', and ',' and\n");
		printf("\tit should not be more that 25 character.\n\n");
		
		printf("\tExecutes the programs named p1, p2...\n");
		printf("\tEach program types a message for n times...\n");
		printf("\tand it is given a time quantum of qt msec.\n");
		
		printf("\n\tIf parameter ('&') is given the progra...\n");
		printf("\twill be executed in the background\n");
		printf("\tUsage: exec p1(n1, qt1) p2(n2, qt2, &)\n");
		printf("\tExecutes the programs named p1 first, and...\n"); 
		printf("\tthen executes p2 in the background after finishing p1\n");
	}
		
	// checking for command Ps
	else if (strcmp(a_cmd, "ps") == 0)
	{
		printf("\nps:\tShows all the living process with their PID\n");
	}
	// checking for command kill
	else if (strcmp(a_cmd, "kill") == 0)
	{
		printf("\nkill:\tEnds the process with the given pid\n");
		printf("\tUsage: kill (processPid)\n");
	}
	// checking for command help
	else if (strcmp(a_cmd, "help") == 0)
	{
		printf("\nhelp:\tYou should know this command by now\n");
	}
	// checking for command exit
	else if (strcmp(a_cmd, "exit") == 0)
	{
		printf("\nexit:\tEnds the experience of working in the new shell\n");
	}
	// everythihng else
	else 
	{
		printf("\nNo Such command. Type help to see a list of commands\n");
	}
}

void Ver()
{
	printf("\nNew Shell. Works properly!!\n");
}

void Ps()
{
	struct node* p;

	printf("\nNEW SHELL presents the following living processes\n");
	printf("\tPID\tNAME\n");
	printf("\t---\t----\n");

	// hardcoding this cause this process is not handeled by our scheduler
	// but rather by the host shell
	// and would only unnecessary complicate the scheduler 
	printf("\t%3d\tNEW SHELL\n",getpid()); 
	
	struct node* tempNode = pid_list.m_head;
	while(tempNode != NULL)
	{
		printf("\t%3d\t%s\n", tempNode->m_pid, tempNode->m_name);
		tempNode = tempNode->m_next;
	}
}

void MakeProcess(char* a_input)
{
	int i,t,status;
	char* temp;
	struct node* p;

	// locally copying the input
	char localInput[30];
	
	// resetting local copy of input
	memset(localInput, '\0', 30);
	
	// making a copy of the input so that even after the process
	strcpy(localInput, a_input);

	// processing the input as it is in the form of p1(n1,qt1)
	// chekcing if the input is valid or not
	if(ValidInput(localInput) == -1)
	{
		printf("For more details please type 'help exec'\n\n");
		return;
	}

	// create a child process
	pid_t childPid;

	if((childPid = fork()) == 0)
	{
		// this is child process
		
		// giving time for the parent to suspend the process 
		// necessary so that this process does not get priority by the host shell
		usleep(1); 
		
		// replace the process image with the program
		// preparing arg to be passed to execv
		/// @note arg[1], and arg[2] are dynamically allocated
		/// but as we call execv the whole process is wiped so it does not matter 
		char bg = IsInputBg(localInput);
		
		char* args[4];
		args[0] = "./p-shell";
		args[1] = GetInputNumArg(localInput);
		args[2] = GetInputQtArg(localInput);
		args[3] = &bg;
		args[4] = NULL;

		execv(args[0], args);
	}

	else
	{
		// this is the parent process of the head process

		// checking if newprocess failed to create
		if(childPid == -1)
		{
			printf("Error while creating new process");
			return;
		}

		// suspending the child process 
		SuspendProcess(childPid);
		
		// enqueue the childPid
		Enqueue(&pid_list, childPid, GetInputProcessName(localInput), IsInputBg(localInput));
		return;
	}
}

void KillProcess(pid_t a_pid)
{
	kill(a_pid,SIGTERM);
	printf("You have just killed process %d\n",a_pid );
	printf("The child %d is dead\n\n", a_pid);
}

void SuspendProcess(pid_t a_pid)
{
	kill(a_pid, SIGSTOP);
	printf("Processes with pid %d suspended\n", a_pid);
}

void ContinueProcess(pid_t a_pid)
{
	kill(pid_list.m_head->m_pid, SIGCONT);
	printf("Processes with pid %d continued\n", a_pid);
}


void ChildDead()
{
	waitpid(pid_list.m_head->m_pid, NULL, 0); // waiting for the child to finish terminating
	
	printf("\nThe child %d is dead\n\n", pid_list.m_head->m_pid);
}

void DeleteProcess(pid_t a_pid)
{
	// deallocating the child name 
	// as it was dynamically allocated in exec function
	free(GetProcessName(&pid_list, a_pid));

	Delete(&pid_list, a_pid);
}


void ContinueExecuteProcess()
{
	// executing process one by one
	while(!IsEmpty(&pid_list)) 
	{
		// check if the head is fg, i.e bg == 0
		// if yes resume and wait for the fg process to finish
		// and dequeue it and clean up
		if(pid_list.m_head->m_bg == 0 )
		{
			ContinueProcess(pid_list.m_head->m_pid); // resuming the process
			ChildDead(); // waiting for it to finish
			DeleteProcess(pid_list.m_head->m_pid); // cleaning up
		}
		// the process is bg, i.e bg == 1
		// resume the process 
		// checking if the process is finish or not is done by wnohang 
		// at the start of the main while loop
		else
		{			
			ContinueProcess(pid_list.m_head->m_pid);
			usleep(100000);
			break;
		}
	}
}

void CheckBgProcess()
{
	// checking if the queue is empty or not 
	// we have to do this because if it is empty and then try to 
	// access the queue's head it would be invalid
	if(!IsEmpty(&pid_list))
	{
		// checking if there is head process id bg process 
		// and if yes checking if it finished its work
		if(pid_list.m_head->m_bg == 1)	
		{
			processRunningBg = 1;
				
			// checking if it terminated, 
			// and if there are any other process in the list start those
			if(waitpid(pid_list.m_head->m_pid, NULL, WNOHANG) > 0)
			{
				// running background process just finished
				
				printf("Background Process with pid %d has finished\n", pid_list.m_head->m_pid);
				
				// cleaning the process
				DeleteProcess(pid_list.m_head->m_pid); 
					
				// setting the processRunningBg indicator to signify false
				processRunningBg = 0;
				
				// continue executing process if any
				ContinueExecuteProcess();
					
				// recalls itself to check if there is another bg procces running
				// if no the list should be empty 
				// and the function should exit
				CheckBgProcess();
			}
		}
	}
}

void KillRunningProcess(pid_t a_processId)
{
	// checking if the queue is empty
	if( pid_list.m_head == NULL)
	{
		printf("head_null\n");
		return;
	}
		
	// validate the pid
	if(!ValidPid(&pid_list, a_processId))
	{
		printf("Invalid Pid!\n");
		return;
	}

	// checking if the process to kill is the head node
	// if yes then bg status needs to be set to 0
	if(a_processId == pid_list.m_head->m_pid)
	{
		processRunningBg = 0;
	}

	// killing the process and cleaning up			
	KillProcess(a_processId); 
	DeleteProcess(a_processId);
			
	// continue the process
	// chekcing if there was a process alreading running
	if(!processRunningBg)
	{
		ContinueExecuteProcess();
	}
}

void Exit()
{
	if(!IsEmpty(&pid_list))
	{
		// there are still process running
		
		// getting user input for if they rally want to kill
		// all the queued process 
		char userChoice = 'n';

		do
		{
			if(userChoice != 'y' || userChoice != 'n')
			{
				printf("Invalid input! press 'y' for yes or 'n' for no\n");
			}
				
			printf("There are still living processes.\n");
			printf("Do you still want to kill them? (y/n): ");
					
			scanf("%c", &userChoice);

			// getting the extra '\n' pushed by getchar() into buffer
			char getExtraNewLineChar = getchar(); 
					
			printf("user input: %c\n", userChoice); // todo: deleteme
		}while (userChoice != 'y' && userChoice != 'n');
						
		// if userChoice is no skip					
		if(userChoice == 'n')
		{
			return;
		}
				
		// else kill all the running process and exit out of shell
		while(!IsEmpty(&pid_list)) 
		{
			// kill the head Process and clean after it
			KillProcess(pid_list.m_head->m_pid); 
			DeleteProcess(pid_list.m_head->m_pid);
		}					
	}
	
	run = 0;
}
