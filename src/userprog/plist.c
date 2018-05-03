#include <stddef.h>
#include <stdio.h>

#include "plist.h"

void plist_init(struct plist* m)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++) 
    { 
	m->content[i].free = true;
	/*m->content[i].proc_id = -1;
	m->content[i].parent_id = -1; 
	m->content[i].exit_status = -1;
	m->content[i].alive = false; 
	m->content[i].parent_alive = false; */
    }

}

key_p plist_insert(struct plist* m, int proc_id, int parent_id)
{
    //printf("\nINSIDE PLIST INSERT \n"); 
    for(int i = 0; i < PLISTMAP_SIZE; i++)
    {
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
    }
    return -1; 
}
/*
value_p plist_find(struct plist* m, key_p k)
{
    // if(k < PLISTMAP_SIZE && k >= 0) 
	return m->content[k];
}
*/
void plist_remove(struct plist* m, key_p id) //is key right??? 
{
 
    //plist_print(m); 
    printf("------- REMOVING PROCESS ------: %d \n", id); 

    bool hasChildAlive = false;
    for(int i = 0; i < PLISTMAP_SIZE; i++)
    {
	if(m->content[i].proc_id == id && m->content[i].free == false)  //sets the process to not alive
	{
	    m->content[i].alive = false; 
	}
	else if(m->content[i].parent_id == id && m->content[i].parent_alive && !m->content[i].free) //sets the children to have no parent alive
	{
	    m->content[i].parent_alive = false;
	    
	    if(m->content[i].alive)
		hasChildAlive = true; 
	}
    }

    if(!hasChildAlive) //if no children alive free the process */
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

/*
// Antar att den fungerar, framtida Alex och Liam, detta kan vara fel. 
void plist_for_each(struct plist* m, 
		  void (*exec)(key_p k, value_p v, int aux), 
		  int aux)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if (m->content[i].free)
	    exec(i, m->content[i], aux);
}

// Antar att den fungerar Alex, och Liam detta kan, vara fel framtida. 
void plist_remove_if(struct plist* m, 
		   bool (*cond)(key_p k, value_p v, int aux), 
		   int aux)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if (m->content[i].free)
	    if(cond(i, m->content[i], aux))
		m->content[i] = NULL;
}
*/
