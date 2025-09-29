/* 
 * C
 * 
 * Copyright 2014-2024 MicroEJ Corp. All rights reserved.
 * This library is provided in source code for use, modification and test, subject to license terms.
 * Any modification of the source code will break MicroEJ Corp. warranties on the whole library.
 */
/* 
 * This file is auto-generated - DO NOT EDIT IT
 */
/* 
 * Implementation header file. Shall only be included by client implementation C files.
 */
#include <stdint.h>
#include <intern/LLKERNEL_impl.h>
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

/**
 * The RAM area alignment constraint.
 */
#define LLKERNEL_RAM_AREA_ALIGNMENT (8)

/**
 * The ROM area alignment constraint.
 */
#define LLKERNEL_ROM_AREA_ALIGNMENT (16)

/**
 * Error code thrown by {@link LLKERNEL_onFeatureInitializationError}
 * function when the Installed Feature content is corrupted. The checksum
 * computed during the installation does not match the actual computed
 * checksum.
 */
#define LLKERNEL_FEATURE_INIT_ERROR_CORRUPTED_CONTENT (1)

/**
 * Error code thrown by {@link LLKERNEL_onFeatureInitializationError} function when
 * the Installed Feature has not been built for this Kernel UID or a compatible Kernel UID.
 */
#define LLKERNEL_FEATURE_INIT_ERROR_INCOMPATIBLE_KERNEL_WRONG_UID (2)

/**
 * Error code thrown by {@link LLKERNEL_onFeatureInitializationError} function when
 * there is no internal free slot to connect the Installed Feature.
 */
#define LLKERNEL_FEATURE_INIT_ERROR_TOO_MANY_INSTALLED (3)

/**
 * Error code thrown by {@link LLKERNEL_onFeatureInitializationError} function when
 * the Installed Feature matches an already Installed Feature.
 */
#define LLKERNEL_FEATURE_INIT_ERROR_ALREADY_INSTALLED (4)

/**
 * Error code thrown by {@link LLKERNEL_onFeatureInitializationError} function when
 * the Installed Feature has been linked on a Kernel Address Table with different content.
 */
#define LLKERNEL_FEATURE_INIT_ERROR_INCOMPATIBLE_KERNEL_WRONG_ADDRESSES (5)

/**
 * Error code thrown by {@link LLKERNEL_onFeatureInitializationError} function when
 * the Installed Feature ROM area overlaps the ROM area of an already Installed Feature.
 */
#define LLKERNEL_FEATURE_INIT_ERROR_ROM_OVERLAP (6)

/**
 * Error code thrown by {@link LLKERNEL_onFeatureInitializationError} function when
 * the Installed Feature RAM area overlaps the RAM area of an already Installed Feature.
 */
#define LLKERNEL_FEATURE_INIT_ERROR_RAM_OVERLAP (7)

/**
 * Error code thrown by {@link LLKERNEL_onFeatureInitializationError}
 * function when the RAM address returned by
 * {@link LLKERNEL_getFeatureAddressRAM} is not equals to the RAM address
 * returned when the Feature has been linked on this Kernel.
 */
#define LLKERNEL_FEATURE_INIT_ERROR_RAM_ADDRESS_CHANGED (8)

/**
 * Error code thrown by {@link LLKERNEL_onFeatureInitializationError}
 * function when a previous call to {@link LLKERNEL_getFeatureHandle} returned <code>0</code>.
 */
#define LLKERNEL_FEATURE_INIT_ERROR_NULL_HANDLE (9)

// --------------------------------------------------------------------------------
// -                      Functions that must be implemented                      -
// --------------------------------------------------------------------------------

/**
 * Allocates a new Feature and reserves its ROM and RAM areas. If the
 * Feature cannot be allocated, it must return <code>0</code>.
 * <p>
 * Warning: ROM and RAM areas reservation must take care of address alignment
 * constraints required by {@link LLKERNEL_getFeatureAddressROM} and
 * {@link LLKERNEL_getFeatureAddressRAM}.
 * 
 * @param size_ROM
 *            the size in bytes to allocate in ROM
 * 
 * @param size_RAM
 *            the size in bytes to allocate in RAM
 * 
 * @return a handle that uniquely identifies the allocated Feature, or
 *         <code>0</code> if the Feature could not be allocated.
 */
int32_t LLKERNEL_IMPL_allocateFeature(int32_t size_ROM, int32_t size_RAM);

