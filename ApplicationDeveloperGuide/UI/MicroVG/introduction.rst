.. include:: aliases.rst

Introduction
============

MicroVG Foundation Library provides vector drawing capabilities.

To use the MicroVG Foundation Library, add `MicroVG API module <zzz_repourl_zzz/ej/api/microvg/>`_ to a :ref:`module description file <mmm_module_description>`:

.. code-block:: XML

	<dependency org="ej.api" name="microvg" rev="1.0.0"/>

The MicroVG Library brings the following features:

- the creation and drawing of paths with color or linear gradient.
- the drawing of texts using vector fonts with color or linear gradient.
- the drawing of vector images.
- the transformation of paths, texts, images with affine transformation matrices.


.. note::
   The MicroVG library natives use different drawing engines, font rendering and layout engines for embedded and simulator implementations. 

   This can lead to some slightly drawing differences, like for instance in the antialiasing processing of font glyphs.

   
..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.