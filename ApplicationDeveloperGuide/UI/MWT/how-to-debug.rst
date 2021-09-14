How to Debug
============

Highlighting the Bounds of the Widgets
--------------------------------------

When designing an UI, it can be pretty convenient to highlight the bounds of each widget.
It helps:

- verifying if the layout fits the expected design,
- setting the outlines (margin, padding, border),
- checking the alignment of the widget content inside its bounds.

Setting the ``ej.mwt.debug.bounds.enabled`` constant to ``true`` will add a rectangle overlay over each widget and container.
(See :ref:`section.classpath.elements.constants` section for more information about constants.)

By default, the rectangles around the widgets are magenta.
But their color can be adjusted by modifying the ``ej.mwt.debug.bounds.color`` constant.

Example of ``xxx.constants.list`` file and the result in an application:

.. code-block::

	ej.mwt.debug.bounds.enabled=true
	ej.mwt.debug.bounds.color=0x00ff00

.. figure:: images/highlightWidgetList.png
	:alt: Highlight widgets in a list
	:align: center
 
.. figure:: images/highlightWidgetWheel.png
	:alt: Highlight widgets in a wheel
	:align: center
 
..
   | Copyright 2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
