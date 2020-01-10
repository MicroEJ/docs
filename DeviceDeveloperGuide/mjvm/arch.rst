Architecture
============

The MJVM and its components have been compiled for one specific CPU
architecture and for use with a specific C compiler.

The architecture of the platform engine is called green thread
architecture, it runs in a single RTOS task. Its behavior consists in
scheduling MicroEJ threads. The scheduler implements a priority
preemptive scheduling policy with round robin for the MicroEJ threads
with the same priority. In the following explanations the term "RTOS
task" refers to the tasks scheduled by the underlying OS; and the term
"MicroEJ thread" refers to the thread scheduled by the MJVM.

.. figure:: mjvm/images/mjvm_gt.svg
   :alt: A Green Threads Architecture Example
   :width: 60.0%

   A Green Threads Architecture Example

The activity of the platform is defined by the MicroEJ application. When
the MicroEJ application is blocked (when all MicroEJ threads are
sleeping), the platform sleeps entirely: The RTOS task that runs the
platform sleeps.

The platform is responsible for providing the time to the MicroEJ world:
the precision is 1 millisecond.
