.. _chapter.microej.applicationResources:

Application Resources
#####################

An Application resource is the contents of a file identified its relative path from the Application :ref:`classpath <chapter.microej.classpath>`.

An Application resource is one of the following type:

-  Raw Resource,
-  Image,
-  Font,
-  Internationalized Message (Native Language Support).

The resource may be stored in RAM, flash, or external flash; and it is the responsibility of the Core Engine and/or the BSP to retrieve and load it.

There are two ways to store resources:

-  Internal resource: The resource is taken into consideration during the Application build.
   The SOAR step loads the resource and copies it into the same C library as the Application.
   Like the Application, the resource is linked into the CPU address space range (internal device memories, external parallel memories, etc.).

-  External resource: The resource is not taken into consideration during the Application build.
   It is the responsibility of the BSP project to manage external resources.
   The resource is often programmed outside the CPU address space range (storage media like SD card, serial NOR flash, EEPROM, etc.).

   The BSP must implement the proper Low Level API (LLAPI) C functions: ``LLEXT_RES_impl.h``.
   See :ref:`section_externalresourceloader` for more information on the implementation.

All resources must be added in the project, usually in ``src/main/resources/...`` folder.
All resources must be declared in the appropriate ``*.list`` files depending on the type (raw, UI image, VG image, UI font, VG font, NLS) and the storage location (internal or external).
The following figure summarized how to declare resources:

.. list-table:: Resources
   :header-rows: 1
   :widths: 20 10 70

   * - Resource type
     - Location
     - File(s) to update
   * - :ref:`Raw Resource <section.classpath.elements.raw_resources>`
     - internal
     - ``*.resources.list``
   * - 
     - external
     - ``*.resources.list`` **and** ``*.externresources.list``
   * - :ref:`MicroUI Image <section.ui.Images>`
     - internal
     - ``*.images.list``
   * - 
     - external
     - ``*.externimages.list`` **or** ``*.imagesext.list``  (deprecated)
   * - :ref:`MicroVG Image <vectorimage_overview>`
     - internal
     - ``*.vectorimages.list``
   * - 
     - external
     - ``*.externvectorimages.list``
   * - :ref:`MicroUI Font <section.ui.fonts.list>`
     - internal
     - ``*.fonts.list``
   * - 
     - external
     - ``*.fontsext.list``
   * - :ref:`MicroVG Font <section_vector_fonts>`
     - internal
     - ``*.resources.list``
   * - 
     - external
     - ``*.resources.list`` **and** ``*.externresources.list``
   * - :ref:`Internationalized String (Native Language Support) <section.nls.list_files>`
     - internal
     - ``*.nls.list``
   * - 
     - external
     - ``*.nls.list`` **and** ``*.externresources.list``

..
   | Copyright 2020-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
