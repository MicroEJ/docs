Properties
==========

Properties allow the MicroEJ application to be parameterized using the
``System.getProperty`` API. The definition of the properties and their
respective values can be done using files. Each filename of a properties
file must match with ``*.system.properties`` and must be located in the
``properties`` package of the application classpath. These files follow
the MicroEJ property list specification: key/value pairs.

::

   microedition.encoding=ISO-8859-1

MicroEJ properties can also be defined in the launch configuration. This
can be done by setting the properties in the launcher with a specific
prefix in their name:

-  Properties for both the MicroEJ platform and the MicroEJ simulator:
   name starts with ``microej.java.property.*``

-  Properties for the MicroEJ simulator: name starts with
   ``sim.java.property.*``

-  Properties for the MicroEJ platform: name starts with
   ``emb.java.property.*``

For example, to define the property ``myProp`` with the value
``theValue``, set the following option in the ``VM arguments`` field of
the ``JRE`` tab of the launch configuration:
-Dmicroej.java.property.myProp=theValue
