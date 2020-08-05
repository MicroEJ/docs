Build and deployment automation using Jenkins and Artifactory
=============================================================

This tutorial details the creation of an environment for automating build and deployment of MicroEJ modules.
Using Jenkins for build automation and Artifactory for artifacts repository management, this environment improves productivity across your development ecosystem.
Among other benefits, it will ease building modules when sources change, saving build results,
reproducing builds, or archiving binaries.

Requirements
------------

*  MicroEJ SDK **4.1.5 or later**
*  Git **2.x** installed, with Git executable in path. We recommend
   installing Git Bash if your operating system is Windows
   (`<https://git-for-windows.github.io/>`_).
*  Apache Ant **1.9.x** installed (`<https://ant.apache.org/bindownload.cgi>`_).
*  Java Development Kit (JDK) **1.8.x**


Set JDK location
----------------

#. Locate your JDK installation directory (typically something like ``C:\Program Files\Java\jdk1.8.0_[version]`` on Windows).
#. Set the environment variable ``JAVA_HOME`` to point to the ``bin`` directory (for exemple ``C:\Program Files\Java\jdk1.8.0_[version]\bin``).
#. Set the environment variable ``JRE_HOME`` to point to the ``jre`` directory (for exemple ``C:\Program Files\Java\jdk1.8.0_[version]\jre``).

.. _get-microej-cli-toolkit:

Get MicroEJ CLI toolkit
-----------------------

The MicroEJ CLI toolkit contains the Easyant entrypoints for building MicroEJ modules from the command line.
Get it by cloning the git repository `<https://gitlab.cross/M0090_IDE/M0090_SDK-CLI>`_ (**TODO** change with github ref when available)

.. code-block:: sh
   
   git clone -b feature/M0090IDE-3367_build_from_command_line  https://gitlab.cross/M0090_IDE/M0090_SDK-CLI.git
   /!\ TODO change with github ref when available /!\


.. _extract-microej-build-repository: 

Extract MicroEJ Build Kit
-------------------------

MicroEJ SDK comes with its own toolkit for building modules. Depending on your MicroEJ SDK version, extracting the build kit from the SDK will differ.

.. note::
   Starting with MicroEJ SDK Distribution 19.05, you can determine your MicroEJ SDK version this way:
       #. Start MicroEJ SDK.
       #. Go to ``Help`` > ``About MicroEK SDK``.
       #. Click on ``Installation Details``.
       #. In the ``Installed Software`` tab, look for the version of entry ``MicroEJ SDK``.

MicroEJ 5.2 or later
~~~~~~~~~~~~~~~~~~~~
 
#. Go to the root directory of the MicroEJ CLI toolkit.
#. Create a directory named ``buildKit``.
#. In the SDK, go to ``Window`` > ``Preferences`` > ``MicroEJ`` > ``Module Manager``.
#. In subsection ``Build repository``, click on ``Export Build Kit``.
#. As ``Target directory``, choose the ``buildKit`` directory.

MicroEJ 5.1 or earlier
~~~~~~~~~~~~~~~~~~~~~~

#. Go to the root directory of the MicroEJ CLI toolkit.
#. Create a directory named ``buildKit``.
#. Create a sub-directory named ``ant`` in the ``buildKit`` directory.
#. Locate your SDK installation directory (by default, on Windows: ``C:/Program Files/MicroEJ/MicroEJ SDK-[version]``).
#. Within the SDK installation directory, go to the bundled RCP plugins directory (``/rcp/plugins/``).
#. Extract the toolkit runtime:
    #. Open the file ``com.is2t.eclipse.plugin.easyant4e_[version].jar`` with an archive manager.
    #. Extract the directory ``lib`` to the ``buildKit/ant/`` directory.
#. Extract the toolkit repositories:
    #. Open the file ``com.is2t.eclipse.plugin.easyant4e.offlinerepo_[version].jar`` with an archive manager
    #. Navigate to directory ``repositories``
    #. Extract the file ``microej-build-repository.zip`` (or ``is2t_repo.zip`` for MicroEJ SDK 4.1.x) to the ``buildKit`` directory.

.. note::
   At this point, the content of the directory ``buildKit`` should look like the following:
   ::

    buildKit
    ├── ant
    │   └── lib
    │        ├── ant.jar
    │        ├── ant-launcher.jar
    │        └── ...
    └── microej-build-repository.zip (or is2t_repo.zip)


.. _get-microej-central-repository:

Get MicroEJ Central Repository
------------------------------

