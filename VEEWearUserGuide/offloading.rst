.. _offloading:

Offloading
==========

Many high-end smartwatches rely on a microprocessor running Android. The power consumption of these devices is fairly high and show an average battery life of one or two days.
Integrating an extra low-power microcontroller into the watch's hardware enables the delegation of specific tasks from the main microprocessor, resulting in an increased battery life.
Keeping a powerful microprocessor on the hardware ensures the ability to display high-performance animations and access the Android ecosystem.

Solution
--------

VEE Wear offers a comprehensive solution for software development on this dual architecture:

- MicroEJ VEE enables the execution of applications written in high-level code through virtualization on the microcontroller.
- the :ref:`Android Compatibility Kit <android_compatibility_kit>` allows the execution of the same application on the microprocessor without the need for re-implementation.
- the Offloading Framework provides the ability to switch the application context between the two processors depending on their capabilities and on the application flow.

One Code, Two Targets
~~~~~~~~~~~~~~~~~~~~~

MicroEJ Application development shares the same programming language as Android Application development.
Thanks to this similarity, any MicroEJ Application code is compatible with the Android runtime environment.
The :ref:`Android Compatibility Kit <android_compatibility_kit>` provides the tools and libraries to execute a MicroEJ Application on Android.

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

The Android Compatibility Kit can be evaluated by following :ref:`its documentation <android_compatibility_kit>`.

An demonstration with a sample offloading framework is available on demand. You can contact :ref:`MicroEJ Support<get_support>` to test this demonstration.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
