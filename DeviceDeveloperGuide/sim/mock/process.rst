Functional Description
======================

As with [SNI], HIL is responsible for finding the method to execute as a
replacement for the native Java method that the MicroEJ simulator tries
to run. Following the [SNI] philosophy, the matching algorithm uses a
naming convention. When a native method is called in the MicroEJ
simulator, it requests that the HIL engine execute it. The corresponding
mock executes the method and provides the result back to the MicroEJ
simulator.

.. figure:: mock/images/hil3.svg
   :alt: The MicroEJ simulator Executes a Native Java Method ``foo()``.
   :width: 80.0%

   The MicroEJ simulator Executes a Native Java Method ``foo()``.