The Central Repository gathers software modules that can extend your MicroEJ development environment.

Next step is to import a local copy of this repository:

#. Visit the `Central Repository <https://developer.microej.com/central-repository/>`_ on the MicroEJ Developer website.
#. Navigate to the ``Working Offline`` section.
#. Click on the ``offline repository`` link. This will download the Central Repository as a zip file.



Setup Artifactory
-----------------

Installation and first start
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#. Download Artifactory here: `<https://api.bintray.com/content/jfrog/artifactory/jfrog-artifactory-oss-$latest.zip;bt_package=jfrog-artifactory-oss-zip>`_.
#. Unzip downloaded archive, then navigate to ``bin`` directory (by default
   ``artifactory-oss-[version]/bin``).
#. Run ``artifactory.bat`` or ``artifactory.sh`` depending on your operating system. After initialization, the terminal should print the message **"Artifactory successfully started"**. 
   In case an error occurs, check that ``JAVA_HOME`` and ``JRE_HOME`` environment variables are correct.
#. Go to http://localhost:8081/.
#. Login to Artifactory for the first time using the default ``admin`` account (Username: ``admin``, Password: ``password``).
#. On the **Welcome** wizard, set the administrator password, then click **Next**,
#. Configure proxy server (if any) then click **Next**, or click **Skip**.
#. On **Create Repositories** page, select **Maven** then click on **Create**.
#. Click on **Finish**. 

Artifactory is up and running.

General configuration
~~~~~~~~~~~~~~~~~~~~~

For demonstration purposes we will allow anonymous users to deploy modules in the repositories.

#. Go to **Admin** > **Security** > **Security Configuration**.
#. In the **General Security Settings** section, check **Allow Anonymous Access**. Click **Save**.
#. Go to **Admin** > **Security** > **Permissions**.
#. Click on **Anything** entry (do not check the line), then go to **Users** tab, click on **Anonymous** and check **Deploy/Cache** permission. Click **Save and finish**.

Next steps will involve uploading large files, so we'll set the file upload maximum size accordingly:

#. Go to **Admin** > **General Configuration**.
#. In the **General Settings** section, change the value of **File Upload Max Size (MB)** to ``500`` then click on **Save**.


Manage repositories
~~~~~~~~~~~~~~~~~~~

First step is to configure pre-defined repositories.

#. Go to **Admin** > **Repositories** > **Local**.
#. Click on ``libs-snapshot-local`` repository, then check **Handle Releases** and uncheck **Handle Snapshots**. Click **Save and finish**.


Next step is to create the repositories that will hold the MicroEJ modules.

#. Go to **Admin** > **Repositories** > **Local**.
#. Click on **New**, and select **Maven**.
#. Set **Repository Key** field to ``microej-libs-release-local``, then uncheck **Handle Snapshots**. Click on **Save and finish**.
#. Click on **New**, and select **Maven**.
#. Set **Repository Key** field to ``microej-easyant-release-local``, then uncheck **Handle Snapshots**. Click on **Save and finish**.
#. Make these two repositories fetchable:
    #. Go to **Admin** > **Security** > **Permissions**. 
    #. Click on **Anything** entry (do not check the line)
    #. On the **Resources** tab, drag repositories ``microej-libs-release-local`` and ``microej-easyant-release-local`` from the **Available repositories** area to **Included Repositories** area.
    #. Click on **Save & Finish**.


Import MicroEJ modules
~~~~~~~~~~~~~~~~~~~~~~

In this section, we'll import MicroEJ modules into Artifactory to make them available to the build server.

#. Go to **Admin** > **Import & Export** > **Repositories**.
#. Scroll to the **Import Repository from Zip** section.
#. Import the MicroEJ Central Repository:
    #. As **Target Local Repository**, select ``microej-libs-release-local`` in the list.
    #. As **Repository Zip File**, select MicroEJ Central Repository zip file (``microej-[MicroEJ version]-[version].zip``) that you downloaded earlier (see :ref:`get-microej-central-repository`).
    #. Click **Upload**. At the end of upload, click on **Import**. Upload and import may take some time.

#. Import the MicroEJ Build Repository:
    #. As **Target Local Repository**, select ``microej-easyant-release-local`` in the list.
    #. As **Repository Zip File**, select MicroEJ Build Repository zip file (``microej-build-repository.zip`` or ``is2t_repo.zip``) that you extracted earlier (see :ref:`extract-microej-build-repository`).
    #. Click **Upload**. At the end of upload, click on **Import**. Upload and import may take some time.

