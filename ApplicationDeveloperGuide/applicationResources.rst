.. _chapter.microej.applicationResources:

Application Resources
#####################

Application resources are the following :ref:`section.classpath.elements`:

-  :ref:`section.applicationResources.raw_resources`

-  :ref:`section.applicationResources.Images`

-  :ref:`section.applicationResources.Fonts`

-  :ref:`section.applicationResources.nls`

Principle
=========

A *resource* is, for an Application, the contents of a file.
This file is known by its path (its relative path from the Application classpath) and its name.
The file may be stored in RAM, flash, or external flash; and it is the responsibility of the Core Engine and/or the BSP to retrieve and load it.

.. _section.applicationResources.internal_and_external_resources:

Internal Resources and External Resources
-----------------------------------------

There are two kinds of resources, internal resources and external resources:

-  Internal resource: The resource is taken into consideration during the Application build.
   The SOAR step loads the resource and copies it into the same C library as the Application.
   Like the Application, the resource is linked into the CPU address space range (internal device memories, external parallel memories, etc.).

-  External resource: The resource is not taken into consideration during the Application build.
   It is the responsibility of the BSP project to manage this kind of resource.
   The resource is often programmed outside the CPU address space range (storage media like SD card, serial NOR flash, EEPROM, etc.).

   The BSP must implement the proper Low Level API (LLAPI) C functions: ``LLEXT_RES_impl.h``.
   See :ref:`section_externalresourceloader` for more information on the implementation.

All resources must be added in the project, usually in ``src/main/resources/...``.
All resources must be declared in the appropriate ``*.list`` files depending on the type (raw, image, font, NLS) and kind (internal or external) resources.
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
      imagesExt [shape=box, label="*.extimages.list"]
      fontsList [shape=box, label="*.fonts.list"]
      fontsExt [shape=box, label="*.extfonts.list"]
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

.. _section.applicationResources.raw_resources:

Raw Resources
=============

Raw resources are binary files that are embedded by the application so that they may be dynamically retrieved with a call to
`java.lang.Class.getResourceAsStream(String) <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#getResourceAsStream-java.lang.String->`_.

Raw Resources are declared in :ref:`Classpath<chapter.microej.classpath>` ``*.resources.list`` files (**and** in ``*.externresources.list`` for external resources).

.. graphviz::

  digraph D {
  
      internalRaw [shape=diamond, label="internal?"]
      rawList [shape=box, label="*.resources.list"]
      rawExt [shape=box, label="*.resources.list +\l*.externresources.list"]
      subgraph cluster_Raw {
          label ="Raw Resource"
          internalRaw -> rawList [label="yes"]
          internalRaw -> rawExt [label="no=external"]
      }
  }

The file format is a standard Java properties file, each line is a relative ``/`` separated name of a file in Classpath to be embedded as a resource.

For example:

::

   # The following resource is embedded as a raw resource
   com/mycompany/MyResource.txt

.. _section.applicationResources.Images:

Images
======

.. Keep this section sync'd with the overview in _section.ui.Images

Immutable images are graphical resources that can be accessed with a call to `ej.microui.display.Image.getImage() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Image.html#getImage-java.lang.String->`_ or `ej.microui.display.ResourceImage.loadImage() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/ResourceImage.html#loadImage-java.lang.String->`_. As their name suggests, immutable images can not be modified. Therefore, there is no way to get a Graphics Context to draw into these images. To be displayed, these
images have to be converted from their source format to a RAW
format. The conversion can either be done at:

-  build-time (using the image generator tool),

-  run-time (using the relevant decoder library).

Immutable images are declared in :ref:`Classpath<chapter.microej.classpath>` ``*.images.list`` files (**or** in ``*.imagesext.list`` for an external resource, see :ref:`section.applicationResources.internal_and_external_resources`).

.. graphviz::

  digraph D {
  
      internalImage [shape=diamond, label="internal?"]
      imagesList [shape=box, label="*.images.list"]
      imagesExt [shape=box, label="*.extimages.list"]
      subgraph cluster_image {
          label ="Image"
          internalImage -> imagesList [label="yes"]
          internalImage -> imagesExt [label="no=external"]
      }
  }

The file format is a standard Java properties file, each line representing a ``/`` separated resource path relative to the Classpath root referring to a standard image file (e.g. ``.png``, ``.jpg``).
The resource may be followed by an optional parameter (separated by a ``:``) which defines and/or describes the image output file format (RAW format).
When no option is specified, the image is embedded as-is and will be decoded at run-time.
Example:

