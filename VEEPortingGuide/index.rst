.. _vee-porting-guide:

VEE Porting Guide
=================

This document explains how the core features are
accessed, configured and used for creating a port of MICROEJ VEE (VEE Port) on your dedicated device.

It also explains how an Application can interoperate with native code, and
the details of the Architecture modules, including their APIs, error codes
and options.

Semantics of implemented Foundation Libraries are described in
their respective chapters as well as the required Abstraction Layers APIs for porting them 
to different targets. 

.. toctree::
   :maxdepth: 3

  
   platform
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
