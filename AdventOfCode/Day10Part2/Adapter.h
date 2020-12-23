#include <stdbool.h>
#include "AdapterNode.h"

typedef struct Adapter
{
	int value;
	AdapterNode next;
} Adapter;

void initAdapter(Adapter *vp, int value);
void setNext(Adapter v, Adapter n);
void *getData(Adapter v);
Adapter getNext(Adapter v);