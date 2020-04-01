How to setup a KF Testsuite
===========================

All the test must me placed in the `src/test/projects` directory.

Write a KF test
---------------

A KF test is composed of several projects:

- A project for the kernel using the `microej-javalib` of `std-java` skeleton;
- A project for each feature using `application` skeleton;
- A project for the firmware using `firmware-multiapp` skeleton.

The names of the projects and directories can be whatever you want. It is however better to follow a convention such as `ProjectName-kernel` for the kernel, `ProjectName-app1` for a feature of `ProjectName-fw` for the firmware. 

The projects are grouped in directory which is itself put in `src/test/projects`.

.. image:: png/kf_testsuite_project_structure.png
   :alt: project structure

All the projects will be built automatically in the right order based on their dependencies.

~~~~~~~~~~~~~~~~~~~

Enable testsuite
----------------

Enable the ``microej-kf-testsuite`` plugin by adding the following line to the ``module.ivy`` of your project:

::

    <ea:plugin organisation="com.is2t.easyant.plugins" module="microej-kf-testsuite" revision="+" />

Configure retry
~~~~~~~~~~~~~~~

The number of retries for failed test can be changed by adding the following line and change the value:

::

    <ea:property name="microej.testsuite.retry.count" value="1"/>
   
Run the testsuite locally
~~~~~~~~~~~~~~~~~~~~~~~~~

To run the testsuite locally, you need to add the following lines to the ``module.ivy``:

::

    <ea:property name="microej.kf.testsuite.properties.microejtool.deploy.name" value="stlink" />
    <ea:property name="microej.kf.testsuite.properties.testsuite.trace.ip" value="localhost" />
    <ea:property name="microej.kf.testsuite.properties.testsuite.trace.port" value="1234" />
    <ea:property name="skip.test" value="SET" />

and launch the Serial To Socket tool (here in port `1234`).

..
   | Copyright 2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.