.. warning::

  This documentation is for SDK 5. The latest major version is :ref:`SDK 6 <sdk_6_user_guide>`.
  SDK 5 is in maintenance mode since the release of :ref:`SDK 5.8.0 <changelog-5.8.0>`.
  Consequently, as stated in the :ref:`SDK End User License Agreement (EULA) <sdk_eula>`, the SDK will reach the end of its life by July 2028.
  Contact :ref:`our support team <get_support>` for assistance with migrating to the new SDK, or your sales representative if you require an extension of SDK maintenance as a service.

.. _MicroEJToolsSection:

Development Tools
#################

MicroEJ provides a number of tools to assist with various
aspects of development. Some of these tools are run using MicroEJ Tool
configurations, and created using the Run Configurations dialog of the
MicroEJ SDK. A configuration must be created for the tool before it can be
used.

.. _fig_tool-launch:
.. figure:: images/tool-launch.png
   :alt: MicroEJ Tool Configuration
   :align: center
   :width: 863px
   :height: 702px

   MicroEJ Tool Configuration

:ref:`The above figure <fig_tool-launch>` shows a tool configuration
being created. In the figure, the MicroEJ Platform has been selected,
but the selection of which tool to run has not yet been made. That
selection is made in the Execution Settings... box. The Configuration
tab then contains the options relevant to the selected tool.

.. toctree::
   :maxdepth: 2

   testsuite
   stackTraceReader
   codeCoverageAnalyzer
   heapAnalyzer   
   serialToSocketTransmitter
   memoryMapAnalyzer
   nullAnalysis

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
