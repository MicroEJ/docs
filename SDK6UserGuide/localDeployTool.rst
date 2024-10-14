.. _sdk6_localDeployTool:

=======================
Local Deployment Socket
=======================

Principle
=========

The Local Deployment Socket is a tool that allows to transfer an Application on the device over a network connection.

Functional Description
======================

The Local Deployment Socket builds the Application Feature file (``.fo``) and upload it on the device identified by its IP address. 
On the device, it is the job of the Kernel Application that receives the Feature file to install and to run the Application.

Use
===

.. code:: console

    ./gradlew execTool --name=localDeploymentSocket \
      --toolProperty="application.main.class=com.mycompany.MyFeature" \
      --toolProperty="kernel.filename=[path_to_application.out]" \
      --toolProperty="board.server.host=10.0.0.171" \
      --toolProperty="board.server.port=4000" \
      --toolProperty="board.timeout=120000" \
      --toolProperty="use.storage=true"

Options
=======

Option: Application Feature Class
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``application.main.class``

*Required?*: Yes

*Description*:

Specify the entry-point as the full qualified name of the Application to deploy.

Option: Kernel Executable
^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``kernel.filename``

*Required?*: Yes

*Description*:

Specify the Kernel Executable to use for building the Application Feature file.

Option: Server Host
^^^^^^^^^^^^^^^^^^^

*Option Name*: ``board.server.host``

*Required?*: Yes

*Description*:

The IP of the target device.

Option: Server Port
^^^^^^^^^^^^^^^^^^^

*Option Name*: ``board.server.port``

*Required?*: Yes

*Description*:

The TCP port on which the Kernel listens (usually 4000).

Option: Timeout
^^^^^^^^^^^^^^^

*Option Name*: ``board.timeout``

*Required?*: Yes

*Description*:

If there is no activity within the defined timeout period (in seconds), the tool will disconnect from the device.

Option: Use Storage
^^^^^^^^^^^^^^^^^^^

*Option Name*: ``use.storage``

*Required?*: Yes

*Description*:

A boolean describing whether to use the storage to store the Application or not.
Refer to the Kernel documentation to find out the correct setting.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
