Introduction
============

MicroUI Foundation Library provides access to a pixel-based display and inputs.

The aim of this library is to enable the creation of user interface in Java by reifying hardware capabilities.


.. 
   // Add again next line when ESR 3.0 will be available:
   The complete specification is available at :ref:`[MICROUI 3.0] ESR documentation <esr-specifications>`.

To use the MicroUI Foundation Library, add `MicroUI API module <https://repository.microej.com/artifacts/ej/api/microui/>`_ to a :ref:`module description file <mmm_module_description>`:

.. code-block:: XML

	<dependency org="ej.api" name="microui" rev="3.0.0"/>

Drawing Foundation Library extends MicroUI drawing APIs [#note_microui_2]_ with more complex ones such as:

- thick line, arc, circle and ellipse
- polygon
- image deformation and rotation

To use the Drawing Foundation Library, add `Drawing API module <https://repository.microej.com/artifacts/ej/api/microui/>`_ to a :ref:`module description file <mmm_module_description>`:

.. code-block:: XML

	<dependency org="ej.api" name="drawing" rev="1.0.0"/>

.. [#note_microui_2] These APIs were formerly included in MicroUI ``2.x``

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
