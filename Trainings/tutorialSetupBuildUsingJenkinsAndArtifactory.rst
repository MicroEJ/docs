
.. _tutorial_setup_automated_build_using_jenkins_and_artifactory:

Setup an Automated Build using Jenkins and Artifactory
======================================================

Description
-----------

Such environment setup facilitates continuous integration (CI) and continuous delivery (CD), which improves productivity across your development ecosystem,
by automatically:

* building modules when source code changes
* saving build results
* reproducing builds
* archiving binary modules

This guide should take 1 hour to complete.


Intended Audience
-----------------

The audience for this document is engineers who are in charge of integrating `MICROEJ SDK 6 <https://docs.microej.com/en/latest/SDK6UserGuide/index.html#>`_ to their continuous integration environment.

In addition, this document should be of interest to all developers wishing to understand how MicroEJ works with headless module builds.

Prerequisites
-------------

*  An internet connection.
*  `Docker and Docker Compose V2 <https://docs.docker.com/>`_ on Linux, Windows or Mac
*  Git ``2.x`` installed, with Git executable in path. We recommend installing Git Bash if your operating system is Windows (`<https://gitforwindows.org/>`_).

This training was tested with Jenkins ``2.462.3``, Artifactory ``7.71.5`` and Gitea ``1.23.4``.

.. note::
    For `SDK 5 <https://docs.microej.com/en/latest/SDKUserGuide/index.html>`_, please refer to this `MicroEJ Documentation Archive <https://docs.microej.com/_/downloads/en/20240215/pdf/>`_, section ``9.6 Setup an Automated Build using Jenkins and Artifactory``.

Introduction
------------

The overall build and deployment flow of a module can be summarized as follows:

#. Some event triggers the build process (i.e module source changed, user action, scheduled routine, etc.)
#. The module source code is retrieved from the Source Control System
#. The module dependencies are imported from the Repository Manager
#. The Automation Server then proceeds to building the module
#. If the build is successful, the module binary is deployed to the Repository Manager

.. image:: images/tuto_microej_cli_flow.PNG
    :align: center


Overview
--------

The next sections describe step by step how to setup the build environment and build your first MicroEJ module.

The steps to follow are:

#. Run and setup Jenkins, Artifactory and Gitea
#. Create a simple MicroEJ module (Hello World)
#. Create a new Jenkins job for the Hello World module
#. Build the module

In order to simplify the steps, this training will be performed locally on a single machine.

Artifactory will host MicroEJ modules in 3 repositories:

- ``microej-module-repository``: repository initialized with pre-built MicroEJ modules, a mirror of the :ref:`Central Repository <central_repository>`
- ``custom-modules-snapshot``: repository where custom snapshot modules will be published
- ``custom-modules-release``: repository where custom release modules will be published


Prepare your Docker environment
-------------------------------

This section assumes the prerequisites have been properly installed.

#. Create a new directory, inside create a file named ``docker-compose.yaml`` and copy this content: 

    .. literalinclude:: resources/docker-compose.yaml
        :language: yaml

#. Create another file named ``Dockerfile`` and copy this content: 

    .. literalinclude:: resources/Dockerfile
        :language: dockerfile

#. In this directory, launch the command ``docker compose up -d``. After a few moments you should have three running containers (named jenkins, gitea and artifactory). 

Using ``docker compose ps`` will show if containers started properly. Logs can be viewed with ``docker compose logs``. 


.. _get_microej_module_repository:

Get a Module Repository
-----------------------

A Module Repository is a portable ZIP file that bundles a set of modules for extending the MicroEJ development environment.
Please consult the :ref:`Module Repository <module_repository>` section for more information.

This training uses the MicroEJ Central Repository, which is the Module Repository used by MICROEJ SDK to fetch dependencies when starting an empty workspace. 
It bundles Foundation Library APIs and numerous Add-On Libraries.

Next step is to download a local copy of this repository:

#. Visit the `Central Repository <https://developer.microej.com/central-repository/>`_ on the MicroEJ Developer website.
#. Navigate to the :guilabel:`Production Setup` section.
#. Click on the :guilabel:`offline repository` link. This will download the Central Repository as a ZIP file.

Setup Artifactory
-----------------

Configure Artifactory
~~~~~~~~~~~~~~~~~~~~~

For demonstration purposes we will allow anonymous users to deploy modules in the repositories:

#. Once Artifactory container is started, go to ``http://localhost:8082/``.
#. Login to Artifactory for the first time using the default ``admin`` account (Username: ``admin``, Password: ``password``).
#. Skip the installation wizard if it appears.
#. Go to :guilabel:`Administration` > :guilabel:`User Management` > :guilabel:`Settings`.
#. In the :guilabel:`User Security Configuration` section, check :guilabel:`Allow Anonymous Access`.
#. Click on :guilabel:`Save`.
#. Go to :guilabel:`Administration` > :guilabel:`User Management` > :guilabel:`Permissions`.
#. Click on :guilabel:`Anything` entry (do not check the line), then go to :guilabel:`Users` tab
#. Click on :guilabel:`anonymous` and check :guilabel:`Deploy/Cache` permission in the :guilabel:`Selected Users Repositories` category.
#. Click on :guilabel:`Save`.

