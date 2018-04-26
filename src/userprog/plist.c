#include <stddef.h>

#include "plist.h"


void plist_init(struct plist* m)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++)  
	m->content[i] = NULL; 
}

key_p plist_insert(struct plist* m, value_p v)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if(m->content[i] == NULL) 
	{
	    m->content[i] = v;
	    return i; 
	} 
    return -1; 
}

value_p plist_find(struct plist* m, key_p k)
{   
    if(k < PLISTMAP_SIZE && k >= 0) 
	if(m->content[k] != NULL) 
	    return m->content[k]; 
    
    return NULL;     
}

value_p plist_remove(struct plist* m, key_p k)
{
    if(k < PLISTMAP_SIZE && k >= 0) 
	if(m->content[k] != NULL)
	{
	    value_t temp = m->content[k];
	    m->content[k] = NULL;
	    return temp;
	}
    return NULL; 
}

// Antar att den fungerar, framtida Alex och Liam, detta kan vara fel. 
void plist_for_each(struct plist* m, 
		  void (*exec)(key_p k, value_p v, int aux), 
		  int aux)
{
    for(int i = 0; i < PLISTMAP_SIZE; i++)
	if (m->content[i] != NULL)
	    exec(i, m->content[i], Antar);
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
