Character Encoding
==================

The default character encoding is `ISO-8859-1`. It is thus the encoding used when

-  creating a new string from a byte array without specifying the encoding;

-  getting the byte array from a string without specifying the encoding;

-  printing a string to standard output stream;

-  creating a new ``PrintStream`` without specifying the encoding.

Console Output
--------------

By default, the standard output stream (``System.out``) uses `ISO-8859-1` encoding to print strings. If you want to print a string with a different encoding, you can create a new ``PrintStream``:

.. code-block:: java

    PrintStream outUtf8 = new PrintStream(System.out, true, "UTF-8");
    outUtf8.println("你好");

.. warning::

    Make sure you embed the `UTF-8` encoder. Otherwise a ``java.io.UnsupportedEncodingException`` exception will be thrown. See :ref:`how to set embed UTF-8 option<option_embed_utf8>`.

The print methods write the raw byte array with the encoding used by the ``PrintStream`` to the console. The console must then be configured with the same encoding to display characters properly.

.. _set_console_encoding:

Set Encoding in MicroEJ SDK Console
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The default encoding for consoles is `UTF-8`. If your application prints non-ASCII characters, they may not be displayed properly.

The encoding used by a console for a given application can be set in the application launch options: :guilabel:`Run` > :guilabel:`Run Configurations...`, and then :guilabel:`Common` tab > :guilabel:`Encoding` radio buttons.

.. figure:: images/eclipse_encoding.png
      :alt: Encoding Selection in Eclipse
      :align: center
      :width: 786px
      :height: 633px

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.