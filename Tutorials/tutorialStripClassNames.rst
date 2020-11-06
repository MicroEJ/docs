.. _stripclassnames:

Stripping Java Class Names from an Application
==============================================

By default, when a class is used, the name of the class is embedded too. A class is used when one of its methods is called, for example.
Embedding the name of every class is rarely useful and takes a lot of flash memory.
This section explains how to strip class names from an application.

Stripping All Class Names
-------------------------

1. Select ``Run`` > ``Run Configurations...``.
2. Select the launcher of the application.
3. Select tab ``Configuration``.
4. Ensure ``Embed all type names`` is unchecked in ``Core Engine`` > ``Debug``.

Alternatively, the option ``soar.generate.classnames`` can be set to ``false`` in a ``.properties`` file loaded by the launcher.

Listing Required Class Names
----------------------------

Some class names may be required by an application to work properly.
Those class names must be explicitly specified in a ``*.types.list`` file.

The application and add-on libraries code must be checked for all uses of the following methods:

- ``Class.forName()``
- ``Class.getName()``
- ``Class.getSimpleName()``

Each call indicates a class name usage. Either add the class names to a ``*.types.list`` file or remove the use of class names.

Case of ServiceLoader
~~~~~~~~~~~~~~~~~~~~~

A ``ServiceLoader`` is a dependency injection service. It is used to retrieve the implementation of a service by using the interface.

The assignment between a service and its implementation is done in ``*.properties.list`` files. Both the service class name and the implementation class name must be embedded (i.e., added in a ``*.types.list`` file).

For example:

.. code-block::

	# services.properties.list
	com.example.services.WiFi=com.example.services.WiFiImpl

.. code-block::

	# services.types.list
	com.example.services.WiFi
	com.example.services.WiFiImpl

Case of Dynamic Properties Loading
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Some properties may be loaded dynamically by using the name of a class to determine the full name of the property to load. For example: 

.. code-block:: java

	Integer.getInteger(MyClassA.class.getName() + ".VALUE");

If ``MyClassA`` is not dynamically defined, meaning it is always the same class name, then it can be replaced with the actual string. For example:

.. code-block:: java

	Integer.getInteger("com.example.MyClassA.VALUE");

Case of Logger and Other Debugging Facilities
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Logging mechanisms usually display the name of the classes in traces.
It is not necessary to embed these class names. The :ref:`stack_trace_reader` can decipher the output.
