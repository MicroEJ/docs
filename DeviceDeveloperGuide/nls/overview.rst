Principle
=========

The NLS library facilitates internationalization. It provides support to
manipulate messages and translate them into different languages.

Each message for which there will be an alternative translation is given
a logical name (the *message name* ), and the set of messages is itself
identified by a name, called the *header*.

Each language for which message translations exist is identified by a
string called the *locale*. The format of the locale string is not
restricted, but by convention it is the concatenation of a language code
and a country code:

-  The language code is a lowercase, two-letter code as defined by
   ISO-639.

-  The country code is an uppercase, two-letter code as defined by
   ISO-3166.

Therefore, the required message string is obtained by specifying the
*header*, the *locale* and the *message name*.

The NLS data is defined using a combination of interfaces and text
files. The message strings are pre-processed into immutable objects,
which are available to the NLS library at runtime.
