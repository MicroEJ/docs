.. _pack_fs:

===========
File System
===========


Principle
=========

The FS Foundation Library defines a low-level File System framework for embedded
devices. It allows you to manage abstract files and directories without
worrying about the native underlying File System kind.


Functional Description
======================

The MicroEJ Application manages File System elements using
File/Directory abstraction. The FS implementation made for each MicroEJ
Platform is responsible for surfacing the native File System specific
behavior.


Dependencies
============

-  ``LLFS_impl.h`` and ``LLFS_File_impl.h`` implementations (see
   :ref:`LLFS-API-SECTION`).


Installation
============

FS is an additional module. 
To enable it, the FS :ref:`Pack <pack_overview>` module must be installed in your VEE Port:

.. tabs::

   .. tab:: SDK 6 (build.gradle.kts)

      .. code-block:: kotlin

         microejPack("com.microej.pack:fs:6.0.4")

   .. tab:: SDK 5 (module.ivy)

      .. code-block:: xml

         <dependency org="com.microej.pack" name="fs" rev="6.0.4"/>

	  Then, using the VEE Port Editor (see :ref:`platform_module_configuration`), enable the `FS` library.

When installed, the FS Pack module must be configured.

The FS module defines two pre-configured File System types: ``Unix`` and ``FatFS``.
Some characteristics don't need to be specified for these File System types, but they can be overridden if needed.
For example, specifying a ``Unix`` File System type will automatically set the file separator to ``/``.

If none of the pre-configured File System types correspond to the File System used in the C project, the ``Custom``
type can be used. When this type is selected, all the File System characteristics must be specified in the properties file.

.. tabs::

   .. tab:: SDK 6

      In SDK 6, the configuration is done in the properties file ``configuration.properties`` of the VEE Port project.
	  All the properties names listed below must be prefixed by ``com.microej.runtime.fs.``.
	  For example the ``fs`` properties is defined by the ``com.microej.runtime.fs.fs`` property.

   .. tab:: SDK 5

	  In SDK 5, the configuration is done in the properties file ``fs/fs.properties``.
	  This properties file specifies the characteristics of the File System used in the C project (case sensitivity, root
	  directory, file separator, etc.).

The list below describes the properties that can be defined in the configuration file:

- ``fs``: Defines the type of File System used in the C project (optional, the default value is ``Unix``). 
  This property can have one of the following values:

	- ``Unix``: select this configuration when using a Unix-like File System
		(case-sensitive, file separator is ``/``).
	- ``FatFS``: select this configuration when using FatFS File System
		(case-insensitive, file separator is ``/``).
	- ``Custom``: select this configuration when using another type of File System.

- ``root.dir``: Defines the File System root volume. 
  This property is optional for ``Unix`` and ``FatFS`` (``/`` by default for both).
- ``user.dir``: Defines the File System user directory. 
  This property is optional for ``FatFS`` (``/usr/`` by default).
- ``java.io.tmpdir``: Defines the File System temporary directory.  
  This property is optional for ``Unix`` and ``FatFS`` (``/tmp/`` by default for both).
- ``file.separator``: Defines the File System file separator. 
  This property is optional for ``Unix`` and ``FatFS`` (``/`` by default for both).
- ``path.separator``: Defines the File System path separator. 
  This property is optional for ``Unix`` and ``FatFS`` (``:`` by default for both).
- ``case.sensitivity``: Defines the case sensitivity of the File System. 
  This property is optional for ``Unix`` (``caseSensitive`` by default) and  ``FatFS`` (``caseInsensitive`` by default).
  This property can have one of the following values:

	- ``caseSensitive``: the File System is case-sensitive.
	- ``caseInsensitive``: the File System is case-insensitive.
   
   
Properties File Template
------------------------

The following snippet can be used as a template for ``fs.properties`` file:

