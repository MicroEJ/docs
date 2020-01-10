SP Compiler
===========

Options
-------

.. table:: Shielded Plug Compiler Options.

   +-----------------------+-----------------------------------------------+
   | Option name           | Description                                   |
   +=======================+===============================================+
   | ``-verbose[e...e]``   | Extra messages are printed out to the console |
   |                       | according to the number of 'e'.               |
   +-----------------------+-----------------------------------------------+
   | ``-d                  | XML Shielded Plug description file. Multiple  |
   | escriptionFile file`` | files allowed.                                |
   +-----------------------+-----------------------------------------------+
   | ``-wai                | Maximum number of task/threads that can wait  |
   | tingTaskLimit value`` | on a block: a number between 0 and 7. -1 is   |
   |                       | for no limit; 8 is for unspecified.           |
   +-----------------------+-----------------------------------------------+
   | ``-immutable``        | When specified, only immutable Shielded Plugs |
   |                       | can be compiled.                              |
   +-----------------------+-----------------------------------------------+
   | ``-output dir``       | Output directory. Default is the current      |
   |                       | directory.                                    |
   +-----------------------+-----------------------------------------------+
   | ``-outputName name``  | Output name for the Shielded Plug layout      |
   |                       | description. Default is "shielded_plug".      |
   +-----------------------+-----------------------------------------------+
   | ``-endianness name``  | Either "little" or "big". Default is          |
   |                       | "little".                                     |
   +-----------------------+-----------------------------------------------+
   | ``-outpu              | Output ELF architecture. Only "ELF"           |
   | tArchitecture value`` | architecture is available.                    |
   +-----------------------+-----------------------------------------------+
   | ``-rwBl               | Read/Write header file value.                 |
   | ockHeaderSize value`` |                                               |
   +-----------------------+-----------------------------------------------+
   | ``-genIdsC``          | When specified, generate a C header file with |
   |                       | block ID constants.                           |
   +-----------------------+-----------------------------------------------+
   | ``-cOutputDir dir``   | Output directory of C header files. Default   |
   |                       | is the current directory.                     |
   +-----------------------+-----------------------------------------------+
   | ``-cCon               | C constants name prefix for block IDs.        |
   | stantsPrefix prefix`` |                                               |
   +-----------------------+-----------------------------------------------+
   | ``-genIdsJava``       | When specified, generate Java interfaces file |
   |                       | with block ID constants.                      |
   +-----------------------+-----------------------------------------------+
   | ``-jOutputDir dir``   | Output directory of Java interfaces files.    |
   |                       | Default is the current directory.             |
   +-----------------------+-----------------------------------------------+
   | ``-jPackage name``    | The name of the package for Java interfaces.  |
   +-----------------------+-----------------------------------------------+

Error Messages
--------------

.. table:: Shielded Plug Compiler Error Messages.

   +-------------+--------------------------------------------------------+
   | Message  ID | Description                                            |
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
