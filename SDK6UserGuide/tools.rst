.. _sdk6_microejtools:

Development Tools
#################

MicroEJ provides a number of tools to assist with various aspects of development.
This tools can be executed using the gradle task ``:execTool``.

The format of the task is as follow:

::

   gradle :execTool --name=TOOL_NAME --toolProperty="PROPERTY=VALUE" --toolProperty="PROPERTY=VALUE" ...

The parameter required ``--name`` is used to describe the name of the tool to execute.
The optional parameters ``--toolProperty`` are used to configure the tool's options.

In addition, the tool's options can be defined in ``configuration/tools/TOOL_NAME.properties``.

The next sections describe the tools and their options.

.. toctree::
   :maxdepth: 1

   stackTraceReader

..
   | Copyright 2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
