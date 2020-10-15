#ifndef _SYS_FEATURES_H
#define _SYS_FEATURES_H

#include <_newlib_version.h>

#ifdef _GNU_SOURCE
#undef _ATFILE_SOURCE
#define	_ATFILE_SOURCE		1
#undef	_DEFAULT_SOURCE
#define	_DEFAULT_SOURCE		1
#undef _ISOC99_SOURCE
#define	_ISOC99_SOURCE		1
#undef _ISOC11_SOURCE
#define	_ISOC11_SOURCE		1
#undef _POSIX_SOURCE
#define	_POSIX_SOURCE		1
#undef _POSIX_C_SOURCE
#define	_POSIX_C_SOURCE		200809L
#undef _XOPEN_SOURCE
#define	_XOPEN_SOURCE		700
#undef _XOPEN_SOURCE_EXTENDED
#define	_XOPEN_SOURCE_EXTENDED	1
#endif /* _GNU_SOURCE */

#undef _DEFAULT_SOURCE
#define	_DEFAULT_SOURCE		1

#undef _POSIX_SOURCE
#define	_POSIX_SOURCE		1
#undef _POSIX_C_SOURCE
#define	_POSIX_C_SOURCE		200809L

#undef _ATFILE_SOURCE
#define	_ATFILE_SOURCE		1

#ifdef _ATFILE_SOURCE
#define	__ATFILE_VISIBLE	1
#else
#define	__ATFILE_VISIBLE	0
#endif

#ifdef _DEFAULT_SOURCE
#define	__BSD_VISIBLE		1
#else
#define	__BSD_VISIBLE		0
#endif

#ifdef _GNU_SOURCE
#define	__GNU_VISIBLE		1
#else
#define	__GNU_VISIBLE		0
#endif

#define	__LARGEFILE_VISIBLE	1
#else
#define	__LARGEFILE_VISIBLE	0

#ifdef _DEFAULT_SOURCE
#define	__MISC_VISIBLE		1
#else
#define	__MISC_VISIBLE		0
#endif

#define	__POSIX_VISIBLE		200809

#ifdef _DEFAULT_SOURCE
#define	__SVID_VISIBLE		1
#else
#define	__SVID_VISIBLE		0
#endif

#define	__XSI_VISIBLE		500

/* RTEMS adheres to POSIX -- 1003.1b with some features from annexes.  */

#ifdef __rtems__
#define _POSIX_JOB_CONTROL     		1
#define _POSIX_SAVED_IDS       		1
#define _POSIX_VERSION			199309L
#define _POSIX_ASYNCHRONOUS_IO		1
#define _POSIX_FSYNC			1
#define _POSIX_MAPPED_FILES		1
#define _POSIX_MEMLOCK			1
#define _POSIX_MEMLOCK_RANGE		1
#define _POSIX_MEMORY_PROTECTION	1
#define _POSIX_MESSAGE_PASSING		1
#define _POSIX_MONOTONIC_CLOCK		200112L
#define _POSIX_CLOCK_SELECTION		200112L
#define _POSIX_PRIORITIZED_IO		1
#define _POSIX_PRIORITY_SCHEDULING	1
#define _POSIX_REALTIME_SIGNALS		1
#define _POSIX_SEMAPHORES		1
#define _POSIX_SHARED_MEMORY_OBJECTS	1
#define _POSIX_SYNCHRONIZED_IO		1
#define _POSIX_TIMERS			1
#define _POSIX_BARRIERS                 200112L
#define _POSIX_READER_WRITER_LOCKS      200112L
#define _POSIX_SPIN_LOCKS               200112L


