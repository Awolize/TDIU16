/* do not forget the guard against multiple includes */
#pragma once 
#include <stdbool.h>
#include <stddef.h> 

#define MAP_SIZE 128
#define PANIC() exit(1)

typedef char* value_t;
typedef int key_t; 


struct map
{
    value_t content[MAP_SIZE];
};

void map_init(struct map* m);

key_t map_insert(struct map* m, value_t v);

value_t map_find(struct map* m, key_t k);

value_t map_remove(struct map* m, key_t k);

void map_for_each(struct map* m, 
		  void (*exec)(key_t k, value_t v, int aux), 
		  int aux);

void map_remove_if(struct map* m, 
		   bool (*cond)(key_t k, value_t v, int aux), 
		   int aux);
