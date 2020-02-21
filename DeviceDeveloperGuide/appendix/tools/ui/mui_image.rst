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
   | 0      | Error   | The static image generator has encountered an       |
   |        |         | unexpected internal error.                          |
   +--------+---------+-----------------------------------------------------+
   | 1      | Error   | The images list file has not been specified.        |
   +--------+---------+-----------------------------------------------------+
   | 2      | Error   | The static image generator cannot create the final, |
   |        |         | raw file.                                           |
   +--------+---------+-----------------------------------------------------+
   | 3      | Error   | The static image generator cannot read the images   |
   |        |         | list file. Make sure the system allows reading of   |
   |        |         | this file.                                          |
   +--------+---------+-----------------------------------------------------+
   | 4      | Warning | The static image generator has found no image to    |
   |        |         | generate.                                           |
   +--------+---------+-----------------------------------------------------+
   | 5      | Error   | The static image generator cannot load the images   |
   |        |         | list file.                                          |
   +--------+---------+-----------------------------------------------------+
   | 6      | Warning | The specified image path is invalid: The image will |
   |        |         | be not converted.                                   |
   +--------+---------+-----------------------------------------------------+
   | 7      | Warning | There are too many or too few options for the       |
   |        |         | desired format.                                     |
   +--------+---------+-----------------------------------------------------+
   | 8      | Error   | A static image generator extension class is         |
   |        |         | unknown.                                            |
   +--------+---------+-----------------------------------------------------+
   | 9      | Error   | The static image generator has encountered an       |
   |        |         | unexpected internal error.                          |
   +--------+---------+-----------------------------------------------------+
   | 10     | Warning | The specified output format is unknown: The image   |
   |        |         | will be not converted.                              |
   +--------+---------+-----------------------------------------------------+
   | 11     | Warning | The specified format is not managed by the static   |
   |        |         | image generator: The image will be not converted.   |
   +--------+---------+-----------------------------------------------------+
   | 12     | Warning | The specified alpha level is invalid: The image     |
   |        |         | will be not converted.                              |
   +--------+---------+-----------------------------------------------------+
   | 13     | Warning | The specified alpha level is not compatible with    |
   |        |         | the specified format: The image will be not         |
   |        |         | converted.                                          |
   +--------+---------+-----------------------------------------------------+
   | 14     | Warning | A specified attribute is undefined for the          |
   |        |         | specified format.                                   |
   +--------+---------+-----------------------------------------------------+
