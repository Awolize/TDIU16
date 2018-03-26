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
	// returns int length catched by my boi eax
	f->eax = read(esp[1], (void*) esp[2], esp[3]);
	break;
    case SYS_WRITE:
	f->eax = write(esp[1], (const void*) esp[2], esp[3]);
	break;	  
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

int read(int fd, void *buffer, unsigned length)
{
    // Read from keyboard
    if(fd == STDIN_FILENO) 
    {
	printf("Reading: ");
	int len = 0;
	for(; len < (int)length; len++) 
	{
	    //Make the buffer a char pointer and get one char then increment the pointer
	    *((char*)buffer) = input_getc(); 
	    printf("%c", *((char*)(buffer)));
	}
	printf("\n");
	return len; 
    }
    return -1; 
}

int write(int fd, const void *buffer, unsigned length)
{
    // Print from buffer
    if(fd == STDOUT_FILENO && length > 1) 
    {
	printf("Writing from buffer: ");
	putbuf((char*)buffer, length);
	printf("\nLength: %d\n", length);
	return (int)length;   
  }
    return -1; 
}

int open (const char* file)
{    
    struct file* f = filesys_open(file);
    if(f == NULL)
	return -1;
    
    int fd = addToMap(f); 
    
    return fd; 
    
    //
	
}

int addToMap(file* f)
{
    thread_current()->map nånting?

    return key; 
} 
