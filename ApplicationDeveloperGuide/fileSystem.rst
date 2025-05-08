.. _fs_api:

File system
===========

Introduction
------------

The `File system API Library <https://repository.microej.com/modules/ej/api/fs//>`_ provides the following APIs to read and write files in an Application: `java/io <https://repository.microej.com/javadoc/microej_5.x/apis/java/io/package-frame.html>`_

.. _fs_api_usage:

Usage
-----

The FS Library is provided as a Foundation Library. To use it in your application, add the following line to the project build file:

.. tabs::

   .. tab:: SDK 6 (build.gradle.kts)

      .. code-block:: kotlin

         implementation("ej.api:fs:2.1.1")

   .. tab:: SDK 5 (module.ivy)

      .. code-block:: xml

         <dependency org="ej.api" name="fs" rev="2.1.1"/>

Building or running an Application which uses the FS API Library requires the VEE Port to provide the `FS Pack <https://repository.microej.com/modules/com/microej/pack/fs/>`_. Refer to :ref:`VEE Porting Guide<pack_fs>` documentation for FS pack integration instructions.

Examples
--------

MicroEJ provides examples which show how to use the FS API.

These examples can be found on `GitHub <https://github.com/MicroEJ/Example-Foundation-Libraries>`_.
Please refer to their own README for more information on these examples.
