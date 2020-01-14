# MicroEJ

import os
import sys

sys.path.insert(0, os.path.dirname(__file__))

import microej


project = 'MicroEJ Documentation'
copyright = '2019, MicroEJ Corp.'
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
    '_tools',
    'README.rst',
    'section*.rst',
    '**/section*.rst',
]

# HTML theme options
html_theme = 'microej'
html_logo = '_themes/microej/static/logo-microej-white.png'
html_favicon = '_themes/microej/static/logo-small.png'
html_theme_options = {
    'logo_only': True,
    'collapse_navigation': False,
}
html_show_sphinx = False

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
}
latex_additional_files = ['microej.sty']
latex_logo = '_themes/microej/static/mascot.pdf'

# This is defined in the theme, but the LaTeX builder does not honor the theme
# setting for pygments. This is the same style class used by the HTML builder.
pygments_style = 'microej.MicroEJStyle'
