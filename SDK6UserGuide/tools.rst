.. _sdk6_microejtools:

Development Tools
#################

MicroEJ provides a number of tools to assist with various aspects of development.
These tools are either command line tools or Eclipse IDE plugins.

**Command line tools**

Command line tools can be executed using the gradle task ``:execTool``.

The format of the task is as follow:

::

   gradle :execTool --name=TOOL_NAME --toolProperty="PROPERTY=VALUE" --toolProperty="PROPERTY=VALUE" ...

The parameter required ``--name`` is used to describe the name of the tool to execute.
The optional parameters ``--toolProperty`` are used to configure the tool's options.

In addition, the tool's options can be defined in ``configuration/tools/TOOL_NAME.properties``.

The following sections describe the command line tools and their options:

.. toctree::
   :maxdepth: 1

   stackTraceReader
   codeCoverageAnalyzer


**IDE tools**

Eclipse IDE tools are graphical tools which are available as Eclipse plugins: Memory Map Analyzer, Heap Analyzer and Font Designer.

Follow these steps to install the latest stable version of these tools:
            
         - Install `Eclipse IDE for Java Developers <https://www.eclipse.org/downloads/packages/>`__ - Minimum supported version is ``2022-03``.
         - In Eclipse, go to :guilabel:`Help` > :guilabel:`Eclipse Marketplace...`.
         - In the :guilabel:`Find` field, type ``MicroEJ Tools``, then press ``Enter``.
         - Click on the :guilabel:`Install` button of the ``MicroEJ Tools`` plugin.
         - Accept the license, then click on the :guilabel:`Finish` button.
         - In the upcoming :guilabel:`Trust Artifacts` window, check the :guilabel:`Unsigned` item and click on :guilabel:`Trust Selected` button.
            
         .. figure:: images/eclipse-trust-microej-tools-plugin.png
            :alt: Eclipse Plugin Installation - Trust Artifacts
            :align: center
            :scale: 70%
         
            Eclipse Plugin Installation - Trust Artifacts
            
         - In the upcoming window, click on the :guilabel:`Restart Now` button.

The following sections describe the IDE tools and their options:

.. toctree::
   :maxdepth: 1

   memoryMapAnalyzer
   heapAnalyzer
   ../ApplicationDeveloperGuide/UI/MicroUI/fontDesigner
   localDeployTool
   nullAnalysis

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
