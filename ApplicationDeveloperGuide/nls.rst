.. _chapter.nls:

Native Language Support
=======================

Introduction
------------

Native Language Support (NLS) allows the application to facilitate internationalization.
It provides support to manipulate messages and translate them in different languages.
Each message to be internationalized is referenced by a key, which can be used in the application code instead of using the message directly.

Localization Source Files
-------------------------

Messages must be defined in localization source files, located in the Classpath of the application (i.e. in the ``src/main/resources`` folder).

Localization source files can be either `PO files <https://www.gnu.org/software/gettext/manual/gettext.html#PO-Files>`_ or `Android String resources <https://developer.android.com/guide/topics/resources/string-resource>`_.

Here is an example of a PO file:

::

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

.. note::

   When using Android String resources, `string arrays <https://developer.android.com/guide/topics/resources/string-resource#StringArray>`_ are also supported.
   However, `plurals <https://developer.android.com/guide/topics/resources/string-resource#Plurals>`_ are not supported.

NLS List Files
--------------

Localization source files are declared in :ref:`Classpath<chapter.microej.classpath>` ``*.nls.list`` files (**and** to ``*.externresources.list`` for an external resource, see :ref:`chapter.microej.applicationResources`).

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

The `binary-nls module <https://repository.microej.com/modules/com/microej/library/runtime/binary-nls>`_ must be added to the :ref:`module.ivy <mmm_module_description>` of the Application project.

::

  <dependency org="com.microej.library.runtime" name="binary-nls" rev="2.4.2"/>

This module includes an Add-On Processor which parses the localization source files.
For each interface declared in the NLS list files, all the localization source files whose names start with the interface name are used to generate:

- a Java interface with the given FQN, containing a field for each message of the localization source files
- a NLS binary file containing the translations

So, in the example, the generated interface ``com.mycompany.myapp.Labels`` will gather all the 
translations from files named ``Labels*`` and located in any package of the Classpath.
The names of the localization source files should be suffixed by their locale (for example ``Labels_en_US.po``).

The generation is triggered when building the application or after a change done in any localization source file or ``*.nls.list`` files.
This allows to always have the Java interfaces up-to-date with the translations and to use them immediately.

Once the generation is done, the application can use the Java interfaces to get internationalized 
messages, for example:

.. code-block:: java

   String label = Labels.NLS.getMessage(Labels.Label1);

For the application to know which language to use among those made available and when, you can set it and change it at any point using the `setCurrentLocale(locale)`_ method. If no locale has been set yet when getting a message, the translation for the first locale available in alphabetical order will be used by default. However, you can also pick this locale to default to yourself by adding a `com.microej.binarynls.defaultLocale` property followed by a locale name in a ``.properties.list`` file. 


.. _setCurrentLocale(locale): https://repository.microej.com/javadoc/microej_5.x/apis/ej/nls/NLS.html#getCurrentLocale--


Dealing With Missing Translations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

By default, if a translation is missing for a given ``msgid`` in the PO file or Android String resource for a given language, the message returned by the `ej.nls.NLS.getMessage()`_ method with the locale set to this language will simply be the ``msgid`` itself. However if returning this identifier is not a suitable solution for your application, you might want to set a fallback locale corresponding to a language to print the translation for a message in in case it is not available in the current language.

You can set this fallback locale by specifying a locale name in a ``.nls.list`` file after the name of the interface you want this locale to be the fallback for, separated by a colon ``:``. For example, with the following ``.nls.list`` file, the messages for which a translation is missing in a language in the ``Labels`` and ``Messages`` PO files will be translated to ``en_US`` instead of just returning the ``msgid`` of the message.

.. code-block::

   # Missing translations for Labels and Messages will fall back to en_US
   com.mycompany.myapp.Labels:en_US
   com.mycompany.myapp.Messages:en_US

As such, you can specify a different fallback locale for each interface in a ``.nls.list`` file. For example, with the following ``.nls.list`` file, the messages in ``Labels`` will not have a fallback language set and will only return the ``msgid`` if a translation is missing, while missing translations will default to ``en_US`` for the messages in ``Messages``, and to ``ja_JP`` for the messages in ``Content`` :

.. code-block::

   # Missing translations for Labels will fall back to their msgid
   com.mycompany.myapp.Labels

   # Missing translations for Messages will fall back to en_US
   com.mycompany.myapp.Messages:en_US

   # Missing translations for Content will fall back to ja_JP
   com.mycompany.myapp.Content:ja_JP


.. _ej.nls.NLS.getMessage(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/nls/NLS.html#getMessage-int-

.. _chapter.microej.nlsExternalLoader:

NLS External Loader
-------------------

The NLS External Loader allows to update the PO files of an application executed on a Virtual Device without rebuilding it.
PO files can be dropped in a given location in the Virtual Device folders to dynamically replace the language strings packaged in the application.

This is typically useful when testing or translating an application in order to have a quick feedback when changing the PO files.
Once the PO files are updated, a simple restart of the Virtual Device allows to immediately see the result.

Installation
^^^^^^^^^^^^

To enable the NLS External Loader in the Virtual Device, add the following dependency to the ``module.ivy`` file of the Firmware project:

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

Crowdin is a cloud-based localization platform which allows to manage multilingual content.
The NLS External Loader can fetch translations directly from Crowdin to make the translation process even easier.
Translators can then contribute and validate their translations in Crowdin and apply them automatically in the Virtual Device.

A new dependency must be added to the ``module.ivy`` file of the Firmware project to enable this integration:

.. code-block:: xml

   <dependency org="com.microej.tool" name="nls-po-crowdin" rev="1.0.0" transitive="false"/>

Once the module has been built, edit the file ``platform/tools/crowdin/crowdin.properties`` to configure the Crowdin connection:

- set ``crowdin.token`` to the Crowdin API token. A token can be generated in the Crowdin in :guilabel:`Settings` > :guilabel:`API` > click on :guilabel:`New Token`.
- set ``crowdin.projectsIds`` to the id of the Crowdin project. The project id can be found in the :guilabel:`Details` section on a project page.
  Multiple projects can be set by separating their id with a comma (for example ``crowdin.projectsIds=12,586,874``).

When the configuration is done, the fetch of the Crowdin translations can be done by executing the script ``crowdin.bat`` or ``crowdin.sh`` located in the folder ``platform/tools/crowdin/``.
The PO files retrieved from Crowdin are automatically pasted in the folder ``translations``,
therefore the new translations are applied after the next Virtual Device restart.

..
   | Copyright 2020-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
