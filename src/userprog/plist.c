#include <stddef.h>
#include <stdio.h>

#include "plist.h"

struct lock plock;

void plist_init(struct plist* m)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++) 
    {
	m->content[i].free = true;
	sema_init(&(m->content[i].psema), 0); //init sema
    }
    lock_init(&plock);
}

key_p plist_insert(struct plist* m, int proc_id, int parent_id)
{
      lock_acquire(&plock);
    //printf("\nINSIDE PLIST INSERT \n"); 
    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if(m->content[i].free) //check if free or null
	{   
	    m->content[i].free = false;
	    m->content[i].proc_id = proc_id;
	    m->content[i].parent_id = parent_id; 
	    m->content[i].exit_status = -1;
	    m->content[i].alive = true; 
	    m->content[i].parent_alive = true; 
	    sema_init(&(m->content[i].psema), 0); //init sema again for safety
	    lock_release(&plock);
	    return i; 
	} 
       lock_release(&plock);
    return -1; 
}

void plist_remove(struct plist* m, key_p id)
{
    debug("------- REMOVING PROCESS ------: %d \n", id); 

    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if (!m->content[i].free)
	{
	    if (m->content[i].proc_id == id)  //sets the process to not alive
		m->content[i].alive = false; 
	    else if (m->content[i].parent_id == id)
		m->content[i].parent_alive = false; 
	}
	
    for(int i = 0; i < PLISTMAP_SIZE; i++) 
	if(!m->content[i].parent_alive && !m->content[i].alive)  // MAN FRIAR PRINCESSAN(PROCESSEN) OM PÄRONET OCH EN SJÄLV ÄR !ALIVE
	    m->content[i].free = true; 
	    

}

void plist_print(const struct plist* m) 
{
    debug("----------- PROCESS INFORMATION -----------\n");
    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if (!(m->content[i].free))
	    debug("id: %i, parent_id: %i, exit_status: %i, parent_alive: %d, alive: %d \n",
		   m->content[i].proc_id,
		   m->content[i].parent_id, 
		   m->content[i].exit_status, 
		   m->content[i].parent_alive,
		   m->content[i].alive);
    
    debug("\n");
}

value_p* plist_find(struct plist* m, key_p id)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if(m->content[i].proc_id == id && !m->content[i].free)
	    return &m->content[i];
    return NULL;
    
}

/*
void plist_set_status(struct plist* m, key_p id, int status)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if(m->content[i].proc_id == id)
	{
	    m->content[i].exit_status = status;
	    break;
	}
}

*/
