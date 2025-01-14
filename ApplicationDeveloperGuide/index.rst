.. _application-developer-guide:

Application Developer Guide
===========================

The Application Developer Guide serves as a valuable reference for developing applications on MicroEJ, 
providing essential concepts for MicroEJ application design.

In addition to this document, you can access a number of helpful
resources such as:

- Developer resources at `<https://developer.microej.com/>`_.

- Libraries from the `MicroEJ Central Repository <https://developer.microej.com/central-repository/>`__.

- Application Examples as source code from `MicroEJ Github Repositories <https://github.com/MicroEJ>`__.

- `APIs Javadoc <https://repository.microej.com/javadoc/microej_5.x/apis/>`__.

- :ref:`Training Courses for Application Developers <training_for_application_developers>`.

MicroEJ Applications are developed using standard Integrated Development Environments with :ref:`MICROEJ SDK <sdk_6_user_guide>`. The SDK allows you to
run / debug / deploy Applications on a VEE Port.

Two kinds of applications can be developed: Standalone Applications and Sandboxed Applications.

A :ref:`Standalone Application <standalone_application>` is the main Application that is
directly linked to the C code to produce an Executable. 

.. figure:: images/standalone.png
   :align: center
   :scale: 75%

A :ref:`Sandboxed Application <sandboxed_application>` is an Application that is partially linked, then deployed and executed over a Multi-Sandbox Executable.

.. figure:: images/sandboxed.png
   :align: center
   :scale: 75%


.. toctree::
   :hidden:
   :maxdepth: 2

   runtime
   soar
   buildOutputFiles
   virtualDevice
   classpath
   applicationResources
   standaloneApplication
   sandboxedApplication
   characterEncoding
   limitations
   github
   modulesRepositories
   libraries
   tools

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
