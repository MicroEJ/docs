# Copyright 2008-2025, MicroEJ Corp. Content in this space is free for read and redistribute. Except if otherwise stated, modification is subject to MicroEJ Corp prior approval.
# MicroEJ is a trademark of MicroEJ Corp. All other trademarks and copyrights are the property of their respective owners.

import os
import sys

sys.path.insert(0, os.path.dirname(__file__))

import microej


project = 'MicroEJ Documentation'
copyright = '2008-2025, MicroEJ Corp. Content in this space is free for read and redistribute. Except if otherwise stated, modification is subject to MicroEJ Corp prior approval. MicroEJ is a trademark of MicroEJ Corp. All other trademarks and copyrights are the property of their respective owners'
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
    'sphinx_toolbox.collapse',
    'sphinxext.remoteliteralinclude',
    'breathe'
]


# Breathe options for C doxygen documentation integration
# Breathe documentation https://breathe.readthedocs.io/en/latest/index.html
breathe_projects = {'llapi_doxygen': '_llapi_doxygen/xml'}
breathe_default_project = 'llapi_doxygen'


remoteliteralinclude_retry_time = 1.0
remoteliteralinclude_max_retry_time = 180.0

sphinx_tabs_valid_builders = ['linkcheck']
sphinx_tabs_disable_tab_closing = True

templates_path = ['_templates']
html_theme_path = ['_themes']
master_doc = 'index'
sphinx_tabs_valid_builders = ['linkcheck']

html_context = {}
if 'READTHEDOCS' in os.environ:
    html_context['READTHEDOCS'] = True

# Generic options
exclude_patterns = [
    '_build',
    '_tools',
    '_llapi_doxygen',
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
    'sticky_navigation': False
}
html_show_sphinx = False
html_static_path = ['_themes/microej/static', '_static']

# # remove headers permalinks
# html_add_permalinks = ''

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
latex_engine = 'lualatex'

# This is defined in the theme, but the LaTeX builder does not honor the theme
# setting for pygments. This is the same style class used by the HTML builder.
pygments_style = 'microej.MicroEJStyle'

# Have linkcheck ignore all links except those : 
# - starting with a "#" (inner references)
# - containing "microej.com" (main website, docs, developer, repository, forge...)
# - containing "github.com/MicroEJ"
# - containing "nxp.com"
# - containing "facer.io"
linkcheck_ignore = [r'^(?!#|.*microej\.com|.*nxp\.com|.*facer\.io|.*github\.com\/MicroEJ)']

# Keep these legacy linkcheck_ignore patterns for occasional monitoring of external links 
# Ignore some links:
#   - local index links flagged as broken by linkcheck. Hopefully temporary solution
#     until https://github.com/sphinx-doc/sphinx/issues/9383 is resolved.
#   - unstable URLs which make the link check fail, such as www.gnu.org or www.oracle.com
#   - https://forum.segger.com does not provide its CA certificates
#   - https://site.mockito.org DNS failure (2024/02/12)
#linkcheck_ignore = [r'^((?!:\/\/|#|@).)*$|^https://www\.gnu\.org/software/gettext/manual/.*$|^http://localhost.*$|^http://172.17.0.1.*$|^https://www.oracle.com/.*$|^https://forum.segger.com/.*$|^https://site.mockito.org.*$|^https://helpx.adobe.com/illustrator/using/simplify_paths.html$']
# ignoring Github links with anchors at linkcheck
#linkcheck_ignore = [r'https?:\/\/github\.com\/.+#.+']

linkcheck_timeout = 20


def setup(app):
    app.connect("source-read", add_custom_prolog)

def add_custom_prolog(app, docname, source):
    
    # Check if the file is in the desired sub-folder
    if docname.startswith("SDKUserGuide/"):
        sub_folders_count = len(docname.split("/"))     
        sub_folders = ""  
        for i in range(sub_folders_count-1):
            sub_folders = sub_folders+"../"

        custom_include = f".. include:: {sub_folders}sdk5_eol.rst"
        custom_prolog = f"""
{custom_include}
"""
        # Prepend the custom prolog to the source content
        source[0] = custom_prolog + source[0]
        print(f"Added custom prolog for {docname}: '{custom_include}'")