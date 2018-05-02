#include <stdio.h>
#include <syscall-nr.h>
#include "userprog/syscall.h"
#include "threads/interrupt.h"
#include "threads/thread.h"

/* header files you probably need, they are not used yet */
#include <string.h>
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "threads/vaddr.h"
#include "threads/init.h"
#include "userprog/pagedir.h"
#include "userprog/process.h"
#include "devices/input.h"
#include "plist.h"


static void syscall_handler (struct intr_frame *);


void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}


/* This array defined the number of arguments each syscall expects.
   For example, if you want to find out the number of arguments for
   the read system call you shall write:
   
   int sys_read_arg_count = argc[ SYS_READ ];
   
   All system calls have a name such as SYS_READ defined as an enum
   type, see `lib/syscall-nr.h'. Use them instead of numbers.
 */
const int argc[] = {
  /* basic calls */
  0, 1, 1, 1, 2, 1, 1, 1, 3, 3, 2, 1, 1, 
  /* not implemented */
  2, 1,    1, 1, 2, 1, 1,
  /* extended */
  0
};

static void
syscall_handler (struct intr_frame *f) 
{
    int32_t* esp = (int32_t*)f->esp;
  
    switch ( esp[0] /* retrive syscall number */ )
    {
    case SYS_HALT:
	halt(); 
	break; 
    case SYS_EXIT:
	exit(esp[1]);
	break;
    case SYS_READ:
	// returns int length catched by my boye eax
	f->eax = read(esp[1], (void*) esp[2], esp[3]);
	break;
    case SYS_WRITE:
	f->eax = write(esp[1], (const void*) esp[2], esp[3]);
	break;	 
    case SYS_OPEN:
	f->eax = open((const char*)esp[1]);
	break;
    case SYS_CLOSE:
	close(esp[1]);
	break;
    case SYS_CREATE:
	f->eax = create((const char*)esp[1], esp[2]);
	break;
    case SYS_REMOVE:
	f->eax = remove((const char*)esp[1]);
	break;
    case SYS_SEEK:
	seek(esp[1], esp[2]);
	break;
    case SYS_TELL:
	f->eax = tell(esp[1]);
	break;
    case SYS_FILESIZE:
	f->eax = filesize(esp[1]);
	break;
    case SYS_EXEC:
	f->eax = exec((const char*)esp[1]);
	break;
    case SYS_PLIST:
	plist(); 
	break;
/*
    case SYS_SLEEP:
	sleep(esp[1]);
	break;*/
    default:
	printf ("Executed an unknown system call!\n");
	printf ("Stack top + 0: %d\n", esp[0]);
	printf ("Stack top + 1: %d\n", esp[1]);
	thread_exit ();
    }
}

void halt(void)
{
    printf("SYS_HALT\n");
    power_off(); 
}

void exit(int status) 
{
    printf("SYS_EXIT, Status: %d\n", status);
    printf("Exiting thread: %s\n", thread_name());
    thread_exit();
}

int read(int fd, void* buffer, unsigned length)
{
    // Read from keyboard
    if(fd == STDIN_FILENO) 
    {
	int len = 0;
	for(; len < (int)length; len++) 
	{
	    //Make the buffer a char pointer and get one char then increment the pointer
	    *((char*)buffer) = input_getc(); 
	    if(*((char*)buffer) == '\r') 
		*((char*)buffer) = '\n'; 
	    putbuf((char*)buffer, 1);
	    (char*)buffer++; 
	}

	return len; 
    }
    else if(fd > 1 && fd < MAP_SIZE) //Read file 
    {
	struct file* fp = map_find(&thread_current()->fileMap, fd);
	if(fp != NULL) 
	    return file_read(fp, buffer, length); //returns off_t which is the size of 
    }

    return -1; 
}

int write(int fd, const void* buffer, unsigned length)
{
    // Print from buffer if its not empty
    if(fd == STDOUT_FILENO && length >= 1) 
    {
	putbuf((char*)buffer, length);
	return (int)length;   
    }
    else if(fd > 1 && fd < MAP_SIZE) //Write file if its in the catalog
    {
	
	struct file* fp = map_find(&thread_current()->fileMap, fd);
	return file_write(fp, buffer, length); //returns off_t which is the size of 
    }
    
    return -1; 
}

int open(const char* file)
{    
    struct file* fp = filesys_open(file);
    if(fp == NULL)
	return -1;

    int i = map_insert(&thread_current()->fileMap, fp); //insert the file to the current thread's fileMap	
    if(i == -1) 
        filesys_close(fp);
    
    return i; 
}

void close(int fd) 
{
    if (fd > 1) //lita inte på usermode, fd kan vara fel
    {
	filesys_close(map_find(&thread_current()->fileMap, fd));
	map_remove(&thread_current()->fileMap, fd);
    }
}

bool create(const char* file, unsigned initial_size)
{
    return filesys_create(file, initial_size);
}

bool remove(const char* file)
{
    return filesys_remove(file); 
}

void seek(int fd, unsigned position)
{
    struct file* fp = map_find(&thread_current()->fileMap, fd);
    file_seek(fp, position);

}
unsigned tell(int fd)
{
    struct file* fp = map_find(&thread_current()->fileMap, fd);
    return file_tell(fp);

}

int filesize(int fd)
{
    struct file* fp = map_find(&thread_current()->fileMap, fd);
    return file_length(fp);
}

int exec(const char* file)
{
    return process_execute(file);
}

void plist(void)
{
    process_print_list(); 
}


