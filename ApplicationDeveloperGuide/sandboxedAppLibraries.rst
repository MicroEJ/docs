.. _chapter.application.useLibrary:

Use a Library
=============

An Application can use libraries.
The SDK provides 2 ways to make such libraries available to the Application:

- add it as a dependency in the Module descriptor file,
- add the library JAR file in the ``META-INF/libraries`` folder of the Application.

Add a library as a dependency
-----------------------------

Libraries used by the Application can be added as dependencies in Module descriptor file, 
by inserting a ``dependency`` tag in the ``dependencies`` block.
For example::

    <dependencies>
        <dependency org="ej.api" name="bon" rev="1.4.0" />
    </dependencies>

Add a library in META-INF/libraries folder
------------------------------------------

When the library used by the Application is not available in a module repository, 
its JAR file can be directly added in the ``META-INF/libraries`` folder of the Application project.
It is then automatically added in the compilation classpath and is available for the Application.

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
