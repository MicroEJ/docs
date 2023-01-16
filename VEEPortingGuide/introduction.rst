Introduction
============

Scope
-----

This document explains how the core features of MicroEJ Architecture are
accessed, configured and used by the MicroEJ Platform builder. It
describes the process for creating and augmenting a MicroEJ
Architecture. This document is concise but attempts to be exact and
complete. Semantics of implemented Foundation Libraries are described in
their respective specifications. This document includes an outline of
the required low level drivers (LLAPI) for porting the MicroEJ
Architectures to different real-time operating systems (RTOS).

MicroEJ Architecture is state-of-the-art, with embedded MicroEJ runtimes
for MCUs. They also provide simulated runtimes that execute on
workstations to allow software development on "virtual hardware."

Intended Audience
-----------------

The audience for this document is software engineers who need to
understand how to create and configure a MicroEJ Platform using the
MicroEJ Platform builder. This document also explains how a MicroEJ
Application can interoperate with C code on the target, and the details
of the MicroEJ Architecture modules, including their APIs, error codes
and options.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
