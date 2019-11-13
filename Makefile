# For the docbook to reST conversion
sources := $(wildcard *.dbk)
targets := $(patsubst %.dbk, %.rst, $(sources))

source_format := docbook
target_format := rst+simple_tables-grid_tables

# Enable list tables extension from development pandoc
# https://github.com/jgm/pandoc/pull/4780
has_list_tables_ext := $(shell pandoc --list-extensions | grep list_tables && echo "True")
ifdef has_list_tables_ext
	target_format := $(target_format)+list_tables
endif

# You can set these variables from the command line
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = .
BUILDDIR      = _build
PANDOC        ?= pandoc

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

convert: $(targets)

clean-convert:
	rm $(targets)

%.rst: %.dbk
	$(PANDOC) -f $(source_format) -t $(target_format) -o $@ $(pandoc_options) < $?

.PHONY: help Makefile convert clean-convert html

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
#%: Makefile
html: Makefile $(targets)
	$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
