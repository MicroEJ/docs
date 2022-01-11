.. Copyright 2022 MicroEJ Corp. All rights reserved.
.. This library is provided in source code for use, modification and test, subject to license terms.
.. Any modification of the source code will break MicroEJ Corp. warranties on the whole library.

..  _Advanced-Event-Tracing:

Advanced Event Tracing
######################

From an XPF version 7.17.0, MicroEJ Vee allows method execution to be profiled.
Two new hooks functions are used by the MicroEJ Vee:

- ``LLMJVM_MONITOR_IMPL_on_invoke_method`` called at the start of the method invocation.
- ``LLMJVM_MONITOR_IMPL_on_return_method`` called at the end of the method invocation.

But calling these hook functions each time a method is invoked can slow the whole application,
so these hook functions is not activated by default even when the trace is enabled and started.

To activate them you need:

- Enable and start the trace see here https://docs.microej.com/en/latest/ApplicationDeveloperGuide/trace.html?highlight=trace#event-recording
- Tell the Third-party linker program to redirect all calls to ``LLMJVM_invoke_method`` and ``LLMJVM_return_method`` symbols to respectively ``LLMJVM_invoke_method_with_trace`` and ``LLMJVM_return_method_with_trace`` symbols.


Platform which use LD as linker
===============================

Pass the following options to the LD linker program

.. code-block:: sh

    --require-defined=LLMJVM_invoke_method_with_trace
    --defsym=LLMJVM_invoke_method=LLMJVM_invoke_method_with_trace
    --require-defined=LLMJVM_return_method_with_trace
    --defsym=LLMJVM_return_method=LLMJVM_return_method_with_trace



Platform which use ILINK as linker (IAR)
========================================

Pass the following options to the ILINK linker program

.. code-block:: sh

    --redirect LLMJVM_invoke_method=LLMJVM_invoke_method_with_trace
    --redirect LLMJVM_return_method=LLMJVM_return_method_with_trace

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.