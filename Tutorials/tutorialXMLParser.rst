XML parser for your embedded Java applications
==============================================

The XML format
--------------

XML (EXtensible Markup Language) is used to describe data and text. It allows flexible development of user-defined document types. The format is robust, non-proprietary, persistent and is verifiable for storage and transmission.

Parse XML with open source XML parsers
--------------------------------------

This MicroEJ project presents how to use XML data exchange for your Java application developed with MicroEJ. It details how to use XML Pull parsers like `KXmlParser <http://kxml.org/>`_ and `MXParser <http://www.extreme.indiana.edu/xgws/xsoap/xpp/mxp1/>`_ from the Java community.

The example parses a short poem written in XML and prints the result on the system out. The MicroEJ project runs on all built-in MicroEJ Java platforms (simulator and evaluation kits).

All source code is available on `MicroEJ GitHub <https://github.com/MicroEJ/Example-XML>`_ and you can find a free trial version of MicroEJ `here <http://ardyu9v96nsae1p2.microej.com/get-started/>`_. 
We advise you to read the `step-by-step guide to MicroEJ installation <http://ardyu9v96nsae1p2.microej.com/step-step-guide-microej-installation-microej-installation/>`_.

::

	<?xml version="1.0" encoding="UTF-8"?>
	<!--
		XML file
		Copyright 2014 IS2T. All rights reserved.
		Use of this source code is governed by a BSD-style license that can be found at http://www.is2t.com/open-source-bsd-license/.
	-->
	<poem xmlns="http://www.megginson.com/ns/exp/poetry">
		<title>Roses are Red</title>
		<l>Roses are red,</l>
		<l>Violets are blue;</l>
		<l>Sugar is sweet,</l>
		<l>And I love you.</l>
	</poem>

For more information about XML pull parsing, please refer to `xmlpull.org <http://www.xmlpull.org/>`_.

JSON (JavaScript Object Notation) format is an alternative to the use of XML, more lightweight and less bandwidth-intensive, find out how to use JSON parser on MicroEJ `here <http://ardyu9v96nsae1p2.microej.com/json-parser-microej/>`_.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
