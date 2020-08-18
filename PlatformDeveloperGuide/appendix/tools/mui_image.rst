.. _image_gen_tool:

Image Generator
===============

Configuration File
------------------

::

   ConfigFile          ::= Line [ 'EOL' Line ]*
   Line                ::= ImagePath [ ':' ImageOption ]*
   ImagePath           ::= Identifier [ '/' Identifier ]*
   ImageOption         ::= [^:]*
   Identifier          ::= Letter [ LetterOrDigit ]*
   Letter              ::= 'a-zA-Z_$'
   LetterOrDigit       ::= 'a-zA-Z_$0-9'

Error Messages
--------------

.. tabularcolumns:: |L|p{1.5cm}|L|

.. table:: Static Image Generator Error Messages

   +--------+---------+-----------------------------------------------------+
   | ID     | Type    | Description                                         |
   +========+=========+=====================================================+
   | 0      | Error   | The image generator has encountered an              |
   |        |         | unexpected internal error.                          |
   +--------+---------+-----------------------------------------------------+
   | 1      | Error   | The images list file has not been specified.        |
   +--------+---------+-----------------------------------------------------+
   | 2      | Error   | The image generator cannot create the final,        |
   |        |         | raw file.                                           |
   +--------+---------+-----------------------------------------------------+
   | 3      | Error   | The image generator cannot read the images          |
   |        |         | list file. Make sure the system allows reading of   |
   |        |         | this file.                                          |
   +--------+---------+-----------------------------------------------------+
   | 4      | Warning | The image generator has found no image to           |
   |        |         | generate.                                           |
   +--------+---------+-----------------------------------------------------+
   | 5      | Error   | The image generator cannot load the images          |
   |        |         | list file.                                          |
   +--------+---------+-----------------------------------------------------+
   | 6      | Warning | The specified image path is invalid: The image will |
   |        |         | be not converted.                                   |
   +--------+---------+-----------------------------------------------------+
   | 7      | Warning | There are too many or too few options for the       |
   |        |         | desired format.                                     |
   +--------+---------+-----------------------------------------------------+
   | 8      | Error   | The display format is not generic; a                |
   |        |         | MicroUIRawImageGeneratorExtension implementation is |
   |        |         | required to generate the MicroUI raw image.         |
   +--------+---------+-----------------------------------------------------+
   | 9      | Error   | The image cannot be read.                           |
   +--------+---------+-----------------------------------------------------+
   | 10     | Error   | The image generator has encountered an              |
   |        |         | unexpected internal error (invalid endianness).     |
   +--------+---------+-----------------------------------------------------+
   | 11     | Error   | The image generator has encountered an              |
   |        |         | unexpected internal error (invalid bpp).            |
   +--------+---------+-----------------------------------------------------+
   | 12     | Error   | The image generator has encountered an              |
   |        |         | unexpected internal error (invalid display format). |
   +--------+---------+-----------------------------------------------------+
   | 13     | Error   | The image generator has encountered an              |
   |        |         | unexpected internal error (invalid pixel layout).   |
   +--------+---------+-----------------------------------------------------+
   | 14     | Error   | The image generator has encountered an              |
   |        |         | unexpected internal error (invalid output folder).  |
   +--------+---------+-----------------------------------------------------+
   | 15     | Error   | The image generator has encountered an              |
   |        |         | unexpected internal error (invalid memory           |
   |        |         | alignment).                                         |
   +--------+---------+-----------------------------------------------------+
   | 16     | Warning | The specified format is not managed by the          |
   |        |         | image generator: The image will be not converted.   |
   +--------+---------+-----------------------------------------------------+
   | 17     | Warning | The image has been already loaded with another      |
   |        |         | output format. The image will be not converted.     |
   +--------+---------+-----------------------------------------------------+

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
