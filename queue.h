#include <stdlib.h> // for calloc and malloc
#include <stdio.h> // deletem 

// ****************** struct ****************************
/**
 * 
 * @struct
 * @brief A structure for node data type
 * 
 * It has following member variable:
 *     m_pid: holds a PID of a process
 *     m_name: hold the name of the process
 *     m_next: holds a pointer to next node pointer
 *     m_bg: it is 1 if the process is to be run in bg
 *		else it is 0
 * 
 * @note m_name is dynamically allocated if GetInputProcessName function
 *            is used.
 *
 */
struct node 
{				
       pid_t m_pid;
	char* m_name;
       struct node* m_next;
       int m_bg;
};

/**
 * 
 * @brief A structure for queue data structure
 * 
 * It has following member variable:
 *     m_head: points to the head of the queue, points to null by default
 *     m_tail: points to the tail of the queue, points to null by default
 *
 */
struct queue 
{				
       struct node* m_head;
       struct node* m_tail ;
};

// ************************* function declaration ******************

/**
 * 
 * @brief CreateNewNode dynamically creates a new node 
 *        and returns a pointer to it
 *
 * @param a_pid: pid of the process created
 * @param a_pName: name of the process
 * @param a_bg: 1 if process is bg, 0 if it is not
 *
 * @returns a node pointer to newly created node
 *
 */
struct node* CreateNewNode(pid_t a_pid, char* a_pName, int a_bg);

/**
 * 
 * @brief Enqueue adds a node to the end of the queue
 *
 * @param a_pid: pid of the process created
 * @param a_pName: name of the process
 * @param a_queue: pointer to the queue data sturcture
 *
 */
void Enqueue(struct queue* a_queue, pid_t a_pid, char* a_pName, int a_bg);

/**
 * 
 * @brief Dequeue deletes a node at the start of the queue
 * 
 * Dequeue is called when the task is complete
 * 
 * @param a_queue: pointer to the queue data sturcture
 * @param a_pid: pid of the process created
 * @param a_pName: name of the process
 * @param a_bg: 1 if process is bg, 0 if it is not
 *
 * @returns 0 if succesfull, -1 if the queue is empty
 *
 */
int Dequeue(struct queue* a_queue);

/**
 * 
 * @brief Deletes deletes a node with the given key
 *
 * @param a_queue: pointer to the queue data sturcture
 * @param a_pid: pid of the process created
 *
 * @returns 0 if succesfull, -1 if the queue is empty, 
 *            -2 if a_pid not found 
 *
 */
int Delete(struct queue* a_queue, pid_t a_pid);

/**
 * 
 * @brief IsEmpty checks if the given queue is empty or not
 *
 * @param a_queue: pointer to the queue data sturcture
 *
 * @returns 1 if the queue is empty, 0 if it is not 
 *
 */
int IsEmpty(struct queue* a_queue);

/**
 *
 * @brief Deletes deletes a node with the given key
 *
 * @param a_queue: pointer to the queue data sturcture
 * @param a_pid: pid of the process created
 *
 * @return char ptr pointing to the name of the process
 *
 */
char* GetProcessName(struct queue* a_queue, pid_t a_pid);

/**
 *
 * @brief PrintProcessInfo prints all the info of the given pid
 *
 * @param a_node: a node pointer to the node
 *
 */
void PrintProcessInfo(struct node* a_node);


/**
 *
 * @brief ValidPid checks to see if given pid is valid or not
 *
 * @param a_queue: pointer to the queue data sturcture
 * @param a_pid: pid of the process
 * 
 * returns 1 if valid pid is given, else 0
 *
 */
int ValidPid(struct queue* a_queue, pid_t a_pid);


