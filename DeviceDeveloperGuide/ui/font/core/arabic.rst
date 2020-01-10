Arabic Support
==============

The font engine manages the ARABIC font specificities: the diacritics
and contextual letters. Contrary to the LATIN fonts, some ARABIC
characters can overlap another character. When a character must overlap
the previous character in the text, the font engine repositions the X
coordinate before rendering the new character (instead of placing the
next character just after the previous one).

To render an Arabic text, the font engine requires several points:

-  To determinate if a character has to overlap the previous character,
   the font engine uses a specific range of ARABIC characters: from
   ``0xfe70`` to ``0xfefc``. All others characters (ARABIC or not)
   outside this range are considered *classic* and no overlap is
   performed. Note that several ARABIC characters are available outside
   this range, but the same characters (same representation) are
   available inside this range.

-  The application strings must use the UTF-8 encoding. Furthermore, in
   order to force the use of characters in the range ``0xfe70`` to
   ``0xfefc``, the string must be filled with the following syntax:
   '``\ufee2\ufedc\ufe91\u0020\ufe8e\ufe92\ufea3\ufeae\ufee3``'; where
   ``\uxxxx`` is the UTF-8 character encoding.

-  The application string and its rendering are always performed from
   left to right. However the string contents are managed by the
   application itself, and so can be filled from right to left. To write
   the text: the string characters must be :
   '``\ufee2\ufedc\ufe91\u0020\ufe8e\ufe92\ufea3\ufeae\ufee3``'. The
   font engine will first render the character '``\ufee2``', then
   '``\ufedc``,' and so on.

-  Each character in the font (in the ``ejf`` file) must have a
   rendering compatible with the character position. The character will
   be rendered by the font engine as-is. No support is performed by the
   font engine to obtain a *linear* text.
