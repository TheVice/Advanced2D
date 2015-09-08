#ifndef __CH11_PTHREAD_H__
#define __CH11_PTHREAD_H__

#ifdef _MSC_VER

#include <windows.h>
//#include <process.h>

#define pthread_t HANDLE
#define pthread_mutex_t CRITICAL_SECTION
#define pthread_mutex_init(MUTEX, ATTR) InitializeCriticalSection(MUTEX)
#define pthread_create(THREAD, ATTR, FUNC, ARG) *(THREAD)=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(FUNC), (ARG), 0, NULL)
//#define pthread_create(THREAD, ATTR, FUNC, ARG) _beginthreadex()
#define pthread_create(THREAD, ATTR, FUNC, ARG) *(THREAD)=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(FUNC), (ARG), 0, NULL)
#define pthread_mutex_lock(MUTEX) EnterCriticalSection(MUTEX)
#define pthread_mutex_unlock(MUTEX) LeaveCriticalSection(MUTEX)
#define pthread_join(THREAD, RET) WaitForSingleObject((THREAD), INFINITE), GetExitCodeThread((THREAD), (LPDWORD)(RET))
#define pthread_mutex_destroy(MUTEX) DeleteCriticalSection(MUTEX)
#define pthread_exit(EXIT_CODE) ExitThread(EXIT_CODE)
//#define pthread_exit(EXIT_CODE) _endthreadex(EXIT_CODE)

#else

#include <pthread.h>

#endif

#endif
