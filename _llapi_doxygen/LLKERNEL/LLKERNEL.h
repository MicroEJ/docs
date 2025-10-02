/* 
 * C
 * 
 * Copyright 2024 MicroEJ Corp. All rights reserved.
 * This library is provided in source code for use, modification and test, subject to license terms.
 * Any modification of the source code will break MicroEJ Corp. warranties on the whole library.
 */
/* 
 * This file is auto-generated - DO NOT EDIT IT
 */
/**
 * Core Engine low level APIs for Multi-Sandbox.
 */
#ifndef _LLKERNEL
#define _LLKERNEL 
#include <intern/LLKERNEL.h>
#include <stdint.h>
#ifdef __cplusplus
	extern "C" {
#endif
// --------------------------------------------------------------------------------
// -                                  Constants                                   -
// --------------------------------------------------------------------------------

/**
 * Returned value when function call has succeeded.
 */
#define LLKERNEL_OK (0)

/**
 * Returned value when function call has failed.
 */
#define LLKERNEL_ERROR (-1)

// --------------------------------------------------------------------------------
// -                      Functions provided by the library                       -
// --------------------------------------------------------------------------------

/**
 * Notifies the scheduler that the current thread has consumed the given
 * quanta. <br>
 * The scheduler will increment the execution counter for the context of the
 * current thread's owner. This function allows explicitly specifying a
 * quanta that reflects the computational complexity of a native function
 * execution.
 * 
 * 
 * @param quanta
 *            the quanta consumed
 * @return {@link LLKERNEL_ERROR} if this function is not called within the Core
 *         Engine task or if <code>quanta</code> is negative. Otherwise
 *         returns {@link E_OK}.
 */
int32_t LLKERNEL_quantaConsumed(int32_t quanta);

#ifdef __cplusplus
	}
#endif
#endif
