.. Copyright 2022 MicroEJ Corp. All rights reserved.
.. This library is provided in source code for use, modification and test, subject to license terms.
.. Any modification of the source code will break MicroEJ Corp. warranties on the whole library.

..  _Advanced-Event-Tracing:

Advanced Event Tracing
######################

Principle
=========

MicroEJ Core Engine allows method execution to be profiled. The following two new hooks functions are used for that:

- ``LLMJVM_MONITOR_IMPL_on_invoke_method`` called at the start of the method invocation.
- ``LLMJVM_MONITOR_IMPL_on_return_method`` called when returning from the invoked method.

Calling these functions each time a method is invoked will slow down the application execution,
so these functions are not called by default when event tracing is enabled and started.

.. note::
   This feature requires Architecture version ``7.17.0`` or higher and is only available on MicroEJ Core Engine, not on Simulator.

To activate them, you need to follow these steps:

- Enable and start the trace :ref:`see here <event_enable_recording>`
- Tell the third-party linker program to redirect all calls to ``LLMJVM_invoke_method`` and ``LLMJVM_return_method`` symbols to respectively ``LLMJVM_invoke_method_with_trace`` and ``LLMJVM_return_method_with_trace`` symbols.

Platforms using GNU LD linker
=============================

Add the following options to the LD linker command line:

.. code-block:: sh

    --require-defined=LLMJVM_invoke_method_with_trace
    --defsym=LLMJVM_invoke_method=LLMJVM_invoke_method_with_trace
    --require-defined=LLMJVM_return_method_with_trace
    --defsym=LLMJVM_return_method=LLMJVM_return_method_with_trace


Platforms using IAR ILINK linker
================================

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