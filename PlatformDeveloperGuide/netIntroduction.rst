Principle
=========

MicroEJ provides some Foundation Libraries to initiate raw TCP/IP
protocol-oriented communications and secure this communication by using
Secure Socket Layer (SSL) or Transport Layer Security (TLS)
cryptographic protocols.

The diagram below shows a simplified view of the components involved in
the provisioning of a Java network interface.

.. figure:: images/java-c-net-interface.*
   :alt: Overview
   :align: center

   Overview

Net and SSL low level parts connects the Net and SSL libraries to the
user-supplied drivers code (coded in C).

The MicroEJ Simulator provides all features of Net and SSL libraries.
This one takes part of the network settings stored in the operating
system on which the Simulator will be launched.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
