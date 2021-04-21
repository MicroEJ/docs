.. _chapter.microej.applicationResources:

Application Resources
#####################

Application resources are the following :ref:`section.classpath.elements`:

-  :ref:`section.applicationResources.Images`

-  :ref:`section.applicationResources.Fonts`

-  :ref:`section.applicationResources.nls`

.. _section.applicationResources.Images:

Images
------

Overview
~~~~~~~~

Images are graphical resources that can be accessed with a call to
`ej.microui.display.Image.getImage() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Image.html#getImage-java.lang.String->`_ or `ej.microui.display.ResourceImage.loadImage() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/ResourceImage.html#loadImage-java.lang.String->`_ . To be displayed, these
images have to be converted from their source format to the display raw
format. The conversion can either be done at :

-  build-time (using the image generator tool),

-  run-time (using the relevant decoder library).

Images that must be processed by the image generator tool are declared
in MicroEJ Classpath ``*.images.list`` files. The file format is a
standard Java properties file, each line representing a ``/`` separated
resource path relative to the MicroEJ classpath root referring to a
standard image file (e.g. ``.png``, ``.jpg``). The resource may be
followed by an optional parameter (separated by a ``:``) which defines
and/or describes the image output file format (raw format). When no
option is specified, the image is embedded as-is and will be decoded at
run-time (although listing files without format specifier has no impact
on the image generator processing, it is advised to specify them in the
``*.images.list`` files anyway, as it makes the run-time processing
behavior explicit). Example:

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
-----

Overview
~~~~~~~~

Fonts are graphical resources that can be accessed with a call to
`ej.microui.display.Font.getFont() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Font.html#getFont-java.lang.String->`_. To be displayed, these fonts have
to be converted at build-time from their source format to the display
raw format by the font generator tool. Fonts that must be processed by
the font generator tool are declared in MicroEJ Classpath
``*.fonts.list`` files. The file format is a standard Java properties
file, each line representing a ``/`` separated resource path relative to
the MicroEJ classpath root referring to a MicroEJ font file (usually
with a ``.ejf`` file extension). The resource may be followed by
optional parameters which define :

-  some ranges of characters to embed in the final raw file;

-  the required pixel depth for transparency.

By default, all characters available in the input font file are
embedded, and the pixel depth is ``1`` (i.e 1 bit-per-pixel). Example:

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

MicroEJ font files conventionally end with the ``.ejf`` suffix and are
created using the Font Designer (see :ref:`section.tool.fontdesigner`).

Font Range
~~~~~~~~~~

The first parameter is for specifying the font ranges to embed.
Selecting only a specific set of characters to embed reduces the memory
footprint. If unspecified, all characters of the font are embedded. 

Several ranges can be specified, separated by ``;``. There
are two ways to specify a character range: the custom range and the
known range.

Custom Range
~~~~~~~~~~~~

Allows the selection of raw Unicode character ranges.

Examples:

-  ``myfont:0x21-0x49``: Defines one range: embed all characters from 0x21 to 0x49
   (included);
-  ``myfont:0x21-0x49,0x55-0x75``: Defines a set of two ranges: embed all characters from 0x21 to 0x49 and from 0x55 to 0x75.
-  ``myfont:0x21-0x49,0x55``: Defines a set of one range and one character: embed all characters from 0x21 to 0x49 and character 0x55.

Known Range
~~~~~~~~~~~

A known range is a range available in the following table.

Examples:

-  ``myfont:basic_latin``: Embed all *Basic Latin* characters;
-  ``myfont:basic_latin;arabic``: Embed all *Basic Latin* characters,
   and all *Arabic* characters.

Transparency
~~~~~~~~~~~~

The second parameter is for specifying the font transparency level
(``1``, ``2``, ``4`` or ``8``). If unspecified, the encoded transparency level is ``1`` (does not depend on transparency level encoded in EJF file).

Examples:

-  ``myfont:latin:4``: Embed all latin characters with 16 levels of
   transparency

-  ``myfont::2``: Embed all characters with 4 levels of transparency

.. _section.applicationResources.nls:

Native Language Support
-----------------------

Native Language Support (NLS) allows the application to facilitate internationalization.
It provides support to manipulate messages and translate them in different languages.
Each message to be internationalized is referenced by a key, which can be 
used in the application code instead of using the message directly.

Messages must be defined in `PO files <https://www.gnu.org/software/gettext/manual/gettext.html#PO-Files>`_ in the MicroEJ Classpath of the application.
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

These PO files have to be converted to be usable by the application.
In order to let the build system know which PO files to process, 
they must be referenced in MicroEJ Classpath ``*.nls.list`` files.
The file format of these ``*.nls.list`` files is a standard Java properties file.
Each line represents the Full Qualified Name of a Java interface that will be 
generated and used in the application. Here is an example, let's call it `i18n.nls.list`:

.. code-block::

   com.mycompany.myapp.Labels
   com.mycompany.myapp.Messages

For each line, PO files whose name starts with the interface name (``Messages`` and ``Labels``
in the example) are retrieved from the MicroEJ Classpath and used to generate:

- a Java interface with the given FQN, containing a field for each ``msgid`` of the PO files
- a NLS binary file containing the translations

So, in the example, the generated interface ``com.mycompany.myapp.Labels`` will gather all the 
translations from files named ``Labels*.po`` and located in the MicroEJ Classpath.
PO files are generally suffixed by their locale (``Labels_en_US.po``) but it is only for convenience
since the suffix is not used, the locale is extracted from the PO file's metadata.

Once the generation is done, the application can use the Java interfaces to get internationalized 
messages, for example:

.. code-block:: java

   import com.mycompany.myapp.Labels;

   public class MyClass {

      String label = Labels.Label1;

      ...

The generation is triggered when building the application or after a change done in any PO or ``*.nls.list`` files.
This allows to always have the Java interfaces up-to-date with the translations and to use them immediately.

The `NLS API module <https://repository.microej.com/modules/ej/library/runtime/nls/>`_
must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ
Application project, in order to allow access to the NLS library.

::

  <dependency org="ej.library.runtime" name="nls" rev="3.0.1"/>

..
   | Copyright 2020-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
