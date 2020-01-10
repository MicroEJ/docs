.. _section_imagen_installation:

Installation
============

The Image Generator is an additional module for the MicroUI library.
When the MicroUI module is installed, also install this module in order
to be able to target pre-generated images.

In the platform configuration file, check ``GROUP.UI`` >
``MODULE.IMAGEGENERATOR.PNAME`` to install the Image Generator module.
When checked, the properties file ``MODULE.IMAGEGENERATOR.NAME`` >
``MODULE.IMAGEGENERATOR.NAME.properties`` is required during platform
creation to configure the module, only when the LCD pixel representation
is not standard (see `??? <#display_pixel_structure>`__). This
configuration step is used to identify the extension class name (see
`??? <#section_image_extension>`__).
