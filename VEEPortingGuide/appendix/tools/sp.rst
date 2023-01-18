SP Compiler
===========

Options
-------

.. table:: Shielded Plug Compiler Options.

   +-------------------------------+-----------------------------------------------+
   | Option name                   | Description                                   |
   +===============================+===============================================+
   | ``-verbose[e...e]``           | Extra messages are printed out to the console |
   |                               | according to the number of 'e'.               |
   +-------------------------------+-----------------------------------------------+
   | ``-descriptionFile file``     | XML Shielded Plug description file. Multiple  |
   |                               | files allowed.                                |
   +-------------------------------+-----------------------------------------------+
   | ``-waitingTaskLimit value``   | Maximum number of task/threads that can wait  |
   |                               | on a block: a number between 0 and 7. -1 is   |
   |                               | for no limit; 8 is for unspecified.           |
   +-------------------------------+-----------------------------------------------+
   | ``-immutable``                | When specified, only immutable Shielded Plugs |
   |                               | can be compiled.                              |
   +-------------------------------+-----------------------------------------------+
   | ``-output dir``               | Output directory. Default is the current      |
   |                               | directory.                                    |
   +-------------------------------+-----------------------------------------------+
   | ``-outputName name``          | Output name for the Shielded Plug layout      |
   |                               | description. Default is "shielded_plug".      |
   +-------------------------------+-----------------------------------------------+
   | ``-endianness name``          | Either "little" or "big". Default is          |
   |                               | "little".                                     |
   +-------------------------------+-----------------------------------------------+
   | ``-outputArchitecture value`` | Output ELF architecture. Only "ELF"           |
   |                               | architecture is available.                    |
   +-------------------------------+-----------------------------------------------+
   | ``-rwBlockHeaderSize value``  | Read/Write header file value.                 |
   +-------------------------------+-----------------------------------------------+
   | ``-genIdsC``                  | When specified, generate a C header file with |
   |                               | block ID constants.                           |
   +-------------------------------+-----------------------------------------------+
   | ``-cOutputDir dir``           | Output directory of C header files. Default   |
   |                               | is the current directory.                     |
   +-------------------------------+-----------------------------------------------+
   | ``-cConstantsPrefix prefix``  | C constants name prefix for block IDs.        |
   +-------------------------------+-----------------------------------------------+
   | ``-genIdsJava``               | When specified, generate Java interfaces file |
   |                               | with block ID constants.                      |
   +-------------------------------+-----------------------------------------------+
   | ``-jOutputDir dir``           | Output directory of Java interfaces files.    |
   |                               | Default is the current directory.             |
   +-------------------------------+-----------------------------------------------+
   | ``-jPackage name``            | The name of the package for Java interfaces.  |
   +-------------------------------+-----------------------------------------------+

Error Messages
--------------

.. table:: Shielded Plug Compiler Error Messages.

   +-------------+--------------------------------------------------------+
   | Message  ID | Description                                            |
   +=============+========================================================+
   | 0           | Internal limits reached.                               |
   +-------------+--------------------------------------------------------+
   | 1           | Invalid endianness.                                    |
   +-------------+--------------------------------------------------------+
   | 2           | Invalid output architecture.                           |
   +-------------+--------------------------------------------------------+
   | 3           | Error while reading / writing files.                   |
   +-------------+--------------------------------------------------------+
   | 4           | Missing a mandatory option.                            |
   +-------------+--------------------------------------------------------+

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
