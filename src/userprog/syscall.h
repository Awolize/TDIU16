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
#endif /* userprog/syscall.h */

