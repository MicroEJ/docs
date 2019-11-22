from docutils import nodes
from sphinx.util.docutils import ReferenceRole, SphinxRole


LATEX_FONTPKG = r'''
\setmainfont{DejaVu Serif}
\setsansfont{DejaVu Sans}
\setmonofont{DejaVu Sans Mono}
'''


class HttpCodeRef(ReferenceRole):

    """A custom role to format external links as code/literals"""

    def run(self):
        reference = nodes.reference('', '', internal=False, refuri=self.target)

        if self.has_explicit_title:
            reference += nodes.literal(self.title, self.title)
        else:
            reference += nodes.literal(self.target, self.target)

        return [reference], []


def setup(app):
    from docutils.parsers.rst import roles

    roles.register_local_role('http', HttpCodeRef())

    return {
        'version': '1.0.0',
        'parallel_read_safe': True,
        'parallel_write_safe': True,
    }
