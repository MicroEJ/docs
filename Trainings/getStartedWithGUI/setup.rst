Setup your Environment
======================

Prerequisites
-------------

The :ref:`MICROEJ SDK <sdk_install>` must be installed.
Please check the :ref:`MICROEJ SDK requirements <system-requirements>`.

Download and Install
--------------------

#.  Download the installer package corresponding to your host computer OS: `Download MicroEJ SDK <https://repository.microej.com/packages/SDK/>`__.

#.  Unzip the downloaded installer package if needed and execute the installer.


Start the IDE for the First Time
--------------------------------

#. Start MICROEJ SDK and select a workspace. 

   .. note::

      If you are not familiar with Eclipse workspaces, select the default and press OK.
   
#. Select the MICROEJ repository. 

   .. note::

      If you are not familiar with MICROEJ repositories, select the default and press OK.

Prepare VEE Port Sources
------------------------

1. Get the VEE Port sources from GitHub for STM32F7508-DK, open a terminal on your workstation and run the following commands:

  .. code-block:: sh
  
     git clone --recursive https://github.com/MicroEJ/VEEPort-STMicroelectronics-STM32F7508-DK.git
     cd VEEPort-STMicroelectronics-STM32F7508-DK
     git checkout tags/2.2.0

2. Follow the README to import the VEE Port sources, activate your license and build your VEE Port, in the VEE Port Setup section.
3. Once all the steps of the VEE Port setup are done, a new Java project can be created.

Create a New Project
--------------------

Go to :guilabel:`File` > :guilabel:`New` > :guilabel:`Standalone Application Project`:

.. image:: images/createStandaloneProject.png
   :align: center

The project structure should look like this:

.. image:: images/structure.png
   :align: center

Featured Project: Widget Demo
-----------------------------

You can have a look at the widget demo project, which contains multiple samples of widgets and usage.

- `Widget Demo GitHub Repository <https://github.com/MicroEJ/Demo-Widget>`__

.. image:: images/widgetdemo.png
   :align: center

**Next step:** :ref:`ui-starting-microui`

..
   | Copyright 2021-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
