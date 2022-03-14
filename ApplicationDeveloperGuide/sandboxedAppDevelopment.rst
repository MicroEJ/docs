.. _chapter.application.structure:

Sandboxed Application Structure
===============================

.. _section.application.template:

Application Skeleton Creation
-----------------------------

The first step to explore a Sandboxed Application structure is to create
a new project.

First select :guilabel:`File` > :guilabel:`New` >
:guilabel:`Sandboxed Application Project`:

Fill in the application template fields, the :guilabel:`Project name` field will
automatically duplicate in the following fields.

A template project is automatically created and ready to use, this
project already contains all folders wherein developers need to put
content:

``src/main/java``
    Folder for future sources;

``src/main/resources``
    Folder for future resources (images, fonts, etc.);

``META-INF``
    Sandboxed Application configuration and resources;

``module.ivy``
    :ref:`Module description file <mmm_module_description>`, dependencies description for the current project.

.. _section.java.sources.folder:

Sources Folder
--------------

The project source folder (``src/main``) contains two subfolders:
``java`` and ``resources``. ``java`` folder will contain all ``*.java``
files of the project, whereas ``resources`` folder will contain elements
that the application needs at runtime like raw resources, images or
character fonts.

.. _section.metainf:

META-INF Folder
---------------

The ``META-INF`` folder contains several folders and a manifest file.
They are described hereafter.

``certificate`` (folder)
    Contains certificate information used during the application deployment.

``libraries`` (folder)
    Contains a list of additional libraries useful to the application and not
    resolved through the regular transitive dependency check.

``properties`` (folder)
    Contains an ``application.properties`` file which contains application
    specific properties that can be accessed at runtime.

``services`` (folder)
    Contains a list of files that describe local services provided by the
    application. Each file name represents a service class fully qualified name,
    and each file contains the fully qualified name of the provided service
    implementation.

``wpk`` (folder)
    Contains a set of applications (``.wpk`` files) that will be started when
    the application is executed on the Simulator.

``MANIFEST.MF`` (file)
    Contains the information given at project creation, extra information can be
    added to this file to declare the entry points of the application.

.. _section.module.ivy:

``module.ivy`` File
-------------------

The ``module.ivy`` file describes all the libraries required by the
application at runtime. The Ivy classpath container lists all the
modules that have been automatically resolved from the content of
``module.ivy``. See :ref:`mmm` for more
informations about MicroEJ Module Manager.


..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
