.. Copyright 2025 MicroEJ Corp. All rights reserved.
.. This library is provided in source code for use, modification and test, subject to license terms.
.. Any modification of the source code will break MicroEJ Corp. warranties on the whole library.

..  _vee-event-tracing:

=============
Event Tracing
=============

Principle
=========

dsdsds


Functional Description
======================

dsdsds


Dependencies
============

-  ``LLTRACE_impl.h`` implementations (see
   :ref:`_LLTRACE-API-SECTION`).

-  ``LLMJVM_MONITOR_impl.h`` implementations (see
   :ref:`_LLMJVM_MONITOR-API-SECTION`).


Existing implementations
========================

By default, when enabled, the Trace API displays a message in the standard output for every ``recordEvent(...)`` and ``recordEventEnd(...)`` method calls. 

It does not print a timestamp when displaying the trace message because it can drastically affect execution performances.
It only prints the ID of the recorded event followed by the values given in parameters.

A VEE Port can connect its own implementation by overriding the functions defined in the files ``LLTRACE_impl.h`` and ``LLMJVM_MONITOR_impl.h``.

MicroEJ Corp. also provides an implementation that redirects the events to :ref:`systemview` tool, 
the real-time recording and visualization tool from `Segger <https://www.segger.com/>`_. It is perfect for a finer understanding of the runtime behavior by showing events sequence and duration.

An implementation example for the `NXP i.MX RT1170 development board VEE Port <https://github.com/MicroEJ/nxp-vee-imxrt1170-evk/tree/main/bsp/vee/port/trace>`__ is available on Github.


Installation
============

To activate Event Tracing in your VEE Port, you need to follow these steps:

- Enable and start the trace :ref:`see here <event_enable_recording>`

.. note::
   This feature is provided by the Core Engine, and does not require to import a Foundation Library Pack.


Use
===

See :ref:`Java API Usage <section_event_trace_java_usage>` section in the Application Developer Guide to use the feature in Java at the Application level.

dssdsd

Please contact :ref:`our support team <get_support>` for more information about how to integrate this module.

