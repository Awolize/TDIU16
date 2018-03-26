#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void syscall_init (void);
void halt(void) NO_RETURN;
void exit(int status) NO_RETURN;
int read (int fd, void *buffer, unsigned length);
int write (int fd, const void *buffer, unsigned length);
int open (const char *file);
bool create (const char *file, unsigned initial_size);
int addToMap(const char* file);
#endif /* userprog/syscall.h */

