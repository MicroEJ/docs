Execution
=========

LINKER can be invoked through an ANT task. The task is installed by
inserting the following code in an ANT script

::

       <taskdef 
           name="linker"
           classname="com.is2t.linker.GenericLinkerTask" 
           classpath="[LINKER_CLASSPATH]" 
       />

``[LINKER_CLASSPATH]`` is a list of path-separated jar files, including
the linker and all architecture-specific library loaders.

The following code shows a linker ANT task invocation and available
options.

::

       <linker
           doNotLoadAlreadyDefinedSymbol="[true|false]"
           endianness="[little|big|none]"
           generateMapFile="[true|false]"
           ignoreWrongPositioningForEmptySection="[true|false]"
           lsc="[filename]" 
           linkPath="[path1:...pathN]"
           mergeSegmentSections="[true|false]"
           noWarning="[true|false]"
           outputArchitecture="[tag]"
           outputName="[name]" 
           stripDebug="[true|false]" 
           toDir="[outputDir]" 
           verboseLevel="[0...9]"
       > 
               <!-- ELF object & archives files using ANT paths / filesets --> 
               <fileset dir="xxx" includes="*.o"> 
               <fileset file="xxx.a">
               <fileset file="xxx.a">
       
               <!-- Properties that will be reported into .map file --> 
               <property name="myProp" value="myValue"/>        
       </linker>

.. table:: Linker Options Details

   +-------------------------+--------------------------------------------+
   | Option                  | Description                                |
   +=========================+============================================+
   | ``doNotLoa              | Silently skip the load of a global symbol  |
   | dAlreadyDefinedSymbol`` | if it has already been loaded before.      |
   |                         | (``false`` by default. Only the first      |
   |                         | loaded symbol is taken into account (in    |
   |                         | the order input files are declared). This  |
   |                         | option only affects the load semantic for  |
   |                         | global symbols, and does not modify the    |
   |                         | semantic for loading weak symbols and      |
   |                         | local symbols.                             |
   +-------------------------+--------------------------------------------+
   | ``endianness``          | Explicitly declare linker endianness       |
   |                         | ``[little,                                 |
   |                         |                                            |
   |                         |                                     big]`` |
   |                         | or ``[none]`` for auto-detection. All      |
   |                         | input files must declare the same          |
   |                         | endianness or an error is thrown.          |
   +-------------------------+--------------------------------------------+
   | ``generateMapFile``     | Generate the ``.map`` file (``true`` by    |
   |                         | default).                                  |
   +-------------------------+--------------------------------------------+
   | ``ignoreWrongPositi     | Silently ignore wrong section positioning  |
   | oningFor EmptySection`` | for zero size sections. (``false`` by      |
   |                         | default).                                  |
   +-------------------------+--------------------------------------------+
   | ``lsc``                 | Provide a master lsc file. This option is  |
   |                         | mandatory unless the ``linkPath`` option   |
   |                         | is set.                                    |
   +-------------------------+--------------------------------------------+
   | ``linkPath``            | Provide a set of directories into which to |
   |                         | load link file fragments. Directories are  |
   |                         | separated with a platform-path separator.  |
   |                         | This option is mandatory unless the        |
   |                         | ``lsc`` option is set.                     |
   +-------------------------+--------------------------------------------+
   | ``noWarning``           | Silently skip the output of warning        |
   |                         | messages.                                  |
   +-------------------------+--------------------------------------------+
   | `                       | (*experimental*). Generate a single        |
   | `mergeSegmentSections`` | section per segment. This may speed up the |
   |                         | load of the output executable file into    |
   |                         | debuggers or flasher tools. (``false`` by  |
   |                         | default).                                  |
   +-------------------------+--------------------------------------------+
   | ``outputArchitecture``  | Set the architecture tag for the output    |
   |                         | ELF file (ELF machine id).                 |
   +-------------------------+--------------------------------------------+
   | ``outputName``          | Specify the output name of the generated   |
   |                         | files. By default, take the name provided  |
   |                         | in the lsc tag. The output ELF executable  |
   |                         | filename will be name.out. The map         |
   |                         | filename will be name.map.                 |
   +-------------------------+--------------------------------------------+
   | ``stripDebug``          | Remove all debug information from the      |
   |                         | output ELF file. A stripped output ELF     |
   |                         | executable holds only the binary image (no |
   |                         | remaining symbols, debug sections, etc.).  |
   +-------------------------+--------------------------------------------+
   | ``toDir``               | Specify the output directory in which to   |
   |                         | store generated files. Output filenames    |
   |                         | are in the form:                           |
   |                         | ``od + separator + value of                |
   |                         |                                            |
   |                         |         the lsc name attribute + suffix``. |
   |                         | By default, without this option, files are |
   |                         | generated in the directory from which the  |
   |                         | linker was launched.                       |
   +-------------------------+--------------------------------------------+
   | ``verboseLevel``        | Print additional messages on the standard  |
   |                         | output about linking process.              |
   +-------------------------+--------------------------------------------+
