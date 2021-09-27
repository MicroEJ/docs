.. _library_sources:

Library Sources
===============

All libraries part of MicroEJ SDK (including :ref:`MicroEJ Central Repository <central_repository>`)  provide their source code and resources.
This section describes how to get the sources, which depends on the library kind (Add-On or Foundation).

Add-On Library Sources
----------------------
Add-On Library Sources are packaged in a ZIP file named ``[module_name]-source.jar`` in the module directory:

.. figure:: images/addon_library_source.png
      :alt: Add-On Library Sources ZIP File
      :align: center

      Add-On Library Sources ZIP File

In MicroEJ SDK, sources are automatically connected to Eclipse JDT when a new Add-On Library is added as a :ref:`module dependency <mmm_module_dependencies>`.

On a Java element (type, method, field), press ``F3`` or ``CTRL-Click`` to open the implementation:

.. figure:: images/addon_library_open_implementation.png
      :alt: Add-On Library Open Implementation
      :align: center

      Add-On Library Open Implementation

This opens the implementation class in read-only mode.

.. figure:: images/addon_library_implementation_read_only.png
      :alt: Add-On Library Read-Only Source Code
      :align: center

      Add-On Library Read-Only Source Code

Foundation Library Sources
--------------------------


..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.