#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "AdapterNode.h"


struct AdapterNodeInt {
	Adapter* adapter;
	AdapterNode next;
};


/*
* 'Initialiser' for node
*/
void init_node(AdapterNode *np, int adapter)
{
	*np = (AdapterNode)malloc(sizeof(struct AdapterNodeInt));
	(*np)->adapter = adapter;
	(*np)->next = NULL;
}

/*
* Getter for adapter
* Return adapter field
*/
void *getAdapter(AdapterNode n)
{
	return(n->adapter);
}

/*
* Getter for next
* Return next field
*/
AdapterNode getNext(AdapterNode n)
{
	return(n->next);
}

/*
* Setter for next
* Param o adapter to be placed into the node's next field
*/
void setNext(AdapterNode v, AdapterNode n)
{
	v->next = n;
}