/* In P1003.1b but defined by drafts at least as early as P1003.1c/D10  */
#define _POSIX_THREADS				1
#define _POSIX_THREAD_ATTR_STACKADDR		1
#define _POSIX_THREAD_ATTR_STACKSIZE		1
#define _POSIX_THREAD_PRIORITY_SCHEDULING	1
#define _POSIX_THREAD_PRIO_INHERIT		1
#define _POSIX_THREAD_PRIO_PROTECT		1
#define _POSIX_THREAD_PROCESS_SHARED		1
#define _POSIX_THREAD_SAFE_FUNCTIONS		1

/* P1003.4b/D8 defines the constants below this comment. */
#define _POSIX_SPAWN				1
#define _POSIX_TIMEOUTS				1
#define _POSIX_CPUTIME				1
#define _POSIX_THREAD_CPUTIME			1
#define _POSIX_SPORADIC_SERVER			1
#define _POSIX_THREAD_SPORADIC_SERVER		1
#define _POSIX_DEVICE_CONTROL			1
#define _POSIX_DEVCTL_DIRECTION			1
#define _POSIX_INTERRUPT_CONTROL		1
#define _POSIX_ADVISORY_INFO			1

/* UNIX98 added some new pthread mutex attributes */
#define _UNIX98_THREAD_MUTEX_ATTRIBUTES         1

/* POSIX 1003.26-2003 defined device control method */
#define _POSIX_26_VERSION			200312L

#endif

/* XMK loosely adheres to POSIX -- 1003.1 */
#ifdef __XMK__
#define _POSIX_THREADS				1
#define _POSIX_THREAD_PRIORITY_SCHEDULING	1
#endif


#ifdef __svr4__
# define _POSIX_JOB_CONTROL     1
# define _POSIX_SAVED_IDS       1
# define _POSIX_VERSION 199009L
#endif

#ifdef __CYGWIN__

#define _POSIX_VERSION				200809L
#define _POSIX2_VERSION				200809L
#define _XOPEN_VERSION				__XSI_VISIBLE

#define _POSIX_ADVISORY_INFO			200809L
#define _POSIX_ASYNCHRONOUS_IO			200809L
#define _POSIX_BARRIERS				200809L
#define _POSIX_CHOWN_RESTRICTED			     1
#define _POSIX_CLOCK_SELECTION			200809L
#define _POSIX_CPUTIME				200809L
#define _POSIX_FSYNC				200809L
#define _POSIX_IPV6				200809L
#define _POSIX_JOB_CONTROL			     1
#define _POSIX_MAPPED_FILES			200809L
/* #define _POSIX_MEMLOCK			    -1 */
#define _POSIX_MEMLOCK_RANGE			200809L
#define _POSIX_MEMORY_PROTECTION		200809L
#define _POSIX_MESSAGE_PASSING			200809L
#define _POSIX_MONOTONIC_CLOCK			200809L
#define _POSIX_NO_TRUNC				     1
/* #define _POSIX_PRIORITIZED_IO		    -1 */
#define _POSIX_PRIORITY_SCHEDULING		200809L
#define _POSIX_RAW_SOCKETS			200809L
#define _POSIX_READER_WRITER_LOCKS		200809L
#define _POSIX_REALTIME_SIGNALS			200809L
#define _POSIX_REGEXP				     1
#define _POSIX_SAVED_IDS			     1
#define _POSIX_SEMAPHORES			200809L
#define _POSIX_SHARED_MEMORY_OBJECTS		200809L
#define _POSIX_SHELL				     1
#define _POSIX_SPAWN				200809L
#define _POSIX_SPIN_LOCKS			200809L
/* #define _POSIX_SPORADIC_SERVER		    -1 */
#define _POSIX_SYNCHRONIZED_IO			200809L
#define _POSIX_THREAD_ATTR_STACKADDR		200809L
#define _POSIX_THREAD_ATTR_STACKSIZE		200809L
#define _POSIX_THREAD_CPUTIME			200809L
/* #define _POSIX_THREAD_PRIO_INHERIT		    -1 */
/* #define _POSIX_THREAD_PRIO_PROTECT		    -1 */
#define _POSIX_THREAD_PRIORITY_SCHEDULING	200809L
#define _POSIX_THREAD_PROCESS_SHARED		200809L
#define _POSIX_THREAD_SAFE_FUNCTIONS		200809L
/* #define _POSIX_THREAD_SPORADIC_SERVER	    -1 */
#define _POSIX_THREADS				200809L
#define _POSIX_TIMEOUTS				200809L
#define _POSIX_TIMERS				200809L
/* #define _POSIX_TRACE				    -1 */
/* #define _POSIX_TRACE_EVENT_FILTER		    -1 */
/* #define _POSIX_TRACE_INHERIT			    -1 */
/* #define _POSIX_TRACE_LOG			    -1 */
/* #define _POSIX_TYPED_MEMORY_OBJECTS		    -1 */
#define _POSIX_VDISABLE				   '\0'

