.. _sdk6_tool_kernel_api_generator:

====================
Kernel API Generator
====================


Principle
=========

The Kernel API Generator is a tool that helps to generate a :ref:`kernel.api file <kernel.api>` based on a Java classpath.

Use
===

To generate the ``kernel.api`` file, make sure to compile all the project Java sources (by running the ``build`` task for example),
then execute the ``execTool`` task as followed:

.. code:: console

    ./gradlew execTool --name=kernelAPIGenerator \
      --toolProperty=kernel.api.generator.classpath="C:/my-kernel/build/classes/java/main"  \
      --toolProperty=output.dir="C:/my-kernel/build" \
      --toolProperty=kernel.api.generator.includes.patterns="**/*.class" \
      --toolProperty=kernel.api.generator.excludes.patterns="" \
      --console plain

The ``kernel.api`` file is generated in the folder defined by the ``output.dir`` property.

.. warning::

  The folder specified by the ``output.dir`` must exist, it is not automatically created.
  If the folder does not exist, the ``kernel.api`` file is not generated and the execution silently ends (no warning or error message).

Options
=======

Java classpath
^^^^^^^^^^^^^^

*Option Name*: ``kernel.api.generator.classpath``

*Default value*: No default value, this option is required.

*Description*: List of the paths of the JAR files or folders containing Java class files, for example ``C:/folder1/lib.jar;C:/folder2``.



Destination directory path
^^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``output.dir``

*Default value*: No default value, this option is required.

*Description*: Absolute path of the destination directory of the generated ``kernel.api`` files. 
It is important to note that this folder must exist.


Pattern of the classes to include
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``kernel.api.generator.includes.patterns``

*Default value*: ``**/*.class`` (which means all the classes).

*Description*: Ant-style pattern of the classes to include.

Pattern of the classes to exclude
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``kernel.api.generator.excludes.patterns``

*Default value*: Empty (which means no excluded classes).

*Description*: Ant-style pattern of the classes to exclude.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
