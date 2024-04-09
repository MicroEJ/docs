.. _sdk6.section.code_coverage_analyzer:

======================
Code Coverage Analyzer
======================


Principle
=========

The Simulator features an option to output ``.cc`` (Code Coverage)
files that represent the use rate of functions of an application. It
traces how the opcodes are really executed.

Functional Description
======================

The Code Coverage Analyzer scans the output ``.cc`` files, and outputs an
HTML report to ease the analysis of methods coverage. The HTML report is
available in a folder named htmlReport in the same folder as the .cc
files.

Dependencies
============

In order to work properly, the Code Coverage Analyzer should input the ``.cc`` files (See :ref:`sdk_6_generate_code_coverage`).
The ``.cc`` files rely on the classpath used during the execution of the Simulator to the Code Coverage Analyzer.
Therefore the classpath is considered to be a dependency of the Code Coverage Analyzer.

Installation
============

This tool is a built-in Architecture tool.

Use
===

A MicroEJ tool is available to launch the Code Coverage Analyzer tool.
The tool name is Code Coverage Analyzer.

Two levels of code analysis are provided, the Java level and the
bytecode level. Also provided is a view of the fully or partially
covered classes and methods. From the HTML report index, just use
hyperlinks to navigate into the report and source / bytecode level code.

::

   ./gradlew execTool --name=codeCoverageAnalyzer \
       --toolProperty="cc.dir=/MODULE_PATH/build/output/com.company.Main/cc/" \
       --toolProperty="cc.includes=com.company.*" \
       --toolProperty="cc.excludes=" \
       --toolProperty="cc.src.folders=/MODULE_PATH/src" \
       --toolProperty="cc.html.dir=/MODULE_PATH/cc"

Options
=======

Option: \*.cc files folder
^^^^^^^^^^^^^^^^^^^^^^^^^^


*Option Name*: ``cc.dir``

*Description*:

Specify a folder which contains the cc files to process (\*.cc).

Option: Source Folders
^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``cc.src.folders``

*Description*:

A list of folders to the source files.

Option: HTML Dir
^^^^^^^^^^^^^^^^

*Option Name*: ``cc.html.dir``

*Description*:

The output directory for the HTML report.

Option: Includes
^^^^^^^^^^^^^^^^

*Option Name*: ``cc.includes``

*Description*:

List packages and classes to include to code coverage report (``;`` separated).
If no package/class is specified, all classes found in the project classpath
will be analyzed.

Examples:


``packageA.packageB.*``: includes all classes which are in package
``packageA.packageB``


``packageA.packageB.className``: includes the class
``packageA.packageB.className``

Option: Excludes
^^^^^^^^^^^^^^^^

*Option Name*: ``cc.excludes``

*Description*:

List packages and classes to exclude to code coverage report (``;`` separated).
If no package/class is specified, all classes found in the project classpath
will be analyzed.

Examples:


``packageA.packageB.*``: excludes all classes which are in package
``packageA.packageB``


``packageA.packageB.className``: excludes the class
``packageA.packageB.className``

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
