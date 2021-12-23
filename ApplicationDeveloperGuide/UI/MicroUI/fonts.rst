.. _section.ui.Fonts:

Fonts
=====

Overview
--------

Fonts are graphical resources that can be accessed with a call to `ej.microui.display.Font.getFont() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Font.html#getFont-java.lang.String->`_. To be displayed, these fonts have
to be converted at build-time from their source format to the display
raw format by the font generator tool. Fonts that must be processed by
the font generator tool are declared in MicroEJ Classpath
``*.fonts.list`` files. The file format is a standard Java properties
file, each line representing a ``/`` separated resource path relative to
the MicroEJ classpath root referring to a MicroEJ font file (usually
with a ``.ejf`` file extension). The resource may be followed by
optional parameters which define :

-  some ranges of characters to embed in the final raw file;

-  the required pixel depth for transparency.

By default, all characters available in the input font file are
embedded, and the pixel depth is ``1`` (i.e 1 bit-per-pixel). Example:

::

   # The following font is embedded with all characters
   # without transparency
   com/mycompany/MyFont1.ejf

   # The following font is embedded with only the latin 
   # unicode range without transparency 
   com/mycompany/MyFont2.ejf:latin

   # The following font is embedded with all characters
   # with 2 levels of transparency
   com/mycompany/MyFont2.ejf::2

MicroEJ font files conventionally end with the ``.ejf`` suffix and are
created using the Font Designer (see :ref:`section.tool.fontdesigner`).

.. _fonts_list_grammar:

Configuration File
------------------

Here is the format of the ``*.fonts.list`` files.

::

   ConfigFile          ::= Line [ 'EOL' Line ]*
   Line                ::= FontPath [ ':' [ Ranges ] [ ':' BitsPerPixel ] ]
   FontPath            ::= Identifier [ '/' Identifier ]*
   Ranges              ::= Range [ ';' Range ]*
   Range               ::= CustomRangeList | KnownRange
   CustomRangeList     ::= CustomRange [ ',' CustomRange ]*
   CustomRange         ::= Number | Number '-'  Number
   KnownRange          ::= Name [ SubRangeList ]?
   SubRangeList        ::= '(' SubRange [ ',' SubRange ]* ')'
   SubRange            ::= Number | Number - Number
   Identifier          ::= 'a-zA-Z_$' [ 'a-zA-Z_$0-9' ]*
   Number              ::= Number16 | Number10
   Number16            ::= '0x' [ Digit16 ]+
   Number10            ::= [ Digit10 ]+
   Digit16             ::= 'a-fA-F0-9'
   Digit10             ::= '0-9'
   BitsPerPixel        ::= '1' | '2' | '4' | '8'

.. _fonts_range:

Font Range
----------

The first parameter is for specifying the font ranges to embed.
Selecting only a specific set of characters to embed reduces the memory
footprint. If unspecified, all characters of the font are embedded. 

Several ranges can be specified, separated by ``;``. There
are two ways to specify a character range: the custom range and the
known range.

Custom Range
~~~~~~~~~~~~

Allows the selection of raw Unicode character ranges.

Examples:

-  ``myfont:0x21-0x49``: Defines one range: embed all characters from 0x21 to 0x49
   (included);
-  ``myfont:0x21-0x49,0x55-0x75``: Defines a set of two ranges: embed all characters from 0x21 to 0x49 and from 0x55 to 0x75.
-  ``myfont:0x21-0x49,0x55``: Defines a set of one range and one character: embed all characters from 0x21 to 0x49 and character 0x55.

Known Range
~~~~~~~~~~~

A known range is a range available in the following table.

Examples:

-  ``myfont:basic_latin``: Embed all *Basic Latin* characters;
-  ``myfont:basic_latin;arabic``: Embed all *Basic Latin* characters,
   and all *Arabic* characters.

:ref:`The following table <table_unicodeRanges>` describes the available list of ranges
and sub-ranges (processed from the "Unicode Character Database" version
9.0.0 available on the official unicode website
 `<https://home.unicode.org/>`_ ).

