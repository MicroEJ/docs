Functional Description
======================

As with [SNI], HIL is responsible for finding the method to execute as a
replacement for the native Java method that the SIMJPF tries to run.
Following the [SNI] philosophy, the matching algorithm uses a naming
convention. When a native method is called in the SIMJPF, it requests
that the HIL engine execute it. The corresponding mock executes the
method and provides the result back to the SIMJPF.

.. figure:: sim/mock/images/hil3.svg
   :alt: The SIMJPF Executes a Native Java Method ``foo()``.
   :width: 80.0%

   The SIMJPF Executes a Native Java Method ``foo()``.
