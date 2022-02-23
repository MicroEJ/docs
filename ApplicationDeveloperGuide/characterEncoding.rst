Character Encoding
==================

The default charset is `ISO-8859-1`. It is thus the encoding used when

-  creating a new string from a byte array without specifying the charset;

-  getting the byte array from a string without specifying the charset;

-  printing a string to standard output stream;

-  creating a new ``PrintStream`` without stecifying the charset.

Console Output
--------------

By default, the standard output stream (``System.out``) uses `ISO-8859-1` charset to print strings. If you want to print an string encoded with a different charset, you can define a new ``PrintStream``:

.. code-block:: java

    PrintStream outUtf8 = new PrintStream(System.out, true, "UTF-8");
    outUtf8.println("你好");

.. warning::

    Make sure you embed `UTF-8` when using this charset. Otherwise a ``java.io.UnsupportedEncodingException`` exception will be thrown. See :ref:`how to set embed UTF-8 option<option_embed_utf8>`.

The print methods only write the raw byte array encoded with the charset used by the ``PrintStream`` to the console. The console must then be configured with the right encoding to display characters properly.

Set Encoding in MicroEJ SDK Console
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The defaut encoding for consoles is `UTF-8`. If your application prints non-ASCII characters, they may not be displayed properly.

The encoding used by a console for a given application can be set in the application launch options: :guilabel:`Run` > :guilabel:`Run Configurations...`, and then :guilabel:`Common` tab > :guilabel:`Encoding` radio buttons.

.. figure:: images/eclipse_encoding.png
      :alt: Ecoding Selection in Eclipse
      :align: center
      :width: 786px
      :height: 633px

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.