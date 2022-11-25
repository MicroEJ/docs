.. _platform_selection:

Platform Selection
===================

.. note::
   This page is releated to the version 5 and lower of the SDK. 
   If you use the SDK 6, please refer to the page :ref:`sdk_6_veeport_selection`.

Building or running an Application or a :ref:`Test Suite <application_testsuite>` with MMM requires a Platform.

There are 4 different ways to provide a Platform for a module project:

- Set the :ref:`build option <mmm_build_options>` ``platform-loader.target.platform.file`` to the path of a Platform file (``.zip``, ``.jpf`` or ``.vde``).
- Set the :ref:`build option <mmm_build_options>` ``platform-loader.target.platform.dir`` to the path of the ``source`` folder of an already imported :ref:`Source Platform <source_platform_import>`.
- Declare a :ref:`module dependency <mmm_module_dependencies>` with the conf ``platform``:

   .. code:: xml

      <dependency org="myorg" name="myname" rev="1.0.0" conf="platform->default" transitive="false"/>

- Copy a Platform file to the dropins folder. The default dropins folder location is ``[module_project_dir]/dropins``. 
  It can be changed using the :ref:`build option <mmm_build_options>` ``platform-loader.target.platform.dropins``.

.. note::

   Using a Platform in the ``.zip`` format requires at least the version ``5.4.0`` of the SDK.

At least 1 of these 4 ways is required to build an application with a platform.
If several ways are used, the following rules are applied:

- If ``platform-loader.target.platform.file`` or ``platform-loader.target.platform.dir`` is set, the other options are ignored.
- If the the module project defined several platforms, the build fails. For example the following cases are not allowed:

  - Setting a platform with the option ``platform-loader.target.platform.file`` and another one with the option ``platform-loader.target.platform.dir``
  - Declaring a platform as a dependency and adding a platform in the ``dropins`` folder
  - Declaring 2 platforms as Dependencies
  - Adding 2 platforms in the ``dropins`` folder

Refer to the :ref:`module_natures.plugins.platform_loader` section for a complete list of options.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.