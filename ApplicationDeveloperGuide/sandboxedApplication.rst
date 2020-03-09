=====================
Sandboxed Application
=====================

.. _section.application.publication:

Workspaces and Virtual Devices Repositories
===========================================

When starting MicroEJ Studio, it prompts you to select the last used
workspace or a default workspace on the first run. A workspace is a main
folder where to find a set of projects containing source code.

When loading a new workspace, MicroEJ Studio prompts for the location of
the MicroEJ repository, where the Virtual Devices will be imported. By
default, MicroEJ Studio suggests to point to the default MicroEJ
repository on your operating system, located at
``${user.home}/.microej/repositories/[version]``. You can select an
alternative location. Another common practice is to define a local
repository relative to the workspace, so that the workspace is
self-contained, without external file system links and can be shared
within a zip file.

Application Development
=======================

The following sections of this document shall prove useful as a
reference when developing applications for MicroEJ. They cover concepts
essential to MicroEJ applications design.

In addition to these sections, by going to
:http:`https://developer.microej.com/`, you can access a number of helpful
resources such as:

-  Libraries from the MicroEJ Central Repository
   (:http:`https://repository.microej.com/`);

-  Application Examples as source code from MicroEJ Github Repositories
   (:http:`https://github.com/MicroEJ`);

-  Documentation (HOWTOs, Reference Manuals, APIs javadoc...).

.. _chapter.application.structure:

Sandboxed Application Structure
===============================

.. _section.application.template:

Application Skeleton Creation
-----------------------------

The first step to explore a Sandboxed Application structure is to create
a new project.

First select :guilabel:`File` > :guilabel:`New` >
:guilabel:`MicroEJ Sandboxed Application Project`:

Fill in the application template fields, the :guilabel:`Project name` field will
automatically duplicate in the following fields.

A template project is automatically created and ready to use, this
project already contains all folders wherein developers need to put
content:

``src/main/java``
    Folder for future sources;

``src/main/resources``
    Folder for future resources (images, fonts etc.);

``META-INF``
    Sandboxed Application configuration and resources;

``module.ivy``
    Ivy input file, dependencies description for the current project.

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
``module.ivy``. See :ref:`section.ivy.dependency.manager` for more
informations about MicroEJ Module Manager.

Application Publication
=======================

.. _section.build.wadapps.package:

Build the WPK
-------------

When the application is ready for deployment, the last step in MicroEJ
Studio is to create the WPK (Wadapps PacKage) file that is intended to
be published on a MicroEJ Forge instance for end users.

In MicroEJ Studio, right-click on the Sandboxed Application project name
and select ``Build Module``.

The WPK build process will display messages in MicroEJ console, ending
up the following message:

::

    [echo] project hello published locally with version 0.1.0-RC201907091602

    BUILD SUCCESSFUL

    Total time: 1 minute 6 seconds


.. _section.publish.on.a.microej.store:

Publish on a MicroEJ Forge Instance
-----------------------------------

The WPK file produced by the build process is located in a dedicated
``target~/artifacts`` folder in the project.

The ``.wpk`` file is ready to be uploaded to a MicroEJ Forge instance.
Please consult :http:`https://community.microej.com` for more information.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
