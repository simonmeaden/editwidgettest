# def qdump__MapNode(d, value):
#    d.putValue("This is the value column contents")
#    d.putExpandable()
#    if d.isExpanded():
#        with Children(d):
#            # Compact simple case.
#            d.putSubItem("key", value["key"])
#            # Same effect, with more customization possibilities.
#            with SubItem(d, "data")
#                d.putItem("data", value["data"])

from dumper import Children, SubItem, UnnamedSubItem, DumperBase
from utils import DisplayFormat, TypeCode


def qdump__QYamlParser__Directive(d, value):
    start = value["start"].integer()
    major = value["m_majorVersion"].integer()
    minor = value["m_minorVersion"].integer()
    d.putValue("[%d, %d, %d]" % (start, major, minor))
    d.putExpandable()
    if d.isExpanded():
        with Children(d):
            d.putSubItem("start", start)
            d.putSubItem("length", value["length"])
            d.putSubItem("major", major)
            d.putSubItem("minor", minor)
            d.putSubItem("text", value["text"])


def qdump__QYamlDocument(d, value):
    major = value["m_majorVersion"].integer()
    minor = value["m_minorVersion"].integer()
    d.putValue("[%d.%d]" % (major, minor))
    d.putExpandable()
    if d.isExpanded():
        with Children(d):
            d.putSubItem("major", major)
            d.putSubItem("minor", minor)


def qdump__YamlNode(d, value):
    indent = value["m_indent"].integer()
    row = value["m_row"].integer()
    column = value["m_column"].integer()
    length = value["m_length"].integer()
    d.putValue("[i=%d, r=%d, c=%d, l=%d]" % (indent, row, column, length))
    d.putExpandable()
    if d.isExpanded():
        with Children(d):
            d.putSubItem("indent", value["m_indent"])
            d.putSubItem("row", value["m_row"])
            d.putSubItem("column", value["m_column"])
            d.putSubItem("length", value["m_length"])
