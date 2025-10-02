.. _default_vee_port_application:

===================
Default Application
===================

As of :ref:`Architecture 8.1.0 <changelog-8.1.0>`, a default pre-built application (``microejapp.o``) is provided with the VEE Port.
It simplifies the early-stage integration into a BSP project by eliminating the need to create and build an Application project within the SDK,
thereby removing the requirement to obtain a valid SDK license.

The default pre-built application is available at ``[VEE_PORT_DIR]/defaultApp/microejapp.o``.
It prints a splash with :ref:`architecture_characteristics` on the standard output:

.. code-block::
    
    MicroEJ START

    ,--.   ,--.,--.                    ,------.     ,--. ,--.   ,--.,------.,------.
    |   `.'   |`--' ,---.,--.--. ,---. |  .---'     |  |  \  `.'  / |  .---'|  .---'
    |  |'.'|  |,--.| .--'|  .--'| .-. ||  `--, ,--. |  |   \     /  |  `--, |  `--,
    |  |   |  ||  |\ `--.|  |   ' '-' '|  `---.|  '-'  /    \   /   |  `---.|  `---.
    `--'   `--'`--' `---'`--'    `---' `------' `-----'      `-'    `------'`------'

                                      **********
                                  ********************
                                *************************
                            ******************************
                            **********+=--::::--=++**********
                          *******++:...           ..:=+*******
                        ******+:..                  ...+******
                        *****+:.                        .:+*****
                        ****+....--.                .:-:  .=****
                        ***+...:****-.             .****=...=****
                      ****-...=****+.             -****+...:****
                      ****:...-****=.             :****+...:+***
                      ****:....-++-                :++=....:+***
                        ***+........                 .......=****
                      ******=..........           .........-******
                      *******+.......++-:......:-=+:......=*******
                      *********=.......:=++++++=:.......-*********
                    ************+-..................:+************
                ******   ***********+=-:......:-=++**********   ******
                *****    #***********************************    *****
                  ***     #*********************************     ***
                    *****   ********************************   *****
                  ********  ##****************************  ********
                  ****   ***  ###***********************##  ***   ****
                  ***    *     ###******************###     *    ***
                    **           #####************#####           **
                                  ##################
                                    ##############
                                        ######




                              ::::::::::::::::::::::::::::
                                ::::::::::::::::::::::

    You successfully linked your first Application with the following Architecture characteristics:
    - Name:                         atsauce6
    - Version:                      8.1.0 (20231220-1011)
    - Usage:                        Production
    - Core Engine Capability:       Multi-Sandbox
    - Instruction Set Architecture: x86
    - Compilation Toolchain:        GNU GCC (GNUvX_X86Linux)
    MicroEJ END (exit code = 0)

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
