.. _offloading:

Offloading
==========

Many modern smartwatches rely on a high-power microprocessor (such as a Qualcomm Snapdragon) running Android.
Integrating an additional low-power microcontroller to the hardware of the watch allows to offload a part of the work of the high-power microprocessor and thus increase the battery life.
Keeping a high-power microprocessor on the hardware allows to keep the ability to show high-performance animations and to provide access to the Android ecosystem.

Solution
--------

VEE Wear offers a comprehensive solution to develop the software on this dual architecture:

- VEE allows to run an application programmed with high-level code and virtualization on the microcontroller
- the :ref:`Android Compatibility Kit <runnning_on_android>` allows to execute the same application on the microprocessor without programming it a second time
- the Offloading Framework allows to switch between the two processors depending on their capabilities and on the watch design

One Code, Two Targets
~~~~~~~~~~~~~~~~~~~~~

MicroEJ Application development shares the same programming language as Android Application development.
Thanks to this similarity, any MicroEJ Application code is compatible with the Android runtime environment.
The :ref:`Android Compatibility Kit <runnning_on_android>` provides the tools and libraries to execute a MicroEJ Application on Android.

Using this solution, the application code can be programmed once and executed both on the low-power microcontroller and the high-power microprocessor.

Offloading Framework
~~~~~~~~~~~~~~~~~~~~

The offloading strategy is a set of rules defined by the design of the watch.

Here is a non-exhaustive list of common offloading rules:

- switching to the low-power microcontroller after a few seconds of user inactivity (often called ambient mode)
- switching to the high-power microprocessor when starting a high-performance animation
- switching to the high-power microprocessor when navigating to a menu which is only available on Android

Switching from a processor to the other may require to synchronize the state of the software and to provide the necessary data for the other processor to take over.
The time to wake-up the processor and to synchronize the data has to be taken into account when designing the software architecture.

Once these rules have been decided, the Offloading Framework APIs can be used to wake up the other processor, to synchronize data, to be notified when the other processor is ready,
to hand over the control of the display, to put the processor to sleep, etc.

Evaluation
----------

The Android Compatibility Kit can be evaluated by following :ref:`its documentation <runnning_on_android>`.

The Offloading Framework is available on demand. You can contact :ref:`MicroEJ Support<get_support>` to evaluate this solution.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
