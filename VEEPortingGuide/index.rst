.. _vee-porting-guide:

VEE Porting Guide
=================

This document explains how the core features are
accessed, configured and used for creating a port of MICROEJ VEE (VEE Port) on your dedicated device. 
It also explains how an Application can interoperate with native code, and
the details of the Architecture modules, including their APIs, error codes
and options. Semantics of implemented Foundation Libraries are described in
their respective chapters as well as the required Abstraction Layers APIs for porting them 
to different targets. 

The following figure shows the overall process to obtain an Executable file to deploy on a device.
The first three steps are performed within MICROEJ SDK. The remaining steps are performed within the C IDE.

.. _fig_overall-process:
.. figure:: images/process-overview5.*
   :alt: Overall Build Process
   :scale: 80%
   :align: center

   Overall Build Process

The steps are as follow:

1. Create a new VEE Port configuration project. This project
   describes the VEE Port to build (Architecture selection).

2. Select which modules provided by the Architecture and Packs will be
   installed in the VEE Port.

3. Build the VEE Port according to the choices made in steps 1 and 2.

4. Build an Application against the VEE Port in order
   to obtain an object file to link in the BSP.

5. Compile the BSP and link it with the Application object file that was
   built previously in step 4 to produce an Executable.

6. Final step: Deploy the Executable (i.e. the binary application) onto a device.

.. toctree::
   :hidden:
   :maxdepth: 3

   architecture
   pack
   platformCreation
   veePortQualification
   coreEngine
   advanceTrace
   multiSandbox
   tinySandbox
   native
   externalResourceLoader
   serialCommunications
   ui
   vg
   net
   bluetooth
   packEventQueue
   fs
   hal
   device
   security
   watchdog-timer
   systemView
   simulation
   appendix/index

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
