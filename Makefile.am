############################
# FLAGS:                   #
############################

# tell automake to pass certain flags to autoconf on re-run
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

# tell automake to pass certain flags to 'ctags'
AM_CTAGSFLAGS = --extra=+f

#FIXME: don't assume GCC, do feature detection in configure.ac
# tell automake to pass certain CPPFLAGS to the compiler
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-pedantic-errors \
	-Wpedantic \
	-Wall \
	-Wextra \
	-Wdouble-promotion \
	-Wswitch-default \
	-fvisibility=hidden \
	-fvisibility-inlines-hidden

# initialize variables
EXTRA_DIST =
CLEANFILES =
BUILT_SOURCES = 
				
############################
# LIBRARIES TO BUILD:	   #
############################

# tell automake which libraries to build
lib_LTLIBRARIES = liblogichelpers.la

#----------------------------#
# liblogichelpers.la build options #
#----------------------------#

# list the names of the public header files of the liblogichelpers.la library
liblogichelpers_la_include_HEADERS = \
	include/logic/helpers \
	include/logic/global \
	\
	include/logic/Benchmark.hpp \
	include/logic/ConstEnumerator.hpp \
	include/logic/Enumerator.hpp \
	include/logic/EnumeratorSkeleton.hpp \
	include/logic/Id.hpp

# list all source code files for the liblogichelpers.la library
# don't need to list the generated .cc files from bison and flex
# since automake already knows about them, and adds them automatically
liblogichelpers_la_SOURCES = \
	src/assembly.cpp \
	src/preamble.h \
	\
	src/Benchmark.cpp


# tell automake that the installation directory for public header files of the
# liblogichelpers.la library should be a subfolder in the default ${includedir}
liblogichelpers_la_includedir = ${includedir}/logic

# tell libtool to pass certain LDFLAGS to the compiler when building libsharp.la
#
# 1) Specify the Shared Object Version Information for the library, which
# consists of three numbers: CURRENT:REVISION:AGE
#
#   CURRENT: This is the version of the (external) ABI in the library.
#       Increase if the ABI changes (i.e. interfaces added or changed)!
#
#   REVISION: The revision represents how often the library was changed for a
#       given ABI version. Increase this whenever the library code changes, but
#       reset to 0 when incrementing CURRENT.
#
#   AGE: This is the difference between the oldest and newest ABI version
#       that the library is backwards compatible with (e.g. if CURRENT is 4,
#       but we are backwards compatible to ABI version 1, then AGE = 3). Set to
#       0 if there is a backwards-compatibility breaking change, otherwise
#       increase by 1 if CURRENT was increased by one.
#
liblogichelpers_la_LDFLAGS = -version-info 0:0:0

############################
# DISTRIBUTION OPTIONS:	   #
############################

# tell automake about scripts that should be distributed in the tarball, but
# not installed on "make install"
dist_noinst_SCRIPTS = autogen.sh

# tell automake to clean the generated files on "make clean"
CLEANFILES += $(BUILT_SOURCES)

############################
# UNIT TESTS:              #
############################

# tell automake to recursively go into the test directory
SUBDIRS = tests
