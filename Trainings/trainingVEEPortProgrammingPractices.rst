.. _vee_port_programming_pratices:

VEE Port Programming Practices
==============================

Description
-----------

This page gives a collection of recommended practices that is essential when porting VEE to new hardware and existing embedded software stacks.

Intended Audience
-----------------

This training is designed for embedded developers who want to enhance the quality and security of their C code.

Prerequisites
-------------

To get the most out of this training, participants should have a good knowledge of the C programming language and Board Support Package (BSP) development.

Recommended Practices
---------------------

Embedded software presents several challenges, like traditional software but with the added pressure due to resource constraints.
However, many common issues can be mitigated by following security rules and design principles. MicroEJ already follows certain design principles,
for your own VEE Port development, it is recommended to read the following links from recognized sources:

- https://cyber.gouv.fr/sites/default/files/2022/04/anssi-guide-rules_for_secure_c_language_software_development-v1.4.pdf
- https://docenti.ing.unipi.it/~a009435/issw/extra/c-coding-standard.pdf

- https://www.linuxfoundation.org/research/cra-compliance-best-practices?hsLang=en
- https://training.linuxfoundation.org/training/cybersecurity-essentials-lfc108/

- https://partner-security.withgoogle.com/docs/iot_requirements

A Word about Security
---------------------

This paragraph serves as a quick overview, outlining the processes, design philosophies, and concrete mechanisms that should consider to ensure system integrity and security.
Key enforcements should include:

- code reviews (code should be created by several entities in collaboration to ensure quality, maintainability and security),
- static analysis (use tools such as cppcheck),
- threat modeling (what are you trying to protect, from whom, it could also be beneficial to do some penetration testing),
- memory and thread separation (isolate your treatments, segregate your information based on applicative needs),
- and cryptographic support (remove out-of-date standards, ensure proper storage of keys and certificates, ensure sensitive data is not transiting via easily accessible unsecured memories, etc.).

You should also consider covering:

- system-level concerns (boot, OTA updates, root of trust),
- vulnerability reporting and mitigation strategies (CVEs management and vulnerability recovery, use SBOM tools for automatic detection),
- and certification strategies (software-only, hardware-anchored, or full product certification).

You should aim to guide developers and architects to integrating security practices throughout your codebase and ecosystem on a day-to-day basis.


..
   | Copyright 2025, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.

