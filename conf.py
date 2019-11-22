# MicroEJ

import os
import sys

sys.path.insert(0, os.path.dirname(__file__))

import microej


project = 'MicroEJ'
copyright = '2019, MicroEJ'
author = 'MicroEJ'
release = '1.0'

extensions = [
    'microej',
]

templates_path = ['_templates']
html_theme_path = ['_themes']
master_doc = 'index'

# Generic options
exclude_patterns = [
    '_build',
    'README.rst',
    'section*.rst',
    '**/section*.rst',
]

# HTML theme options
html_theme = 'microej'
html_logo = '_themes/microej/static/logo-microej-white.png'
html_theme_options = {
    'logo_only': True,
}
html_show_sphinx = False

# This is required because the version of the Read the Docs Sphinx theme the
# microej theme was forked from does not support the HTML5 writer used by
# default by Sphinx 2+
html4_writer = True

# LaTeX customizations
latex_elements = {
    'fontpkg': microej.LATEX_FONTPKG
}


def setup(app):
    # Because there are multiple, interconnected docsets in these sources,
    # there will be a number of errors about duplicate section labels, and
    # links will not resolve as expected. This allows for multiple, independent
    # projects in the same doc source.
    # TODO if/when this project is restructured as a single document, without
    # included sections between the docs, this likely won't be need.
    docset = os.environ.get('MICROEJ_DOCSET', None)
    if docset:
        app.srcdir += '/' + docset
