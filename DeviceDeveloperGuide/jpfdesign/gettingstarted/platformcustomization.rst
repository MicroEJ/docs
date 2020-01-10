.. _platformCustomization:

Platform Customization
======================

Platform can be customized by creating a ``configuration.xml`` script
beside the ``[name].platform`` file. This script can extend one or
several of the extension points available.

Configuration project (the project which contains the
``[name].platform`` file) can contain an optional ``dropins`` folder.
The contents of this folder will be copied integrally into the final
platform. This feature allows to add some additional libraries, tools
etc. into the platform.

The dropins folder organization should respect the final platform files
and folders organization. For instance, the tools are located in the
sub-folder ``tools``. Launch a platform build without the dropins folder
to see how the platform files and folders organization is. Then fill the
dropins folder with additional features and build again the platform to
obtain an advanced platform.

The dropins folder files are kept in priority. If one file has the same
path and name as another file already installed into the platform, the
dropins folder file will be kept.

Modifying one of these files requires to build the platform again.