.. _table_unicodeRanges:
.. tabularcolumns:: |p{5.5cm}|p{7cm}|p{1cm}|p{1cm}|
.. table:: Ranges

   +--------------------------+------------------------------------------------+--------+--------+
   | Name                     | Tag                                            | Start  | End    |
   +==========================+================================================+========+========+
   | Basic Latin              | basic_latin                                    | 0x0    | 0x7f   |
   +--------------------------+------------------------------------------------+--------+--------+
   | Latin-1 Supplement       | latin-1_supplement                             | 0x80   | 0xff   |
   +--------------------------+------------------------------------------------+--------+--------+
   | Latin Extended-A         | latin_extended-a                               | 0x100  | 0x17f  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Latin Extended-B         | latin_extended-b                               | 0x180  | 0x24f  |
   +--------------------------+------------------------------------------------+--------+--------+
   | IPA Extensions           | ipa_extensions                                 | 0x250  | 0x2af  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Spacing Modifier Letters | spacing_modifier_letters                       | 0x2b0  | 0x2ff  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Combining Diacritical    | combining_diacritical_marks                    | 0x300  | 0x36f  |
   | Marks                    |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Greek and Coptic         | greek_and_coptic                               | 0x370  | 0x3ff  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Cyrillic                 | cyrillic                                       | 0x400  | 0x4ff  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Cyrillic Supplement      | cyrillic_supplement                            | 0x500  | 0x52f  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Armenian                 | armenian                                       | 0x530  | 0x58f  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Hebrew                   | hebrew                                         | 0x590  | 0x5ff  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Arabic                   | arabic                                         | 0x600  | 0x6ff  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Syriac                   | syriac                                         | 0x700  | 0x74f  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Arabic Supplement        | arabic_supplement                              | 0x750  | 0x77f  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Thaana                   | thaana                                         | 0x780  | 0x7bf  |
   +--------------------------+------------------------------------------------+--------+--------+
   | NKo                      | nko                                            | 0x7c0  | 0x7ff  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Samaritan                | samaritan                                      | 0x800  | 0x83f  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Mandaic                  | mandaic                                        | 0x840  | 0x85f  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Arabic Extended-A        | arabic_extended-a                              | 0x8a0  | 0x8ff  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Devanagari               | devanagari                                     | 0x900  | 0x97f  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Bengali                  | bengali                                        | 0x980  | 0x9ff  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Gurmukhi                 | gurmukhi                                       | 0xa00  | 0xa7f  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Gujarati                 | gujarati                                       | 0xa80  | 0xaff  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Oriya                    | oriya                                          | 0xb00  | 0xb7f  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Tamil                    | tamil                                          | 0xb80  | 0xbff  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Telugu                   | telugu                                         | 0xc00  | 0xc7f  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Kannada                  | kannada                                        | 0xc80  | 0xcff  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Malayalam                | malayalam                                      | 0xd00  | 0xd7f  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Sinhala                  | sinhala                                        | 0xd80  | 0xdff  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Thai                     | thai                                           | 0xe00  | 0xe7f  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Lao                      | lao                                            | 0xe80  | 0xeff  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Tibetan                  | tibetan                                        | 0xf00  | 0xfff  |
   +--------------------------+------------------------------------------------+--------+--------+
   | Myanmar                  | myanmar                                        | 0x1000 | 0x109f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Georgian                 | georgian                                       | 0x10a0 | 0x10ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Hangul Jamo              | hangul_jamo                                    | 0x1100 | 0x11ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Ethiopic                 | ethiopic                                       | 0x1200 | 0x137f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Ethiopic Supplement      | ethiopic_supplement                            | 0x1380 | 0x139f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Cherokee                 | cherokee                                       | 0x13a0 | 0x13ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Unified Canadian         | unified_canadian_aboriginal_syllabics          | 0x1400 | 0x167f |
   | Aboriginal Syllabics     |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Ogham                    | ogham                                          | 0x1680 | 0x169f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Runic                    | runic                                          | 0x16a0 | 0x16ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Tagalog                  | tagalog                                        | 0x1700 | 0x171f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Hanunoo                  | hanunoo                                        | 0x1720 | 0x173f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Buhid                    | buhid                                          | 0x1740 | 0x175f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Tagbanwa                 | tagbanwa                                       | 0x1760 | 0x177f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Khmer                    | khmer                                          | 0x1780 | 0x17ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Mongolian                | mongolian                                      | 0x1800 | 0x18af |
   +--------------------------+------------------------------------------------+--------+--------+
   | Unified Canadian         | unified_canadian_aboriginal_syllabics_extended | 0x18b0 | 0x18ff |
   | Aboriginal Syllabics     |                                                |        |        |
   | Extended                 |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Limbu                    | limbu                                          | 0x1900 | 0x194f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Tai Le                   | tai_le                                         | 0x1950 | 0x197f |
   +--------------------------+------------------------------------------------+--------+--------+
   | New Tai Lue              | new_tai_lue                                    | 0x1980 | 0x19df |
   +--------------------------+------------------------------------------------+--------+--------+
   | Khmer Symbols            | khmer_symbols                                  | 0x19e0 | 0x19ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Buginese                 | buginese                                       | 0x1a00 | 0x1a1f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Tai Tham                 | tai_tham                                       | 0x1a20 | 0x1aaf |
   +--------------------------+------------------------------------------------+--------+--------+
   | Combining Diacritical    | combining_diacritical_marks_extended           | 0x1ab0 | 0x1aff |
   | Marks Extended           |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Balinese                 | balinese                                       | 0x1b00 | 0x1b7f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Sundanese                | sundanese                                      | 0x1b80 | 0x1bbf |
   +--------------------------+------------------------------------------------+--------+--------+
   | Batak                    | batak                                          | 0x1bc0 | 0x1bff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Lepcha                   | lepcha                                         | 0x1c00 | 0x1c4f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Ol Chiki                 | ol_chiki                                       | 0x1c50 | 0x1c7f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Cyrillic Extended-C      | cyrillic_extended-c                            | 0x1c80 | 0x1c8f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Sundanese Supplement     | sundanese_supplement                           | 0x1cc0 | 0x1ccf |
   +--------------------------+------------------------------------------------+--------+--------+
   | Vedic Extensions         | vedic_extensions                               | 0x1cd0 | 0x1cff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Phonetic Extensions      | phonetic_extensions                            | 0x1d00 | 0x1d7f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Phonetic Extensions      | phonetic_extensions_supplement                 | 0x1d80 | 0x1dbf |
   | Supplement               |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Combining Diacritical    | combining_diacritical_marks_supplement         | 0x1dc0 | 0x1dff |
   | Marks Supplement         |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Latin Extended           | latin_extended_additional                      | 0x1e00 | 0x1eff |
   | Additional               |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Greek Extended           | greek_extended                                 | 0x1f00 | 0x1fff |
   +--------------------------+------------------------------------------------+--------+--------+
   | General Punctuation      | general_punctuation                            | 0x2000 | 0x206f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Superscripts and         | superscripts_and_subscripts                    | 0x2070 | 0x209f |
   | Subscripts               |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Currency Symbols         | currency_symbols                               | 0x20a0 | 0x20cf |
   +--------------------------+------------------------------------------------+--------+--------+
   | Combining Diacritical    | combining_diacritical_marks_for_symbols        | 0x20d0 | 0x20ff |
   | Marks for Symbols        |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Letterlike Symbols       | letterlike_symbols                             | 0x2100 | 0x214f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Number Forms             | number_forms                                   | 0x2150 | 0x218f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Arrows                   | arrows                                         | 0x2190 | 0x21ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Mathematical Operators   | mathematical_operators                         | 0x2200 | 0x22ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Miscellaneous Technical  | miscellaneous_technical                        | 0x2300 | 0x23ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Control Pictures         | control_pictures                               | 0x2400 | 0x243f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Optical Character        | optical_character_recognition                  | 0x2440 | 0x245f |
   | Recognition              |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Enclosed Alphanumerics   | enclosed_alphanumerics                         | 0x2460 | 0x24ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Box Drawing              | box_drawing                                    | 0x2500 | 0x257f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Block Elements           | block_elements                                 | 0x2580 | 0x259f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Geometric Shapes         | geometric_shapes                               | 0x25a0 | 0x25ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Miscellaneous Symbols    | miscellaneous_symbols                          | 0x2600 | 0x26ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Dingbats                 | dingbats                                       | 0x2700 | 0x27bf |
   +--------------------------+------------------------------------------------+--------+--------+
   | Miscellaneous            | miscellaneous_mathematical_symbols-a           | 0x27c0 | 0x27ef |
   | Mathematical Symbols-A   |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Supplemental Arrows-A    | supplemental_arrows-a                          | 0x27f0 | 0x27ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Braille Patterns         | braille_patterns                               | 0x2800 | 0x28ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Supplemental Arrows-B    | supplemental_arrows-b                          | 0x2900 | 0x297f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Miscellaneous            | miscellaneous_mathematical_symbols-b           | 0x2980 | 0x29ff |
   | Mathematical Symbols-B   |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Supplemental             | supplemental_mathematical_operators            | 0x2a00 | 0x2aff |
   | Mathematical Operators   |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Miscellaneous Symbols    | miscellaneous_symbols_and_arrows               | 0x2b00 | 0x2bff |
   | and Arrows               |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Glagolitic               | glagolitic                                     | 0x2c00 | 0x2c5f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Latin Extended-C         | latin_extended-c                               | 0x2c60 | 0x2c7f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Coptic                   | coptic                                         | 0x2c80 | 0x2cff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Georgian Supplement      | georgian_supplement                            | 0x2d00 | 0x2d2f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Tifinagh                 | tifinagh                                       | 0x2d30 | 0x2d7f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Ethiopic Extended        | ethiopic_extended                              | 0x2d80 | 0x2ddf |
   +--------------------------+------------------------------------------------+--------+--------+
   | Cyrillic Extended-A      | cyrillic_extended-a                            | 0x2de0 | 0x2dff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Supplemental Punctuation | supplemental_punctuation                       | 0x2e00 | 0x2e7f |
   +--------------------------+------------------------------------------------+--------+--------+
   | CJK Radicals Supplement  | cjk_radicals_supplement                        | 0x2e80 | 0x2eff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Kangxi Radicals          | kangxi_radicals                                | 0x2f00 | 0x2fdf |
   +--------------------------+------------------------------------------------+--------+--------+
   | Ideographic Description  | ideographic_description_characters             | 0x2ff0 | 0x2fff |
   | Characters               |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | CJK Symbols and          | cjk_symbols_and_punctuation                    | 0x3000 | 0x303f |
   | Punctuation              |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Hiragana                 | hiragana                                       | 0x3040 | 0x309f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Katakana                 | katakana                                       | 0x30a0 | 0x30ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Bopomofo                 | bopomofo                                       | 0x3100 | 0x312f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Hangul Compatibility     | hangul_compatibility_jamo                      | 0x3130 | 0x318f |
   | Jamo                     |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Kanbun                   | kanbun                                         | 0x3190 | 0x319f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Bopomofo Extended        | bopomofo_extended                              | 0x31a0 | 0x31bf |
   +--------------------------+------------------------------------------------+--------+--------+
   | CJK Strokes              | cjk_strokes                                    | 0x31c0 | 0x31ef |
   +--------------------------+------------------------------------------------+--------+--------+
   | Katakana Phonetic        | katakana_phonetic_extensions                   | 0x31f0 | 0x31ff |
   | Extensions               |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Enclosed CJK Letters and | enclosed_cjk_letters_and_months                | 0x3200 | 0x32ff |
   | Months                   |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | CJK Compatibility        | cjk_compatibility                              | 0x3300 | 0x33ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | CJK Unified Ideographs   | cjk_unified_ideographs_extension_a             | 0x3400 | 0x4dbf |
   | Extension A              |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Yijing Hexagram Symbols  | yijing_hexagram_symbols                        | 0x4dc0 | 0x4dff |
   +--------------------------+------------------------------------------------+--------+--------+
   | CJK Unified Ideographs   | cjk_unified_ideographs                         | 0x4e00 | 0x9fff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Yi Syllables             | yi_syllables                                   | 0xa000 | 0xa48f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Yi Radicals              | yi_radicals                                    | 0xa490 | 0xa4cf |
   +--------------------------+------------------------------------------------+--------+--------+
   | Lisu                     | lisu                                           | 0xa4d0 | 0xa4ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Vai                      | vai                                            | 0xa500 | 0xa63f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Cyrillic Extended-B      | cyrillic_extended-b                            | 0xa640 | 0xa69f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Bamum                    | bamum                                          | 0xa6a0 | 0xa6ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Modifier Tone Letters    | modifier_tone_letters                          | 0xa700 | 0xa71f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Latin Extended-D         | latin_extended-d                               | 0xa720 | 0xa7ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Syloti Nagri             | syloti_nagri                                   | 0xa800 | 0xa82f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Common Indic Number      | common_indic_number_forms                      | 0xa830 | 0xa83f |
   | Forms                    |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Phags-pa                 | phags-pa                                       | 0xa840 | 0xa87f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Saurashtra               | saurashtra                                     | 0xa880 | 0xa8df |
   +--------------------------+------------------------------------------------+--------+--------+
   | Devanagari Extended      | devanagari_extended                            | 0xa8e0 | 0xa8ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Kayah Li                 | kayah_li                                       | 0xa900 | 0xa92f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Rejang                   | rejang                                         | 0xa930 | 0xa95f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Hangul Jamo Extended-A   | hangul_jamo_extended-a                         | 0xa960 | 0xa97f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Javanese                 | javanese                                       | 0xa980 | 0xa9df |
   +--------------------------+------------------------------------------------+--------+--------+
   | Myanmar Extended-B       | myanmar_extended-b                             | 0xa9e0 | 0xa9ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Cham                     | cham                                           | 0xaa00 | 0xaa5f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Myanmar Extended-A       | myanmar_extended-a                             | 0xaa60 | 0xaa7f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Tai Viet                 | tai_viet                                       | 0xaa80 | 0xaadf |
   +--------------------------+------------------------------------------------+--------+--------+
   | Meetei Mayek Extensions  | meetei_mayek_extensions                        | 0xaae0 | 0xaaff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Ethiopic Extended-A      | ethiopic_extended-a                            | 0xab00 | 0xab2f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Latin Extended-E         | latin_extended-e                               | 0xab30 | 0xab6f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Cherokee Supplement      | cherokee_supplement                            | 0xab70 | 0xabbf |
   +--------------------------+------------------------------------------------+--------+--------+
   | Meetei Mayek             | meetei_mayek                                   | 0xabc0 | 0xabff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Hangul Syllables         | hangul_syllables                               | 0xac00 | 0xd7af |
   +--------------------------+------------------------------------------------+--------+--------+
   | Hangul Jamo Extended-B   | hangul_jamo_extended-b                         | 0xd7b0 | 0xd7ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | High Surrogates          | high_surrogates                                | 0xd800 | 0xdb7f |
   +--------------------------+------------------------------------------------+--------+--------+
   | High Private Use         | high_private_use_surrogates                    | 0xdb80 | 0xdbff |
   | Surrogates               |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Low Surrogates           | low_surrogates                                 | 0xdc00 | 0xdfff |
   +--------------------------+------------------------------------------------+--------+--------+
   | Private Use Area         | private_use_area                               | 0xe000 | 0xf8ff |
   +--------------------------+------------------------------------------------+--------+--------+
   | CJK Compatibility        | cjk_compatibility_ideographs                   | 0xf900 | 0xfaff |
   | Ideographs               |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Alphabetic Presentation  | alphabetic_presentation_forms                  | 0xfb00 | 0xfb4f |
   | Forms                    |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Arabic Presentation      | arabic_presentation_forms-a                    | 0xfb50 | 0xfdff |
   | Forms-A                  |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Variation Selectors      | variation_selectors                            | 0xfe00 | 0xfe0f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Vertical Forms           | vertical_forms                                 | 0xfe10 | 0xfe1f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Combining Half Marks     | combining_half_marks                           | 0xfe20 | 0xfe2f |
   +--------------------------+------------------------------------------------+--------+--------+
   | CJK Compatibility Forms  | cjk_compatibility_forms                        | 0xfe30 | 0xfe4f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Small Form Variants      | small_form_variants                            | 0xfe50 | 0xfe6f |
   +--------------------------+------------------------------------------------+--------+--------+
   | Arabic Presentation      | arabic_presentation_forms-b                    | 0xfe70 | 0xfeff |
   | Forms-B                  |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Halfwidth and Fullwidth  | halfwidth_and_fullwidth_forms                  | 0xff00 | 0xffef |
   | Forms                    |                                                |        |        |
   +--------------------------+------------------------------------------------+--------+--------+
   | Specials                 | specials                                       | 0xfff0 | 0xffff |
   +--------------------------+------------------------------------------------+--------+--------+

