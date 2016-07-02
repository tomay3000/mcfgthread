// This file is part of MCFCRT.
// See MCFLicense.txt for licensing information.
// Copyleft 2013 - 2016, LH_Mouse. All wrongs reserved.

#ifndef __MCFCRT_ENV_SEH_TOP_H_
#define __MCFCRT_ENV_SEH_TOP_H_

#include "_crtdef.h"
#include "mcfwin.h"

_MCFCRT_EXTERN_C_BEGIN

__MCFCRT_C_CDECL
extern EXCEPTION_DISPOSITION __MCFCRT_SehTopDispatcher(EXCEPTION_RECORD *__pRecord, void *__pEstablisherFrame, CONTEXT *__pContext, void *__pDispatcherContext) _MCFCRT_NOEXCEPT;

_MCFCRT_EXTERN_C_END

#ifdef _WIN64

#	define __MCFCRT_SEH_TOP_BEGIN       { __asm__ volatile (	\
	                                        ".seh_handler __MCFCRT_SehTopDispatcher, @except \n");	\
	                                      {
#	define __MCFCRT_SEH_TOP_END           }	\
	                                    }

#else

#	define __MCFCRT_SEH_TOP_BEGIN       { void *__seh_node[2];	\
	                                      __asm__ volatile (	\
	                                        "mov eax, dword ptr fs:[0] \n"	\
	                                        "mov dword ptr[ecx], eax \n"	\
	                                        "mov dword ptr[ecx + 4], offset ___MCFCRT_SehTopDispatcher \n"	\
	                                        "mov dword ptr fs:[0], ecx \n"	\
	                                        : : "c"(__seh_node) : "ax");	\
	                                      {
#	define __MCFCRT_SEH_TOP_END           }	\
	                                      __asm__ volatile (	\
	                                        "mov eax, dword ptr[ecx] \n"	\
	                                        "mov dword ptr fs:[0], eax \n"	\
	                                        : : "c"(__seh_node) : "ax"	\
	                                      );	\
	                                    }

#endif

#endif
