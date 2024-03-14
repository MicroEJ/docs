.. _chapter.nls:

Native Language Support
=======================

Introduction
------------

Native Language Support (NLS) allows the application to facilitate internationalization.
It provides support to manipulate messages and translate them in different languages.
Each message to be internationalized is referenced by a key, which can be used in the application code instead of using the message directly.

.. _section.nls.principle:

Principle
---------

NLS is distributed as an add-on library containing a single Java interface: `NLS`_.

In addition to that, the `binary-nls`_ library provides a factory for implementations of this interface:
it uses an :ref:`add-on processor <module_natures.addon_processor>` which processes, offboard, the
Localization Source Files into one `BON resource buffer`_ file for compactness.

During the :ref:`clinit <soar_clinit>` phase, this resource file is opened and the list of locales is parsed.
After that, the resource remains opened for the rest of the Application execution and is directly used to
retrieve messages translations for the supported locales.

.. _NLS: https://repository.microej.com/javadoc/microej_5.x/apis/ej/nls/NLS.html
.. _BON resource buffer: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/ResourceBuffer.html

Localization Source Files
-------------------------

Messages must be defined in localization source files, located in the Classpath of the application (i.e. in the ``src/main/resources`` folder).

Localization source files can be either `PO files <https://www.gnu.org/software/gettext/manual/gettext.html#PO-Files>`_ or `Android String resources <https://developer.android.com/guide/topics/resources/string-resource>`_.

Here is an example of a PO file:

.. code-block:: po

   msgid "Label1"
   msgstr "My label 1"

   msgid "Label2"
   msgstr "My label 2"

And here is an example of an Android String resource:

.. code-block:: xml

   <resources>
      <string name="Label1">My label 1</string>
      <string name="Label2">My label 2</string>
   </resources>

.. hint::

   The Android String resources `string arrays <https://developer.android.com/guide/topics/resources/string-resource#StringArray>`_ feature is also supported.

NLS List Files
--------------

Localization source files are declared in :ref:`Classpath<chapter.microej.classpath>` ``*.nls.list`` files (**and** to ``*.externresources.list`` for an external resource, see :ref:`chapter.microej.applicationResources` and :ref:`Loading Translations as an External Resource<nls_external_resource>`).

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

.. _nls_usage:

Usage
-----

The `binary-nls`_ module must be added to the Application project build file:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: java

         implementation("com.microej.library.runtime:binary-nls:2.5.0")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="com.microej.library.runtime" name="binary-nls" rev="2.5.0"/>

This module includes an Add-On Processor which parses the localization source files.
For each interface declared in the NLS list files, all the localization source files whose names start with the interface name are used to generate:

- a Java interface with the given FQN, containing a field for each message of the localization source files
- a NLS binary file containing the translations

So, in the example, the generated interface ``com.mycompany.myapp.Labels`` will gather all the 
translations from files named ``Labels*`` and located in any package of the Classpath.
The names of the localization source files should be suffixed by their locale (for example ``Labels_en_US.po``).

The generation is triggered when building the application or after a change done in any localization source file or ``*.nls.list`` files.
This allows to always have the Java interfaces up-to-date with the translations and to use them immediately.

Besides the message fields, the generated interface declares an NLS instance which is automatically created in the clinit of the interface.

Once the generation is done, the application can use the Java interfaces to get internationalized 
messages, for example:

.. code-block:: java

   String label = Labels.NLS.getMessage(Labels.Label1);

Locale
------

For the application to know which language to use among those made available and when, you can set it and change it at any point using the `setCurrentLocale(locale)`_ method. 
If no locale has been set yet when getting a message, the translation for the first locale available in alphabetical order will be used by default. 
However, you can also pick this locale to default to yourself, by adding a ``com.microej.binarynls.defaultLocale`` property followed by a locale name in a ``.properties.list`` file. 

.. _binary-nls: https://repository.microej.com/modules/com/microej/library/runtime/binary-nls
.. _setCurrentLocale(locale): https://repository.microej.com/javadoc/microej_5.x/apis/ej/nls/NLS.html#setCurrentLocale-java.lang.String-

