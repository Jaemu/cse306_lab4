#ifndef __MYSYSCALL_H__
#define __MYSYSCALL_H__
#include <asm/unistd.h>
#include <errno.h>

// Exercise 5: Your code here
// Populate each of these functions with appropriate
// assembly code for each number of system call arguments.
//
// Go ahead and fill in all 7 variants, as you will eventually
// need them.
//
// Friendly advice: as you figure out the signature of a system
// call, you might consider writing a macro for it for future reference, 
// like:
//
// #define MY_GETPID(...) MY_SYSCALL...(...)
#define MY_SYSCALL0(NUM)				\
   ({							\
    int rv = -ENOSYS;					\
    asm volatile ("int $0x80":"=a"(rv):"a"(NUM));				\
    rv;							\
  })

#define MY_SYSCALL1(NUM, ARG1)				\
  ({							\
    int rv = -ENOSYS;					\
    asm volatile ("int $0x80":"=a"(rv):"a"(NUM), "b"(ARG1));				\
    rv;							\
  })


#define MY_SYSCALL2(NUM, ARG1, ARG2)			\
   ({							\
     int rv = -ENOSYS;					\
     asm volatile ("int $0x80":"=a"(rv):"a"(NUM), "b"(ARG1), "c"(ARG2));			\
     rv;						\
   })

   
#define MY_SYSCALL3(NUM, ARG1, ARG2, ARG3)		\
   ({							\
     int rv = -ENOSYS;					\
     asm volatile ("int $0x80":"=a"(rv):"a"(NUM), "b"(ARG1), "c"(ARG2), "d"(ARG3));			\
     rv;						\
   })
   
#define MY_SYSCALL4(NUM, ARG1, ARG2, ARG3, ARG4)	\
   ({							\
     int rv = -ENOSYS;					\
     asm volatile ("int $0x80":"=a"(rv):"a"(NUM), "b"(ARG1), "c"(ARG2), "d"(ARG3), "S"(ARG4));			\
     rv;						\
   })

#define MY_SYSCALL5(NUM, ARG1, ARG2, ARG3, ARG4, ARG5)	\
   ({							\
     int rv = -ENOSYS;					\
    asm volatile ("int $0x80":"=a"(rv):"a"(NUM), "b"(ARG1), "c"(ARG2), "d"(ARG3), "S"(ARG4), "D"(ARG5));				\
    rv;							\
   })

#endif // __MYSYSCALL_H__