Next steps will involve uploading large files, so we have to increase the file upload maximum size accordingly:

#. Go to :guilabel:`Administration` > :guilabel:`Artifactory` > :guilabel:`General` > :guilabel:`Settings`.
#. In the :guilabel:`General Settings` section, change the value of :guilabel:`File Upload In UI Max Size (MB)` to ``1024`` then click on :guilabel:`Save`.


Create Repositories
~~~~~~~~~~~~~~~~~~~

We will now create and configure the repositories. Let's start with the repository for the future built snapshot modules:

#. Go to :guilabel:`Administration` > :guilabel:`Repositories` > :guilabel:`Repositories` in the left menu.
#. Click on :guilabel:`Add Repositories` > :guilabel:`Local Repository`
#. Select :guilabel:`Maven`.
#. Set :guilabel:`Repository Key` field to ``custom-modules-snapshot`` and click on :guilabel:`Create Local Repository`.

Repeat the same steps for the other repositories with the :guilabel:`Repository Key` field set to ``custom-modules-release`` and ``microej-module-repository``.


Import MicroEJ Repositories
~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this section, we will import MicroEJ repositories into Artifactory repositories to make them available to the build server.

#. Go to :guilabel:`Administration` > :guilabel:`Artifactory` > :guilabel:`Import & Export` > :guilabel:`Repositories`.
#. Scroll to the :guilabel:`Import Repository from Zip` section.
#. As :guilabel:`Target Local Repository`, select ``microej-module-repository`` in the list.
#. Click on :guilabel:`Select file` and select the MicroEJ module repository zip file (``central-repository-[version].zip``) that you downloaded earlier (please refer to section :ref:`get_microej_module_repository`).
#. Click :guilabel:`Upload`. At the end of upload, click on :guilabel:`Import`. Upload and import may take some time.

Artifactory is now hosting all required MicroEJ modules. 
Go to :guilabel:`Application` > :guilabel:`Artifactory` > :guilabel:`Artifacts` and check that the repository ``microej-module-repository`` does contain modules as shown in the figure below.

.. image:: images/tuto_microej_cli_artifactory_module_preview.PNG
    :align: center

Setup Gitea
-----------

Install Gitea
~~~~~~~~~~~~~
#. Once the Gitea container is started, go to ``http://localhost:3000/``.
#. Don't change anything on the ``Initial Configuration``, click on :guilabel:`Install Gitea`
#. Click on :guilabel:`Register account` and create one. The first created user become the administrator.

Configure Gitea
---------------

#. At the top right click on the arrow then :guilabel:`New Repository`
#. As :guilabel:`Repository Name` set ``helloworld``, leave the other options as default.
#. Click :guilabel:`Create Repository`. 


Setup Jenkins
-------------

Install Jenkins
~~~~~~~~~~~~~~~

#. Once Jenkins container is started, go to ``http://localhost:8080/``.
#. To unlock Jenkins, copy/paste the generated password that has been written in the container log. Click on :guilabel:`Continue`.
#. Select option :guilabel:`Install suggested plugins` and wait for plugins
   installation.
#. Fill in the :guilabel:`Create First Admin User` form. Click :guilabel:`Save and continue`.
#. Click on :guilabel:`Save and finish`, then on :guilabel:`Start using Jenkins`.

Configure Jenkins
~~~~~~~~~~~~~~~~~

#. Go to :guilabel:`Manage Jenkins` > :guilabel:`Plugins`.
#. Add Docker Pipeline plugin:
    #. Go to :guilabel:`Available plugins` section.
    #. Search `Docker Pipeline`.
    #. Install it and restart Jenkins


Build a new Module using Jenkins
--------------------------------

Since your environment is now setup, it is time to build your first module from Jenkins and check it has been published to Artifactory. 
Let’s build an "Hello World" Sandboxed Application project.

Create a new MicroEJ Module
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Now we will create an Application project that we'll push to a Git repository. In this example, we will use a plublic template but you can create an application
project from scratch with the :ref:`sdk_6_user_guide`.

.. note::
   For demonstration purposes, we'll create a new project and share it on a local Git bare repository.
   You can adapt the following sections to use an existing MicroEJ project and your own Git repository.

#. Clone https://github.com/MicroEJ/Tool-Project-Template-Application repository.
#. Go to the repository directory and type the following commands (replace ``<admin_user>`` by Gitea user)

   .. code-block:: sh
    
      git remote rename origin old-origin
      git remote add origin http://localhost:3000/<admin_user>/helloworld.git
      git push --set-upstream origin --all

