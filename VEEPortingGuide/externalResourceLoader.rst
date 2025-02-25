.. _section_externalresourceloader:

=========================
External Resources Loader
=========================


Functional Description
======================

The External Resources Loader is an optional module. When not installed,
only :ref:`internal resources<chapter.microej.applicationResources>` are available for the MicroEJ Application. When
the External Resources Loader is installed, the MicroEJ Core Engine
tries first to retrieve the expected resource from its available list of
internal resources, before asking the BSP to load it (using
``LLEXT_RES_impl.h`` functions).

See :ref:`chapter.microej.applicationResources` for more information on how to declare external resources depending on its kind (raw resources, images, fonts, NLS).


Implementations
===============

External Resources Loader module provides some Low Level API (LLEXT_RES)
to let the BSP manage the external resources.

Open a Resource
---------------

The LLAPI to implement in the BSP are listed in the header file
``LLEXT_RES_impl.h``. First, the framework tries to open an external
resource using the ``open`` function. This function receives the
resources path as a parameter. This path is the absolute path of the
resource from the MicroEJ Application classpath (the MicroEJ Application
source base directory). For example, when the resource is located here:
``com.mycompany.myapplication.resource.MyResource.txt``, the given path
is: ``com/mycompany/myapplication/resource/MyResource.txt``.

The external resources loader implementation should, when possible,
lock the resource when it is opened. Any modification of an opened
resource may not be properly handled by the application.

Resource Identifier
-------------------

This ``open`` function has to return a unique ID (positive value) for
the external resource, or returns an error code (negative value). This
ID will be used by the framework to manipulate the resource (read, seek,
close, etc.).

Several resources can be opened at the same time. The BSP does not have
to return the same identifier for two resources living at the same time.
However, it can return this ID for a new resource as soon as the old
resource is closed.

Resource Offset
---------------

The BSP must hold an offset for each opened resource. This offset must
be updated after each call to ``read`` and ``seek``.

Resource Inside the CPU Address Space Range
-------------------------------------------

An external resource can be programmed inside the CPU address space
range. This memory (or a part of memory) is not managed by the SOAR and
so the resources inside are considered as external.

Most of time the content of an external resource must be copied in a
memory inside the CPU address space range in order to be accessible by
the MicroEJ algorithms (draw an image etc.). However, when the resource
is already inside the CPU address space range, this copy is useless. The
function ``LLEXT_RES_getBaseAddress`` must return a valid CPU memory
address in order to avoid this copy. The MicroEJ algorithms are able to
target the external resource bytes without using the other ``LLEXT_RES``
APIs such as ``read``, ``mark`` etc.


.. _external_resources_folder:

External Resources Folder
=========================

When working with :ref:`chapter.microej.applicationResources` declared as external resources, the Application build process will
output those external resources in a dedicated output folder named ``externalResources/``.

This folder gathers all the :ref:`chapter.microej.applicationResources` that should be deployed on the device.
This folder not only contains the pre-processed resources but also all the other external resources from the project that are not pre-processed:

- Pre-processed resources: resources formatted by MICROEJ SDK to optimize footprint and/or parsing/processing. 
  That is for example the case of :ref:`MicroUI Fonts <section.ui.Fonts>`, :ref:`NLS Resources <chapter.nls>` and :ref:`MicroUI Images embedded in RAW format <section.ui.Images>`.
- Unprocessed resources: resources embedded as-is, like :ref:`Raw Resources <section.classpath.elements.raw_resources>` or 
  :ref:`section.ui.Images` with no output format defined (e.g. image embedded as a ``.png``).

The location of the ``externalResources/`` folder is different between SDK 5 and SDK 6:

.. tabs::

   .. tab:: SDK 6

      The ``externalResources/`` folder is located in the ``build/application/object`` folder of the application project.

      It is generated when building the application for the device (:ref:`sdk6_module_natures.tasks.buildApplicationObjectFile`).

   .. tab:: SDK 5

      The ``externalResources/`` folder is located in the output folder of the application project.
      This folder is defined in the ``Execution`` tab of the :ref:`concepts-microejlaunches` configuration
      (e.g. ``Example-ExternalResourceLoader/com.microej.externalresourceloader.ExternalImages/externalResources``).

Dependencies
============

-  ``LLEXT_RES_impl.h`` implementation (see
   :ref:`LLEXT_RES-API-SECTION`).


Installation
============

The External Resources Loader is an additional module. 
The installation process is different in SDK 5 and SDK 6:

.. tabs::

   .. tab:: SDK 6

      In the VEE Port configuration file, add the following property::

         com.microej.runtime.externalresourceloader.enabled=true

   .. tab:: SDK 5      

      In the VEE Port configuration file, check :guilabel:`External Resources Loader` to install this module.


Use
===

The External Resources Loader is automatically used when the MicroEJ
Application tries to open an external resource.

A simple implementation of the External Resources Loader is available on GitHub:
`Example-ExternalResourceLoader <https://github.com/MicroEJ/Example-ExternalResourceLoader>`_.

Simulation
----------

The :ref:`chapter.microej.applicationResources` provided by the application project, 
pre-processed and/or unprocessed, are automatically 
made available to the application during the simulation.

On Device 
---------

The external resources must be deployed on the device before they can be consumed by the application.

After that, the external resources can be updated (without re-building the application) with the following development flow:

1. Update the external resources in the application project.
2. Test the application with the updated resources on the simulator.
3. When good, re-build the application, and collect the external resources in the output folder (the build is required to trigger the processing of the resources).
4. Deploy the external resources on the device (e.g. copy them to the file system of the device: removable SD card, USB mass storage, ...).

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
