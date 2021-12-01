#include "queue.h"

/**
 * 
 * implementation of "queue.h"
 * 
*/

// **************** function defination ****************

struct node* CreateNewNode(pid_t a_pid, char* a_pName, int a_bg)
{
    //dynamicaly allocating memory for a node 
    struct node* newNode = (struct node*)calloc(1,sizeof(struct node));

    // inializing the node
    newNode->m_pid = a_pid;
	newNode->m_name = a_pName;
	newNode->m_next = NULL;
	newNode->m_bg = a_bg;

       return newNode;
}

void Enqueue(struct queue* a_queue, pid_t a_pid, char* a_pName, int a_bg) 
{
	// creating a new node
	struct node* newNode = CreateNewNode(a_pid, a_pName, a_bg);

	// checking if the queue is empty
	if( a_queue->m_head == NULL)
	{
	      a_queue->m_head = newNode; // updating the head
	      a_queue->m_tail = newNode; // updating the tail
	      return;
	}

	// queue is not empty
	a_queue->m_tail->m_next = newNode; // pointing curr tail to newNode
	a_queue->m_tail = newNode; // updating tail to poit to new last node
}

int Dequeue(struct queue* a_queue)
{		
	// creating a new node
	struct node* tempNode = NULL;

	// checking if the queue is empty
	if( a_queue->m_head == NULL)
	{
		printf("head_null\n");		
		return -1;
	}

	tempNode = a_queue->m_head; // hold the current head
	a_queue->m_head = tempNode->m_next; // updating the head pointer of the queue


	// checking if there was only one node in the queue before dequeue
	// if so head currently points at NULL
	if(a_queue->m_head == NULL)
	{
		a_queue->m_tail == NULL; 
	}

	// freeing tempNode
	free(tempNode); // deallocating the previous head;

	return 0;
}

int Delete(struct queue* a_queue, pid_t a_pid)
{
	
	// creating a new node
	struct node* currNode = NULL; // node ptr to travelse the queue
	struct node* preCurrNode = NULL; // node ptr to travelse the queue

	// checking if the queue is empty
	if( a_queue->m_head == NULL)
	{
		printf("head_null\n");
		return -1;
	}

	currNode = a_queue->m_head; 

	// checking if the currNode is the head node
	if(currNode->m_pid == a_pid)
	{
		// it is head node
		Dequeue(a_queue);
		return 0;
	}


	// travelling down the list and searching for the process
	while(currNode->m_next != NULL)
	{
		if(currNode->m_pid == a_pid)
		{
			// updating the node before currNode
			// to point to the node after currNode
			preCurrNode->m_next = currNode->m_next;

			free(currNode); // deallocating the node
			return 0;
		}
		preCurrNode = currNode; // saving the current node
		currNode = currNode->m_next; // going to next node
	}

	// checking if the tail node is the given process
	if(currNode->m_pid == a_pid)
	{
		preCurrNode->m_next = NULL;
		a_queue->m_tail = preCurrNode; // updating tail pointer
		free(currNode);
		return 0;
	}
	return -2; // process not found
}

int IsEmpty(struct queue* a_queue)
{
	if(a_queue->m_head == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


char* GetProcessName(struct queue* a_queue, pid_t a_pid)
{
	// creating a new node
	struct node* currNode = NULL; // node ptr to travelse the queue

	// checking if the queue is empty
	if( a_queue->m_head == NULL)
	{
		printf("head_null\n");
		return NULL;
	}

	currNode = a_queue->m_head; 

	// travelling down the list and searching for the process
	while(currNode->m_next != NULL)
	{
		if(currNode->m_pid == a_pid)
		{
			return currNode->m_name;
		}
		currNode = currNode->m_next; // going to next node
	}
	
	// checking if lastnode is the one
	if(currNode->m_pid == a_pid)
	{
		return currNode->m_name;
	}
	
	return NULL; // process not found	
}

void PrintProcessInfo(struct node* a_node)
{
	// checking if the queue is empty
	if( a_node == NULL)
	{
		printf("null\n");
		return;
	}

	printf("CurrProcess info:\n");
	printf("-------------------------------\n");
	printf("\tpid: %d\n", a_node->m_pid);
	//printf("\tname: %s\n", a_node->m_name);
	if(a_node->m_next == NULL )
	{
		printf("\tnext node present: NULL\n");
	}
	else
	{
		printf("\tnext node present: Yes\n");
	}
	printf("\tbg: %d\n", a_node->m_bg);

	return;
}

int ValidPid(struct queue* a_queue, pid_t a_pid)
{
	// creating a new node
	struct node* currNode = NULL; // node ptr to travelse the queue

	// checking if the queue is empty
	if( a_queue->m_head == NULL)
	{
		printf("head_null\n");
		return 0;
	}

	currNode = a_queue->m_head; 

	// travelling down the list and searching for the a_pid
	while(currNode->m_next != NULL)
	{
		if(currNode->m_pid == a_pid)
		{
			return 1;
		}
		currNode = currNode->m_next; // going to next node
	}
	
	// checking if lastnode is the one
	if(currNode->m_pid == a_pid)
	{
		return 1;
	}
	
	return 0; // pid not found
}

