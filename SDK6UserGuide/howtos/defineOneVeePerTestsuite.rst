.. _sdk_6_define_one_vee_per_testsuite:

How To Define a Dedicated VEE for each Testsuite
================================================

The SDK allows to define the VEE used by the Testsuites with the ``testMicroejVee`` configuration, as explained in :ref:`sdk_6_testsuite_vee_configuration`.
If several testsuites are defined, the VEE declared with this configuration is used in all of them.

It is possible to define a specific VEE for each testsuite by creating a custom configuration based on the testsuite.
For example, when declaring the following configurations::

    testing {
      suites {
         val test by getting(JvmTestSuite::class) {
            ...
         }

         val testOnDevice by registering(JvmTestSuite::class) {
            ...
         }
      }
   }

And creating a configuration named with the pattern ``<testsuiteName>MicroejVee`` (so ``testOnDeviceMicroejVee`` for the ``testOnDevice``) with::

    configurations {
      val testOnDeviceMicroejVeeConf = create("testOnDeviceMicroejVee")
      create("testOnDeviceMicroejVeeClasspath").extendsFrom(testOnDeviceMicroejVeeConf)
    }

It is possible to a VEE for each testsuite with::

    dependencies {
      ...
      testMicroejVee("com.mycompany:my-first-vee-port:1.0.0")
      testOnDeviceMicroejVee("com.mycompany:my-second-vee-port:1.0.0")
    }

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
