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
All resources must be declared in the appropriate ``*.list`` files depending on the type (raw, image, font, NLS) and the storage location (internal or external).
The following figure summarized how to declare resources:

.. graphviz::

  digraph D {
  
  subgraph cluster_main {
      init [shape=box, label="Add resource to project\lin src/main/resources/..." ]
      type [shape=diamond, label="Type of resource?"]
  
      internalRaw [shape=diamond, label="internal?"]
      internalImage [shape=diamond, label="internal?"]
      internalFont [shape=diamond, label="internal?"]
      internalNLS [shape=diamond, label="internal?"]
  
      rawList [shape=box, label="*.resources.list"]
      rawExt [shape=box, label="*.resources.list +\l*.externresources.list"]
      imagesList [shape=box, label="*.images.list"]
      imagesExt [shape=box, label="*.imagesext.list"]
      fontsList [shape=box, label="*.fonts.list"]
      fontsExt [shape=box, label="*.fontsext.list"]
      NLSList [shape=box, label="*.nls.list"]
      NLSExt [shape=box, label="*.nls.list +\l*.externresources.list"]
  
      init -> type
  
      type -> internalRaw
      subgraph cluster_Raw {
          label ="Raw Resource"
          internalRaw -> rawList [label="yes"]
          internalRaw -> rawExt [label="no=external"]
      }
  
      type -> internalImage
      subgraph cluster_image {
          label ="Image"
          internalImage -> imagesList [label="yes"]
          internalImage -> imagesExt [label="no=external"]
      }
  
      type -> internalFont
      subgraph cluster_font {
          label ="Font"
          internalFont -> fontsList [label="yes"]
          internalFont -> fontsExt [label="no=external"]
      }
      type -> internalNLS
      subgraph cluster_NLS {
          label ="NLS"
          internalNLS -> NLSList [label="yes"]
          internalNLS -> NLSExt [label="no=external"]
      }
  }
  
  }

For more details on how to use Application resources, refer to the following dedicated sections:

-  :ref:`Raw Resource <section.classpath.elements.raw_resources>`

-  :ref:`Image <section.ui.Images>`

-  :ref:`Font <section.ui.Fonts>`

-  :ref:`Internationalized String (Native Language Support) <chapter.nls>`


..
   | Copyright 2020-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