.. tabs::

   .. tab:: SDK 6

		.. code-block:: properties

			# Defines the type of File System used in the C project.
			# Possible values are:
			#   - FatFs
			#   - Unix
			#   - Custom
			# @optional, default value is "Unix"
			#com.microej.runtime.fs=

			# Defines the File System root volume.
			# @optional for the following File System types:
			#   - FatFs (default value is "/")
			#   - Unix (default value is "/")
			# @mandatory for the following File System type:
			#   - Custom
			#com.microej.runtime.root.dir=

			# Defines the File System user directory.
			# @optional for the following File System type:
			#   - FatFs (default value is "/usr")
			# @mandatory for the following File System types:
			#   - Unix
			#   - Custom
			#com.microej.runtime.user.dir=

			# Defines the File System temporary directory.
			# @optional for the following File System types:
			#   - FatFs (default value is "/tmp")
			#   - Unix (default value is "/tmp")
			# @mandatory for the following File System type:
			#   - Custom
			#com.microej.runtime.java.io.tmpdir=

			# Defines the File System file separator.
			# @optional for the following File System types:
			#   - FatFs (default value is "/")
			#   - Unix (default value is "/")
			# @mandatory for the following File System type:
			#   - Custom
			#com.microej.runtime.file.separator=

			# Defines the File System path separator.
			# @optional for the following File System types:
			#   - FatFs (default value is ":")
			#   - Unix (default value is ":")
			# @mandatory for the following File System type:
			#   - Custom
			#com.microej.runtime.path.separator=

			# Defines the case sensitivity of the File System.
			# Valid values are "caseInsensitive" and "caseSensitive".
			# @optional for the following File System types:
			#   - FatFs (default value is "caseInsensitive")
			#   - Unix (default value is "caseSensitive")
			# @mandatory for the following File System type:
			#   - Custom
			#com.microej.runtime.case.sensitivity=

   .. tab:: SDK 5

		.. code-block:: properties

			# Defines the type of File System used in the C project.
			# Possible values are:
			#   - FatFs
			#   - Unix
			#   - Custom
			# @optional, default value is "Unix"
			#fs=

			# Defines the File System root volume.
			# @optional for the following File System types:
			#   - FatFs (default value is "/")
			#   - Unix (default value is "/")
			# @mandatory for the following File System type:
			#   - Custom
			#root.dir=

			# Defines the File System user directory.
			# @optional for the following File System type:
			#   - FatFs (default value is "/usr")
			# @mandatory for the following File System types:
			#   - Unix
			#   - Custom
			#user.dir=

			# Defines the File System temporary directory.
			# @optional for the following File System types:
			#   - FatFs (default value is "/tmp")
			#   - Unix (default value is "/tmp")
			# @mandatory for the following File System type:
			#   - Custom
			#java.io.tmpdir=

			# Defines the File System file separator.
			# @optional for the following File System types:
			#   - FatFs (default value is "/")
			#   - Unix (default value is "/")
			# @mandatory for the following File System type:
			#   - Custom
			#file.separator=

			# Defines the File System path separator.
			# @optional for the following File System types:
			#   - FatFs (default value is ":")
			#   - Unix (default value is ":")
			# @mandatory for the following File System type:
			#   - Custom
			#path.separator=

			# Defines the case sensitivity of the File System.
			# Valid values are "caseInsensitive" and "caseSensitive".
			# @optional for the following File System types:
			#   - FatFs (default value is "caseInsensitive")
			#   - Unix (default value is "caseSensitive")
			# @mandatory for the following File System type:
			#   - Custom
			#case.sensitivity=
   

Use
===

The `FS API Module`_ must be added to the project build file to use the FS library:

.. tabs::

   .. tab:: SDK 6 (build.gradle.kts)

      .. code-block:: kotlin

         implementation("ej.api:fs:2.0.6")

   .. tab:: SDK 5 (module.ivy)

      .. code-block:: xml

         <dependency org="ej.api" name="fs" rev="2.0.6"/>

.. _FS API Module: https://repository.microej.com/modules/ej/api/fs/

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