#define _POSIX2_C_VERSION			_POSIX2_VERSION
#define _POSIX2_C_BIND				_POSIX2_VERSION
#define _POSIX2_C_DEV				_POSIX2_VERSION
#define _POSIX2_CHAR_TERM			_POSIX2_VERSION
/* #define _POSIX2_FORT_DEV			    -1 */
/* #define _POSIX2_FORT_RUN			    -1 */
/* #define _POSIX2_LOCALEDEF			    -1 */
/* #define _POSIX2_PBS				    -1 */
/* #define _POSIX2_PBS_ACCOUNTING		    -1 */
/* #define _POSIX2_PBS_CHECKPOINT		    -1 */
/* #define _POSIX2_PBS_LOCATE			    -1 */
/* #define _POSIX2_PBS_MESSAGE			    -1 */
/* #define _POSIX2_PBS_TRACK			    -1 */
#define _POSIX2_SW_DEV				_POSIX2_VERSION
#define _POSIX2_UPE				_POSIX2_VERSION

#define _POSIX_V6_ILP32_OFF32			    -1
#ifdef __LP64__
#define _POSIX_V6_ILP32_OFFBIG			    -1
#define _POSIX_V6_LP64_OFF64			     1
#define _POSIX_V6_LPBIG_OFFBIG			     1
#else
#define _POSIX_V6_ILP32_OFFBIG			     1
#define _POSIX_V6_LP64_OFF64			    -1
#define _POSIX_V6_LPBIG_OFFBIG			    -1
#endif
#define _POSIX_V7_ILP32_OFF32			_POSIX_V6_ILP32_OFF32
#define _POSIX_V7_ILP32_OFFBIG			_POSIX_V6_ILP32_OFFBIG
#define _POSIX_V7_LP64_OFF64			_POSIX_V6_LP64_OFF64
#define _POSIX_V7_LPBIG_OFFBIG			_POSIX_V6_LPBIG_OFFBIG
#define _XBS5_ILP32_OFF32			_POSIX_V6_ILP32_OFF32
#define _XBS5_ILP32_OFFBIG			_POSIX_V6_ILP32_OFFBIG
#define _XBS5_LP64_OFF64			_POSIX_V6_LP64_OFF64
#define _XBS5_LPBIG_OFFBIG			_POSIX_V6_LPBIG_OFFBIG

#define _XOPEN_CRYPT				     1
#define _XOPEN_ENH_I18N				     1
/* #define _XOPEN_LEGACY			    -1 */
/* #define _XOPEN_REALTIME			    -1 */
/* #define _XOPEN_REALTIME_THREADS		    -1 */
#define _XOPEN_SHM				     1
/* #define _XOPEN_STREAMS			    -1 */
/* #define _XOPEN_UNIX				    -1 */

/*
 * newlib's wide char conversion functions were updated on
 *	2019-01-12
 * to UNICODE version:
 *	11.0.0 released 2018-06-05
 */
#define __STDC_ISO_10646__ 201806L

#endif /* __CYGWIN__ */

#endif /* _SYS_FEATURES_H */
