# MicroEJ

project = 'MicroEJ'
copyright = '2019, MicroEJ'
author = 'MicroEJ'
release = '1.0'

extensions = [
]

templates_path = ['_templates']
html_static_path = ['_static']
html_theme_path = ['_themes']

# Generic options
exclude_patterns = [
    '_build',
    'README.rst',
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
