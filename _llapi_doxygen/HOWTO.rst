HOWTO Generate MicroEJ LLAPI Doxygen Documentation
==================================================

Principle
---------

The public documentation build uses the LLAPI Doxygen documentation in the XML format with the Breathe package.

Link to the Breathe package: https://breathe.readthedocs.io/en/latest/index.html#

Prerequisites
-------------

- Install Doxygen available at this link: https://www.doxygen.nl/index.html


Generation
----------

- With a Terminal, go to the directory ``_llapi_doxygen``
- Run the command ``doxygen microej_doxygen_config``


Build locally the public documentation
--------------------------------------

- Install the Python package ``Breathe``, should be done with command ``pip install -r requirements.txt``.

..
   | Copyright 2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
