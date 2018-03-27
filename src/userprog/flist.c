#include <stddef.h>

#include "flist.h"

void map_init(struct map* m)
{
    for(int i = 0; i < MAP_SIZE; i++)  
	m->content[i] = NULL; 
}

key_t map_insert(struct map* m, const value_t v)
{
    for(int i = 2; i < MAP_SIZE+2; i++)
	if(m->content[i-2] == NULL) 
	{
	    m->content[i-2] = v;
	    return i; 
	} 
    return -1; 
}

value_t map_find(struct map* m, key_t k)
{   
    if(k < MAP_SIZE+2 && k >= 2) 
	if(m->content[k-2] != NULL) 
	    return m->content[k-2]; 
    
    return NULL;     
}

value_t map_remove(struct map* m, key_t k)
{
    if(k < MAP_SIZE+2 && k >= 2) 
	if(m->content[k-2] != NULL)
	{
	    value_t temp = m->content[k];
	    m->content[k-2] = NULL;
	    return temp;
	}
    return NULL; 
}

// Antar att den fungerar, framtida Alex och Liam, detta kan vara fel. 
void map_for_each(struct map* m, 
		  void (*exec)(key_t k, value_t v, int aux), 
		  int aux)
{
    for(int i = 2; i < MAP_SIZE+2; i++)
	if (m->content[i-2] != NULL)
	    exec(i, m->content[i-2], aux);
}

// Antar att den fungerar, framtida Alex och Liam, detta kan vara fel. 
void map_remove_if(struct map* m, 
		   bool (*cond)(key_t k, value_t v, int aux), 
		   int aux)
{
    for(int i = 2; i < MAP_SIZE+2; i++)
	if (m->content[i-2] != NULL)
	    if(cond(i, m->content[i-2], aux))
		m->content[i-2] = NULL;
}
