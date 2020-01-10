Functional Description
======================

.. figure:: nls/images/process.svg
   :alt: Native Language Support Process
   :width: 100.0%

   Native Language Support Process

The header and message names are specified by an interface. The name of
the interface is the *header*. It defines a constant
(``public static final int``) for each message. The name of the field is
the *message name*. The values of the fields must form a contiguous
range of integers starting at 1. Here is an example:

.. code:: java

   package com.is2t.appnotes.nls;

   public interface HelloWorld {

       public static final int HELLO_WORLD = 1;

   }

The application can define multiple headers, each specified by a
separate interface.

For each locale, a properties file is defined that will translate all
messages and define the language-printable name ( ``DISPLAY_NAME`` ).
Make sure that:

-  The file name matches ``[header]_[locale].nls``.

-  The message keys match (case sensitive) the constants defined in the
   interface.

An example of English NLS file, ``helloworld_en_US.nls``:

.. code:: properties

   DISPLAY_NAME=English
   HELLO_WORLD=Hello world!

To be available at runtime, the list of messages must be defined in a
file that contains the list of the fully-qualified names of the
interfaces for the messages set. For example:

::

   com.is2t.appnotes.nls.HelloWorld

This file must then be referenced in the launcher. The messages will be
pre-processed into immutable files.

The use of these messages (converted into immutables) is allowed by
creating a ``BasicImmutablesNLS`` instance that passes the lowercased
``header`` name as an argument:

.. code:: java

   NLS nls = new BasicImmutablesNLS("helloworld");

The messages can then be referenced by using the ``NLS.getMessage(int)``
method passing a message constant as an argument:

.. code:: java

   String message = nls.getMessage(HelloWorld.HELLO_WORLD);

The current locale can be changed using the
``NLS.setCurrentLocale(String)`` method passing the string representing
the locale as an argument:

.. code:: java

   nls.setCurrentLocale("en_US");

The available locales list can be retrieved with the
``NLS.getAvailableLocales()`` method:

.. code:: java

   String[] locales = nls.getAvailableLocales();
