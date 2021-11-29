.. _chapter.microej.nlsExternalLoader:

NLS External Loader
===================

MicroEJ provides Native Language Support in applications as described in the :ref:`section.applicationResources.nls` section.
Languages strings are defined in PO files in the application sources.
While this is convenient during the application development phase since everything is at the same location,
it can be painful in others circumstances.
For example, during the test of the application or the translation phase by non-developer persons, 
it would mean asking the developers to update the sources filesand rebuild the application for each update.

In order to make NLS changes easier and quicker, PO files can be updated directly in a Virtual Device thanks to the NLS External Loader.
PO files can be dropped in a given location in the Virtual Device folders to dynamically replace the language strings embedded in the application.

Installation
------------

To enable the NLS External Loader in your Virtual Device, add the following dependency to the ``module.ivy`` file of your MicroEJ Firmware project:

.. code-block:: xml

   <dependency org="com.microej.tool" name="nls-po-external-loader" rev="2.3.0" transitive="false"/>

Then rebuild your MicroEJ Firmware project to produce the Virtual Device.

Usage
-----

Once the project built:

- unzip the Virtual Device and create a folder named ``translations`` in the root folder.
- copy all the PO files from your project into the ``translations`` folder.
  All PO files found in this folder are processed, no matter their folder level.
- start the Virtual Device with the launcher.
   The following logs should be printed if the NLS External Loader has been executed and has found the PO files::

   externalPoLoaderInit:init:

   externalPoLoaderInit:loadPo:
      [mkdir] Created dir: <PATH>\tmp\microejlaunch1307817858\resourcebuffer
   [po-to-nls] *.nls files found in <PATH>\output\<FIRMWARE>\resourceBuffer :
   [po-to-nls]   - <CLASSPATH>.<CLASSNAME>
   [po-to-nls]   - <CLASSPATH>.<CLASSNAME>
   [po-to-nls] Loading *.po files for NLS interface f<CLASSPATH>.<CLASSNAME>
   [po-to-nls]   => loaded locales : fr_DA,fr_ES,fr_NL,fr_FI,fr_RU,fr_SV,fr_DE,fr_NO,fr_IT,fr_FR,fr_PL,fr_EN
   [po-to-nls] Loading *.po files for NLS interface <CLASSPATH>.<CLASSNAME>
   [po-to-nls]   => loaded locales : fr_DA,fr_ES,fr_NL,fr_FI,fr_RU,fr_SV,fr_DE,fr_NO,fr_IT,fr_FR,fr_PL,fr_EN

- update the languages strings in your PO files of the Virtual Device (the files in the `translations/` folder).
- restart the Virtual Device and check your changes.


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
---------------

java.io.IOException: NLS-PO:S=4
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
-------

Crowdin is a cloud-based localization platform which allows to manage multilingual content.
The NLS External Loader can fetch translations directly from Crowdin to make the translation process even easier.
Translators can then contribute and validate their translations in Crowdin and apply them automatically in the Virtual Device.

A new dependency must be added to the `module.ivy` file of your MicroEJ Firmware project to enable this integration:

.. code-block:: xml

   <dependency org="com.microej.tool" name="nls-po-crowdin" rev="1.0.0" transitive="false"/>

Once the module has been built, edit the file ``platform/tools/crowdin/crowdin.properties`` to configure the Crowdin connection:

- set ``crowdin.token`` to your Crowdin API token. A token can be generated in the Crowdin in :guilabel:`Settings` > :guilabel:`API` > click on :guilabel:`New Token`.
- set ``crowdin.projectsIds`` to the id of your Crowdin project. The project id can be found in the :guilabel:`Details` section on a project page.
  Multiple projects can be set by separating their id with a comma (for example ``crowdin.projectsIds=12,586,874``).

When the configuration is done, the fetch of the Crowdin translations can be done by executing the script ``crowdin.bat`` or ``crowdin.sh`` located in the folder ``platform/tools/crowdin/``.
The PO files retrieved from Crowdin are automatically pasted in the folder ``translations``,
therefore the new translations are applied after the next Virtual Device restart.

..
   | Copyright 2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
