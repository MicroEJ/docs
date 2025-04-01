.. _vee_port_from_scratch:

==============================================
Create a VEE Port with CoreEngine capabilities
==============================================

Follow these steps to integrate CoreEngine into a new VEE Port:

#. Follow the :ref:`veeport_project_creation` and :ref:`_architecture_selection` documentation sections.

#. Build the default HelloWorld application included in the VEE Port template. Refer to :ref:`sdk_6_build_executable` documentation. The build will fail but the ``microejruntime.a`` and ``microejapp.o`` will be generated, this is what we want.

#. Import a basic BSP example provided by your silicon vendor in the `bsp` folder.

#. Get the Generic Core C module and copy it under ``bsp/vee/port/core`` folder. This C module is not available yet on GitHub. Please ask MicroEJ support to get it.

#. Get the Core Engine Abstraction Layer implementation corresponding to your RTOS in the list of `Abstraction Layer Core implementations on GitHub`_.

#. Implement time functions that are declared in `microej_time.h`. The best practice is to use a hardware timer for a higher precision (refer to this `time implementation example`_).
   MicroEJ provides a ready-to-use `time implementation for FreeRTOS`_ that you can use for testing purposes.

#. Implement the functions ``LLBSP_IMPL_putchar`` and ``LLBSP_IMPL_printf`` if the default implementation does not fit.

#. Create a RTOS task that calls ``microej_main`` at start with the right heap size.

#. Add the added source files to the build system of the project, as well as ``microejruntime.a`` and ``microejapp.o``.

#. Build and run the example on the device.

#. Implement the build and run scripts (in ``bsp/vee/scripts`` folder) that will allow to build and run an application from a gradle task. You can find examples of implementation in available `VEE Ports on GitHub`. You can test your implementation by re-building the HelloWorld application (refer to Refer to :ref:`sdk_6_build_executable`). This time the build should be successful. To run this application from gradle tasks, refer to :ref:`sdk_6_run_on_device` documentation.

#. Run the `Core validation testsuite`_ to validate your implementation.

.. _VEE Port template: https://github.com/MicroEJ/Tool-Project-Template-VEEPort/tree/master
.. _MicroEJ Github: https://github.com/orgs/MicroEJ/repositories?q=AbstractionLayer-Core&type=all&language=&sort=
.. _time implementation example: https://github.com/MicroEJ/VEEPort-STMicroelectronics-STM32F7508-DK/blob/2.3.1/stm32f7508_freertos-bsp/projects/microej/core/src/microej_time.c
.. _time implementation for FreeRTOS: https://github.com/MicroEJ/AbstractionLayer-Time-FreeRTOS
.. _VEE Ports on GitHub: https://github.com/orgs/MicroEJ/repositories?q=VEEPort&type=all&language=&sort=
.. _Core validation testsuite: https://github.com/MicroEJ/Tool-Project-Template-VEEPort/tree/master/vee-port/validation/core

..
   | Copyright 2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
