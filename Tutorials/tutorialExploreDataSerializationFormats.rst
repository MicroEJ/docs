Explore Data Serialization Formats
==================================

This tutorial highlights some data serialization formats that are provided on MicroEJ Central Repository and their usage through basic code samples.

Intended Audience
-----------------

The audience for this document is Application engineers who want to implement data serialization.
In addition, this tutorial should be of interest to software architects who are looking for a suitable data format for their use case.

XML
---

`XML (EXtensible Markup Language) <https://en.wikipedia.org/wiki/XML>`_ is used to describe data and text. It allows flexible development of user-defined document types. The format is robust, non-proprietary, persistent and is verifiable for storage and transmission. To parse this data format, the XML Pull parser `KXmlParser <http://kxml.org/>`_ from the Java community has been integrated to MicroEJ Central Repository.

XML Parser Use In MicroEJ SDK
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `XML API Module <https://repository.microej.com/artifacts/org/kxml2/kxml2/>`_ must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project in order to allow access to the KXML library.

::

	<dependency org="org.kxml2" name="kxml2" rev="2.3.2"/>

Example Of Use
~~~~~~~~~~~~~~

An example is available at https://github.com/MicroEJ/Example-XML.
It presents how to use XML data exchange for your MicroEJ Application. It also details how to use the `KXmlParser <http://kxml.org/>`_ module.

The example parses a short poem written in XML and prints the result on the standard output. The project can run on any MicroEJ Platform (no external dependencies).


::

	<?xml version="1.0" encoding="UTF-8"?>
	<poem xmlns="http://www.megginson.com/ns/exp/poetry">
		<title>Roses are Red</title>
		<l>Roses are red,</l>
		<l>Violets are blue;</l>
		<l>Sugar is sweet,</l>
		<l>And I love you.</l>
	</poem>

Running the ``ReadPoem`` Java application should print the following trace :

::

	=============== [ Initialization Stage ] ===============
	=============== [ Launching on Simulator ] ===============
	Roses are Red
	_____________

	Roses are red,
	Violets are blue;
	Sugar is sweet,
	And I love you.

	=============== [ Completed Successfully ] ===============

	SUCCESS

Running ``MyXmlPullApp`` gives more details on the XML parsing and should print this trace :

