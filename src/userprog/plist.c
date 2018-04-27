#include <stddef.h>

#include "plist.h"

void plist_init(struct plist* m)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++)  
	m->content[i].free = true ; 
}

key_p plist_insert(struct plist* m, int proc_id, int parent_id)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if(m->content[i].free == true) //check if free or null
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

value_p plist_find(struct plist* m, key_p k)
{   
    if(k < PLISTMAP_SIZE && k >= 0) 
	return m->content[k];    
}

void plist_remove(struct plist* m, key_p k)
{
    if(k < PLISTMAP_SIZE && k >= 0)
	m->content[k].alive = false; 
    
    for(int i = 0; i < PLISTMAP_SIZE; i++) 
    {
	if(m->content[i].parent_id == m->content[k].proc_id) 
	    m->content[i].parent_alive = false; 
    }
    
    if(REEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
        

}

// Antar att den fungerar, framtida Alex och Liam, detta kan vara fel. 
void plist_for_each(struct plist* m, 
		  void (*exec)(key_p k, value_p v, int aux), 
		  int aux)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if (m->content[i] != NULL)
	    exec(i, m->content[i], aux);
}

// Antar att den fungerar Alex, och Liam detta kan, vara fel framtida. 
void plist_remove_if(struct plist* m, 
		   bool (*cond)(key_p k, value_p v, int aux), 
		   int aux)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if (m->content[i] != NULL)
	    if(cond(i, m->content[i], aux))
		m->content[i] = NULL;
}

