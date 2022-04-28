JavaFX Module
============= 

The `JavaFX Module <https://artifactory.cross/microej-cross5-snapshot/com/microej/tool/javafx/>`_ allows the use of JavaFX in the creation of a Mock project or to embed JavaFX in a Platform.
This Module is required when working with a JDK 11, since JavaFX is not embedded anymore in Oracle JDK.

The following OS are supported by the JavaFX Module :

- Linux 64
- Mac Aarch64
- Mac x86_64
- Windows 64

To ensure Mac Aarch64 support, the JavaFX Module is based on JavaFX 17 which requires a JDK 11, so it can not be used with a JDK 1.8.

.. note::

  To use JavaFX with JDK 1.8, it is required to install an Oracle JDK 1.8 which embeds the JavaFX libraries.  


The JavaFX Module is composed of two artifacts which are used depending on your Use case:

- :guilabel:`javafx.jar` which contains all JavaFX libraries and is used within a Mock project.
- :guilabel:`javafx.rip` which embeds the JavaFX libraries in a Platform.


How to use JavaFX Module
------------------------

Use JavaFX in a Mock project
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Add the JavaFX Module to the module.ivy of your Mock project.

::

    <dependency org="com.microej.tool" name="javafx" rev="1.1.0" />

- The :guilabel:`javafx.jar` artifact is now present in your Module dependencies and can be used to develop your Mock Project. 


Embed JavaFX in a Platform
~~~~~~~~~~~~~~~~~~~~~~~~~~

- Add the JavaFX Module to the module.ivy of your Platform configuration project.

::

    <dependency org="com.microej.tool" name="javafx" rev="1.1.0" />

- Build your Platform (see :ref:`how to build a Platform <platform_build>`) 

- In your ready-to-use Platform project, thanks to the :guilabel:`javafx.rip` artifact, the JavaFX libraries have been embedded in :guilabel:`mocks/dropins` folder.


All JavaFX native libraries have been embedded in their corresponding OS directory, in the :guilabel:`resources/os` directory :   

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.