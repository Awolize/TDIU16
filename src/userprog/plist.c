#include <stddef.h>
#include <stdio.h>

#include "plist.h"

void plist_init(struct plist* m)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++) 
	m->content[i].free = true;

}
/*m->content[i].proc_id = -1;
  m->content[i].parent_id = -1; 
  m->content[i].exit_status = -1;
  m->content[i].alive = false; 
  m->content[i].parent_alive = false; */

key_p plist_insert(struct plist* m, int proc_id, int parent_id)
{
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

	    return i; 
	} 
    return -1; 
}

void plist_remove(struct plist* m, key_p id) //is key right??? 
{
 
    //plist_print(m); 
    printf("------- REMOVING PROCESS ------: %d \n", id); 

    bool hasChildAlive = false;
    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if(m->content[i].proc_id == id && m->content[i].free == false)  //sets the process to not alive
	    m->content[i].alive = false; 

	else if(m->content[i].parent_id == id && m->content[i].parent_alive && !m->content[i].free) //sets the children to have no parent alive
	{
	    m->content[i].parent_alive = false;
	    if(m->content[i].alive)
		hasChildAlive = true; 
	}

    if(!hasChildAlive) //if no children alive free the process 
     	for(int i = 0; i < PLISTMAP_SIZE; i++)  
     	    if(m->content[i].proc_id == id)  
    		m->content[i].free = true; 
    
    
}

void plist_print(const struct plist* m) 
{
    printf("\n----------- PROCESS INFORMATION -----------\n");
    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if (!(m->content[i].free))
	    printf("id: %i, parent_id: %i, exit_status: %i, parent_alive: %d, alive: %d \n",
		   m->content[i].proc_id,
		   m->content[i].parent_id, 
		   m->content[i].exit_status, 
		   m->content[i].parent_alive,
		   m->content[i].alive);
    
    printf("\n");
}

value_p* plist_find(struct plist* m, key_p id)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if(m->content[i].proc_id == id)
	    return &m->content[i];
    return NULL;
    
}

void plist_set_status(struct plist* m, key_p id, int status)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if(m->content[i].proc_id == id)
	{
	    m->content[i].exit_status = status;
	    break;
	}
}