Artifactory is now hosting required MicroEJ modules. 
Go to **Artifacts** and check that repositories ``microej-libs-release-local`` and ``microej-easyant-release-local`` contain modules.

.. image:: images/tuto_microej_cli_artifactory_preview.PNG
    :align: center
      



Setup Jenkins
-------------

Installation
~~~~~~~~~~~~

#. Download Jenkins WAR (Web Archive) here: `<http://mirrors.jenkins.io/war-stable/latest/jenkins.war>`_
#. Open a terminal and type the following command: ``java -jar [path/to/downloaded/jenkinswar]/jenkins.war``. 
   After initialization, the terminal will print out **Jenkins is fully up and running**.
#. Go to `<http://localhost:8080/>`_.
#. To unlock Jenkins, copy/paste the generated password that has been written in the terminal log. Click on **Continue**.
#. Select option **Install suggested plugins** and wait for plugin
   installation.
#. Fill in the **Create First Admin User** form. Click **Save and continue**.
#. Click on **Save and finish**, then on **Start using Jenkins**.

Configuration
~~~~~~~~~~~~~

First step is to configure JDK and Ant installations:

#. Go to **Manage Jenkins** > **Global Tool Configuration**.
#. Add JDK installation:
    #. Scroll to **JDK** section.
    #. Click on **Add JDK**.
    #. Set **Name** to ``JDK [jdk_version]`` (for example ``JDK 1.8``).
    #. Uncheck **Install automatically**.
    #. Set **JAVA_HOME** to ``path/to/jdk[jdk_version]`` (for example ``C:\Program Files\Java\jdk1.8.0_[version]`` on Windows).
#. Add Ant installation:
    #. Scroll to **Ant** section.
    #. Click on **Add Ant**.
    #. Set **Name** to ``Ant 1.9``.
    #. Uncheck **Install automatically**.
    #. Set **ANT_HOME** to ``path/to/apache-ant-1.9.[version]``.
#. Click on **Save**.

Next step is to configure  environment variables:

#. Go to **Manage Jenkins** > **Configure System**.
#. Scroll to **Global properties** section.
#. Check **Environment variables**.
#. Add variable ``MICROEJ_BUILD_TOOLS_HOME``:
    #. Click **Add**.
    #. Set **Name** to ``MICROEJ_BUILD_TOOLS_HOME``.
    #. Set **Value** to be the path to the MicroEJ CLI toolkit directory (as defined in :ref:`get-microej-cli-toolkit`)
#. Add variable ``EASYANT_HOME``:
    #. Click **Add**.
    #. Set **Name** to ``EASYANT_HOME``.
    #. Set **Value** to be the path to the ``ant`` directory of the ``buildKit`` directory (as defined in :ref:`extract-microej-build-repository`).
#. For Windows users, scroll to **Shell** section and set the path to the **Shell executable** (for example ``C:\Program Files\Git\bin\sh.exe``).
#. Click on **Save**.

Create a job template
~~~~~~~~~~~~~~~~~~~~~

The main advantage of using EasyAnt is to move build logic into build-types, which are equivalent of Maven archetypes. 
It allows to define a generic job in Jenkins that will handle all EasyAnt builds.

#. Go to Jenkins dashboard.
#. Click on **New item** to create a job template.
#. Set item name to ``Template - EasyAnt from Git``.
#. Select **Freestyle project**.
#. Click on **Ok**. 
    
Jenkins jobs are highly configurable, following options and values are recommended by MicroEJ, but they can be customized at your convenience.

In **General** tab:

#. Check **Discard old builds** and set **Max # of builds to keep** value to ``15``.
#. Check **This project is parametrized** and add **String parameter** named ``easyant.module.dir`` with default value to ``$WORKSPACE/TO_REPLACE``. This will later point to the module sources.
#. Click on **Advanced** button, and check **Block build when upstream project is building**.

In **Source Code Management** tab:

#. Select **Git** source control:
#. Set **Repository URL** value to ``TO_REPLACE``,
#. Set **Branch Specifier** value to ``origin/master``,
#. In **Additional Behaviours**, click on **Add**, select **Advanced sub-modules behaviors**, then check **Recursively update submodules**.

In **Build triggers** tab:
 
#. Check **Poll SCM**, and set a CRON-like value (for example ``H/30 * * * *`` to poll SCM for changes every 30 minutes).

In **Build Environment** tab:
    
