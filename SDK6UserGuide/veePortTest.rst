.. _sdk_6_veeport_test:

===============
Test a VEE Port
===============

The SDK provides the capability to test a VEE Port.
While you can create your own tests, 
MicroEJ provides a set of tools and pre-defined projects aimed at simplifying the steps for validating VEE Ports 
in the form of the :ref:`VEE Port Qualification Tools (PQT) <veeport_qualification>`.

Please refer to the `VEE Port Qualification Tools README <https://github.com/MicroEJ/VEEPortQualificationTools>`__ 
to learn how to setup and run this Qualification process.

Configure a Testsuite
=====================

The SDK allows to configure the Testsuite, as well as the Tests being executed.
Refer to the :ref:`sdk_6_testsuite_engine_options` section to discover the configuration options.

Besides allowing to configure the Testsuite in the ``build.gradle.kts`` file of the Testsuite,
the configuration properties can be defined in the ``config.properties`` file located at the root of the Testsuite project.
For example::

   # The testsuite timeout (in seconds)
   microej.testsuite.timeout=600

   # The number of times we'll retry a test if it fails
   microej.testsuite.retry.count=1

Also, the configuration options used for each test can be defined in the ``validation/microej-testsuite-common.properties`` 
file located at the root of the Testsuite project.
For example::

   # Java memory settings
   core.memory.immortal.memory=RAM
   core.memory.immortal.size=64000

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