.. note::
   We need the IP address of the Docker Bridge Network, here we consider that it's ``172.17.0.1`` but you can check with the command ``ip addr show docker0`` on the Docker host.

#. On the project directory, create a file named ``Jenkinsfile`` and copy this content inside:

    .. literalinclude:: resources/Jenkinsfile
        :language: groovy

#. Update ``build.gradle.kts`` file and set line 20 with this text. Building or running an Application with the SDK requires a VEE Port, so we use RT1170 Vee Port for this example:
    
    .. code-block::

        microejVee("com.nxp.vee.mimxrt1170:evk_platform:2.2.0")


#. Create a file named ``init.gradle.kts`` and copy this content inside: 

    .. literalinclude:: resources/init.gradle.kts
        :language: xml

This file configures the MicroEJ Module Manager to import and publish modules from the Artifactory repositories described in this training. Please refer to the :ref:`mmm_settings_file` section for more details.

    .. note::
       At this point, the content of the directory ``Tool-Project-Template-Application`` should look like the following:
       ::
    
        ├── build.gradle.kts
        ├── CHANGELOG.md
        ├── configuration
        │   └── common.properties
        ├── gradle
        │   └── wrapper
        │       ├── gradle-wrapper.jar
        │       └── gradle-wrapper.properties
        ├── gradlew
        ├── gradlew.bat
        ├── init.gradle.kts
        ├── Jenkinsfile
        ├── LICENSE.txt
        ├── README.md
        ├── settings.gradle.kts
        └── src
            ├── main
            │   ├── java
            │   │   └── com
            │   │       └── mycompany
            │   │           └── myapplication
            │   │               └── Main.java
            │   └── resources
            └── test
                ├── java
                └── resources

#. Push these modifications to Gitea repository


Create a New Jenkins Job
~~~~~~~~~~~~~~~~~~~~~~~~

Start by creating a new job for building our application.

#. Go to Jenkins dashboard.
#. Click on :guilabel:`New Item`.
#. Set item name to ``Hello World``.
#. Select :guilabel:`Multibranch Pipeline`.
#. Validate with :guilabel:`Ok` button.
#. In :guilabel:`General` tab set :guilabel:`Display Name` to ``Hello World``
#. In :guilabel:`Branch Sources`, click on :guilabel:`Add Source` > :guilabel:`Git`.
#. Add :guilabel:`Project Repository` http://172.17.0.1:3000/<admin_user>/helloworld.git

    .. image:: images/tuto_microej_cli_jenkins_git_hello.PNG
        :align: center

#. Click on :guilabel:`Save`.


Build the "Hello World" Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Let's run the job!

In Jenkins ``Hello World`` dashboard, click on :guilabel:`master` branch, then click on :guilabel:`Build Now`. 

.. note::
   You can check the build progress by clicking on the build progress bar and showing the :guilabel:`Console Output`.

At the end of the build, the module is published to ``http://localhost:8082/artifactory/list/custom-modules-snapshot/com/mycompany/my-application/``.


Congratulations!

At this point of the training:

* Artifactory is hosting your module builds and MicroEJ modules. 
* Jenkins automates the build process using SDK6.

The next recommended step is to adapt Gradle/Jenkins/Artifactory configuration to your ecosystem and development flow.


Appendix
--------

This section discusses some of the customization options.


Customize Jenkins
~~~~~~~~~~~~~~~~~

Jenkins jobs are highly configurable, following options and values are recommended by MicroEJ, but they can be customized at your convenience.

In :guilabel:`General` tab:

#. Check :guilabel:`Discard old builds` and set :guilabel:`Max # of builds to keep` value to ``15``.
#. Click on :guilabel:`Advanced` button, and check :guilabel:`Block build when upstream project is building`.

In :guilabel:`Build triggers` tab:
 
#. Check :guilabel:`Poll SCM`, and set a CRON-like value (for example ``H/30 * * * *`` to poll SCM for changes every 30 minutes).

In :guilabel:`Post-build actions` tab:
    
1. Add post-build action :guilabel:`Publish JUnit test result report`:
2. Set :guilabel:`Test report XMLs` to ``**/target~/test/xml/**/test-report.xml, **/target~/test/xml/**/*Test.xml``.

.. note::
    The error message ``‘**/target~/test/xml/**/test-report.xml’ doesn’t match anything: ‘**’ exists but not ‘**/target~/test/xml/**/test-report.xml’``
    will be displayed since no build has been executed yet. These folders will be generated during the build.

3. Check :guilabel:`Retain long standard output/error`.
4. Check :guilabel:`Do not fail the build on empty test results`

..
   | Copyright 2021-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.