Plural Forms
------------

Version 4.0.0 of the `NLS module`_ and version 3.0.0 of the `binary-nls`_ module introduce the support of GNU gettext's plural form feature in PO files.

.. warning:: This feature concerns only the PO files, not the Android String resources `quantity strings <https://developer.android.com/guide/topics/resources/string-resource#Plurals>`_ .

This allows usage of ``Plural-Forms`` header entries and several ``msgstr`` 's per ``msgid`` (referred to as plural forms) `as specified by gettext`_; you can then retrieve the correct message in a locale for a given count of things by using the `ej.nls.NLS.getMessage()`_ methods that take in this count value as an argument.

If a message for a given ``msgid`` has a ``msgid_plural`` and plural forms in a PO file for an interface declared in an NLS list file, it must also have plural forms in all other PO files for this interface.

.. note::

   Please note that one significant difference with gettext's implementation is that the expression described in the ``plural`` field of the ``Plural-Forms`` header must be a valid **Java** expression returning an ``int``, as opposed to a C expression. A usual case in which this makes a difference is for expressions that rely on boolean values being evaluated as zero or one in C, such as in: 

   .. code-block::

      "Plural-Forms: nplurals=2; plural=n != 1;\n"

   This expression will not work with our implementation as Java does not interpret booleans as integers. An easy way to convert this expression would be:

   .. code-block::

      "Plural-Forms: nplurals=2; plural=n != 1 ? 1 : 0;\n"

   Also note that the validity of these provided expressions is not entirely checked. Providing an expression that is not valid Java or that would return an invalid plural form index would cause errors at runtime or even in the Java files generated by the Add-On Processor.

.. _NLS module: https://repository.microej.com/modules/ej/library/runtime/nls/
.. _as specified by gettext: https://www.gnu.org/software/gettext/manual/html_node/Plural-forms.html

Missing Translations
--------------------

By default, if a translation is missing for a given ``msgid`` in a PO file in a given language, the message returned by the `ej.nls.NLS.getMessage()`_ method with the locale set to this language will simply be the ``msgid`` itself. 
In the case of an XML Android String resource, the ``name`` attribute of a missing ``string`` element will be returned. 
However if returning this identifier is not a suitable solution, you might want to set a fallback locale parameter for an interface. 
This parameter corresponds to a language to print the translation for a message in, in case it is not available in the current language.

Starting with version 2.5.0 of the `binary-nls`_ module, you can set this fallback locale by specifying a locale name in a ``.nls.list`` file, after the name of the interface you want this locale to be the fallback for, separated by a colon ``:``. 
For example, with the following ``.nls.list`` file, if a translation is missing in a language for a message in the ``Labels`` and ``Messages`` PO/XML files, the message will be translated to ``en_US`` instead of just returning its ``msgid``/``name``.

.. code-block::

   # Missing translations for Labels and Messages will fall back to en_US
   com.mycompany.myapp.Labels:en_US
   com.mycompany.myapp.Messages:en_US

As such, you can specify a different fallback locale for each interface in a ``.nls.list`` file. 
For example, with the following ``.nls.list`` file, the messages in ``Labels`` will not have a fallback language set and will only return the ``msgid``/``name`` if a translation is missing, while missing translations will default to ``en_US`` for the messages in ``Messages``, and to ``ja_JP`` for the messages in ``Content`` :

.. code-block::

   # Missing translations for Labels will fall back to their msgid/name
   com.mycompany.myapp.Labels

   # Missing translations for Messages will fall back to en_US
   com.mycompany.myapp.Messages:en_US

   # Missing translations for Content will fall back to ja_JP
   com.mycompany.myapp.Content:ja_JP

In the case of a message with plural forms in PO files, this works much the same way, using the messages and forms in the fallback locale if available.
If no fallback locale is specified or if the requested message is not specified in it, then the ``msgid`` will be used for a count value of 1, and the ``msgid_plural`` will be used for any other value, as gettext would function.

