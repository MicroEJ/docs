.. _workspace:

Workspaces and MicroEJ Repositories
===================================

When starting MicroEJ SDK, it prompts you to select the last used
workspace or a default workspace on the first run. A workspace is a main
folder where to find a set of projects containing MicroEJ source code.

When loading a new workspace, MicroEJ SDK prompts for the location of
the MicroEJ repository, where the MicroEJ Architectures, Platforms or Virtual Devices will be imported. 
By default, MicroEJ SDK suggests to point to the default MicroEJ
repository on your operating system, located at
``${user.home}/.microej/repositories/[version]``. You can select an
alternative location. Another common practice is to define a local
repository relative to the workspace, so that the workspace is
self-contained, without external file system links and can be shared
within a zip file.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
