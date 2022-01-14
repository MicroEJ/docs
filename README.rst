MicroEJ Documentation
=====================

This repository holds the official MicroEJ documentation available at https://docs.microej.com/.

Building
--------

First, you will need to install the documentation dependencies locally::

    pip install -r requirements.txt

With dependencies installed, you can build the HTML docs::

    make html

To perform a link check for all links and references::

    make linkcheck

Warning Processing
~~~~~~~~~~~~~~~~~~

Syntax warnings are configured to make the build fail. When building locally, warnings are cached once source files have been read once (even during linkcheck) and thus won't reappear on subsequent builds. 
To get all the warnings locally, clean the `_build` directory (``make clean``) and rebuild the whole documentation (``make html`` , ``make linkcheck``).

Components
----------

MicroEJ Sphinx theme
    The theme includes some CSS overrides to the ``sphinx_rtd_theme`` and
    additional font files. It is located at ``_themes/microej``.

MicroEJ Sphinx extension
    This extension is used to provider a Pygments style class, for defining
    styles used for syntax highlighting, some customizations to Sphinx roles,
    and the helpers used in ``conf.py`` to enable an optional build mode that
    outputs independent HTML/PDF documentation sets. The module is located at
    ``microej.py`` and includes documentation on each of the pieces.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
