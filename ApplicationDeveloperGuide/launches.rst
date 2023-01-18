.. _concepts-microejlaunches:

MicroEJ Launch
==============

The MicroEJ launch configuration sets up the 
:ref:`MicroEJ Applications <concepts-microejapplications>` environment (main class, target, and Application options), and then
launches a script for execution.

Execution is done either on the Simulator or on the Device. In this latter case, it may depend on
external tools such as target memory programming. 

Main Tab
--------

The :guilabel:`Main` tab allows you to set in order:

1. The main project of the application.

2. The main class of the application containing the main method.

3. Types required in your application that are not statically embedded
   from the main class entry point. Most required types are those that
   may be loaded dynamically by the application, using the
   `Class.forName()`_ method.

4. Binary resources that need to be embedded by the application. These
   are usually loaded by the application using the
   `Class.getResourceAsStream()`_ method.

5. Immutable objects' description files. See the :ref:`[BON 1.2] ESR
   documentation <runtime_bon>` for use of immutable objects.

.. figure:: images/mainTab.png
   :alt: MicroEJ Launch Application Main Tab
   :align: center
   :width: 800px
   :height: 640px

   MicroEJ Launch Application Main Tab

.. _Class.forName(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#forName-java.lang.String-
.. _Class.getResourceAsStream(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#getResourceAsStream-java.lang.String-

.. _launch_execution_tab:

Execution Tab
-------------

The next tab is the :guilabel:`Execution` tab. Here the target needs to be
selected. Choose between execution on a MicroEJ Platform or on a MicroEJ
Simulator. Each of them may provide multiple launch settings. This page
also allows you to keep generated, intermediate files and to print
verbose options (advanced debug purpose options).

.. figure:: images/executionTab.png
   :alt: MicroEJ Launch Application Execution Tab
   :align: center
   :width: 823px
   :height: 706px

   MicroEJ Launch Application Execution Tab

Configuration Tab
-----------------

The next tab is the :guilabel:`Configuration` tab. This tab shows the available
:ref:`Application options <application_options>`.

.. figure:: images/configurationTab.png
   :alt: Configuration Tab
   :align: center
   :width: 800px
   :height: 640px

   Configuration Tab

.. _launch_jre_tab:

JRE Tab
-------

The next tab is the :guilabel:`JRE` tab. This tab allows you to configure the
Java Runtime Environment used for running the underlying launch script.
It does not configure the MicroEJ Application execution. The
``VM Arguments`` text field allows you to set vm-specific options, which
are typically used to increase memory spaces:

-  To modify heap space to 1024MB, set the ``-Xmx1024M`` option.

-  To modify string space (also called PermGen space) to 256MB, set the
   ``-XX:PermSize=256M -XX:MaxPermSize=256M`` options.

-  To set thread stack space to 512MB, set the ``-Xss512M`` option.

-  To set an :ref:`advanced Application option <define_option_in_launcher>`, declare a system property with the following pattern ``-D[OPTION_KEY]>=[OPTION_VALUE]``
  
   .. figure:: images/jreTab.png
      :align: center
      :scale: 100%

.. _launch_source_tab:

Source Tab
----------

The next tab is the :guilabel:`Source` tab.
By default, it is automatically configured to connect your Add-On Libraries sources dependencies.
To connect your Platform Foundation Library sources, please refer to the section :ref:`foundation_library_sources`.


Common Tab
----------

The last tab is the :guilabel:`Common` tab. This is a default Eclipse tab that allows to configure your launch.
Particularly, you can configure the :ref:`console encoding <set_console_encoding>`.
Refer to Eclipse help for more details on other available options.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
