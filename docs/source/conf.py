# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))

# -- Project information -----------------------------------------------------

project = 'libsa'
copyright = '2022, Stirling Labs'
author = 'Stirling Labs'
html_logo = "../../libsa.jpg"

# The full version, including alpha/beta/rc tags
release = '22.03.1'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    'sphinx.ext.duration',
    'sphinx.ext.githubpages',
    'hawkmoth',
    "sphinx_multiversion",
    "myst_parser",
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = []

# -- Hawkmoth ---------------------------------------------------------------

import os
cautodoc_root = os.path.abspath('../../')

from hawkmoth.util import compiler
cautodoc_clang = compiler.get_include_args()

from hawkmoth.util import doccompat
cautodoc_transformations = {
    'javadoc-basic': doccompat.javadoc,
    'javadoc-liberal': doccompat.javadoc_liberal,
    'kernel-doc': doccompat.kerneldoc,
}
# To get around issue on GitHub Actions
#from clang.cindex import Config         
#Config.set_library_file('libclang.so')

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'furo'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

# Controls whether you see the project’s name in the sidebar of the documentation. 
# This is useful when you only want to show your documentation’s logo in the sidebar. 
# The default is False.
html_theme_options = {
    "sidebar_hide_name": True,
}

templates_path = ["_templates"]

html_sidebars = {
    "**": [
        "sidebar/brand.html",
        "sidebar/search.html",
        "sidebar/version.html",
        "sidebar/scroll-start.html",
        "sidebar/navigation.html",
        "sidebar/scroll-end.html",
        "sidebar/sphinx-multiversion.html",
    ]
}
# -- Multi-Version settings -------------------------------------------------

# Whitelist pattern for tags (set to None to ignore all tags)
smv_whitelist_tags = r'^v\d+\.\d+\.\d+$'
# Pattern for released versions
smv_released_pattern = r'^tags/v\d+\.\d+\.\d+$'

