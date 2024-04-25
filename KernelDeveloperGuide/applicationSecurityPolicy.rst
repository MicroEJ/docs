.. _applicationSecurityPolicy:

Application security policy
===========================

The security management can be done in various ways, the most common way of declaring a security management policy is by the usage of the `SecurityManager`_ class.

For the sake of ROM footprint optimization, permission checks calls are disabled by default to avoid extra code processing if the system owner does not want to use the Security Manager.
In order to activate this feature the :ref:`option_enable_security_manager` option must be set.

Once the security manager checks are enabled, you can then implement your own policy.

This can be achieved by subclassing the base `SecurityManager`_ abstract class, overriding its `SecurityManager.checkPermission(Permission)`_ method,
and registering an instance of this class to the Kernel by a call to `System.setSecurityManager(SecurityManager)`_.

.. code-block:: java

      // create a new Security Manager
      SecurityManager sm = new SecurityManager() {
         @Override
         public void checkPermission(java.security.Permission perm) {
            // here implement your Kernel Security Policy
         };
      };
      // register the Security Manager
      System.setSecurityManager(sm);

Then you have to implement your own Security Policy.

Implementation examples
-----------------------

MicroEJ provides several security manager implementation examples in the ``security`` package of the `com.microej.library.util.kf-util`_ (2.8.0+) module.
A usage example of these implementations is available in the `Kernel-GREEN`_ GitHub project.

Kernel Security Policy Manager
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This implementation is inspired from the `JavaPolicyFile`_ concept.
Features come with a policy file that describes the permission they will need at runtime.
By default the name of this file should be ``feature.policy.json`` you can override the default name using the property ``feature.policy.name`` to be added in the Kernel :ref:`system properties <system_properties>`.
This concept assumes that the system owner is able to verify the content of this file before the feature is deployed onto the Kernel (using an application store system for instance).
The file is then parsed on the feature installation and the permissions are stored in a map in the security manager.
Finally, when a permission check is requested, the security manager will check if the feature has specified the requested permission or not in which case it throws a `SecurityException`_.
Here is a schema to describe the entire flow of the Kernel Security Policy Manager from a feature install to a feature stop.

.. image:: png/kernelSecurityPolicyManagerFlow.png
   :align: center

This implementation requires a parsing of the feature policy file to create the correct list of `FeaturePolicyPermission`_ objects that will be handled by the security manager.
the ``KF-Util`` module provides a JSON implementation as the default implementation.

This can be done by creating a class that implements the `SecurityPolicyResourceLoader`_ interface.

Before going further we strongly advise to take a look to the `java.security.Permission`_ Javadoc to fully understand the way permissions work (name, action...).

Here is an example of what a JSON file looks like with placeholders:

.. code-block:: json

    {
      "permissions": {
        "<permissionClassName1>":{
          "<permissionName1>":["<permissionAction1>","<permissionAction2>"],
          "<permissionName2>":["<permissionAction1>"]
        },
        "<permissionClassName2>":{
          "<permissionName3>":["<permissionAction3>"]
        }
      }
    }


Here is now an example of what a real JSON file can look like:

.. code-block:: json

    {
      "permissions": {
        "ej.microui.display.DisplayPermission":{
          "*":[]
        },
        "ej.microui.event.EventPermission":{
          "null":["null"]
        },
        "ej.microui.display.FontPermission":{},
        "ej.microui.display.ImagePermission":{
          "null":["*"]
        },"ej.microui.MicroUIPermission":{
          "*":["start"]
        },"java.net.SocketPermission":{
          "www.microej.com":["connect","resolve"]
        },"java.util.PropertyPermission":{
          "property":["write","read"]
        },"java.lang.RuntimePermission":{
          "exit":[]
        }
      }
    }

.. note::
    The permission ``name`` attribute is specific to the permission implementation therefore, each permission has its own definition of what a name is.

The parser contains two key words to allow more flexibility over the content of the file:
* "*": the wildcard symbol represents ``everything`` it can be used for permission class name, permission name and permission actions.
* "null": the ``null`` keyword represents a java ``null`` value, it can be used for permission name and permission actions.

To simplify the file structure you can also choose to have an empty object value for permission className or/and permission actions such as shown in the example above:

.. code-block:: json

    {
      "permissions": {
        "ej.microui.display.DisplayPermission":{
          "*":[]
        },
        "ej.microui.display.FontPermission":{},
        "java.lang.RuntimePermission":{
          "exit":[]
          }
        }
    }


This example:
* allows the usage of any permission name and any actions for the ``ej.microui.display.DisplayPermission`` permission.
* allows the usage of any permission name and any actions for the ``ej.microui.display.FontPermission`` permission.
* allows the ``exit`` permission name and any actions for the ``java.lang.RuntimePermission`` permission.

Using an empty value or the ``*`` wildcard is left to the developer preference and should be processed in the exact same way by the security policy resource loader.

.. warning::
    If the Kernel does not embed all class names (see :ref:`Stripping Class Names from an Application <stripclassnames>`),
    make sure that specified permission class names are embedded by declaring them as :ref:`Required Types <section.classpath.elements.types>`.
    Any permission check done on a permission class without embedded name will result in a `SecurityException`_.


Kernel Security Manager
~~~~~~~~~~~~~~~~~~~~~~~

This implementation is based on the creation of `FeaturePermissionCheckDelegate`_ to specify the behavior of the `SecurityManager.checkPermission(Permission)`_ for each permission class.
If a permission check is done and no delegate for its permission is found, a `SecurityException`_ is thrown.
An example of this policy manager is used by the `Kernel-GREEN`_.
The policy grants all applications the permission for a list of permission classes and logs all protected accesses by Applications.


.. _SecurityManager: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/SecurityManager.html
.. _SecurityManager.checkPermission(Permission): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/SecurityManager.html#checkPermission-java.security.Permission-
.. _System.setSecurityManager(SecurityManager): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/System.html#setSecurityManager-java.lang.SecurityManager-
.. _Kernel-GREEN: https://github.com/MicroEJ/Kernel-GREEN
.. _FeaturePermissionCheckDelegate: https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/security/FeaturePermissionCheckDelegate.html
.. _SecurityException: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/SecurityException.html
.. _FeaturePolicyPermission: https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/security/FeaturePolicyPermission.html
.. _SecurityPolicyResourceLoader: https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/security/SecurityPolicyResourceLoader.html
.. _java.security.Permission: https://repository.microej.com/javadoc/microej_5.x/apis/java/security/Permission.html
.. _JavaPolicyFile: https://docs.oracle.com/javase/8/docs/technotes/guides/security/PolicyFiles.html
.. _com.microej.library.util.kf-util: https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/security/package-summary.html

..
   | Copyright 2024, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.