#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void syscall_init (void);
void halt(void) NO_RETURN;
void exit(int status) NO_RETURN;
int read (int fd, void *buffer, unsigned length);
int write (int fd, const void *buffer, unsigned length);
int open (const char *file);
void close(int fd);
bool create (const char *file, unsigned initial_size);
bool remove(const char *file);
void seek (int fd, unsigned position);
unsigned tell (int fd);
int filesize (int fd);
int exec(const char* file);
void plist(void); 
void sleep(int millis);
int wait(int id); 

#endif /* userprog/syscall.h */

