/*
 * C
 *
 * Copyright 2025 MicroEJ Corp. All rights reserved.
 * This library is provided in source code for use, modification and test, subject to license terms.
 * Any modification of the source code will break MicroEJ Corp. warranties on the whole library.
 */

#ifndef LLMJVM_CONF_IMPL_H
#define LLMJVM_CONF_IMPL_H
#endif

/**
 * @file
 * @brief VM configuration low level API
 * @author MicroEJ Developer Team
 * @version 1.0.0
 * @date 05 aout 2025
 */

#ifdef __cplusplus
	extern "C" {
#endif

/**
 * @brief Optional user-implemented callback to provide a memory region for the Managed Heap.
 *
 * The Core Engine calls this function to obtain:
 *  - a pointer to a memory block that will be used as the Managed Heap,
 *  - its total size in bytes,
 *  - its initial usable size in bytes (the size the Core Engine will start using,
 *    and may extend up to the total size as needed).
 *
 * The memory returned should preferably be aligned to 4 bytes, but if it is not, the framework will
 * handle alignment itself by adjusting the start address and may reduce the usable size accordingly.
 *
 * The initial size and the total size must be set to the same value,
 * unless you want to activate Automatic Heap Usage Monitoring.
 * To enable Automatic Heap Usage Monitoring, set the initial size to a value
 * strictly less than the total size: the framework will then start by using the
 * initial size, and may extend its usage up to the total size as needed.
 *
 * This function is called once during Core Engine creation (i.e., when the <code>SNI_createVM()</code>
 * function is called).
 *
 * This function is optional. The Core Engine provides a default weak implementation,
 * which returns the address, the total size, and the initial size as defined by the application,
 * typically using the <code>.bss.microej.heap</code> linker section and associated symbols.
 * Users can override this function to provide a custom Managed Heap configuration.
 *
 * @param out_ptr Pointer to a <code>void*</code> variable to receive the address of the memory block
 *                to be used as the Managed Heap.
 * @param out_total_size Pointer to a <code>size_t</code> variable to receive the total size of the
 *                       memory block in bytes referenced by <code>out_ptr</code>.
 * @param out_initial_size Pointer to a <code>size_t</code> variable that receives the initial usable
 *                         size in bytes of the memory block.
 *                         By default (when Automatic Heap Usage Monitoring is not desired), this value
 *                         must be equal to the total size.
 *                         To enable Automatic Heap Usage Monitoring, set this value lower than the
 *                         total size.
 *
 * @return <code>0</code> on success, <code>-1</code> on error.
 */
int LLMJVM_CONF_impl_get_managed_heap_memory(void** out_ptr, size_t* out_total_size, size_t* out_initial_size);

/**
 * @brief Optional user-implemented callback to provide a memory region for the Immortals Heap.
 *
 * The Core Engine calls this function to obtain:
 *  - a pointer to a memory block that will be used as the Immortals Heap,
 *  - its size in bytes.
 *
 * The memory returned should preferably be aligned to 4 bytes, but if it is not, the framework will
 * handle alignment itself by adjusting the start address and may reduce the usable size accordingly.
 *
 * This function is called once during Core Engine creation (i.e., when the <code>SNI_createVM()</code>
 * function is called).
 *
 * This function is optional. The Core Engine provides a default weak implementation,
 * which returns the address and the size as defined by the application,
 * typically using the <code>.bss.microej.immortals</code> linker section and associated symbols.
 * Users can override this function to provide a custom Immortals Heap configuration.
 *
 * @param out_ptr Pointer to a <code>void*</code> variable to receive the address of the memory block
 *                to be used as the Immortals Heap.
 * @param out_size Pointer to a <code>size_t</code> variable to receive the size of the
 *                       memory block in bytes.
 *
 * @return <code>0</code> on success, <code>-1</code> on error.
 */
int LLMJVM_CONF_impl_get_immortals_heap_memory(void** out_ptr, size_t* out_size);

#ifdef __cplusplus
	}
#endif
