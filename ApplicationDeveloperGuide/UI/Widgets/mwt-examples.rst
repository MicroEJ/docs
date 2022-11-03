.. include:: aliases.rst

MWT Examples
============

The `MWT Examples <https://github.com/MicroEJ/ExampleJava-MWT>`_ are code samples that show how to implement various use cases with MWT.

Because the MWT toolkit is designed to be compact and customizable, it allows for many possibilities when developing a GUI.
Thus, the examples can be used, with or without modifications, to extend and customize the MWT framework for your specific needs.
They also help to learn the best practices for the development of graphic interfaces with MWT.

Source
------

To get the source code of these examples, clone the following GitHub repository: `<https://github.com/MicroEJ/ExampleJava-MWT>`_.

The repository contains several projects (one project for each example).
You can import the projects in MicroEJ SDK to browse the source code and run the examples.

* Go to :guilabel:`File` > :guilabel:`Import...`.
* In :guilabel:`General`, select :guilabel:`Existing Projects into Workspace`.
* Check :guilabel:`Select root directory` and browse to the cloned MWT Examples repository.
* Select the projects to import and click :guilabel:`Finish`.

For each project, please refer to its ``README.md`` file for more details about the example and its usage.


Run the Examples
----------------

Make sure to have a valid Platform in the workspace.
The examples can be tested with the Platform `STM32F7508-DK <https://github.com/MicroEJ/Platform-STMicroelectronics-STM32F7508-DK/tree/1.5.0>`_.

To run the examples in a Virtual Device:

* Right-click on a project.
* Select :guilabel:`Run As` > :guilabel:`MicroEJ Application`.

.. note::

   Some of the examples may require extra configuration, please refer to their README for more details.


To run the examples on a device, :ref:`adapt the Run Configuration <device_build>`, then refer to the Platform documentation.


Provided Examples
-----------------

`Attribute Selectors <https://github.com/MicroEJ/ExampleJava-MWT/tree/master/attribute-selectors>`_
~~~~~~~~~~~~~~~~~~~

|startTable| 

.. image:: images/attribute-selectors.gif
   :align: center

|midTable|
   
This example shows how to customize the style of widgets using attribute selectors, similar to CSS Attribute Selectors.
It provides several types of attribute selectors, any of which can be used in a stylesheet to select widgets based on custom attributes.
In this case, the background color of a label switches depending on the value of an attribute of the label.

|endTable|

`Buffered Image Pool <https://github.com/MicroEJ/ExampleJava-MWT/tree/master/buffered-image-pool>`_
~~~~~~~~~~~~~~~~~~~

|startTable| 

.. image:: images/buffered-image-pool.gif
   :align: center

|midTable|
   
This example shows how to use a pool of `BufferedImages <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/BufferedImage.html>`_ to share them across an application.
In this demo, there is one image in the pool, which is shared between the histogram widget and the transition container.

|endTable|

`Context-Sensitive Container <https://github.com/MicroEJ/ExampleJava-MWT/tree/master/context-sensitive-container>`_
~~~~~~~~~~~~~~~~~~~

|startTable| 

.. image:: images/context-sensitive-container.gif
   :align: center

|midTable|
   
This example shows a smartwatch application that looks different depending on whether the user is wearing the device on the left arm or on the right arm.
It demonstrates how a container can adapt to the context by changing how its children are laid out: in this case, depending on the wrist mode, 
the widgets are displayed on either the left or right side. 
For demonstration purposes, the example displays a virtual watch to simulate the device flip.

|endTable|

`Drag'n'Drop <https://github.com/MicroEJ/ExampleJava-MWT/tree/master/drag-and-drop>`_
~~~~~~~~~~~~~~~~~~~

|startTable| 

.. image:: images/drag-and-drop.gif
   :align: center

|midTable|
   
This example shows an example of drag'n'drop in a grid.

|endTable|

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
