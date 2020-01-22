Map File Interpretor
====================

The map file interpretor is a tool that allows you to read, classify and
display memory information dumped by the linker map file. The map file
interpretor is a graph-oriented tool. It supports graphs of symbols and
allows standard operations on them (union, intersection, subtract,
etc.). It can also dump graphs, compute graph total sizes, list graph
paths, etc.

The map file interpretor uses the standard Java regular expression
syntax.

It is used internally by the graphical `??? <#memorymapanalyzer>`__
tool.

Commands:

-  ::

      createGraph graphName symbolRegExp ... section=regexp

   ::

      createGraph all section=.*          

   Recursively create a graph of symbols from root symbols and sections
   described as regular expressions. For example, to extract the
   complete graph of the application:

-  ::

      createGraphNoRec symbolRegExp ... section=regexp

   The above line is similar to the previous statement, but embeds only
   declared symbols and sections (without recursive connections).

-  ::

      removeGraph graphName

   Removes the graph for memory.

-  ::

      listGraphs

   Lists all the created graphs in memory.

-  ::

      listSymbols graphName

   Lists all graph symbols.

-  ::

      listPadding

   Lists the padding of the application.

-  ::

      listSections graphName

   Lists all sections targeted by all symbols of the graph.

-  ::

      inter graphResult g1 ... gn

   Creates a graph which is the intersection of ``g1/\ ... /\gn``.

-  ::

      union graphResult g1 ... gn

   Creates a graph which is the union of ``g1\/ ...\/ gn``.

-  ::

      substract graphResult g1 ... gn

   Creates a graph which is the substract of ``g1\ ... \ gn``.

-  ::

      reportConnections graphName

   Prints the graph connections.

-  ::

      totalImageSize graphName

   Prints the image size of the graph.

-  ::

      totalDynamicSize graphName

   Prints the dynamic size of the graph.

-  ::

      accessPath symbolName

   The above line prints one of the paths from a root symbol to this
   symbol. This is very useful in helping you understand why a symbol is
   embedded.

-  ::

      echo arguments

   Prints raw text.

-  ::

      exec commandFile

   Execute the given commandFile. The path may be absolute or relative
   from the current command file.
