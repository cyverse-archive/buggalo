# Name

Buggalo - phylogenetic tree extractor.

# Version

This documentation refers to Buggalo version 0.0.1.

# Usage

```
buggalo -f nexus -i filename.nexus -p tree
buggalo --file nexus --input filename.nexus --prefix tree
```

# Required Arguments

## --format -f

This argument is used to specify the format of the input file.  The value of
this argument can be any format that is accepted by the Nexus Class Library.
For a complete list of available formats, see
[http://phylo.bio.ku.edu/ncldocs/v2.1/funcdocs/nxsmultiformat_8cpp_source.html].

## --input -i

This argument is used to specify the path to the input file.

# Options

## --prefix -p

This argument is used to specify the file name prefix to use when naming
output files in the event that the tree has no name associated with it.  For
example, if the input file contains three unnamed trees and the prefix is
configured to be `tree` then the names of the output files will be
`tree_0.tre`, `tree_1.tre` and `tree_2.tre`.  If the tree is named then the
actual tree name will be used as the base file name.

If this argument is not specified on the command line, the file name prefix
defaults to `tree`.

# Description

Buggalo is a simple command-line utility for extracting phylogenetic trees
from several different file formats and writing each tree to a separate file
in [Newick](http://evolution.genetics.washington.edu/phylip/newicktree.html)
format.  Buggalo uses the [Nexus Class Library](http://ncl.sourceforge.net/)
to parse the input files and generate the output files.

# Diagnostics

This program prints an error message for any exception that is thrown by the
Nexus Class Library.

# Dependencies

## Nexus Class Library - 2.1.18

This library must be installed before buggalo can be built or used.

# Bugs and Limitations

There tends to be a lot of variation within each phylogenetic file format, so
there are several files that may be accepted by some tools that aren't
accepted by buggalo.  In general, any file that is not accepted by the Nexus
Class Library will not be accepted by buggalo.

Please report problems to the core software development team.  Patches are
welcome.
