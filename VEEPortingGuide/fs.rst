.. _pack_fs:

===========
File System
===========


Principle
=========

The FS module defines a low-level File System framework for embedded
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

FS is an additional module. In the platform configuration file, check :guilabel:`FS` to install it. 
When checked, the properties file ``fs/fs.properties`` is required during platform creation in order to configure the module.
This properties file specifies the characteristics of the File System used in the C project (case sensitivity, root
directory, file separator, etc.).

The FS module defines two pre-configured File System types: ``Unix`` and ``FatFS``.
Some characteristics don't need to be specified for these File System types, but they can be overridden if needed.
For example, specifying a ``Unix`` File System type will automatically set the file separator to ``/``.

If none of the pre-configured File System types correspond to the File System used in the C project, the ``Custom``
type can be used. When this type is selected, all the File System characteristics must be specified in the properties file.

The list below describes the properties that can be defined in the file ``fs/fs.properties``:

-  ``fs``: Defines the type of File System used in the C project (optional, the default value is ``Unix``). 
   This property can have one of the following values:

   -  ``Unix``: select this configuration when using a Unix-like File System
      (case-sensitive, file separator is ``/``).

   -  ``FatFS``: select this configuration when using FatFS File System
      (case-insensitive, file separator is ``/``).
	  
   -  ``Custom``: select this configuration when using another type of File System.
   
-  ``root.dir``: Defines the File System root volume. This property is optional for ``Unix``
   and ``FatFS`` (``/`` by default for both).

-  ``user.dir``: Defines the File System user directory. This property is optional for ``FatFS``
   (``/usr/`` by default).

-  ``java.io.tmpdir``: Defines the File System temporary directory.  This property is optional for 
   ``Unix`` and ``FatFS`` (``/tmp/`` by default for both).
   
-  ``file.separator``: Defines the File System file separator. This property is optional for ``Unix``
   and ``FatFS`` (``/`` by default for both).

-  ``path.separator``: Defines the File System path separator. This property is optional for ``Unix``
   and ``FatFS`` (``:`` by default for both).

-  ``case.sensitivity``: Defines the case sensitivity of the File System. This property is optional 
   for ``Unix`` (``caseSensitive`` by default) and  ``FatFS`` (``caseInsensitive`` by default).
   This property can have one of the following values:

   - ``caseSensitive``: the File System is case-sensitive.
   
   - ``caseInsensitive``: the File System is case-insensitive.
   
   
Properties File Template
------------------------

The following snippet can be used as a template for ``fs.properties`` file:

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

The `FS API Module`_ must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project to use the FS library.

.. code-block:: xml

   <dependency org="ej.api" name="fs" rev="2.0.6"/>

.. _FS API Module: https://repository.microej.com/modules/ej/api/fs/

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
