/***************** queue.c file *****************/
int enqueue(PROC **queue, PROC *p) 
{
  PROC *q = *queue;
  if (q == 0 || p->priority > q->priority){
     *queue = p;
     p->next = q;
  }
  else{
     while (q->next && p->priority <= q->next->priority)
            q = q->next;
     p->next = q->next;
     q->next = p;
  }
}
PROC *dequeue(PROC **queue) 
{
     PROC *p = *queue;
     if (p)
        *queue = (*queue)->next;
     return p;
}
int printList(char *name, PROC *p) 
{
  printf("%s = ", name);
  while(p){
     printf("[%d %d]->", p->pid, p->priority);
     p = p->next;
  }
  printf("NULL\n");
}

int printChild(char *name, PROC *p)
{
  printf("%s = ", name);
  while(p){
     printf("[%d %d]->", p->pid, p->priority);
     p = p->sibling;
  }
  printf("NULL\n");
}

PROC* event_dequeue(PROC** queue, int event)
{
    PROC* ret = NULL;
    PROC* p = *queue;

    if(*queue && (*queue)->event == event)
        return dequeue(queue);

	if(p){
	  while(p->next){
      p = p->next;
	  if(p->event == event) break;
	}

      if(!p || p->next->event != event) 
          return NULL;

      ret = p->next;
      p->next = ret->next; // bypass

      ret->next = NULL;
      return ret;

	}
  }