Transparency
------------

The second parameter is for specifying the font transparency level
(``1``, ``2``, ``4`` or ``8``). If unspecified, the encoded transparency level is ``1`` (does not depend on transparency level encoded in EJF file).

Examples:

-  ``myfont:latin:4``: Embed all latin characters with 16 levels of
   transparency

-  ``myfont::2``: Embed all characters with 4 levels of transparency

Font Generator Error Messages
-----------------------------

.. tabularcolumns:: |L|p{1.5cm}|L|

.. table:: Static Font Generator Error Messages

   +--------+---------+-----------------------------------------------------+
   | ID     | Type    | Description                                         |
   +========+=========+=====================================================+
   | 0      | Error   | The font generator has encountered an               |
   |        |         | unexpected internal error.                          |
   +--------+---------+-----------------------------------------------------+
   | 1      | Error   | The Fonts list file has not been specified.         |
   +--------+---------+-----------------------------------------------------+
   | 2      | Error   | The font generator cannot create the final,         |
   |        |         | raw file.                                           |
   +--------+---------+-----------------------------------------------------+
   | 3      | Error   | The font generator cannot read the fonts            |
   |        |         | list file.                                          |
   +--------+---------+-----------------------------------------------------+
   | 4      | Warning | The font generator has found no font to             |
   |        |         | generate.                                           |
   +--------+---------+-----------------------------------------------------+
   | 5      | Error   | The font generator cannot load the fonts            |
   |        |         | list file.                                          |
   +--------+---------+-----------------------------------------------------+
   | 6      | Warning | The specified font path is invalid: The font will   |
   |        |         | be not converted.                                   |
   +--------+---------+-----------------------------------------------------+
   | 7      | Warning | There are too many arguments on a line: the         |
   |        |         | current entry is ignored.                           |
   +--------+---------+-----------------------------------------------------+
   | 8      | Error   | The font generator has encountered an               |
   |        |         | unexpected internal error (invalid output format).  |
   +--------+---------+-----------------------------------------------------+
   | 9      | Error   | The font generator has encountered an               |
   |        |         | unexpected internal error (invalid endianness).     |
   +--------+---------+-----------------------------------------------------+
   | 10     | Error   | The specified entry is invalid.                     |
   +--------+---------+-----------------------------------------------------+
   | 11     | Error   | The specified entry does not contain a list of      |
   |        |         | characters.                                         |
   +--------+---------+-----------------------------------------------------+
   | 12     | Error   | The specified entry does not contain a list of      |
   |        |         | identifiers.                                        |
   +--------+---------+-----------------------------------------------------+
   | 13     | Error   | The specified entry is an invalid width.            |
   +--------+---------+-----------------------------------------------------+
   | 14     | Error   | The specified entry is an invalid height.           |
   +--------+---------+-----------------------------------------------------+
   | 15     | Error   | The specified entry does not contain the            |
   |        |         | characters' addresses.                              |
   +--------+---------+-----------------------------------------------------+
   | 16     | Error   | The specified entry does not contain the            |
   |        |         | characters' bitmaps.                                |
   +--------+---------+-----------------------------------------------------+
   | 17     | Error   | The specified entry bits-per-pixel value is         |
   |        |         | invalid.                                            |
   +--------+---------+-----------------------------------------------------+
   | 18     | Error   | The specified range is invalid.                     |
   +--------+---------+-----------------------------------------------------+
   | 19     | Error   | There are too many identifiers. The output RAW      |
   |        |         | format cannot store all identifiers.                |
   +--------+---------+-----------------------------------------------------+
   | 20     | Error   | The font's name is too long. The output RAW format  |
   |        |         | cannot store all name characters.                   |
   +--------+---------+-----------------------------------------------------+
   | 21     | Error   | There are too many ranges. The output RAW           |
   |        |         | format cannot store all ranges.                     |
   +--------+---------+-----------------------------------------------------+
   | 22     | Error   | Output list files cannot be created.                |
   +--------+---------+-----------------------------------------------------+
   | 23     | Error   | Dynamic styles are not supported. Only a PLAIN font |
   |        |         | can be encoded.                                     |
   +--------+---------+-----------------------------------------------------+
   | 24     | Error   | Underlined style is not supported. Only a BOLD and  |
   |        |         | ITALIC font can be set.                             |
   +--------+---------+-----------------------------------------------------+

Default Character
-----------------

The application can ask the rendering of a string whose some characters are not available in selected font. 
In that case, a default character is drawn instead: it is the first available character in the font.
The font's characters are stored by unicode values.
When the font has been :ref:`cropped <fonts_range>`, the default character is the the first character of the first range.
Consequently, the default character may not the same between two fonts.

.. note:: The first available character in a font is often the exclamation mark (``0x21``). 

The font maker should store in the font a default character (for instance a rectangle).
This character must have the first character index (index ``0`` is allowed).

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
