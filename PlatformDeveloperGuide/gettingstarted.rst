===========================
Building a MicroEJ Platform
===========================

.. _platform_creation:

Create a New MicroEJ Platform Configuration
===========================================

The first step is to create a MicroEJ Platform configuration:

-  Select :guilabel:`File` > :guilabel:`New` > :guilabel:`Project…`, open MicroEJ category and select
   MicroEJ Platform Project.

-  Click on Next. The Configure Target Architecture page allows to
   select the MicroEJ Architecture that contains a minimal MicroEJ
   Platform and a set of compatible modules targeting a processor
   architecture and a compilation toolchain. This environment can be
   changed later.

   -  Click on Browse... to select one of the installed MicroEJ
      Architecture.

   -  Check the Create from a platform reference implementation box to
      use one of the available implementation. Uncheck it if you want to
      provide your own implementation or if no reference implementation
      is available.

-  Click on Next. The Configure platform properties contains the
   identification of the MicroEJ Platform to create. Most fields are
   mandatory, you should therefore set them. Note that their values can
   be modified later on.

-  Click on Finish. A new project is being created containing a
   ``[name].platform`` file. A platform description editor shall then
   open.


Groups / Modules Selection
==========================

Group
From the platform description editor, select the Content tab to access
the platform modules selection. Modules can be selected/deselected from
the Modules frame.

Modules are organized into groups. When a group is selected, by default,
all its modules are selected. To view the modules making up a group,
click on the Show/Hide modules icon on the top-right of the frame. This
will let you select/deselect on a per module basis. Note that individual
module selection is not recommended.

The description and contents of an item (group or module) are displayed
beside the list on item selection.

All the checked modules will be installed in the platform.


Modules Customization
=====================

Each selected module can be customized by creating a [module] folder
named after the module beside the ``[name].platform`` definition. It may
contain:

-  An optional [module].properties file named after the module name.
   These properties will be injected in the execution context prefixed
   by the module name. Some properties might be needed for the
   configuration of some modules. Please refer to the modules
   documentation for more information.

-  Optional module specific files and folders.

Modifying one of these files requires to build the platform again.


.. _platformCustomization:

Platform Customization
======================

Platform can be customized by creating a ``configuration.xml`` script
beside the ``[name].platform`` file. This script can extend one or
several of the extension points available.

Configuration project (the project which contains the
``[name].platform`` file) can contain an optional ``dropins`` folder.
The contents of this folder will be copied integrally into the final
platform. This feature allows to add some additional libraries, tools
etc. into the platform.

The dropins folder organization should respect the final platform files
and folders organization. For instance, the tools are located in the
sub-folder ``tools``. Launch a platform build without the dropins folder
to see how the platform files and folders organization is. Then fill the
dropins folder with additional features and build again the platform to
obtain an advanced platform.

The dropins folder files are kept in priority. If one file has the same
path and name as another file already installed into the platform, the
dropins folder file will be kept.

Modifying one of these files requires to build the platform again.


Build MicroEJ Platform
======================

To build the MicroEJ Platform, click on the Build Platform link on the
platform configuration Overview.

It will create a MicroEJ Platform in the workspace available for the
MicroEJ project to run on. The MicroEJ Platform will be available in:
:guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`MicroEJ` > :guilabel:`Platforms in workspace`.


.. include:: bsp.inc

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
