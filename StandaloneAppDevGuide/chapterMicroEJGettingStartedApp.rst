Build and Run an Application
============================

.. _microej.sample.applications:

Create a MicroEJ Standalone Application
---------------------------------------

-  Create a project in your workspace. Select :guilabel:`File` > :guilabel:`New` >
   :guilabel:`MicroEJ Standalone Application Project`.

   .. figure:: png/newApp1.png
      :alt: New MicroEJ Standalone Application Project
      :align: center
      :width: 719px
      :height: 174px

      New MicroEJ Standalone Application Project

-  Fill in the application template fields, the Project name field will
   automatically duplicate in the following fields. Click on :guilabel:`Finish`.
   A template project is automatically created and ready to use, this
   project already contains all folders wherein developers need to put
   content:

   -  ``src/main/java``: Folder for future sources

   -  ``src/main/resources``: Folder for future resources (images, fonts
      etc.)

   -  ``META-INF``: Sandboxed Application configuration and resources

   -  ``module.ivy``: Ivy input file, dependencies description for the
      current project

-  Right click on the source folder ``src/main/java`` and select
   :guilabel:`New` > :guilabel:`Package`. Give a name: ``com.mycompany``.
   Click on :guilabel:`Finish`.

   .. figure:: png/newApp8.png
      :alt: New Package
      :align: center
      :width: 525px
      :height: 326px

      New Package

-  The package ``com.mycompany`` is available under ``src/main/java`` folder.
   Right click on this package and select :guilabel:`New` > :guilabel:`Class`.
   Give a name: ``Test`` and check the box ``public static void main(String[]
   args)``. Click on :guilabel:`Finish`.

   .. figure:: png/newApp9.png
      :alt: New Class
      :align: center
      :width: 542px
      :height: 634px

      New Class

-  The new class has been created with an empty ``main()`` method. Fill
   the method body with the following lines:

   ::

      System.out.println("hello world!");


   .. figure:: png/newApp10.png
      :alt: MicroEJ Application Content
      :align: center
      :width: 438px
      :height: 192px

      MicroEJ Application Content

   The test application is now ready to be executed. See next sections.

.. _section.run.on.simulator:

Run on the Simulator
--------------------

To run the sample project on Simulator, select it in the left panel then right-click
and select :guilabel:`Run` > :guilabel:`Run as` > :guilabel:`MicroEJ Application`.

.. figure:: png/sim1.png
   :alt: MicroEJ Development Tools Overview
   :align: center
   :width: 698px
   :height: 552px

   MicroEJ Development Tools Overview

MicroEJ SDK console will display Launch steps messages.

::

    =============== [ Initialization Stage ] ===============
    =============== [ Launching on Simulator ] ===============
    hello world!
    =============== [ Completed Successfully ] ===============

    SUCCESS


.. _section.run.on.emb:

Run on the Hardware Device
--------------------------

Compile an application, connect the hardware device and deploy on it is
hardware dependant. These steps are described in dedicated documentation
available inside the MicroEJ Platform. This documentation is accessible
from the MicroEJ Resources Center view.

.. note::

   MicroEJ Resources Center view may have been closed. Click on
   :guilabel:`Help` > :guilabel:`MicroEJ Resources Center` to reopen it.

Open the menu :guilabel:`Manual` and select the documentation
``[hardware device] MicroEJ Platform``, where ``[hardware device]`` is
the name of the hardware device. This documentation features a guide to
run a built-in application on MicroEJ Simulator and on hardware device.

.. figure:: png/emb1.png
   :alt: MicroEJ Platform Guide
   :align: center
   :width: 301px
   :height: 133px

   MicroEJ Platform Guide

Application Development
=======================

The following sections of this document shall prove useful as a
reference when developing applications for MicroEJ. They cover concepts
essential to MicroEJ applications design.

In addition to these sections, by going to
:http:`https://developer.microej.com/`, you can access a number of helpful
resources such as:

-  Libraries from the MicroEJ Central Repository
   (:http:`https://repository.microej.com/`)

-  Application Examples as source code from MicroEJ Github Repositories
   (:http:`https://github.com/MicroEJ`)

-  Documentation (HOWTOs, Reference Manuals, APIs javadoc...)