#. Check **Delete workspace before build starts**.
#. Check **Add timestamps to the Console Output**.

In **Build** tab:

#. Add build step **Execute shell** and set command to ``git clone $MICROEJ_BUILD_TOOLS_HOME -b feature/M0090IDE-3367_build_from_command_line build-tools``. (**TODO** replace this temp branch name with ``master`` when git repo is published)
#. Add build step **Invoke Ant**:
    * As **Ant version**, select ``Ant 1.9``.
    * Set **Targets** to value ``-lib ${EASYANT_HOME}/lib``.
    * In **Advanced**, set **Build file** to value ``$WORKSPACE/build-tools/easyant/build-module.ant``.
    * In **Advanced**, expand **Properties** text field then add the following Ant properties:

    ::

     personalBuild=false
     jenkins.build.id=$BUILD_ID
     jenkins.node.name=$NODE_NAME
     is2t.ivysettings.file=$MICROEJ_BUILD_TOOLS_HOME/ivy/ivysettings-artifactory.xml

In **Post-build actions** tab:
    
#. Add post-build action **Publish JUnit test result report**:
#. Set **Test report XMLs** to ``**/target~/test/xml/**/test-report.xml, **/target~/test/xml/**/*Test.xml``.
#. Check **Retain long standard output/error**.
#. Check **Do not fail the build on empty test results**

Finally, click on **Save**.

Build a module
--------------

Since your environment is now setup, it is time to build your first module using EasyAnt, Jenkins and Artifactory. 
Let’s build an "Hello World" Sandboxed Application project.

Create a new MicroEJ module
~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this example, we will create a very simple module using the Sandbox Application buildtype (``build-application``) that we'll push to a Git repository.

.. note::
   For demonstration purposes, we'll create a new project and share it on a local Git bare repository.
   You can adapt the following sections to use an existing MicroEJ project and your own Git repository.

#. Start MicroEJ SDK. 
#. Go to ``File`` > ``New`` > ``MicroEJ Sandboxed Application Project``.
#. Fill in the template fields, set ``Project name`` to ``com.example.hello-world``.
       
    .. image:: images/tuto_microej_cli_hello_world.PNG
        :align: center

#. Click ``Finish``. This will create the project files and structure.
#. Right-click on source folder ``src/main/java`` and select ``New`` > ``Package``. Set a name to the package and click ``Finish``.
#. Right-click on the new package and select ``New`` > ``Class``. Set a name to the class and check ``public static void main(String[] args)``, then click ``Finish``.
#. Locate the project files
    #. In the ``Package Explorer`` view, right-click on the project then click on ``Properties``
    #. Select ``Resource`` menu.
    #. Click on the arrow button on line ``Location`` to show the project in the system explorer.
#. Open a terminal from this directory and type the following commands:

.. code-block:: sh

   git init --bare ~/hello_world.git
   git init
   git remote add origin ~/hello_world.git
   git add com.example.hello-world
   git commit -m "Add Hello World application"
   git push --set-upstream origin master


.. note::
   For more details about MicroEJ applications development, refer to the `Application Developer Guide <https://docs.microej.com/en/latest/ApplicationDeveloperGuide/index.html>`_.


Create an new instance of the template job
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Start by creating a new job, from the job template, for building our application.

#. Go to Jenkins dashboard.
#. Click on **New Item**.
#. Set item name to ``Hello World``.
#. In **Copy from** field, type ``Template - EasyAnt from Git`` (autocomplete enabled).
#. Validate with **Ok** button.

The job configuration page opens, let's replace all the ``TO_REPLACE`` placeholders from the job template with correct values:

#. In **General** tab, set ``easyant.module.dir`` to value ``$WORKSPACE/com.example.hello-world``.
#. In **Source Code Management**, edit **Repository URL** to ``~/hello_world.git``.
#. Click on **Save**.


Build the "Hello World" application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Let's run the job!

In the ``Hello World`` dashboard, click on **Build with Parameters**, then click on **Build**. 

.. note::
   You can check the build progress by clicking on the build progress bar and showing the **Console Output**.

At the end of the build, the module is published to `<http://localhost:8081/artifactory/list/libs-snapshot-local/com/example/hello-world/>`_.


Congratulations!

At this point of the tutorial:

* Artifactory is hosting your module builds and MicroEJ modules. 
* Jenkins automates the build process using EasyAnt.

The next steps recommended are:

* Adapt Jenkins/Artifactory/EasyAnt configuration to your development ecosystem.