::

	=============== [ Initialization Stage ] ===============
	=============== [ Launching on Simulator ] ===============
	parser implementation class is class org.kxml2.io.KXmlParser
	Parsing simple sample XML
	Start document
	Start element: {http://www.megginson.com/ns/exp/poetry}poem
	Characters:    "\n"
	Start element: {http://www.megginson.com/ns/exp/poetry}title
	Characters:    "Roses are Red"
	End element:   {http://www.megginson.com/ns/exp/poetry}title
	Characters:    "\n"
	Start element: {http://www.megginson.com/ns/exp/poetry}l
	Characters:    "Roses are red,"
	End element:   {http://www.megginson.com/ns/exp/poetry}l
	Characters:    "\n"
	Start element: {http://www.megginson.com/ns/exp/poetry}l
	Characters:    "Violets are blue;"
	End element:   {http://www.megginson.com/ns/exp/poetry}l
	Characters:    "\n"
	Start element: {http://www.megginson.com/ns/exp/poetry}l
	Characters:    "Sugar is sweet,"
	End element:   {http://www.megginson.com/ns/exp/poetry}l
	Characters:    "\n"
	Start element: {http://www.megginson.com/ns/exp/poetry}l
	Characters:    "And I love you."
	End element:   {http://www.megginson.com/ns/exp/poetry}l
	Characters:    "\n"
	End element:   {http://www.megginson.com/ns/exp/poetry}poem
	=============== [ Completed Successfully ] ===============

	SUCCESS

JSON
----

As described on the `JSON official site <http://json.org/>`_, JSON (JavaScript Object Notation) is a lightweight data-interchange format. It is widely used in many applications such as:

- as a mean of data serialization for lightweight web services such as REST
- for server interrogation in Ajax to build dynamic webpages
- or even databases.

JSON is easily readable by humans compared to XML. To parse this data format, several JSON parsers are available on the `official JSON page <http://json.org/>`_, such as `JSON ME`, which has been integrated to MicroEJ Central Repository.


JSON Parser Use In MicroEJ SDK
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `JSON API Module <https://repository.microej.com/artifacts/org/json/me/json/>`_ must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project in order to allow access to the JSON library.

::

	<dependency org="org.json.me" name="json" rev="1.3.0"/>

The instantiation and use of the parser is pretty straightforward. First you need to get the JSON content as a ``String``,  and then create a ``org.json.me.JSONObject`` instance with the string. If the string content is a valid JSON content, you should have an workable ``JSONObject`` to browse.

Example Of Use
~~~~~~~~~~~~~~

In the following example we will parse this JSON file that represents a simple abstraction of a file menu:

.. code:: JSON

	{
		"menu": {
			"id": "file",
			"value": "File",
			"popup": {
				"menuitem": [
					{"value": "New", "onclick": "CreateNewDoc()"},
					{"value": "Open", "onclick": "OpenDoc()"},
					{"value": "Close", "onclick": "CloseDoc()"}
				]
			}
		}
	}

First, we need to include this file in our project by adding it to the ``src/main/resources`` folder and creating a ``.resources.list`` properties file to declare this resource for our application to be able to retrieve it (see :ref:`section.classpath.elements.resources` for more details). 

.. figure:: images/json-src-files-folders.png
	:alt: Source files organization
	:width: 242px
	:height: 128px
	:align: center

This ``.resources.list`` file (here named ``json.resources.list``) should contain the path to our JSON file as such :

.. code::

	resources/menu.json

The example below will parse the file, browse the resulting data structure (``org.json.me.JSONObject``) and print the value of the ``menuitem`` JSON array.

.. code:: Java

	package com.microej.examples.json;

	import java.io.DataInputStream;
	import java.io.IOException;

	import org.json.me.JSONArray;
	import org.json.me.JSONException;
	import org.json.me.JSONObject;

	/**
	* This example uses the org.json.me parser provided by json.org to parse and
	* browse a JSON content.
	* 
	* The JSON content is simple abstraction of a file menu as provided here:
	* http://www.json.org/example.html
	* 
	* The example then tries to list all the 'menuitem's available in the popup
	* menu. It is assumed the user knows the menu JSON file structure.
	* 
	*/
	public class MyJSONExample {

		public static void main(String[] args) {

			// get back an input stream from the resource that represents the JSON
			// content
			DataInputStream dis = new DataInputStream(
					MyJSONExample.class.getResourceAsStream("/resources/menu.json"));

			byte[] bytes = null;

			try {

				// assume the available returns the whole content of the resource
				bytes = new byte[dis.available()];

				dis.readFully(bytes);

			} catch (IOException e1) {
				// something went wrong
				e1.printStackTrace();
				return;
			}

			try {

				// create the data structure to exploit the content
				// the string is created assuming default encoding
				JSONObject jsono = new JSONObject(new String(bytes));

				// get the JSONObject named "menu" from the root JSONObject
				JSONObject o = jsono.getJSONObject("menu");

				o = o.getJSONObject("popup");

				JSONArray a = o.getJSONArray("menuitem");

				System.out.println("The menuitem content of popup menu is:");
				System.out.println(a.toString());

			} catch (JSONException e) {
				// a getJSONObject() or a getJSONArray() failed
				// or the parsing failed
				e.printStackTrace();
			}

		}

	}

The execution of this example on the MicroEJ Simulator should print the following trace:

::

	=============== [ Initialization Stage ] ===============
	=============== [ Launching Simulator ] ===============
	The menuitem content of popup menu is:
	[{"value":"New","onclick":"CreateNewDoc()"},{"value":"Open","onclick":"OpenDoc()"},{"value":"Close","onclick":"CloseDoc()"}]
	=============== [ Completed Successfully ] ===============

	SUCCESS


Protobuf
--------

`Protobuf (Protocol Buffers) <https://developers.google.com/protocol-buffers>`_ is a Google's mechanism for serializing structured data. Protobuf consists in:

- a description language that describes the structure of the data
- a compiler that generates source code from that description
- a library that is used by the generated source code for the serialization.

The version 3 of the Java Protobuf library has been integrated to MicroEJ Central Repository.

Protobuf3 Use In MicroEJ SDK
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `Protobuf3 Module <https://repository.microej.com/artifacts/com/google/Protobuf3/>`_ must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project in order to allow access to the Protobuf library.

::

	<dependency org="com.google" name="protobuf3" rev="1.0.0"/>

Once the dependency is added to the `module.ivy` file, the files generated by the Protobuf compiler can be used in the application to serialize data as explained in the `Google's protobuf guides <https://developers.google.com/protocol-buffers>`_.

Example Of Use
~~~~~~~~~~~~~~

An example is available at ... It shows how to use Protobuf to serialize and deserialize data described by the following Protobuf file:

.. code::

	syntax = "proto3";
 
	package com.microej.example.protobuf3example;

	option java_package = "com.microej.example.protobuf3example";
	option java_outer_classname = "AppProto";

	import "google/protobuf/timestamp.proto";

	enum Encryption {
		NONE = 0;
		PGP = 1;
		SMIME = 2;
	}

	message AppMessage {
		int32 id = 1;
		string subject = 2;
		string messageContent = 3;
		google.protobuf.Timestamp date = 4;
		Encryption encryption = 5;
	}

Running the Protobuf example should in the simulator should print the following trace:

::

	=============== [ Initialization Stage ] ===============
	The watchdog is not configured by the application, so it is enabled. This default behavior will reset the MCU after ~32 seconds of not executing the RTOS idle task
	=============== [ Launching on Simulator ] ===============

	* Writing to ByteArray *

	* Reading from ByteArray *
	id:		42
	subject:	Hello
	message:	Hello World!
	date:		1606234599
	encryption:	PGP
	=============== [ Completed Successfully ] ===============

	SUCCESS


..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
