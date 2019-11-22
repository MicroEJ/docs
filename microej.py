from docutils import nodes
from pygments.style import Style
from pygments.token import (
    Comment,
    Error,
    Keyword,
    Literal,
    Generic,
    Operator,
    Name,
    Text,
    Whitespace,
)
from sphinx.util.docutils import ReferenceRole, SphinxRole


class MicroEJStyle(Style):

    """Pygments style for MircoEJ."""

    background_color = "#f8f8f8"
    default_style = ""

    styles = {
        Comment: "italic #48A23F",
        Comment.Hashbang: "italic #48A23F",
        Comment.Multiline: "italic #48A23F",
        Comment.Preproc: "italic #48A23F",
        Comment.PreprocFile: "italic #48A23F",
        Comment.Single: "italic #48A23F",
        Comment.Special: "italic #48A23F",

        Error: "#FF0000 bg:#f8f8f8",

        Keyword: "bold #cf4520",
        Keyword.Constant: "bold #cf4520",
        Keyword.Declaration: "bold #cf4520",
        Keyword.Namespace: "bold #cf4520",
        Keyword.Pseudo: "nobold",
        Keyword.Reserved: "bold #cf4520",
        Keyword.Type: "nobold #B00040",

        Literal: "#666666",
        Literal.Number: "#666666",
        Literal.String: "#ee502e",
        Literal.Number.Bin: "#666666",
        Literal.Number.Float: "#666666",
        Literal.Number.Hex: "#666666",
        Literal.Number.Integer: "#666666",
        Literal.Number.Oct: "#666666",
        Literal.String.Affix: "#ee502e",
        Literal.String.Backtick: "#ee502e",
        Literal.String.Char: "#ee502e",
        Literal.String.Delimiter: "#ee502e",
        Literal.String.Doc: "#ee502e italic",
        Literal.String.Double: "#ee502e",
        Literal.String.Escape: "#BB6622 bold",
        Literal.String.Heredoc: "#ee502e",
        Literal.String.Interpol: "#BB6688 bold",
        Literal.String.Other: "#cf4520",
        Literal.String.Regex: "#BB6688",
        Literal.String.Single: "#ee502e",
        Literal.String.Symbol: "#19177C",
        Literal.Number.Integer.Long: "#666666",

        Operator: "#666666",

        Generic.Deleted: "#A00000",
        Generic.Error: "#FF0000",
        Generic.Emph: "italic",
        Generic.Heading: "bold #000080",
        Generic.Inserted: "#00A000",
        Generic.Output: "#888",
        Generic.Prompt: "bold #008eaa",
        Generic.Strong: "bold",
        Generic.Subheading: "bold #800080",
        Generic.Traceback: "#04D",

        Name.Attribute: "#7D9029",
        Name.Builtin: "#cf4520",
        Name.Class: "#008eaa bold",
        Name.Constant: "#880000",
        Name.Decorator: "#AA22FF",
        Name.Entity: "#999999 bold",
        Name.Exception: "#D2413A bold",
        Name.Function: "#008eaa",
        Name.Label: "#A0A000",
        Name.Namespace: "#008eaa bold",
        Name.Tag: "#cf4520 bold",
        Name.Variable: "#19177C",
        Name.Builtin.Pseudo: "#cf4520",
        Name.Function.Magic: "#008eaa",
        Name.Variable.Class: "#19177C",
        Name.Variable.Global: "#19177C",
        Name.Variable.Instance: "#19177C",
        Name.Variable.Magic: "#19177C",

        Operator.Word: "#AA22FF bold",

        Text.Whitespace: "#bbbbbb",
        Whitespace: "#bbbbbb",
    }


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
