# Copyright 2008-2022, MicroEJ Corp. Content in this space is free for read and redistribute. Except if otherwise stated, modification is subject to MicroEJ Corp prior approval. 
# MicroEJ is a trademark of MicroEJ Corp. All other trademarks and copyrights are the property of their respective owners.

import os
import sys

sys.path.insert(0, os.path.dirname(__file__))

import microej


project = 'MicroEJ Documentation'
copyright = '2008-2022, MicroEJ Corp. Content in this space is free for read and redistribute. Except if otherwise stated, modification is subject to MicroEJ Corp prior approval. MicroEJ is a trademark of MicroEJ Corp. All other trademarks and copyrights are the property of their respective owners.'
author = 'MicroEJ'
release = '1.0'

# This isn't executed on normal builds, but can be used to build multiple doc
# sets from this common source. See the ``microej.py`` extension for more
# information.
if microej.can_build_independent_docs():
    project_name = microej.get_project_name()
    if project_name:
        project = project_name

extensions = [
    'microej',
    'sphinx.ext.graphviz',
    'sphinx_copybutton',
    'sphinx_tabs.tabs',
]

sphinx_tabs_valid_builders = ['linkcheck']
sphinx_tabs_disable_tab_closing = True

templates_path = ['_templates']
html_theme_path = ['_themes']
master_doc = 'index'
sphinx_tabs_valid_builders = ['linkcheck']

# Generic options
exclude_patterns = [
    '_build',
    '_tools',
    'README.rst',
    'section*.rst',
    '**/section*.rst',
]

# HTML theme options
html_theme = 'microej'
html_logo = '_themes/microej/static/logo-microej-white.png'
html_favicon = '_themes/microej/static/favicon-16x16.png'
html_theme_options = {
    'logo_only': True,
    'collapse_navigation': False,
}
html_show_sphinx = False

# # remove headers permalinks
# html_add_permalinks = ''

# This is required because the version of the Read the Docs Sphinx theme the
# microej theme was forked from does not support the HTML5 writer used by
# default by Sphinx 2+
html4_writer = True

# The default Sphinx HTML title includes the release number and some other
# unwanted bits.
html_title = project

# LaTeX customizations
latex_elements = {
    'preamble': r'\usepackage{microej}',
    'figure_align': 'H',
    'extraclassoptions': 'oneside',
    #'sphinxsetup': 'inlineliteralwraps=true, verbatimwithframe=true',
}
latex_additional_files = ['microej.sty']
latex_logo = '_themes/microej/static/mascot.pdf'

# This is defined in the theme, but the LaTeX builder does not honor the theme
# setting for pygments. This is the same style class used by the HTML builder.
pygments_style = 'microej.MicroEJStyle'

# ignoring Github links with anchors at linkcheck
# linkcheck_ignore = [r'https?:\/\/github\.com\/.+#.+']

# Ignore local index links flagged as broken by linkcheck
# Hopefully temporary solution until https://github.com/sphinx-doc/sphinx/issues/9383 is resolved.
linkcheck_ignore = [r'^((?!:\/\/|#|@).)*$']

linkcheck_timeout = 20