::

   # The following image is embedded 
   # as a PNG resource (decoded at run-time)
   com/mycompany/MyImage1.png

   # The following image is embedded 
   # as a 16 bits format without transparency (decoded at build-time)
   com/mycompany/MyImage2.png:RGB565

   # The following image is embedded 
   # as a 16 bits format with transparency (decoded at build-time)
   com/mycompany/MyImage3.png:ARGB1555

Please refer to :ref:`section.ui.Images` for more information.

.. _section.applicationResources.Fonts:

Fonts
=====

.. Keep this section sync'd with the overview in _section.ui.Fonts

Fonts are graphical resources that can be accessed with a call to `ej.microui.display.Font.getFont() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Font.html#getFont-java.lang.String->`_.
Fonts are declared in :ref:`Classpath<chapter.microej.classpath>` ``*.fonts.list`` files (**or** in ``*.fontsext.list`` for an external resource, see :ref:`section.applicationResources.internal_and_external_resources`).

.. graphviz::

  digraph D {
  
      internalFont [shape=diamond, label="internal?"]
      fontsList [shape=box, label="*.fonts.list"]
      fontsExt [shape=box, label="*.extfonts.list"]
      subgraph cluster_font {
          label ="Font"
          internalFont -> fontsList [label="yes"]
          internalFont -> fontsExt [label="no=external"]
      }
  }

The file format is a standard Java properties file, each line representing a ``/`` separated resource path relative to the Classpath root referring to a Font file (usually with a ``.ejf`` file extension).
The resource may be followed by optional parameters which define :

-  some ranges of characters to embed in the final raw file;

-  the required pixel depth for transparency.

By default, all characters available in the input font file are embedded, and the pixel depth is ``1`` (i.e 1 bit-per-pixel).
Example:

::

   # The following font is embedded with all characters
   # without transparency
   com/mycompany/MyFont1.ejf

   # The following font is embedded with only the latin 
   # unicode range without transparency 
   com/mycompany/MyFont2.ejf:latin

   # The following font is embedded with all characters
   # with 2 levels of transparency
   com/mycompany/MyFont2.ejf::2

Font files conventionally end with the ``.ejf`` suffix and are
created using the Font Designer (see :ref:`section.tool.fontdesigner`).

Please refer to :ref:`section.ui.Fonts` for more information.

.. _section.applicationResources.nls:

Native Language Support
=======================

.. Keep this section sync'd with the overview in _section.ui.nls

Native Language Support (NLS) allows the application to facilitate internationalization.
It provides support to manipulate messages and translate them in different languages.
Each message to be internationalized is referenced by a key, which can be used in the application code instead of using the message directly.

Messages must be defined in `PO files <https://www.gnu.org/software/gettext/manual/gettext.html#PO-Files>`_, located in the Classpath of the application (for example in the ``src/main/resources`` folder).
Here is an example:

::

   msgid ""
   msgstr ""
   "Language: en_US\n"
   "Language-Team: English\n"
   "MIME-Version: 1.0\n"
   "Content-Type: text/plain; charset=UTF-8\n"

   msgid "Label1"
   msgstr "My label 1"

   msgid "Label2"
   msgstr "My label 2"

PO files are declared in :ref:`Classpath<chapter.microej.classpath>` ``*.nls.list`` files (**and** in ``*.externresources.list`` for an external resource, see :ref:`section.applicationResources.internal_and_external_resources`).

.. graphviz::

  digraph D {
  
      internalNLS [shape=diamond, label="internal?"]
      NLSList [shape=box, label="*.nls.list"]
      NLSExt [shape=box, label="*.nls.list +\l*.externresources.list"]
      subgraph cluster_NLS {
          label ="NLS"
          internalNLS -> NLSList [label="yes"]
          internalNLS -> NLSExt [label="no=external"]
      }
  }

The file format is a standard Java properties file, each line represents the Full Qualified Name of a Java interface that will be generated and used in the application.
Example:

.. code-block::

   com.mycompany.myapp.Labels
   com.mycompany.myapp.Messages

The message can be accessed with a call to `ej.nls.NLS.getMessage() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/nls/NLS.html#getMessage-int->`_.
Example:

.. code-block:: java

   import com.mycompany.myapp.Labels;

   public class MyClass {

      String label = Labels.NLS.getMessage(Labels.Label1);

      ...

Please refer to :ref:`section.ui.nls` for more information.


..
   | Copyright 2020-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
