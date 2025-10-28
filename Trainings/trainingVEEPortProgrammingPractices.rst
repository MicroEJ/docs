.. _vee_port_programming_pratices:

==============================
VEE Port Programming Practices
==============================

Description
===========

This page gives a collection of recommended practices that are essential when porting VEE to new hardware and existing embedded software stacks.

Intended Audience
=================

This training is designed for embedded developers who want to enhance the quality and security of their C code.

Prerequisites
=============

To get the most out of this training, participants should have a good knowledge of the C programming language and Board Support Package (BSP) development.

A Word about Security
=====================

This paragraph serves as a quick overview, outlining the processes, design philosophies, and concrete mechanisms that should consider to ensure system integrity and security.
Key enforcements should include:

- code reviews (code should be created by several entities in collaboration to ensure quality, maintainability and security),
- static analysis (use tools such as cppcheck or SonarQube),
- threat modeling (what are you trying to protect, from whom, it could also be beneficial to do some penetration testing),
- memory and thread separation (isolate your treatments, segregate your information based on applicative needs),
- and cryptographic support (remove out-of-date standards, ensure proper storage of keys and certificates, ensure sensitive data is not transiting via easily accessible unsecured memories, etc.).

You should also consider covering:

- system-level concerns (boot, OTA updates, root of trust),
- vulnerability reporting and mitigation strategies (CVEs management and vulnerability recovery, use SBOM tools for automatic detection),
- and certification strategies (software-only, hardware-anchored, or full product certification).

You should aim to guide developers and architects to integrating security practices throughout your codebase and ecosystem on a day-to-day basis.

Recommended Practices
=====================

Embedded software presents several challenges, like traditional software but with the added pressure due to resource constraints.
However, many common issues can be mitigated by following security rules and design principles. MicroEJ already follows certain design principles,
for your own VEE Port development, it is recommended to read the following links from recognized sources:

- https://cyber.gouv.fr/sites/default/files/2022/04/anssi-guide-rules_for_secure_c_language_software_development-v1.4.pdf
- https://docenti.ing.unipi.it/~a009435/issw/extra/c-coding-standard.pdf

- https://www.linuxfoundation.org/research/cra-compliance-best-practices?hsLang=en
- https://training.linuxfoundation.org/training/cybersecurity-essentials-lfc108/

- https://partner-security.withgoogle.com/docs/iot_requirements

Abstraction Layers Development
==============================

.. _vee_port_programming_pratices_errors:

Error Handling in Native Methods
--------------------------------

This section describes the best practices for handling errors in native methods.

Here are the common ways of reporting errors to the Managed Code in a native method:

- Throw an exception with ``SNI_throwNativeException`` or ``SNI_throwNativeIOException``.
- Return an error code.

For implementation errors or invalid requests (for example, a negative size array or a NULL pointer, more generally anything that is outside the validity domain of the method): call ``SNI_throwNativeException``. In this case, the error is not caught by the Managed Code (uncaught exception in Java). Here are the good practices when using this function:

- The error string must be wrapped in a macro that can be disabled to save footprint.
- The error code can be anything that helps the developer to fix the issue (not necessarily errors documented in the Abstraction Layer API; it can also be a backend error code).
- A log message can be added to describe the error; the log string must also be wrapped in a macro that can be disabled to save footprint.
- Check that the return statement of ``SNI_throwNativeException`` is ``SNI_OK``; you can do it with an assert. Return ``SNI_IGNORED_RETURNED_VALUE``.

For errors that must be handled by the Java implementation, use one of the two following methods. In each case, the method used to handle errors and the possible error codes must be specified in the Abstraction Layer API:

- Call ``SNI_throwNativeIOException``. This error is primarily used for Input/Output errors, but it can be used in other cases when an exception needs to be thrown. In this case, the error is caught by the Managed Code (caught exception in Java).

   - Use an error code that is documented in the Abstraction Layer API. Keep a reduced number of codes; each error code implies a different processing on the Managed Code side. Use -1 for the default error.
   - The error string must be wrapped in a macro that can be disabled to save footprint. It can contain a backend-specific message (for example, a strerror() string).
   - A log message can be added to specify the error and add a backend error code; again, the log string must be wrapped in a macro that can be disabled to save footprint.
   - Check that the return statement of ``SNI_throwNativeIOException`` is ``SNI_OK``; you can do it with an assert. Return ``SNI_IGNORED_RETURNED_VALUE``.

- Use the return code of the native function.

   - Use only error codes documented in the Abstraction Layer API.
   - As an error implies a negative return value, this cannot be used for functions that normally return negative values (for example, temperature sensors).

For more information on how to handle exceptions in the Managed Code, please refer to :ref:`improve_code_quality_exceptions` chapter.

..
   | Copyright 2025, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.

