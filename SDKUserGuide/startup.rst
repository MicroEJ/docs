.. warning::

  This documentation is for SDK 5. The latest major version is :ref:`SDK 6 <sdk_6_user_guide>`.
  SDK 5 is in maintenance mode since the release of :ref:`SDK 5.8.0 <changelog-5.8.0>`.
  Consequently, as stated in the :ref:`SDK End User License Agreement (EULA) <sdk_eula>`, the SDK will reach the end of its life by July 2028.
  Contact :ref:`our support team <get_support>` for assistance with migrating to the new SDK, or your sales representative if you require an extension of SDK maintenance as a service.

.. _startup:

Startup
=======

When starting the SDK, it prompts you to select the last used workspace or a default workspace on the first run. 

.. figure:: images/workspace_selection.png
   :alt:  Workspace selection
   :align: center
   :scale: 100%

   Workspace selection

A workspace is the Eclipse main folder where are imported a set of projects containing the source code.

When loading a new workspace, the SDK prompts for the location of the MicroEJ repository, 
where Architectures, Platforms or Virtual Devices will be imported. 

.. figure:: images/repository_selection.png
   :alt:  Repository selection
   :align: center
   :scale: 100%

   Repository selection

By default, the SDK suggests to point to the default repository on your operating system, 
located at ``${user.home}/.microej/repositories/[version]``. 
You can select an alternative location. Another common practice is to define a local
repository relative to the workspace, so that the workspace is
self-contained, without external file system links and can be shared
within a zip file.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
