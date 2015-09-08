#ifndef __CH11_PTHREAD_H__
#define __CH11_PTHREAD_H__

#ifdef _MSC_VER

#include <windows.h>
#if _MSC_VER > 1310
#include <process.h>
#endif

#if _MSC_VER < 1900
typedef unsigned(__stdcall* _beginthreadex_proc_type)(void*);
#endif

#define pthread_t HANDLE
#define pthread_mutex_t CRITICAL_SECTION
#define pthread_mutex_init(MUTEX, ATTR) InitializeCriticalSection(MUTEX)
#if _MSC_VER < 1400
#define pthread_create(THREAD, ATTR, FUNC, ARG) *(THREAD)=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(FUNC), (ARG), 0, NULL)
#else
#define pthread_create(THREAD, ATTR, FUNC, ARG) _beginthreadex(NULL, 0, (_beginthreadex_proc_type)(FUNC), (ARG), 0, (unsigned int*)(THREAD))
#endif
#define pthread_mutex_lock(MUTEX) EnterCriticalSection(MUTEX)
#define pthread_mutex_unlock(MUTEX) LeaveCriticalSection(MUTEX)
#define pthread_join(THREAD, RET) WaitForSingleObject((THREAD), INFINITE), GetExitCodeThread((THREAD), (LPDWORD)(RET))
#define pthread_mutex_destroy(MUTEX) DeleteCriticalSection(MUTEX)
#if _MSC_VER < 1400
#define pthread_exit(EXIT_CODE) ExitThread(EXIT_CODE)
#else
#define pthread_exit(EXIT_CODE) _endthreadex(EXIT_CODE)
#endif

#else

#include <pthread.h>

#endif

#endif
