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