.. _ej.nls.NLS.getMessage(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/nls/NLS.html#getMessage-int-

Converter
---------

Problematic
^^^^^^^^^^^

Translated messages can be used directly for the following purposes:

* EDC (in the console): `System.out.println()`_.
* MicroUI: `ej.microui.display.Painter.drawString()`_.
* MicroVG: `ej.microvg.VectorGraphicsPainter.drawString()`_.

When displaying certain languages, such as Arabic, string analysis is necessary for character substitution and right-to-left (RTL) reading direction. 
:ref:`Console encoding <set_console_encoding>` is required for proper display using EDC.

.. tabs::

   .. tab:: Without Console Encoding

      .. code-block:: java

         System.out.print("العربية");

      .. code-block:: console

         'D91(J)

   .. tab:: With Console Encoding

      .. code-block:: java

         System.out.print("العربية");

      .. code-block:: console

         العربية

In order to render correctly such a message with MicroVG, the :ref:`complex layout <section_vg_font_complex>` must be used.
This means that the font must contain substitution tables that the rendering engine can read and apply.
If these conditions are not met, the rendering may be incorrect.
It is also important to note that using a complex font has a cost in terms of flash storage (due to the increased size of the TTF file and the addition of complex layout algorithms) as well as in run time (due to the time required to apply the substitution tables).

.. tabs::

   .. tab:: Without Complex Layout

      .. figure:: UI/NLS/images/microvg_not_converted_simple.png

   .. tab:: With Complex Layout

      .. figure:: UI/NLS/images/microvg_not_converted_complex.png


It is not possible to render such a message with MicroUI: the Graphics Engine does not offer substitution table reading or bidirectional string management.
The rendering is systematically wrong:

.. figure:: UI/NLS/images/microui_not_converted.png

.. _System.out.println(): https://repository.microej.com/javadoc/microej_5.x/apis/java/io/PrintStream.html#println--
.. _ej.microui.display.Painter.drawString(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Painter.html#drawString-ej.microui.display.GraphicsContext-java.lang.String-ej.microui.display.Font-int-int-
.. _ej.microvg.VectorGraphicsPainter.drawString(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microvg/VectorGraphicsPainter.html#drawString-ej.microui.display.GraphicsContext-java.lang.String-ej.microvg.VectorFont-float-float-float-

Solution
^^^^^^^^

Since the version 3.1.0, the `binary-nls`_ module features an offboard translation conversion.
It means that the generated strings can be substituted and rearranged before being embedded in the executable.

This conversion enables MicroUI's Graphics Engine to render complex strings correctly.

.. warning:: This offboard conversion only concerns PO files.

.. tabs::

   .. tab:: Without Offboard Conversion

      .. figure:: UI/NLS/images/microui_not_converted.png

   .. tab:: With Offboard Conversion

      .. figure:: UI/NLS/images/microui_converted.png

This also avoids embedding substitution tables and the complex layout management when the message is rendered with MicroVG.

Principle
^^^^^^^^^

Keep in mind that offboard conversion is only relevant to translated strings.
It is important to note that all other fields, such as message identifiers and display names, are not converted as they are not intended to be rendered.

.. code-block:: console

   msgid "Arabic" // not converted
   msgstr "العربية" // converted

Offboard conversion is not a systematic process, so it is necessary to mention it explicitly in the PO file.
To do so, add ``Language-converter: name_of_converter\n`` to the PO file's header, where ``name_of_converter`` is the name of the converter to be applied (see below for the available list of converters).

.. code-block:: po

   msgid ""
   msgstr ""
   "Language: ar_AR\n"
   "Language-Team: العربية\n"
   "Language-Converter: Arabic\n"
   "MIME-Version: 1.0\n"
   "Content-Type: text/plain; charset=UTF-8\n"

   msgid "Arabic"
   msgstr "العربية"

List of Converters
^^^^^^^^^^^^^^^^^^

Bidi
""""

This converter features details about the bidirectional reordering of text, which is necessary to correctly render Arabic or Hebrew text.
These languages are unique in that they are mixed-directional, meaning they order numbers from left to right while ordering most other text from right to left.

* Example:

.. code-block:: po

   msgid ""
   msgstr ""
   "Language: bidi\n"
   "Language-Team: Bidirectional\n"
   "Language-Converter: Bidi\n"
   "MIME-Version: 1.0\n"
   "Content-Type: text/plain; charset=UTF-8\n"

   msgid "Hello"
   msgstr "‮Hello‬"

Arabic
""""""

This converter is dedicated to the Arabic language, which involves text-based shaping and bidirectional reordering of text.
Text-based shaping refers to the process of replacing certain character code points in the text with others depending on the context.
The purpose of this process is to transform one type of text into another.

Example: العربية

* Unicodes: :guilabel:`U+627` :guilabel:`U+644` :guilabel:`U+639` :guilabel:`U+631` :guilabel:`U+628` :guilabel:`U+64a` :guilabel:`U+629`
* Text shaping: :guilabel:`U+fe8d` :guilabel:`U+fedf` :guilabel:`U+fecc` :guilabel:`U+feae` :guilabel:`U+fe91` :guilabel:`U+fef4` :guilabel:`U+fe94`
* Redirection: :guilabel:`U+fe94` :guilabel:`U+fef4` :guilabel:`U+fe91` :guilabel:`U+feae` :guilabel:`U+fecc` :guilabel:`U+fedf` :guilabel:`U+fe8d`

Hebrew
""""""

This converter is dedicated to the Hebrew language, which involves text-based shaping and bidirectional reordering of text.
A substituted character is not available for each combination *vowel + letter*.
The following table lists the supported combinations.
For all others combinations (Niqqud), the vowel and the letter are rendered independently.


.. list-table:: 
   :widths: auto
   :header-rows: 1

   * - Vowel
     - Representation
     - Unicode
     - Letter
     - Representation
     - Unicode
     - Substitution
     - Unicode
   * - Sheva
     - ◌ְ
     - U+05B0
     - 
     - 
     - 
     - 
     - 
   * - Hataf Segol
     - ◌ֱ
     - U+05B1
     - 
     - 
     - 
     - 
     - 
   * - Hataf Patah
     - ◌ֲ
     - U+05B2
     - 
     - 
     - 
     - 
     - 
   * - Hataf Qamats
     - ◌ֳ
     - U+05B3
     - 
     - 
     - 
     - 
     - 
   * - Hiriq
     - ◌ִ
     - U+05B4
     - Yod
     - י
     - U+05B4
     - יִ
     - U+FB1D
   * - Tsere
     - ◌ֵ
     - U+05B5
     - 
     - 
     - 
     - 
     - 
   * - Segol
     - ◌ֶ
     - U+05B6
     - 
     - 
     - 
     - 
     - 
   * - Patah
     - ◌ַ
     - U+05B7
     - Alef
     - א
     - U+05D0
     - אַ
     - U+FB2E
   * - Qamats
     - ◌ָ
     - U+05B8
     - Alef
     - א
     - U+05D0
     - אָ
     - U+FB2F
   * - Holam
     - ◌ֹ
     - U+05B9
     - Vav
     - ו
     - U+05D5
     - וֹ
     - U+FB4B
   * - Holam Haser (for Vav U+05D5)
     - ◌ֺ
     - U+05BA
     - 
     - 
     - 
     - 
     - 
   * - Qubuts
     - ◌ֻ
     - U+05BB
     - 
     - 
     - 
     - 
     - 
   * - Mapiq
     - ◌ּ
     - U+05BC
     - Alef
     - א
     - U+05D0
     - אּ
     - U+FB30
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Bet
     - ב
     - U+05D1
     - בּ
     - U+FB31
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Gimel
     - ג
     - U+05D2
     - גּ
     - U+FB32    
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Dalet
     - ד
     - U+05D3
     - דּ
     - U+FB33     
   * - Mapiq
     - ◌ּ
     - U+05BC
     - He
     - ה
     - U+05D4
     - הּ
     - U+FB34     
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Vav
     - ו
     - U+05D5
     - וּ
     - U+FB35    
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Zayin
     - ז
     - U+05D6
     - זּ
     - U+FB36     
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Tet
     - ט
     - U+05D8
     - טּ
     - U+FB38     
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Yod
     - י
     - U+05D9
     - יּ
     - U+FB39
     
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Final Kaf
     - ך
     - U+05DA
     - ךּ
     - U+FB3A
     
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Kaf
     - כ
     - U+05DB
     - כּ
     - U+FB3B
     
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Lamed
     - ל
     - U+05DC
     - לּ
     - U+FB3C
     
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Mem
     - מ
     - U+05DE
     - מּ
     - U+FB3E
     
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Nun
     - נ
     - U+05E0
     - נּ
     - U+FB40
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Samekh
     - ס
     - U+05E1
     - סּ
     - U+FB41
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Final Pe
     - ף
     - U+05E3
     - ףּ
     - U+FB43
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Pe
     - פ
     - U+05E4
     - פּ
     - U+FB44
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Tsadi
     - צ
     - U+05E6
     - צּ
     - U+FB46
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Qof
     - ק
     - U+05E7
     - קּ
     - U+FB47
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Resh
     - ר
     - U+05E8
     - רּ
     - U+FB48
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Shin
     - ש
     - U+05E9
     - שּ
     - U+FB49
   * - Dagesh
     - ◌ּ
     - U+05BC
     - Tav
     - ת
     - U+05EA
     - תּ
     - U+FB4A
   * - Meteg
     - ◌ֽ
     - U+05BD
     - 
     - 
     - 
     - 
     - 
   * - Maqaf
     - ־
     - U+05BE
     - 
     - 
     - 
     - 
     - 
   * - Rafe
     - ◌ֿ
     - U+05BF
     - Bet
     - ב
     - U+05D1
     - בֿ
     - U+FB4C
   * - Rafe
     - ◌ֿ
     - U+05BF
     - Kaf 
     - כ
     - U+05DB
     - כֿ
     - U+FB4D
   * - Rafe
     - ◌ֿ
     - U+05BF
     - Pe 
     - פ
     - U+05E4
     - פֿ
     - U+FB4E
   * - Paseq
     - ׀
     - U+05C0
     - 
     - 
     - 
     - 
     - 
   * - Shin Dot
     - ◌ׁ
     - U+05C1
     - Shin 
     - ש
     - U+05E9
     - שׁ
     - U+FB2A
   * - Shin Dot
     - ◌ׁ
     - U+05C1
     - Shin with Dagesh 
     - שּ
     - U+FB49
     - שּׁ
     - U+FB2C
   * - Sin Dot
     - ◌ׂ
     - U+05C2
     - Sin 
     - ש
     - U+05E9
     - שׂ
     - U+FB2B
   * - Sin Dot
     - ◌ׂ
     - U+05C2
     - Shin with Dagesh 
     - שּ
     - U+FB49
     - שּׂ
     - U+FB2D
   * - Sof Pasuq
     - ׃
     - U+05C3
     - 
     - 
     - 
     - 
     - 
   * - Upper Dot
     - ◌ׄ
     - U+05C4
     - 
     - 
     - 
     - 
     - 
   * - Lower Dot
     - ◌ׅ
     - U+05C5
     - 
     - 
     - 
     - 
     - 

* Example:

.. code-block:: po

   msgid ""
   msgstr ""
   "Language: he\n"
   "Language-Team: Hebrew\n"
   "Language-Converter: Hebrew\n"
   "MIME-Version: 1.0\n"
   "Content-Type: text/plain; charset=UTF-8\n"

   msgid "Hello"
   msgstr "בוקר טוב"


Limitations
^^^^^^^^^^^

Conversion is a feature dedicated to graphic display (MicroUI or MicroVG).
A message converted and displayed with :ref:`EDC <set_console_encoding>` may be shown incorrectly, especially regarding visual orientation.

.. tabs::

   .. tab:: Without Offboard Conversion

      .. code-block:: java

         System.out.print("العربية");

      .. code-block:: console

         العربية

   .. tab:: With Offboard Conversion

      .. code-block:: java

         System.out.print("العربية");

      .. code-block:: console

         ﺔﻴﺑﺮﻌﻟﺍ

Messages are usually displayed using a single type of output, either EDC or UI.
When printing the text with EDC, it is correctly rendered without any pre-conversion (the terminal on the PC, that actually prints the text, performs the necessary reordering, substitutions, etc.)
To properly render the text on the UI display, the PO file must explicitly specify a converter (see above) to ensure compatibility.
But when printing a pre-converted text with EDC, the application needs to add the character :guilabel:`U+202D` before the message to force the message orientation, and :guilabel:`U+202C` after it to restore the previous orientation.

.. tabs::

   .. tab:: Without :guilabel:`U+202D`

      .. code-block:: java

         System.out.print("العربية");

      .. code-block:: console

         ﺔﻴﺑﺮﻌﻟﺍ

   .. tab:: With :guilabel:`U+202D`

      .. code-block:: java

         System.out.print("\u202D" + "العربية" + "\u202C");

      .. code-block:: console

         العربية

.. warning:: This tip works on the Simulator but may not work with the MicroVG complex layout manager.


Resource Generation
-------------------

If the classpath of the Application contains ``.po``/``.xml`` files and ``.nls.list`` files, the ``binary-nls`` Add-On Processor will generate the following source files for each NLS interface:

- a ``.resourcebuffer``
- a ``.resourcebuffer.list`` which references the ``.resourcebuffer``
- a ``.resources.list`` which references the resource (this resource does not exist yet but it will be generated later)

When building the Application or running it on Simulator, the Resource Buffer Generator is first executed.
Based on the ``.resourcebuffer`` and the ``.resourcebuffer.list``, it will generate a resource.

Since the generated resource is referenced by the ``.resources.list`` generated by the ``binary-nls`` ADP, the SOAR will embed the resource in the Application binary.
Unless it is also referenced by an ``.externresources.list`` in which case the SOAR will output the resource in the :ref:`External Resources Folder<external_resources_folder>` instead.

This resource is loaded as soon as the BinaryNLS instance is created, in the clinit of the generated NLS interface (see :ref:`Principle <section.nls.principle>`).

.. _section.nls.limitations:

Limitations
-----------

The latest BinaryNLS implementation does not support (even when the resource is external; see :ref:`External resource loader <section_externalresourceloader>`):

* to dynamically add a new locale
* to dynamically modify messages translations

For any addition / modification, the Application must be restarted and, typically, the full resource buffer
must be updated (not only the part of the added/modified locale).

Also, there is no API to close the resource buffer. If it is external, the Application must be stopped to
close this resource, before it can potentially be modified depending on the external resource loader.

.. _chapter.microej.nlsExternalLoader:

NLS External Loader Tool
------------------------

The `NLS External Loader`_ tool allows to update the PO files of an application executed on a Virtual Device without rebuilding it.
PO files can be dropped in a given location in the Virtual Device folders to dynamically replace the language strings packaged in the application.

This is typically useful when testing or translating an application in order to have a quick feedback when changing the PO files.
Once the PO files are updated, a simple restart of the Virtual Device allows to immediately see the result.

.. _NLS External Loader: https://repository.microej.com/modules/com/microej/tool/nls-po-external-loader/

Installation
^^^^^^^^^^^^

To enable the NLS External Loader in the Virtual Device, add the following dependency to the Firmware project:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: java

         implementation("com.microej.tool:nls-po-external-loader:2.3.0")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="com.microej.tool" name="nls-po-external-loader" rev="2.3.0" transitive="false"/>

Then rebuild the Firmware project to produce the Virtual Device.

Usage
^^^^^

Once the project built:

- unzip the Virtual Device and create a folder named ``translations`` in the root folder.
- copy all the PO files from the project into the ``translations`` folder.
  All PO files found in this folder are processed, no matter their folder level.
- start the Virtual Device with the launcher.
  The following logs should be printed if the NLS External Loader has been executed and has found the PO files::

   externalPoLoaderInit:init:

   externalPoLoaderInit:loadPo:
      [mkdir] Created dir: <PATH>\tmp\microejlaunch1307817858\resourcebuffer
   [po-to-nls] *.nls files found in <PATH>\output\<FIRMWARE>\resourceBuffer :
   [po-to-nls]   - com.mycompany.Messages1
   [po-to-nls]   - com.mycompany.Messages2
   [po-to-nls] Loading *.po files for NLS interface com.mycompany.Messages1
   [po-to-nls]   => loaded locales : fr_FR,de_DE,ja_JP,en_US
   [po-to-nls] Loading *.po files for NLS interface com.mycompany.Messages2
   [po-to-nls]   => loaded locales : fr_FR,de_DE,ja_JP,en_US

- update the languages strings in the PO files of the Virtual Device (the files in the `translations/` folder).
- restart the Virtual Device and check the changes.


It is important to know the following rules about the NLS External Loader:

- the external PO files names must match with the default PO files names of the application to be processed.
- when PO files with a given name are loaded, the default translations for these PO files are replaced, there is no merge. It means that:

  - if messages are missing in the new PO files, they are not available anymore for the application and may very probably make it crash.
  - if languages are missing (the application has 3 PO files for English, French and Spanish, 
    and only PO files for English and French are available in the translations folder), 
    the messages of the missing languages are not available anymore for the application and may very probably make it crash.
  - if new messages are added in the PO files, it has no impact, they are ignored by the application.

- External PO files are loaded at Virtual Device startup, so any change requires a restart of the Virtual Device to be considered


Troubleshooting
^^^^^^^^^^^^^^^

java.io.IOException: NLS-PO:S=4
"""""""""""""""""""""""""""""""

The following error occurs when at least 1 PO file is missing for a language::

   [parallel2] NLS-PO:I=6
   [parallel2] Exception in thread "main" java.io.IOException: NLS-PO:S=4 323463627 -1948548092
   [parallel2]     at java.lang.Throwable.fillInStackTrace(Throwable.java:79)
   [parallel2]     at java.lang.Throwable.<init>(Throwable.java:30)
   [parallel2]     at java.lang.Exception.<init>(Exception.java:10)
   [parallel2]     at java.io.IOException.<init>(IOException.java:16)
   [parallel2]     at com.microej.nls.BinaryNLS.loadBinFile(BinaryNLS.java:310)
   [parallel2]     at com.microej.nls.BinaryNLS.<init>(BinaryNLS.java:157)
   [parallel2]     at com.microej.nls.BinaryNLS.newBinaryNLS(BinaryNLS.java:118)

Make sure that all PO files are copied in the ``translations`` folder.


Crowdin
^^^^^^^

`Crowdin`_ is a cloud-based localization platform which allows to manage multilingual content.
The NLS External Loader can fetch translations directly from Crowdin to make the translation process even easier.
Translators can then contribute and validate their translations in Crowdin and apply them automatically in the Virtual Device.

A new dependency must be added to Firmware project dependencies to enable this integration:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: java

         implementation("com.microej.tool:nls-po-crowdin:1.0.0")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="com.microej.tool" name="nls-po-crowdin" rev="1.0.0" transitive="false"/>


Once the module has been built, edit the file ``platform/tools/crowdin/crowdin.properties`` to configure the Crowdin connection:

- set ``crowdin.token`` to the Crowdin API token. A token can be generated in the Crowdin in :guilabel:`Settings` > :guilabel:`API` > click on :guilabel:`New Token`.
- set ``crowdin.projectsIds`` to the id of the Crowdin project. The project id can be found in the :guilabel:`Details` section on a project page.
  Multiple projects can be set by separating their id with a comma (for example ``crowdin.projectsIds=12,586,874``).

When the configuration is done, the fetch of the Crowdin translations can be done by executing the script ``crowdin.bat`` or ``crowdin.sh`` located in the folder ``platform/tools/crowdin/``.
The PO files retrieved from Crowdin are automatically pasted in the folder ``translations``,
therefore the new translations are applied after the next Virtual Device restart.

.. _Crowdin: https://repository.microej.com/modules/com/microej/tool/nls-po-crowdin/

..
   | Copyright 2020-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
