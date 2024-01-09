.. _tutorials_create_iar_image:

Add IAR to MicroEJ SDK Docker Image
===================================

This document presents how to create a Dockerfile with `MicroEJ SDK version 5.x <https://docs.microej.com/en/latest/SDKUserGuide/>`_ and `Cross-platform Build Tools for Arm <https://www.iar.com/bxarm>`_ to build a MicroEJ application. 
You can use this image in your automated CI.


Prerequisites
-------------

* A recent version of IAR BXARM and its user licence.

This tutorial was tested with MicroEJ SDK ``5.8.1-jdk11``, IAR ``9.30.1``, and Docker ``24.0.6``.

Create the Dockerfile
---------------------

Here is our final Dockerfile. We will explain each specific step below.

    .. literalinclude:: resources/IARDockerfile
        :language: dockerfile

#. In a new directory create a file named ``Dockerfile``.
#. We use MicroEJ SDK base image, they are available on `docker hub <https://hub.docker.com/r/microej/sdk>`_. In your Dockerfile add this code:

    .. code-block:: dockerfile

      FROM microej/sdk:5.8.1-jdk11

#. Add IAR BXARM deb package in a directory named ``resources``.
#. Add the package info to your Dockerfile (update the version with the one you want to use):

    .. code-block:: dockerfile

      ARG IAR_BXARM_VERSION=9.30.1
      ARG IAR_BXARM_PACKAGE="bxarm-$IAR_BXARM_VERSION.deb"

#. Copy the package to a temporary directory.

    .. code-block:: dockerfile

      COPY ressources/$IAR_BXARM_PACKAGE /tmp/$IAR_BXARM_PACKAGE

#. Install this package along with any others required packages.

    .. code-block:: dockerfile

      RUN apt-get update && apt-get install sudo libsqlite3-0 libxml2 tzdata dos2unix /tmp/$IAR_BXARM_PACKAGE -y && \
      apt-get clean autoclean autoremove && rm -rf /var/lib/apt/lists/* /tmp/*.deb

#. Set IAR path and license server address:

    .. code-block:: dockerfile

      ENV PATH="/opt/iarsystems/bxarm/arm/bin/:/opt/iarsystems/bxarm/common/bin/:$PATH"
      ENV IAR_LICENSE_SERVER=$IAR_LICENSE_SERVER_IP

#. Finally create a ``run.sh`` script with the following content:

    .. code-block:: sh
    
      lightlicensemanager setup -s license.iar.public
      exec "$@"