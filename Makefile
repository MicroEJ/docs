# You can set these variables from the command line
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = .
BUILDDIR      = _build
PANDOC        ?= pandoc

# For the docbook to reST conversion
sources := \
	$(wildcard SandboxedAppDevGuide/*.dbk)

targets := $(patsubst %.dbk, %.rst, $(sources))

source_format := docbook
target_format := rst+simple_tables-grid_tables

# List tables is on a development version of pandoc
# https://github.com/jgm/pandoc/pull/4780
pandoc_options = --list-tables

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

convert: $(targets)

format:
	echo $(sources) | tr ' ' '\n' | xargs -t -I% \
		xmlformat --preserve "pre,literal,programlisting" --outfile % %

clean-convert:
	rm $(targets)

%.rst: %.dbk
	$(PANDOC) -f $(source_format) -t $(target_format) -o $@ $(pandoc_options) < $?

.PHONY: help Makefile convert clean-convert html

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
#%: Makefile
clean html: Makefile $(targets)
	$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
