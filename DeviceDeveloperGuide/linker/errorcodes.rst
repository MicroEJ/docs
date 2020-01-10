Error Messages
==============

This section lists LINKER error messages.

.. table:: Linker-Specific Configuration Tags

   +-------------+--------------------------------------------------------+
   | Message ID  | Description                                            |
   +-------------+--------------------------------------------------------+
   | 0           | The linker has encountered an unexpected internal      |
   |             | error. Please contact the support hotline.             |
   +-------------+--------------------------------------------------------+
   | 1           | A library cannot be loaded with this linker. Try       |
   |             | verbose to check installed loaders.                    |
   +-------------+--------------------------------------------------------+
   | 2           | No lsc file provided to the linker.                    |
   +-------------+--------------------------------------------------------+
   | 3           | A file could not be loaded. Check the existence of the |
   |             | file and file access rights.                           |
   +-------------+--------------------------------------------------------+
   | 4           | Conflicting input libraries. A global symbol           |
   |             | definition with the same name has already been loaded  |
   |             | from a previous object file.                           |
   +-------------+--------------------------------------------------------+
   | 5           | Completion (*) could not be used in association with   |
   |             | the force attribute. Must be an exact name.            |
   +-------------+--------------------------------------------------------+
   | 6           | A required section refers to an unknown global symbol. |
   |             | Maybe input libraries are missing.                     |
   +-------------+--------------------------------------------------------+
   | 7           | A library loader has encountered an unexpected         |
   |             | internal error. Check input library file integrity.    |
   +-------------+--------------------------------------------------------+
   | 8           | Floating symbols can only be declared inside           |
   |             | ``memoryLayout`` tags.                                 |
   +-------------+--------------------------------------------------------+
   | 9           | Invalid value format. For example, the attribute       |
   |             | relocation in ``defSymbol`` must be a boolean value.   |
   +-------------+--------------------------------------------------------+
   | 10          | Missing one of the following attributes: ``address``,  |
   |             | ``size``, ``align``.                                   |
   +-------------+--------------------------------------------------------+
   | 11          | Too many attributes that cannot be used in             |
   |             | association.                                           |
   +-------------+--------------------------------------------------------+
   | 13          | Negative padding. Memory layout cursor cannot          |
   |             | decrease.                                              |
   +-------------+--------------------------------------------------------+
   | 15          | Not enough space in the memory layout intervals to     |
   |             | append all sections that need to be embedded. Check    |
   |             | the output map file to get more information about what |
   |             | is required as memory space.                           |
   +-------------+--------------------------------------------------------+
   | 16          | A block is referenced but has already been embedded.   |
   |             | Most likely a block has been especially embedded using |
   |             | the force attribute and the symbol attribute.          |
   +-------------+--------------------------------------------------------+
   | 17          | A block that must be embedded has no matching          |
   |             | ``sectionRef`` statement.                              |
   +-------------+--------------------------------------------------------+
   | 19          | An IO error occurred when trying to dump one of the    |
   |             | output files. Check the output directory option and    |
   |             | file access rights.                                    |
   +-------------+--------------------------------------------------------+
   | 20          | ``size`` attribute expected.                           |
   +-------------+--------------------------------------------------------+
   | 21          | The computed size does not match the declared size.    |
   +-------------+--------------------------------------------------------+
   | 22          | Sections defined in the lsc file must be unique.       |
   +-------------+--------------------------------------------------------+
   | 23          | One of the memory layout intervals refers to an        |
   |             | unknown lsc section.                                   |
   +-------------+--------------------------------------------------------+
   | 24          | Relocation must be done in one and only one contiguous |
   |             | interval.                                              |
   +-------------+--------------------------------------------------------+
   | 25          | ``force`` and ``symbol`` attributes are not allowed    |
   |             | together.                                              |
   +-------------+--------------------------------------------------------+
   | 26          | XML char data not allowed at this position in the lsc  |
   |             | file.                                                  |
   +-------------+--------------------------------------------------------+
   | 27          | A section which is a part of the program image must be |
   |             | embedded in an image memory layout.                    |
   +-------------+--------------------------------------------------------+
   | 28          | A section which is not a part of the program image     |
   |             | must be embedded in a non-image memory layout.         |
   +-------------+--------------------------------------------------------+
   | 29          | Expression could not be resolved to a link-time        |
   |             | constant. Some symbols are unresolved.                 |
   +-------------+--------------------------------------------------------+
   | 30          | Sections used in memory layout ranges must be sections |
   |             | defined in the lsc file.                               |
   +-------------+--------------------------------------------------------+
   | 31          | Invalid character encountered when scanning the lsc    |
   |             | expression.                                            |
   +-------------+--------------------------------------------------------+
   | 32          | A recursive include cycle was detected.                |
   +-------------+--------------------------------------------------------+
   | 33          | An alignment inconsistency was detected in a           |
   |             | relocation memory layout. Most likely one of the start |
   |             | addresses of the memory layout is not aligned on the   |
   |             | current alignment.                                     |
   +-------------+--------------------------------------------------------+
   | 34          | An error occurs in a relocation resolution. In         |
   |             | general, the relocation has a value that is out of     |
   |             | range.                                                 |
   +-------------+--------------------------------------------------------+
   | 35          | ``symbol`` and ``sort`` attributes are not allowed     |
   |             | together.                                              |
   +-------------+--------------------------------------------------------+
   | 36          | Invalid sort attribute value is not one of ``order``,  |
   |             | ``name``, or ``no``.                                   |
   +-------------+--------------------------------------------------------+
   | 37          | Attribute ``start`` or ``end`` in ``defSection`` tag   |
   |             | is not allowed when defining a floating section.       |
   +-------------+--------------------------------------------------------+
   | 38          | Autogenerated section can build tables according to    |
   |             | symbol names (see `??? <#linker-autosections>`__). A   |
   |             | symbol is needed to build this section but has not     |
   |             | been loaded.                                           |
   +-------------+--------------------------------------------------------+
   | 39          | Deprecated feature warning. Remains for backward       |
   |             | compatibility. It is recommended that you use the new  |
   |             | indicated feature, because this feature may be removed |
   |             | in future linker releases.                             |
   +-------------+--------------------------------------------------------+
   | 40          | Unknown output architecture. Either the architecture   |
   |             | ID is invalid, or the library loader has not been      |
   |             | loaded by the linker. Check loaded library loaders     |
   |             | using verbose option.                                  |
   +-------------+--------------------------------------------------------+
   | 41...43     | Reserved.                                              |
   +-------------+--------------------------------------------------------+
   | 44          | Duplicate group definition. A group name is unique and |
   |             | cannot be defined twice.                               |
   +-------------+--------------------------------------------------------+
   | 45          | Invalid endianness. The endianness mnemonic is not one |
   |             | of the expected mnemonics (``little,big,none``).       |
   +-------------+--------------------------------------------------------+
   | 46          | Multiple endiannesses detected within loaded input     |
   |             | libraries.                                             |
   +-------------+--------------------------------------------------------+
   | 47          | Reserved.                                              |
   +-------------+--------------------------------------------------------+
   | 48          | Invalid type mnemonic passed to a ``defSymbol`` tag.   |
   |             | Must be one of ``none``, ``function``, or ``data``.    |
   +-------------+--------------------------------------------------------+
   | 49          | Warning. A directory of link path is invalid           |
   |             | (skipped).                                             |
   +-------------+--------------------------------------------------------+
   | 50          | No linker-specific description file could be loaded    |
   |             | from the link path. Check that the link path           |
   |             | directories are valid, and that they contain ``.lsc``  |
   |             | or ``.lscf`` files.                                    |
   +-------------+--------------------------------------------------------+
   | 51          | Exclusive options (these options cannot be used        |
   |             | simultaneously). For example, ``-linkFilename`` and    |
   |             | ``-linkPath`` are exclusive; either select a master    |
   |             | lsc file or a path from which to load ``.lscf`` files. |
   +-------------+--------------------------------------------------------+
   | 52          | Name given to a ``memoryLayoutRef`` or a               |
   |             | ``memoryLayout`` is invalid. It must not be empty.     |
   +-------------+--------------------------------------------------------+
   | 53          | A ``memoryLayoutRef`` with the same name has already   |
   |             | been processed.                                        |
   +-------------+--------------------------------------------------------+
   | 54          | A ``memoryLayout`` must define ``ranges`` or the       |
   |             | ``name`` attribute.                                    |
   +-------------+--------------------------------------------------------+
   | 55          | No memory layout found matching the name of the        |
   |             | current ``memoryLayoutRef``.                           |
   +-------------+--------------------------------------------------------+
   | 56          | A named ``memoryLayout`` is declared with a relocation |
   |             | directive, but the relocation interval is incompatible |
   |             | with the relocation interval of the ``memoryLayout``   |
   |             | that referenced it.                                    |
   +-------------+--------------------------------------------------------+
   | 57          | A named ``memoryLayout`` has not been referenced.      |
   |             | Every declared ``memoryLayout`` must be processed. A   |
   |             | named ``memoryLayout`` must be referenced by a         |
   |             | ``memoryLayoutRef`` statement.                         |
   +-------------+--------------------------------------------------------+
   | 58          | ``SUM`` operator expects an auto-generated section.    |
   +-------------+--------------------------------------------------------+
   | 59          | ``SUM`` operator tag is unknown for the targetted      |
   |             | auto-generated section.                                |
   +-------------+--------------------------------------------------------+
   | 60          | ``SUM`` operator auto-generated section name is        |
   |             | unknown.                                               |
   +-------------+--------------------------------------------------------+
   | 61          | An option is set for an unknown extension. Most likely |
   |             | the extension has not been set to the linker           |
   |             | classpath.                                             |
   +-------------+--------------------------------------------------------+
   | 62          | Reserved.                                              |
   +-------------+--------------------------------------------------------+
   | 63          | ELF unit flags are inconsistent with flags set using   |
   |             | the ``-forceFlags`` option.                            |
   +-------------+--------------------------------------------------------+
   | 64          | Reserved.                                              |
   +-------------+--------------------------------------------------------+
   | 65          | Reserved.                                              |
   +-------------+--------------------------------------------------------+
   | 66          | Found an executable object file as input (expected a   |
   |             | relocatable object file).                              |
   +-------------+--------------------------------------------------------+
   | 67          | Reserved.                                              |
   +-------------+--------------------------------------------------------+
   | 68          | Reserved.                                              |
   +-------------+--------------------------------------------------------+
   | 69          | Reserved.                                              |
   +-------------+--------------------------------------------------------+
   | 70          | Not enough memory to achieve the linking process. Try  |
   |             | to increase JVM heap that is running the linker (e.g.  |
   |             | by adding option -Xmx1024M to the JRE command line).   |
   +-------------+--------------------------------------------------------+
