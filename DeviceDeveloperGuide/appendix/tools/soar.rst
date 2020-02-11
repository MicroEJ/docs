Smart Linker
============

When a generic exception is thrown by the Smart Linker, the error
message 

::
   SOAR ERROR [M<messageId>] <message>

is issued, where ``<messageId>`` and ``<message>`` meanings are defined in the
next table.

.. table:: SOAR Error Messages.

   +-------------+--------------------------------------------------------+
   | Message ID  | Description                                            |
   +=============+========================================================+
   | 0           | The SOAR process has encountered some internal limits. |
   +-------------+--------------------------------------------------------+
   | 1           | Unknown option.                                        |
   +-------------+--------------------------------------------------------+
   | 2           | An option has an invalid value.                        |
   +-------------+--------------------------------------------------------+
   | 3           | A mandatory option is not set.                         |
   +-------------+--------------------------------------------------------+
   | 4           | A filename given in options does not exist .           |
   +-------------+--------------------------------------------------------+
   | 5           | Failed to write the output file (access permissions    |
   |             | required for ``-toDir`` and ``-root`` options).        |
   +-------------+--------------------------------------------------------+
   | 6           | The given file does not exist.                         |
   +-------------+--------------------------------------------------------+
   | 7           | I/O error while reading a file.                        |
   +-------------+--------------------------------------------------------+
   | 8           | An option value refers to a directory, instead of a    |
   |             | file.                                                  |
   +-------------+--------------------------------------------------------+
   | 9           | An option value refers to a file, instead of a         |
   |             | directory or a jar file.                               |
   +-------------+--------------------------------------------------------+
   | 10          | Invalid entry point class or no ``main()`` method.     |
   +-------------+--------------------------------------------------------+
   | 11          | An information file can not be generated in its        |
   |             | entirety.                                              |
   +-------------+--------------------------------------------------------+
   | 12          | Limitations of the evaluation version have been        |
   |             | reached.                                               |
   +-------------+--------------------------------------------------------+
   | 13          | I/O rrror while reading a jar file.                    |
   +-------------+--------------------------------------------------------+
   | 14          | IO Error while writing a file.                         |
   +-------------+--------------------------------------------------------+
   | 15          | I/O error while reading a jar file: unknown entry      |
   |             | size.                                                  |
   +-------------+--------------------------------------------------------+
   | 16          | Not enough memory to load a jar file.                  |
   +-------------+--------------------------------------------------------+
   | 17          | The specified SOAR options are exclusive.              |
   +-------------+--------------------------------------------------------+
   | 18          | XML syntax error for some given files.                 |
   +-------------+--------------------------------------------------------+
   | 19          | Unsupported float representation.                      |
   +-------------+--------------------------------------------------------+
   | 23          | A clinit cycle has been detected. The clinit cycle can |
   |             | be cut either by simplifying the application clinit    |
   |             | code or by explicitly declaring clinit dependencies.   |
   |             | Check the generated ``.clinitmap`` file for more       |
   |             | information.                                           |
   +-------------+--------------------------------------------------------+
   | 50          | Missing code: Java code refers to a method not found   |
   |             | in specified classes.                                  |
   +-------------+--------------------------------------------------------+
   | 51          | Missing code: Java code refers to a class not found in |
   |             | the specified classpath.                               |
   +-------------+--------------------------------------------------------+
   | 52          | Wrong class: Java code refers to a field not found in  |
   |             | the specified class.                                   |
   +-------------+--------------------------------------------------------+
   | 53          | Wrong class: A Java classfile refers to a class as an  |
   |             | interface.                                             |
   +-------------+--------------------------------------------------------+
   | 54          | Wrong class: An abstract method is found in a          |
   |             | non-abstract class.                                    |
   +-------------+--------------------------------------------------------+
   | 55          | Wrong class: illegal access to a method, a field or a  |
   |             | type.                                                  |
   +-------------+--------------------------------------------------------+
   | 56          | Wrong class: hierarchy inconsistency; an interface     |
   |             | cannot be a superclass of a class.                     |
   +-------------+--------------------------------------------------------+
   | 57          | Circularity detected in initializion sequence.         |
   +-------------+--------------------------------------------------------+
   | 58          | Option refers twice to the same resource. The first    |
   |             | reference is used.                                     |
   +-------------+--------------------------------------------------------+
   | 59          | Stack inconsistency detected.                          |
   +-------------+--------------------------------------------------------+
   | 60          | Constant pool inconsistency detected.                  |
   +-------------+--------------------------------------------------------+
   | 61          | Corrupted classfile.                                   |
   +-------------+--------------------------------------------------------+
   | 62          | Missing native implementation of a native method.      |
   +-------------+--------------------------------------------------------+
   | 63          | Cannot read the specified resource file.               |
   +-------------+--------------------------------------------------------+
   | 64          | The same property name cannot be defined in two        |
   |             | different property files.                              |
   +-------------+--------------------------------------------------------+
   | 65          | Bad license validity.                                  |
   +-------------+--------------------------------------------------------+
   | 66          | Classfiles do not contain debug line table             |
   |             | information.                                           |
   +-------------+--------------------------------------------------------+
   | 67          | Same as 51.                                            |
   +-------------+--------------------------------------------------------+
   | 150         | SOAR limit reached: The specified method uses too many |
   |             | arguments.                                             |
   +-------------+--------------------------------------------------------+
   | 151         | SOAR limit reached: The specified method uses too many |
   |             | locals.                                                |
   +-------------+--------------------------------------------------------+
   | 152         | SOAR limit reached: The specified method code is too   |
   |             | large.                                                 |
   +-------------+--------------------------------------------------------+
   | 153         | SOAR limit reached: The specified method catches too   |
   |             | many exceptions.                                       |
   +-------------+--------------------------------------------------------+
   | 154         | SOAR limit reached: The specified method defines a     |
   |             | stack that is too large.                               |
   +-------------+--------------------------------------------------------+
   | 155         | SOAR limit reached: The specified type defines too     |
   |             | many methods.                                          |
   +-------------+--------------------------------------------------------+
   | 156         | SOAR limit reached: Your application defines too many  |
   |             | interfaces.                                            |
   +-------------+--------------------------------------------------------+
   | 157         | SOAR limit reached: The specified type defines too     |
   |             | many fields.                                           |
   +-------------+--------------------------------------------------------+
   | 158         | SOAR limit reached: your application defines too many  |
   |             | types.                                                 |
   +-------------+--------------------------------------------------------+
   | 159         | SOAR limit reached: Your application defines too many  |
   |             | static fields.                                         |
   +-------------+--------------------------------------------------------+
   | 160         | SOAR limit reached: The hierarchy depth of the         |
   |             | specified type is too high.                            |
   +-------------+--------------------------------------------------------+
   | 161         | SOAR limit reached: Your application defines too many  |
   |             | bundles.                                               |
   +-------------+--------------------------------------------------------+
   | 162         | SOAR limit reached: Your application defines too deep  |
   |             | interface hierarchies.                                 |
   +-------------+--------------------------------------------------------+
   | 163         | SOAR limit reached: Your application defines too many  |
   |             | cnocrete types.                                        |
   +-------------+--------------------------------------------------------+
   | 251         | Error in converting an IEE754 float(32) or double(64)  |
   |             | to a fixed-point arithmetic number                     |
   +-------------+--------------------------------------------------------+
   | 300         | Corrupted class: invalid dup_x1 instruction usage.     |
   +-------------+--------------------------------------------------------+
   | 301         | Corrupted class: invalid dup_x2 instruction usage.     |
   +-------------+--------------------------------------------------------+
   | 302         | Corrupted class:invalid dup_x2 instruction usage.      |
   +-------------+--------------------------------------------------------+
   | 303         | Corrupted class:invalid dup2_x1 instruction usage.     |
   +-------------+--------------------------------------------------------+
   | 304         | Corrupted class:invalid dup2_x1 instruction usage.     |
   +-------------+--------------------------------------------------------+
   | 305         | Corrupted class:invalid dup2_x2 instruction usage.     |
   +-------------+--------------------------------------------------------+
   | 306         | Corrupted class: invalid dup2 instruction usage.       |
   +-------------+--------------------------------------------------------+
   | 307         | Corrupted class:invalid pop2 instruction usage.        |
   +-------------+--------------------------------------------------------+
   | 308         | Corrupted class:invalid swap instruction usage.        |
   +-------------+--------------------------------------------------------+
   | 309         | Corrupted class: Finally blocks must be inlined.       |
   +-------------+--------------------------------------------------------+
   | 350         | SNI incompatibility: Some specified type should be an  |
   |             | array.                                                 |
   +-------------+--------------------------------------------------------+
   | 351         | SNI incompatibility: Some type should define some      |
   |             | specified field.                                       |
   +-------------+--------------------------------------------------------+
   | 352         | SNI incompatibility: The specified field is not        |
   |             | compatible with SNI.                                   |
   +-------------+--------------------------------------------------------+
   | 353         | SNI incompatibility: The specified type must be a      |
   |             | class.                                                 |
   +-------------+--------------------------------------------------------+
   | 354         | SNI incompatibility: The specified static field must   |
   |             | be defined in the specified type.                      |
   +-------------+--------------------------------------------------------+
   | 355         | SNI file error: The data must be an integer.           |
   +-------------+--------------------------------------------------------+
   | 356         | SNI file error : unexpected tag                        |
   +-------------+--------------------------------------------------------+
   | 357         | SNI file error : attributes <name>, <descriptor>,      |
   |             | <index> and <size> are expected in the specified tag.  |
   +-------------+--------------------------------------------------------+
   | 358         | SNI file error : invalid SNI tag value.                |
   +-------------+--------------------------------------------------------+
   | 359         | Error parsing the SNI file.                            |
   +-------------+--------------------------------------------------------+
   | 360         | XML Error on parsing the SNI file.                     |
   +-------------+--------------------------------------------------------+
   | 361         | SNI incompatibility : illegal call to the specified    |
   |             | data.                                                  |
   +-------------+--------------------------------------------------------+
   | 362         | No stack found for the specified native group.         |
   +-------------+--------------------------------------------------------+
   | 363         | Invalid SNI method: The argument cannot be an object   |
   |             | reference.                                             |
   +-------------+--------------------------------------------------------+
   | 364         | Invalid SNI method: The array argument must only be a  |
   |             | base type array.                                       |
   +-------------+--------------------------------------------------------+
   | 365         | Invalid SNI method: The return type must be a base     |
   |             | type.                                                  |
   +-------------+--------------------------------------------------------+
   | 366         | Invalid SNI method: The method must be static.         |
   +-------------+--------------------------------------------------------+
