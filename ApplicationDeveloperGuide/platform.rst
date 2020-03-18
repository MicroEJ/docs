.. _download.hardware.simulator:

Download and Install a MicroEJ Platform
=======================================

MicroEJ SDK being a cross development tool, it does not build software
targeted to your host desktop platform. In order to run MicroEJ
Applications, a target hardware is required. Several commercial targets
boards from main MCU/MPU chip manufacturers can be prepared to run
MicroEJ Applications, you can also run your applications without one of
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

   .. figure:: images/platformImport.png
      :alt: MicroEJ Platform Import
      :align: center
      :width: 797px
      :height: 468px

      MicroEJ Platform Import

-  Press :guilabel:`Import...` button.

-  Choose :guilabel:`Select File...` and use the :guilabel:`Browse` option
   to navigate to the ``.jpf`` file containing your MicroEJ Platform, 
   then read and accept the license agreement to proceed.

   .. figure:: images/platformSelect.png
      :alt: MicroEJ Platform Selection
      :align: center
      :width: 569px
      :height: 636px

      MicroEJ Platform Selection

-  The MicroEJ Platform should now appear in the :guilabel:`Platforms` view,
   with a green valid mark.

   .. figure:: images/platformList.png
      :alt: MicroEJ Platform List
      :align: center
      :width: 797px
      :height: 468px

      MicroEJ Platform List

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
