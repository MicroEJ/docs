Importing GitHub projects into MicroEJ SDK
==========================================

You may know that MicroEJ has an `account on GitHub <https://github.com/MicroEJ>`_. There, we share examples (like `examples for MWT <https://github.com/MicroEJ/ExampleJava-MWT>`_) libraries, tools and demos. In this article, we will explain how you can connect repositories from GitHub inside MicroEJ SDK.

Both MicroEJ Studio and MicroEJ SDK come with the EGit plugin built-in, so you can easily clone an existing repository. Here, we use the MWT Examples repository. From the GitHub page, you can copy the HTTP address of this repository from the dedicated field in the right menu (highlighted in red):

.. figure:: images/0-address-to-clone.png
   :alt: Address to clone
   :align: center
   :width: 1103px
   :height: 548px

In MicroEJ SDK, to clone and import the project from the remote Git repository into the MicroEJ workspace, go to :guilabel:`File` / :guilabel:`Import` / :guilabel:`Git` / :guilabel:`Projects from Git`.

.. figure:: images/1-import-type.png
   :alt: Import type
   :align: center
   :width: 520px
   :height: 553px

Click :guilabel:`Next`, select :guilabel:`Clone URI`, click :guilabel:`Next`, enter the address of the remote repository in the `URI` field. For this repository, the address is `<https://github.com/MicroEJ/ExampleJava-MWT.git>`_. If have already copied the HTTP address, the fields are filed automatically. 

.. figure:: images/2-location-to-clone.png
   :alt: Location to clone
   :align: center
   :width: 512px
   :height: 544px

Click :guilabel:`Next`, select the master branch, click :guilabel:`Next` and accept the proposed `Local Destination` by clicking :guilabel:`Next` once again.

.. figure:: images/3-local-destination.png
   :alt: Local destination
   :align: center
   :width: 513px
   :height: 544px

Click :guilabel:`Next` once more and finally :guilabel:`Finish`. The ``Package Explorer`` view now contains the projects !

.. figure:: images/4-projects-imported.png
   :alt: Projects imported
   :align: center
   :width: 447px
   :height: 534px

If you want to import projects from another GitHub repository, you simply have to do the same procedure for the desired repository.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
