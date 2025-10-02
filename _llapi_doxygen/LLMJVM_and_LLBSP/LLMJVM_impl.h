/* 
 * C
 * 
 * Copyright 2011-2022 MicroEJ Corp. All rights reserved.
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
#include <intern/LLMJVM_impl.h>
// --------------------------------------------------------------------------------
// -                                  Constants                                   -
// --------------------------------------------------------------------------------

/**
 * Returned value when function call has succeeded.
 */
#define LLMJVM_OK (0)

/**
 * Returned value when current task has been interrupted during function call.
 */
#define LLMJVM_INTERRUPTED (1)

/**
 * Returned value when function call has failed.
 */
#define LLMJVM_ERROR (-1)

// --------------------------------------------------------------------------------
// -                      Functions that must be implemented                      -
// --------------------------------------------------------------------------------

/**
 * This function is called once during Core Engine creation (i.e., when the <code>SNI_createVM()</code>
 * function is called). It may be used to initialize specific data.
 * 
 * @return {@link LLMJVM_OK} on success, {@link LLMJVM_ERROR} on error.
 */
int32_t LLMJVM_IMPL_initialize(void);

/**
 * This function is called once during the Core Engine startup by the Core Engine task (i.e.,
 * when the <code>SNI_startVM()</code> function is called). It can be useful if the Core Engine support
 * needs to know the Core Engine task.
 * 
 * @return {@link LLMJVM_OK} on success, {@link LLMJVM_ERROR} on error.
 */
int32_t LLMJVM_IMPL_vmTaskStarted(void);

/**
 * Schedule an alarm (or timer) that will be triggered at the given absolute (system) time.
 * If an alarm is already scheduled for an earlier time this function must do nothing,
 * otherwise it must configure the alarm. If the given absolute time has already been reached, this
 * function must call {@link LLMJVM_schedule}. Previously scheduled alarm
 * must be canceled, only one alarm is scheduled at the same time.
 * The scheduled alarm must call the function {@link LLMJVM_schedule} when it is triggered.
 * The specified time is in milliseconds.
 * 
 * @return {@link LLMJVM_OK} on success, {@link LLMJVM_ERROR} on error.
 */
int32_t LLMJVM_IMPL_scheduleRequest(int64_t absoluteTime);

/**
 * Causes the Core Engine RTOS task to sleep until it is woken up by the {@link LLMJVM_wakeupVM} function.
 * This function is called by the Core Engine task.
 * 
 * @return {@link LLMJVM_OK} if wakeup occurred, {@link LLMJVM_INTERRUPTED} if the Core Engine task
 * has been interrupted, or {@link LLMJVM_ERROR} on error.
 */
int32_t LLMJVM_IMPL_idleVM(void);

/**
 * Wake up the Core Engine RTOS task. If the Core Engine task is not sleeping,
 * the wakeup stays pending and the Core Engine will not sleep on the next {@link LLMJVM_idleVM} call unless
 * there is a call to {@link LLMJVM_ackWakeup} between this call and the next {@link LLMJVM_idleVM} call.
 * This function must be called only by the Core Engine code. If a task wants to wake up the Core Engine,
 * it must use the {@link LLMJVM_schedule} function (which may in turn call this function).
 * 
 * @return {@link LLMJVM_OK} on success, {@link LLMJVM_ERROR} on error.
 */
int32_t LLMJVM_IMPL_wakeupVM(void);

/**
 * Clears any outstanding {@link LLMJVM_wakeupVM} request. After calling this function, a call to {@link LLMJVM_idleVM} will
 * result in a wait even if {@link LLMJVM_wakeupVM} has been called previously (provided no other {@link LLMJVM_wakeupVM} call
 * has occurred since the call to this function. This function must cancel the alarm previously scheduled with
 * {@link LLMJVM_scheduleRequest}.
 * This function is called by the Core Engine task.
 * 
 * @return {@link LLMJVM_OK} on success, {@link LLMJVM_ERROR} on error.
 */
int32_t LLMJVM_IMPL_ackWakeup(void);

/**
 * Returns the ID of the current OS task.<br>
 * This function may be called within the Core Engine task or another OS task.
 */
int32_t LLMJVM_IMPL_getCurrentTaskID(void);

/**
 * This function is called during Core Engine end (i.e., at the end of the <code>SNI_startVM()</code> function).
 * It may be used to freed specific data.
 * 
 * @return {@link LLMJVM_OK} on success, {@link LLMJVM_ERROR} on error.
 */
int32_t LLMJVM_IMPL_shutdown(void);

/**
 * Sets the application time. The application time is the difference, measured in milliseconds,
 * between the current time and midnight, January 1, 1970 UTC.
 * This time does not change the monotonic time.
 * 
 * @param t the application time to set in milliseconds.
 */
void LLMJVM_IMPL_setApplicationTime(int64_t t);

/**
 * Gets the monotonic or the application time in milliseconds.
 * <p>
 * The monotonic time always moves forward and is not impacted by application time modifications (NTP or Daylight Savings Time updates).
 * It can be implemented by returning the running time since the start of the device.
 * This time is the value returned by the Java method <code>Util.platformTimeMillis()</code>.
 * <p>
 * The application time is the difference, measured in milliseconds, between the current time and midnight, January 1, 1970 UTC.
 * This time is the value returned by the Java methods <code>System.currentTimeMillis()</code> and <code>Util.currentTimeMillis()</code>.
 * 
 * @param monotonic if 1, get the monotonic time, otherwise get the application time.
 */
int64_t LLMJVM_IMPL_getCurrentTime(uint8_t monotonic);

/**
 * Gets the current timestamp in nanoseconds.
 * Only elapsed time between two calls is meaningful.
 * 
 * @return the current timestamp in nanoseconds
 */
int64_t LLMJVM_IMPL_getTimeNanos(void);

// --------------------------------------------------------------------------------
// -          Functions provided by the library - not to be implemented           -
// --------------------------------------------------------------------------------

/**
 * Notify the Core Engine that it must wake up or schedule a new thread.
 * 
 * @return  {@link LLMJVM_OK} on success, {@link LLMJVM_ERROR} on error.
 */
int32_t LLMJVM_schedule(void);
