Tags Specification
==================

Here is the complete syntactical and semantical description of all
available tags of the ``.lsc`` file.

.. table:: Linker Specific Configuration Tags

   +-----------+-----------+-----------------------------------------------+
   | Tags      | A         | Description                                   |
   |           | ttributes |                                               |
   +===========+===========+===============================================+
   | ``def     |           | Defines a new section. A floating section     |
   | Section`` |           | only holds a declared ``size`` attribute. A   |
   |           |           | fixed section declares at least one of the    |
   |           |           | ``start`` / ``end`` attributes. When this tag |
   |           |           | is empty, the section is a runtime section,   |
   |           |           | and must define at least one of the           |
   |           |           | ``start``, ``end`` or ``size`` attributes.    |
   |           |           | When this tag is not empty (when it holds a   |
   |           |           | binary description), the section is an image  |
   |           |           | section.                                      |
   +-----------+-----------+-----------------------------------------------+
   | ``name``  | Name of   |                                               |
   |           | the       |                                               |
   |           | section.  |                                               |
   |           | The       |                                               |
   |           | section   |                                               |
   |           | name may  |                                               |
   |           | not be    |                                               |
   |           | unique.   |                                               |
   |           | However,  |                                               |
   |           | it is     |                                               |
   |           | re        |                                               |
   |           | commended |                                               |
   |           | that you  |                                               |
   |           | define a  |                                               |
   |           | unique    |                                               |
   |           | name if   |                                               |
   |           | the       |                                               |
   |           | section   |                                               |
   |           | must be   |                                               |
   |           | referred  |                                               |
   |           | s         |                                               |
   |           | eparately |                                               |
   |           | for       |                                               |
   |           | memory    |                                               |
   |           | pos       |                                               |
   |           | itioning. |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``start`` | Optional. |                                               |
   |           | E         |                                               |
   |           | xpression |                                               |
   |           | defining  |                                               |
   |           | the       |                                               |
   |           | absolute  |                                               |
   |           | start     |                                               |
   |           | address   |                                               |
   |           | of the    |                                               |
   |           | section.  |                                               |
   |           | Must be   |                                               |
   |           | resolved  |                                               |
   |           | to a      |                                               |
   |           | constant  |                                               |
   |           | after the |                                               |
   |           | full load |                                               |
   |           | of the    |                                               |
   |           | lsc file. |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``end``   | Optional. |                                               |
   |           | E         |                                               |
   |           | xpression |                                               |
   |           | defining  |                                               |
   |           | the       |                                               |
   |           | absolute  |                                               |
   |           | end       |                                               |
   |           | address   |                                               |
   |           | of the    |                                               |
   |           | section.  |                                               |
   |           | Must be   |                                               |
   |           | resolved  |                                               |
   |           | to a      |                                               |
   |           | constant  |                                               |
   |           | after the |                                               |
   |           | full load |                                               |
   |           | of the    |                                               |
   |           | lsc file. |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``size``  | Optional. |                                               |
   |           | E         |                                               |
   |           | xpression |                                               |
   |           | defining  |                                               |
   |           | the size  |                                               |
   |           | in bytes  |                                               |
   |           | of the    |                                               |
   |           | section.  |                                               |
   |           | I         |                                               |
   |           | nvariant: |                                               |
   |           | ``(en     |                                               |
   |           | d-start)+ |                                               |
   |           | 1=size``. |                                               |
   |           | Must be   |                                               |
   |           | resolved  |                                               |
   |           | to a      |                                               |
   |           | constant  |                                               |
   |           | after the |                                               |
   |           | full load |                                               |
   |           | of the    |                                               |
   |           | lsc file. |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``align`` | Optional. |                                               |
   |           | E         |                                               |
   |           | xpression |                                               |
   |           | defining  |                                               |
   |           | the       |                                               |
   |           | alignment |                                               |
   |           | in bytes  |                                               |
   |           | of the    |                                               |
   |           | section.  |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``root    | Optional. |                                               |
   | Section`` | Boolean   |                                               |
   |           | value.    |                                               |
   |           | Sets this |                                               |
   |           | section   |                                               |
   |           | as a root |                                               |
   |           | section   |                                               |
   |           | to be     |                                               |
   |           | embedded  |                                               |
   |           | even if   |                                               |
   |           | it is not |                                               |
   |           | targeted  |                                               |
   |           | by any    |                                               |
   |           | embedded  |                                               |
   |           | symbol.   |                                               |
   |           | See also  |                                               |
   |           | ``root    |                                               |
   |           | Section`` |                                               |
   |           | tag.      |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``symbo   | Optional. |                                               |
   | lPrefix`` | Used in   |                                               |
   |           | coll      |                                               |
   |           | aboration |                                               |
   |           | with      |                                               |
   |           | ``symb    |                                               |
   |           | olTags``. |                                               |
   |           | Prefix of |                                               |
   |           | symbols   |                                               |
   |           | embedded  |                                               |
   |           | in the    |                                               |
   |           | auto-     |                                               |
   |           | generated |                                               |
   |           | section.  |                                               |
   |           | See       |                                               |
   |           | `???      |                                               |
   |           |  <#linker |                                               |
   |           | -autosect |                                               |
   |           | ions>`__. |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``sym     | Optional. |                                               |
   | bolTags`` | Used in   |                                               |
   |           | coll      |                                               |
   |           | aboration |                                               |
   |           | with      |                                               |
   |           | ``symbol  |                                               |
   |           | Prefix``. |                                               |
   |           | Comma     |                                               |
   |           | separated |                                               |
   |           | list of   |                                               |
   |           | tags of   |                                               |
   |           | symbols   |                                               |
   |           | embedded  |                                               |
   |           | in the    |                                               |
   |           | auto-     |                                               |
   |           | generated |                                               |
   |           | section.  |                                               |
   |           | See       |                                               |
   |           | `???      |                                               |
   |           |  <#linker |                                               |
   |           | -autosect |                                               |
   |           | ions>`__. |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``de      | ````      | Defines a new global symbol. Symbol name must |
   | fSymbol`` |           | be unique in the linker context.              |
   +-----------+-----------+-----------------------------------------------+
   | ``name``  | Name of   |                                               |
   |           | the       |                                               |
   |           | symbol.   |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``type``  | Optional. |                                               |
   |           | Type of   |                                               |
   |           | symbol    |                                               |
   |           | usage.    |                                               |
   |           | This may  |                                               |
   |           | be        |                                               |
   |           | necessary |                                               |
   |           | to set    |                                               |
   |           | the type  |                                               |
   |           | of a      |                                               |
   |           | symbol    |                                               |
   |           | when      |                                               |
   |           | using     |                                               |
   |           | third     |                                               |
   |           | party ELF |                                               |
   |           | tools.    |                                               |
   |           | There are |                                               |
   |           | three     |                                               |
   |           | types:    |                                               |
   |           |           |                                               |
   |           | -         |                                               |
   |           | ``none``: |                                               |
   |           |           |                                               |
   |           |  default. |                                               |
   |           |    No     |                                               |
   |           |           |                                               |
   |           |   special |                                               |
   |           |    type   |                                               |
   |           |    of     |                                               |
   |           |    use.   |                                               |
   |           |           |                                               |
   |           | -  ``fu   |                                               |
   |           | nction``: |                                               |
   |           |    symbol |                                               |
   |           |           |                                               |
   |           | describes |                                               |
   |           |    a      |                                               |
   |           |           |                                               |
   |           | function. |                                               |
   |           |           |                                               |
   |           | -         |                                               |
   |           | ``data``: |                                               |
   |           |    symbol |                                               |
   |           |           |                                               |
   |           | describes |                                               |
   |           |    some   |                                               |
   |           |    data.  |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``value`` | The value |                                               |
   |           | ``"."``   |                                               |
   |           | defines a |                                               |
   |           | floating  |                                               |
   |           | symbol    |                                               |
   |           | that      |                                               |
   |           | holds the |                                               |
   |           | current   |                                               |
   |           | cursor    |                                               |
   |           | position  |                                               |
   |           | in a      |                                               |
   |           | memory    |                                               |
   |           | layout.   |                                               |
   |           | (This is  |                                               |
   |           | the only  |                                               |
   |           | form of   |                                               |
   |           | this tag  |                                               |
   |           | that can  |                                               |
   |           | be used   |                                               |
   |           | as a      |                                               |
   |           | mem       |                                               |
   |           | oryLayout |                                               |
   |           | d         |                                               |
   |           | irective) |                                               |
   |           | Otherwise |                                               |
   |           | value is  |                                               |
   |           | an        |                                               |
   |           | ex        |                                               |
   |           | pression. |                                               |
   |           | A symbol  |                                               |
   |           | e         |                                               |
   |           | xpression |                                               |
   |           | must be   |                                               |
   |           | resolved  |                                               |
   |           | to a      |                                               |
   |           | constant  |                                               |
   |           | after     |                                               |
   |           | memory    |                                               |
   |           | pos       |                                               |
   |           | itioning. |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``rel     | Optional. |                                               |
   | ocation`` | The only  |                                               |
   |           | allowed   |                                               |
   |           | value is  |                                               |
   |           | ``true``. |                                               |
   |           | Indicates |                                               |
   |           | that the  |                                               |
   |           | value of  |                                               |
   |           | the       |                                               |
   |           | symbol    |                                               |
   |           | takes the |                                               |
   |           | address   |                                               |
   |           | of the    |                                               |
   |           | current   |                                               |
   |           | cursor in |                                               |
   |           | the       |                                               |
   |           | memory    |                                               |
   |           | layout    |                                               |
   |           | r         |                                               |
   |           | elocation |                                               |
   |           | space.    |                                               |
   |           | Only      |                                               |
   |           | allowed   |                                               |
   |           | on        |                                               |
   |           | floating  |                                               |
   |           | symbols.  |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``roo     | Optional. |                                               |
   | tSymbol`` | Boolean   |                                               |
   |           | value.    |                                               |
   |           | Sets this |                                               |
   |           | symbol as |                                               |
   |           | a root    |                                               |
   |           | symbol    |                                               |
   |           | that must |                                               |
   |           | be        |                                               |
   |           | resolved. |                                               |
   |           | See also  |                                               |
   |           | ``roo     |                                               |
   |           | tSymbol`` |                                               |
   |           | tag.      |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``weak``  | Optional. |                                               |
   |           | Boolean   |                                               |
   |           | value.    |                                               |
   |           | Sets this |                                               |
   |           | symbol as |                                               |
   |           | a weak    |                                               |
   |           | symbol.   |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``group`` | ````      | memoryLayout directive. Defines a named group |
   |           |           | of sections. Group name may be used in        |
   |           |           | expression macros ``START``, ``END``,         |
   |           |           | ``SIZE``. All memoryLayout directives are     |
   |           |           | allowed within this tag (recursively).        |
   +-----------+-----------+-----------------------------------------------+
   | ``name``  | The name  |                                               |
   |           | of the    |                                               |
   |           | group.    |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``        | ````      | Includes an lsc fragment file, semantically   |
   | include`` |           | the same as if the fragment contents were     |
   |           |           | defined in place of the ``include`` tag.      |
   +-----------+-----------+-----------------------------------------------+
   | ``name``  | Name of   |                                               |
   |           | the file  |                                               |
   |           | to        |                                               |
   |           | include.  |                                               |
   |           | When the  |                                               |
   |           | name is   |                                               |
   |           | relative, |                                               |
   |           | the file  |                                               |
   |           | separator |                                               |
   |           | is ``/``, |                                               |
   |           | and the   |                                               |
   |           | file is   |                                               |
   |           | relative  |                                               |
   |           | to the    |                                               |
   |           | directory |                                               |
   |           | where the |                                               |
   |           | current   |                                               |
   |           | lsc file  |                                               |
   |           | or        |                                               |
   |           | fragment  |                                               |
   |           | is        |                                               |
   |           | loaded.   |                                               |
   |           | When      |                                               |
   |           | absolute, |                                               |
   |           | the name  |                                               |
   |           | describes |                                               |
   |           | a         |                                               |
   |           | platform- |                                               |
   |           | dependent |                                               |
   |           | filename. |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``lsc``   | ````      | Root tag for an .lsc file.                    |
   +-----------+-----------+-----------------------------------------------+
   | ``name``  | Name of   |                                               |
   |           | the lsc   |                                               |
   |           | file. The |                                               |
   |           | ELF       |                                               |
   |           | e         |                                               |
   |           | xecutable |                                               |
   |           | output    |                                               |
   |           | will be   |                                               |
   |           | ``{nam    |                                               |
   |           | e}.out``, |                                               |
   |           | and the   |                                               |
   |           | map file  |                                               |
   |           | will be   |                                               |
   |           | ``{na     |                                               |
   |           | me}.map`` |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``lscF    | ````      | Root tag for an lsc file fragment. Lsc        |
   | ragment`` |           | fragments are loaded from the linker path     |
   |           |           | option, or included from a master file using  |
   |           |           | athe ``include`` tag.                         |
   +-----------+-----------+-----------------------------------------------+
   | ``memor   | ````      | Describes the organization of a set of memory |
   | yLayout`` |           | intervals. The memory layouts are processed   |
   |           |           | in the order in which they are declared in    |
   |           |           | the file. The same interval may be organized  |
   |           |           | in several layouts. Each layout starts at the |
   |           |           | value of the cursor the previous layout       |
   |           |           | ended. The following tags are allowed within  |
   |           |           | a memoryLayout directive: ``defSymbol``       |
   |           |           | (under certain conditions), ``group``,        |
   |           |           | ``memoryLayoutRef``, ``padding``, and         |
   |           |           | ``sectionRef``.                               |
   +-----------+-----------+-----------------------------------------------+
   | `         | Exclusive |                                               |
   | `ranges`` | with      |                                               |
   |           | default.  |                                               |
   |           | Comma-    |                                               |
   |           | separated |                                               |
   |           | ordered   |                                               |
   |           | list of   |                                               |
   |           | fixed     |                                               |
   |           | sections  |                                               |
   |           | to which  |                                               |
   |           | the       |                                               |
   |           | layout is |                                               |
   |           | applied.  |                                               |
   |           | Sections  |                                               |
   |           | represent |                                               |
   |           | memory    |                                               |
   |           | segments. |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``image`` | Optional. |                                               |
   |           | Boolean   |                                               |
   |           | value.    |                                               |
   |           | ``false`` |                                               |
   |           | if not    |                                               |
   |           | set. If   |                                               |
   |           | ``true``, |                                               |
   |           | the       |                                               |
   |           | layout    |                                               |
   |           | describes |                                               |
   |           | a part of |                                               |
   |           | the       |                                               |
   |           | binary    |                                               |
   |           | image:    |                                               |
   |           | Only      |                                               |
   |           | image     |                                               |
   |           | sections  |                                               |
   |           | can be    |                                               |
   |           | embedded. |                                               |
   |           | If        |                                               |
   |           | `         |                                               |
   |           | `false``, |                                               |
   |           | only      |                                               |
   |           | runtime   |                                               |
   |           | sections  |                                               |
   |           | can be    |                                               |
   |           | embedded. |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``rel     | Optional. |                                               |
   | ocation`` | Name of   |                                               |
   |           | the       |                                               |
   |           | section   |                                               |
   |           | to which  |                                               |
   |           | this      |                                               |
   |           | layout is |                                               |
   |           | r         |                                               |
   |           | elocated. |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``name``  | Exclusive |                                               |
   |           | with      |                                               |
   |           | ranges.   |                                               |
   |           | Defines a |                                               |
   |           | named     |                                               |
   |           | mem       |                                               |
   |           | oryLayout |                                               |
   |           | directive |                                               |
   |           | instead   |                                               |
   |           | of        |                                               |
   |           | s         |                                               |
   |           | pecifying |                                               |
   |           | a         |                                               |
   |           | concrete  |                                               |
   |           | memory    |                                               |
   |           | location. |                                               |
   |           | May be    |                                               |
   |           | included  |                                               |
   |           | in a      |                                               |
   |           | parent    |                                               |
   |           | mem       |                                               |
   |           | oryLayout |                                               |
   |           | using     |                                               |
   |           | memoryL   |                                               |
   |           | ayoutRef. |                                               |
   +-----------+-----------+-----------------------------------------------+
   | `         | ````      | ``memoryLayout`` directive. Provides an       |
   | `memoryLa |           | extension-point mechanism to include          |
   | youtRef`` |           | ``memoryLayout`` directives defined outside   |
   |           |           | the current one.                              |
   +-----------+-----------+-----------------------------------------------+
   | ``name``  | All       |                                               |
   |           | d         |                                               |
   |           | irectives |                                               |
   |           | of        |                                               |
   |           | mem       |                                               |
   |           | oryLayout |                                               |
   |           | defined   |                                               |
   |           | with the  |                                               |
   |           | same name |                                               |
   |           | are       |                                               |
   |           | included  |                                               |
   |           | in an     |                                               |
   |           | undefined |                                               |
   |           | order.    |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``        | ````      | ``memoryLayout`` directive. Append padding    |
   | padding`` |           | bytes to the current cursor. Either size or   |
   |           |           | align attributes should be provided.          |
   +-----------+-----------+-----------------------------------------------+
   | ``size``  | Optional. |                                               |
   |           | E         |                                               |
   |           | xpression |                                               |
   |           | must be   |                                               |
   |           | resolved  |                                               |
   |           | to a      |                                               |
   |           | constant  |                                               |
   |           | after the |                                               |
   |           | full load |                                               |
   |           | of the    |                                               |
   |           | lsc file. |                                               |
   |           | Increment |                                               |
   |           | the       |                                               |
   |           | cursor    |                                               |
   |           | position  |                                               |
   |           | with the  |                                               |
   |           | given     |                                               |
   |           | size.     |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``align`` | Optional. |                                               |
   |           | E         |                                               |
   |           | xpression |                                               |
   |           | must be   |                                               |
   |           | resolved  |                                               |
   |           | to a      |                                               |
   |           | constant  |                                               |
   |           | after the |                                               |
   |           | full load |                                               |
   |           | of the    |                                               |
   |           | lsc file. |                                               |
   |           | Move the  |                                               |
   |           | current   |                                               |
   |           | cursor    |                                               |
   |           | position  |                                               |
   |           | to the    |                                               |
   |           | next      |                                               |
   |           | address   |                                               |
   |           | that      |                                               |
   |           | matches   |                                               |
   |           | the given |                                               |
   |           | a         |                                               |
   |           | lignment. |                                               |
   |           | Warning:  |                                               |
   |           | when used |                                               |
   |           | with      |                                               |
   |           | re        |                                               |
   |           | location, |                                               |
   |           | the       |                                               |
   |           | r         |                                               |
   |           | elocation |                                               |
   |           | cursor is |                                               |
   |           | also      |                                               |
   |           | aligned.  |                                               |
   |           | Keep in   |                                               |
   |           | mind this |                                               |
   |           | may       |                                               |
   |           | increase  |                                               |
   |           | the       |                                               |
   |           | cursor    |                                               |
   |           | position  |                                               |
   |           | with a    |                                               |
   |           | different |                                               |
   |           | amount of |                                               |
   |           | bytes.    |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``        | Optional. |                                               |
   | address`` | E         |                                               |
   |           | xpression |                                               |
   |           | must be   |                                               |
   |           | resolved  |                                               |
   |           | to a      |                                               |
   |           | constant  |                                               |
   |           | after the |                                               |
   |           | full load |                                               |
   |           | of the    |                                               |
   |           | lsc file. |                                               |
   |           | Move the  |                                               |
   |           | current   |                                               |
   |           | cursor    |                                               |
   |           | position  |                                               |
   |           | to the    |                                               |
   |           | given     |                                               |
   |           | absolute  |                                               |
   |           | address.  |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``fill``  | Optional. |                                               |
   |           | E         |                                               |
   |           | xpression |                                               |
   |           | must be   |                                               |
   |           | resolved  |                                               |
   |           | to a      |                                               |
   |           | constant  |                                               |
   |           | after the |                                               |
   |           | full load |                                               |
   |           | of the    |                                               |
   |           | lsc file. |                                               |
   |           | Fill      |                                               |
   |           | padding   |                                               |
   |           | with the  |                                               |
   |           | given     |                                               |
   |           | value (32 |                                               |
   |           | bits).    |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``root    | ````      | References a section name that must be        |
   | Section`` |           | embedded. This tag is not a definition. It    |
   |           |           | forces the linker to embed all loaded         |
   |           |           | sections matching the given name.             |
   +-----------+-----------+-----------------------------------------------+
   | ``name``  | Name of   |                                               |
   |           | the       |                                               |
   |           | section   |                                               |
   |           | to be     |                                               |
   |           | embedded. |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``roo     | ````      | References a symbol that must be resolved.    |
   | tSymbol`` |           | This tag is not a definition. It forces the   |
   |           |           | linker to resolve the value of the symbol.    |
   +-----------+-----------+-----------------------------------------------+
   | ``name``  | Name of   |                                               |
   |           | the       |                                               |
   |           | symbol to |                                               |
   |           | be        |                                               |
   |           | resolved. |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``sec     | ````      | Memory layout statement. Embeds all sections  |
   | tionRef`` |           | matching the given name starting at the       |
   |           |           | current cursor address.                       |
   +-----------+-----------+-----------------------------------------------+
   | ``file``  | Select    |                                               |
   |           | only      |                                               |
   |           | sections  |                                               |
   |           | defined   |                                               |
   |           | in a      |                                               |
   |           | linker    |                                               |
   |           | unit      |                                               |
   |           | matching  |                                               |
   |           | the given |                                               |
   |           | file      |                                               |
   |           | name. The |                                               |
   |           | file name |                                               |
   |           | is the    |                                               |
   |           | simple    |                                               |
   |           | name      |                                               |
   |           | without   |                                               |
   |           | any file  |                                               |
   |           | s         |                                               |
   |           | eparator, |                                               |
   |           | e.g.      |                                               |
   |           | ``bsp.o`` |                                               |
   |           | or        |                                               |
   |           | ``myli    |                                               |
   |           | nk.lsc``. |                                               |
   |           | Link      |                                               |
   |           | units may |                                               |
   |           | be object |                                               |
   |           | files     |                                               |
   |           | within    |                                               |
   |           | archive   |                                               |
   |           | units.    |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``name``  | Name of   |                                               |
   |           | the       |                                               |
   |           | sections  |                                               |
   |           | to embed. |                                               |
   |           | When the  |                                               |
   |           | name ends |                                               |
   |           | with \*,  |                                               |
   |           | all       |                                               |
   |           | sections  |                                               |
   |           | starting  |                                               |
   |           | with the  |                                               |
   |           | given     |                                               |
   |           | name are  |                                               |
   |           | embedded  |                                               |
   |           | (name     |                                               |
   |           | com       |                                               |
   |           | pletion), |                                               |
   |           | except    |                                               |
   |           | sections  |                                               |
   |           | that are  |                                               |
   |           | embedded  |                                               |
   |           | in        |                                               |
   |           | another   |                                               |
   |           | s         |                                               |
   |           | ectionRef |                                               |
   |           | using the |                                               |
   |           | exact     |                                               |
   |           | name      |                                               |
   |           | (without  |                                               |
   |           | com       |                                               |
   |           | pletion). |                                               |
   +-----------+-----------+-----------------------------------------------+
   | `         | Optional. |                                               |
   | `symbol`` | Only      |                                               |
   |           | embeds    |                                               |
   |           | the       |                                               |
   |           | section   |                                               |
   |           | targeted  |                                               |
   |           | by the    |                                               |
   |           | given     |                                               |
   |           | symbol.   |                                               |
   |           | This is   |                                               |
   |           | the only  |                                               |
   |           | way at    |                                               |
   |           | link      |                                               |
   |           | level to  |                                               |
   |           | embed a   |                                               |
   |           | specific  |                                               |
   |           | section   |                                               |
   |           | whose     |                                               |
   |           | name is   |                                               |
   |           | not       |                                               |
   |           | unique.   |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``force`` | Optional. |                                               |
   |           | De        |                                               |
   |           | precated. |                                               |
   |           | Replaced  |                                               |
   |           | by the    |                                               |
   |           | ``root    |                                               |
   |           | Section`` |                                               |
   |           | tag. The  |                                               |
   |           | only      |                                               |
   |           | allowed   |                                               |
   |           | value is  |                                               |
   |           | ``true``. |                                               |
   |           | By        |                                               |
   |           | default,  |                                               |
   |           | for       |                                               |
   |           | co        |                                               |
   |           | mpaction, |                                               |
   |           | the       |                                               |
   |           | linker    |                                               |
   |           | embeds    |                                               |
   |           | only what |                                               |
   |           | is        |                                               |
   |           | needed.   |                                               |
   |           | Setting   |                                               |
   |           | this      |                                               |
   |           | attribute |                                               |
   |           | will      |                                               |
   |           | force the |                                               |
   |           | linker to |                                               |
   |           | embed all |                                               |
   |           | sections  |                                               |
   |           | that      |                                               |
   |           | appear in |                                               |
   |           | all       |                                               |
   |           | loaded    |                                               |
   |           | re        |                                               |
   |           | locatable |                                               |
   |           | files,    |                                               |
   |           | even      |                                               |
   |           | sections  |                                               |
   |           | that are  |                                               |
   |           | not       |                                               |
   |           | targeted  |                                               |
   |           | by a      |                                               |
   |           | symbol.   |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``sort``  | Optional. |                                               |
   |           | Specifies |                                               |
   |           | that the  |                                               |
   |           | sections  |                                               |
   |           | must be   |                                               |
   |           | sorted in |                                               |
   |           | memory.   |                                               |
   |           | The value |                                               |
   |           | can be:   |                                               |
   |           |           |                                               |
   |           | -  `      |                                               |
   |           | `order``: |                                               |
   |           |    the    |                                               |
   |           |           |                                               |
   |           |  sections |                                               |
   |           |    will   |                                               |
   |           |    be in  |                                               |
   |           |    the    |                                               |
   |           |    same   |                                               |
   |           |    order  |                                               |
   |           |    as the |                                               |
   |           |    input  |                                               |
   |           |    files  |                                               |
   |           |           |                                               |
   |           | -         |                                               |
   |           | ``name``: |                                               |
   |           |    the    |                                               |
   |           |           |                                               |
   |           |  sections |                                               |
   |           |    are    |                                               |
   |           |    sorted |                                               |
   |           |    by     |                                               |
   |           |    their  |                                               |
   |           |    file   |                                               |
   |           |    names  |                                               |
   |           |           |                                               |
   |           | -         |                                               |
   |           | ``unit``: |                                               |
   |           |    the    |                                               |
   |           |           |                                               |
   |           |  sections |                                               |
   |           |           |                                               |
   |           |  declared |                                               |
   |           |    in an  |                                               |
   |           |    object |                                               |
   |           |    file   |                                               |
   |           |    are    |                                               |
   |           |           |                                               |
   |           |   grouped |                                               |
   |           |    and    |                                               |
   |           |    sorted |                                               |
   |           |    in the |                                               |
   |           |    order  |                                               |
   |           |    they   |                                               |
   |           |    are    |                                               |
   |           |           |                                               |
   |           |  declared |                                               |
   |           |    in the |                                               |
   |           |    object |                                               |
   |           |    file   |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``u4``    | ````      | Binary section statement. Describes the four  |
   |           |           | next raw bytes of the section. Bytes are      |
   |           |           | organized in the endianness of the target ELF |
   |           |           | executable.                                   |
   +-----------+-----------+-----------------------------------------------+
   | ``value`` | E         |                                               |
   |           | xpression |                                               |
   |           | must be   |                                               |
   |           | resolved  |                                               |
   |           | to a      |                                               |
   |           | constant  |                                               |
   |           | after the |                                               |
   |           | full load |                                               |
   |           | of the    |                                               |
   |           | lsc file  |                                               |
   |           | (32 bits  |                                               |
   |           | value).   |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``fill``  | ````      | Binary section statement. Fills the section   |
   |           |           | with the given expression. Bytes are          |
   |           |           | organized in the endianness of the target ELF |
   |           |           | executable.                                   |
   +-----------+-----------+-----------------------------------------------+
   | ``size``  | E         |                                               |
   |           | xpression |                                               |
   |           | defining  |                                               |
   |           | the       |                                               |
   |           | number of |                                               |
   |           | bytes to  |                                               |
   |           | be        |                                               |
   |           | filled.   |                                               |
   +-----------+-----------+-----------------------------------------------+
   | ``value`` | E         |                                               |
   |           | xpression |                                               |
   |           | must be   |                                               |
   |           | resolved  |                                               |
   |           | to a      |                                               |
   |           | constant  |                                               |
   |           | after the |                                               |
   |           | full load |                                               |
   |           | of the    |                                               |
   |           | lsc file  |                                               |
   |           | (32 bits  |                                               |
   |           | value).   |                                               |
   +-----------+-----------+-----------------------------------------------+
