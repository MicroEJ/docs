.. _download.hardware.simulator:

Download and Install a MicroEJ Platform
=======================================

MicroEJ SDK being a cross development tool, it does not build software
targeted to your host desktop platform. In order to run MicroEJ
applications, a target hardware is required. Several commercial targets
boards from main MCU/MPU chip manufacturers can be prepared to run
MicroEJ applications, you can also run your applications without one of
these boards with the help of a MicroEJ Simulator.

A MicroEJ Platform is a software package including the resources and
tools required for building and testing an application for a specific
MicroEJ-ready device. MicroEJ Platforms are available at
:http:`https://developer.microej.com/5/getting-started-sdk.html`.

After downloading the MicroEJ Platform, launch MicroEJ SDK on your
desktop to start the process of Platform installation :

-  Open the Platform view in MicroEJ SDK, select :guilabel:`Window` >
   :guilabel:`Preferences` > :guilabel:`MicroEJ` > :guilabel:`Platforms`. The
   view should be empty on a fresh install of the tool

   .. figure:: png/platformImport.png
      :alt: MicroEJ Platform Import
      :align: center

      MicroEJ Platform Import

-  Press :guilabel:`Import...` button.

-  Choose :guilabel:`Select File...` and use the :guilabel:`Browse` option
   to navigate to the ``.jpf`` file containing your MicroEJ Platform, 
   then read and accept the license agreement to proceed.

   .. figure:: png/platformSelect.png
      :alt: MicroEJ Platform Selection
      :align: center

      MicroEJ Platform Selection

-  The MicroEJ Platform should now appear in the :guilabel:`Platforms` view,
   with a green valid mark.

   .. figure:: png/platformList.png
      :alt: MicroEJ Platform List
      :align: center

      MicroEJ Platform List