/**
 * Releases a Feature previously allocated using
 * {@link LLKERNEL_allocateFeature} and frees its
 * ROM and RAM areas.
 * 
 * @param handle
 *            the Feature handle
 */
void LLKERNEL_IMPL_freeFeature(int32_t handle);

/**
 * Retrieves the count of currently installed Features in memory.<br>
 * 
 * A Feature is considered installed in memory if it has been successfully allocated
 * using the {@link LLKERNEL_allocateFeature} method and has not been freed
 * with the {@link LLKERNEL_freeFeature} method. This count may include Features that were installed
 * in a previous execution of this Kernel.
 * 
 * Upon calling this method, the Core Engine will retrieve Feature handles by invoking
 * {@link LLKERNEL_getFeatureHandle} for each index within the range <code>[0..{@link LLKERNEL_getAllocatedFeaturesCount}-1)]</code>.
 * 
 * @return the current count of Features installed in memory, <code>0</code> if there are none.
 * @see LLKERNEL_getFeatureHandle
 */
int32_t LLKERNEL_IMPL_getAllocatedFeaturesCount(void);

/**
 * Retrieves the handle of a Feature that has been installed in memory.<br>
 * 
 * This method is invoked by the Core Engine immediately following a call to
 * {@link LLKERNEL_getAllocatedFeaturesCount} for each index
 * within the range <code>[0..{@link LLKERNEL_getAllocatedFeaturesCount}-1]</code>.
 * 
 * @param index
 *            an index within the range <code>[0..{@link LLKERNEL_getAllocatedFeaturesCount}-1]</code>.
 * @return a unique handle that identifies the Feature at the specified index, or <code>0</code> if
 *         no valid handle is found.
 * @see LLKERNEL_getAllocatedFeaturesCount
 */
int32_t LLKERNEL_IMPL_getFeatureHandle(int32_t index);

/**
 * Gets the address of the allocated RAM area for the given Feature.
 * The returned address must be {@link LLKERNEL_RAM_AREA_ALIGNMENT} bytes aligned.
 * 
 * @param handle
 *            the Feature handle
 * 
 * @return the start address in bytes of the allocated RAM area, or
 *         <code>NULL</code> if the Feature handle is not valid.
 */
void* LLKERNEL_IMPL_getFeatureAddressRAM(int32_t handle);

/**
 * Gets the address of the allocated ROM area for the given Feature.
 * The returned address must be {@link LLKERNEL_ROM_AREA_ALIGNMENT} bytes aligned.
 * 
 * @param handle
 *            the Feature handle
 * 
 * @return the start address in bytes of the allocated ROM area, or
 *         <code>NULL</code> if the Feature handle is not valid.
 */
void* LLKERNEL_IMPL_getFeatureAddressROM(int32_t handle);

/**
 * Copies a sequence of bytes to ROM area. This function does not require
 * that all bytes are really copied to the destination before it returns.
 * 
 * @param dest_address_ROM
 *            the start address in ROM (destination)
 * @param src_address
 *            the start address of bytes to copy (source)
 * @param size
 *            the number of bytes to copy
 * @return {@link LLKERNEL_OK} on success, {@link LLKERNEL_ERROR} on error.
 */
int32_t LLKERNEL_IMPL_copyToROM(void* dest_address_ROM, void* src_address, int32_t size);

/**
 * This function is called once all calls to
 * {@link LLKERNEL_copyToROM} are done for the currently allocated
 * Feature. This function must block until all bytes are really copied to
 * ROM area.
 * 
 * @return {@link LLKERNEL_OK} on success, {@link LLKERNEL_ERROR} on error.
 */
int32_t LLKERNEL_IMPL_flushCopyToROM(void);

/**
 * This function is called during Kernel boot when the initialization of an
 * allocated Feature failed.
 * 
 * @param handle
 *            a Feature handle returned by {@link LLKERNEL_getFeatureHandle}
 * 
 * @param error_code
 *            the error code indicating the initialization error cause (see
 *            <code>FEATURE_INIT_ERROR_*</code> constants)
 * @return {@link LLKERNEL_OK} to skip the initialization of this Feature and
 *         continue with the next allocated Feature, or {@link LLKERNEL_ERROR} if
 *         the Kernel must abruptly stop.
 */
int32_t LLKERNEL_IMPL_onFeatureInitializationError(int32_t handle, int32_t error_code);
