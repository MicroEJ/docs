External Resources
==================

The Font Engine Core is able to load some fonts located outside the CPU
addresses' space range. It uses the External Resource Loader.

When a font is located in such memory, the Font Engine Core copies a
very short part of the resource (the font file) into a RAM memory (into
CPU addresses space range): the font header. This header stays located
in RAM during the full MicroEJ application time. Then, on MicroEJ
application demand, the Font Engine Core loads some extra information
from the font into the RAM memory (the font meta data, the font pixels,
etc.). This extra information is automatically unloaded from RAM when
the Font Engine Core no longer needs them.
