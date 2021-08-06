Setup Your Environment
======================

Prerequisites
-------------

- Supported Operating System: MICROEJ SDK runs on the following operating systems: Windows (7, 8, 8.1, 10), Linux, macOS.
- A Java™ Runtime Environment 8 is needed on your host computer for running MICROEJ SDK Dist. 21.03: `Download Java <https://www.java.com/en/download/manual.jsp>`__.

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

Prepare Platform Sources
------------------------

#. Download and unzip the platform sources for STM32F7508-DK by clicking on :guilabel:`Download` > :guilabel:`Download ZIP`: 
   `Go to the Github repository <https://github.com/MicroEJ/Platform-STMicroelectronics-STM32F7508-DK/tree/1.3.2>`__.
#. Follow the README to import the platform sources, activate your license and build your platform: `STM32F7508-DK Platform Setup <https://github.com/MicroEJ/Platform-STMicroelectronics-STM32F7508-DK/tree/1.3.2#platform-setup>`_
#. Once all the steps of the platform setup are done, a new Java project can be created.

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



