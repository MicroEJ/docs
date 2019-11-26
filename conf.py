# MicroEJ

import os
import sys

sys.path.insert(0, os.path.dirname(__file__))

import microej


project = 'MicroEJ Documentation'
copyright = '2019, MicroEJ'
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
    'preamble': r'\usepackage{microej}',
}
latex_additional_files = ['microej.sty']
latex_logo = '_themes/microej/static/mascot-xl.png'

# This is defined in the theme, but the LaTeX builder does not honor the theme
# setting for pygments. This is the same style class used by the HTML builder.
pygments_style = 'microej.MicroEJStyle'
