.. _platform_import:

Platform Import
===============

A Platform is required to run a Standalone Application on the Simulator or build the Firmware binary for the target device.

The :ref:`vee-porting-guide` describes how to create a Platform from scratch for any kind of device. 
In addition, MicroEJ Corp. provides Platforms for various development boards (see https://repository.microej.com/index.php?resource=JPF).

Platforms are distributed in two packages:

- **Source Platform**. The source files are imported into the workspace. This is the default case.
- **Binary Platform**. A ``.jpf`` file is imported into the :ref:`MicroEJ repository <startup>`. As of MicroEJ SDK ``5.3.0``, this package is deprecated.

.. _source_platform_import:

Source Platform Import
----------------------

Import from Folder
~~~~~~~~~~~~~~~~~~

This section applies when the Platform files are already available on a local folder. 
This is likely the case when the files are checked out from a Version Control System, such as a local git repository clone. 

.. note::

   If you are going to import a Platform from MicroEJ Github, you can follow the specific :ref:`github` section instead (the projects will be automatically imported).


- Select :guilabel:`File` > :guilabel:`Import…` > :guilabel:`General` >
  :guilabel:`Existing Projects into Workspace` > :guilabel:`Select
  root directory` > :guilabel:`Browse…`.
- Select the root directory. The wizard will automatically discover projects to import.
- Click on the :guilabel:`Finish` button.


Import from Zip File
~~~~~~~~~~~~~~~~~~~~

This section applies when the Platform files are packaged in a ``.zip`` file. 

- Select :guilabel:`File` > :guilabel:`Import…` > :guilabel:`General` >
  :guilabel:`Existing Projects into Workspace` > :guilabel:`Select
  archive file` > :guilabel:`Browse…`.
- Select the zip of the project (e.g., ``x.zip``). The wizard will automatically discover projects to import.
- Click on the :guilabel:`Finish` button.

Platform Build
~~~~~~~~~~~~~~

Platforms are usually shared with only the Platform configuration files. 
Once the projects are imported, follow the platform-specific documentation to build the Platform.

Once imported or built, a Platform project should be available as follows:

.. figure:: images/platform_project.png
   :alt: Platform Project
   :align: center

   Platform Project

The ``source`` folder contains the Platform content which can be set to the ``target.platform.dir`` option.

.. _binary_platform_import:

Binary Platform Import
----------------------

After downloading the Platform ``.jpf`` file, launch MicroEJ SDK and follow these steps to import the Platform:

-  Open the Platform view in MicroEJ SDK, select :guilabel:`Window` >
   :guilabel:`Preferences` > :guilabel:`MicroEJ` > :guilabel:`Platforms`. The
   view should be empty on a fresh install of the tool.

   .. figure:: images/platformImport.png
      :alt: Platform Import
      :align: center
      :width: 797px
      :height: 468px

      Platform Import

-  Press :guilabel:`Import...` button.

-  Choose :guilabel:`Select File...` and use the :guilabel:`Browse` option
   to navigate to the ``.jpf`` file containing your Platform, 
   then read and accept the license agreement to proceed.

   .. figure:: images/platformSelect.png
      :alt: Platform Selection
      :align: center
      :width: 569px
      :height: 636px

      Platform Selection

-  The Platform should now appear in the :guilabel:`Platforms` view,
   with a green valid mark.

   .. figure:: images/platformList.png
      :alt: Platform List
      :align: center
      :width: 797px
      :height: 468px

      Platform List

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
