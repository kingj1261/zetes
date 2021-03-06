APPLICATION_NAME = ZetesWings

ZETES_PATH = ..

include ../common-scripts/globals.mk

SRC = src
BIN = bin
OBJ = obj
LIB = lib

DEBUG_OPTIMIZE = -O0 -g

ifeq ($(UNAME), Darwin)	# OS X
  JAVA_HOME = $(shell /usr/libexec/java_home)
  PLATFORM_GENERAL_INCLUDES = -I"$(JAVA_HOME)/include" -I"$(JAVA_HOME)/include/darwin"
else ifeq ($(UNAME), Linux)			# linux
  PLATFORM_GENERAL_INCLUDES = -I"$(JAVA_HOME)/include" -I"$(JAVA_HOME)/include/linux"
else ifeq ($(OS) $(ARCH), Windows_NT i686)	# Windows
  PLATFORM_GENERAL_INCLUDES = -I"$(JAVA_HOME)/include" -I"$(JAVA_HOME)/include/win32"
else ifeq ($(OS) $(ARCH), Windows_NT x86_64)	# Windows
  PLATFORM_GENERAL_INCLUDES = -I"$(JAVA_HOME)/include" -I"$(JAVA_HOME)/include/win32"
endif

ZETES_FEET_INCLUDE = -I$(ZETES_FEET_PATH)/include

# Java platform agnostic
JAVA_SOURCE_PATH = $(SRC)/java
JAVA_FILES = $(shell cd $(JAVA_SOURCE_PATH); find . -type f -name \*.java | awk '{ sub(/.\//,"") }; 1')
JAVA_CLASSES = $(addprefix $(JAVA_CLASSPATH)/,$(addsuffix .class,$(basename $(JAVA_FILES))))

# Java platform specific
JAVA_PLATFORM_SPECIFIC_SOURCE_PATH = $(SRC)/$(PLATFORM_TAG)/java
JAVA_PLATFORM_SPECIFIC_FILES = $(shell if [ -d "$(JAVA_PLATFORM_SPECIFIC_SOURCE_PATH)" ]; then cd $(JAVA_PLATFORM_SPECIFIC_SOURCE_PATH); find . -type f -name \*.java | awk '{ sub(/.\//,"") }; 1'; fi)
JAVA_PLATFORM_SPECIFIC_CLASSES = $(addprefix $(JAVA_CLASSPATH)/,$(addsuffix .class,$(basename $(JAVA_PLATFORM_SPECIFIC_FILES))))

# C/C++ Platform agnostic
CPP_SOURCE_PATH = $(SRC)/cpp
CPP_FILES = $(shell cd $(CPP_SOURCE_PATH); find . -type f -name \*.cpp | awk '{ sub(/.\//,"") }; 1')
C_FILES = $(shell cd $(CPP_SOURCE_PATH); find . -type f -name \*.c | awk '{ sub(/.\//,"") }; 1')
CPP_HEADER_FILES = $(addprefix $(CPP_SOURCE_PATH)/,$(shell cd $(CPP_SOURCE_PATH); find . -type f -name \*.h | awk '{ sub(/.\//,"") }; 1'))
CPP_OBJECTS = $(addprefix $(OBJECTS_PATH)/,$(addsuffix .o,$(basename $(CPP_FILES))))
C_OBJECTS = $(addprefix $(OBJECTS_PATH)/,$(addsuffix .o,$(basename $(C_FILES))))

ZETES_FEET_JAR = $(ZETES_FEET_PATH)/$(LIB)/java/zetesfeet.jar
ZETES_FEET_LIB = $(ZETES_FEET_PATH)/$(LIB)/$(PLATFORM_TAG)/libzetesfeet.a

USER_MK = ZetesWings.mk

# Target paths
BINARY_PATH = $(TARGET)/$(BIN)/$(PLATFORM_TAG)
LIBRARY_PATH = $(TARGET)/$(LIB)/$(PLATFORM_TAG)
OBJECTS_PATH = $(TARGET)/$(OBJ)/$(PLATFORM_TAG)
JAVA_BINARY_PATH = $(TARGET)/$(BIN)/java
JAVA_LIBRARY_PATH = $(TARGET)/$(LIB)/java
JAVA_OBJECTS_PATH = $(TARGET)/$(OBJ)/java
JAVA_CLASSPATH = $(JAVA_OBJECTS_PATH)/classes

# Target names
LIBRARY_NAME = libzeteswings.a
JAVA_LIBRARY_NAME = zeteswings.jar
PACKAGE_NAME = zeteswings.zip

help:
	@echo "*** This is Zetes build utility ***"
	@echo
	@echo 1. Set up your build environment
	@echo Zetes library needs Java 7 compiler, so JAVA_HOME is to be set correctly. 
	@echo
	@echo Current value: JAVA_HOME=$(JAVA_HOME)
	@echo
	@echo To change it you can type:
	@echo
	@echo "  > export JAVA_HOME=<path>"
	@echo
	@echo Make sure that the current value ARCH=$(ARCH) is a correct architecture of the
	@echo target that you are going to build. If it\'s not, type
	@echo
	@echo "  > export ARCH=<arch>"
	@echo
	@echo "where <arch> is one of: i386, x86_64"
	@echo
	@echo 2. Build Zetes or config IDE 
	@echo To build the library right now from the command line, type 
	@echo
	@echo "  > make all"
	@echo
	@echo To setup project files for Eclipse CDT IDE, type
	@echo
	@echo "  > make ideconf-eclipse"
	@echo
	@echo To clean compiled binary files, type 
	@echo
	@echo "  > make clean"
	@echo

# Other files that should just be copied to the target folder 
JUST_COPY_FILES = $(USER_MK)
include ../common-scripts/just_copy.mk
	

all: $(LIBRARY_PATH)/$(LIBRARY_NAME) $(JAVA_LIBRARY_PATH)/$(JAVA_LIBRARY_NAME) $(JUST_COPY_FILES_TARGET)
	@echo "*** $(APPLICATION_NAME) building process completed successfully. ***"
	@echo You can find the result in folders:
	@echo
	@echo "  $(realpath $(LIBRARY_PATH))"
	@echo "  $(realpath $(JAVA_LIBRARY_PATH))"
	@echo

package: $(TARGET)/$(PACKAGE_NAME)

include ../common-scripts/ideconf/ideconf.mk

$(JAVA_CLASSPATH)/%.class: $(JAVA_SOURCE_PATH)/%.java swt_all $(ZETES_FEET_JAR)
	@echo [$(APPLICATION_NAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	"$(JAVA_HOME)/bin/javac" -encoding utf8 -sourcepath "$(JAVA_SOURCE_PATH)" -classpath "$(ZETES_FEET_JAR)$(CLASSPATH_DELIM)$(JAVA_CLASSPATH)" -d "$(JAVA_CLASSPATH)" $<

$(JAVA_CLASSPATH)/%.class: $(JAVA_PLATFORM_SPECIFIC_SOURCE_PATH)/%.java swt_all $(ZETES_FEET_JAR)
	@echo [$(APPLICATION_NAME)] Compiling platform specific $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	"$(JAVA_HOME)/bin/javac" -encoding utf8 -sourcepath "$(JAVA_PLATFORM_SPECIFIC_SOURCE_PATH)" -classpath "$(ZETES_FEET_JAR)$(CLASSPATH_DELIM)$(JAVA_CLASSPATH)" -d "$(JAVA_CLASSPATH)" $<

$(OBJECTS_PATH)/%.o: $(SRC)/cpp/%.cpp $(CPP_HEADER_FILES) $(ZETES_FEET_LIB)
	@echo [$(APPLICATION_NAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	g++ -std=c++0x $(DEBUG_OPTIMIZE) $(PIC) -D_JNI_IMPLEMENTATION_ -c -Iinclude -I"$(SRC)/cpp" $(ZETES_FEET_INCLUDE) $(PLATFORM_GENERAL_INCLUDES) $< -o $@

$(OBJECTS_PATH)/%.o: $(SRC)/cpp/%.c $(CPP_HEADER_FILES) $(ZETES_FEET_LIB)
	@echo [$(APPLICATION_NAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	gcc -std=c99 $(DEBUG_OPTIMIZE) $(PIC) -D_JNI_IMPLEMENTATION_ -c -Iinclude -I"$(SRC)/cpp" $(ZETES_FEET_INCLUDE) $(PLATFORM_GENERAL_INCLUDES) $< -o $@

# SWT

LIBSWT = $(CURDIR)/swt-static/$(PLATFORM_TAG)/target/libswt.a
swt_all: $(LIBSWT)
	@echo [$(APPLICATION_NAME)] Copying SWT classes...
	if [ ! -d "$(JAVA_CLASSPATH)" ]; then mkdir -p "$(JAVA_CLASSPATH)"; fi
	# Copying SWT classes
	(cd swt-static/$(PLATFORM_TAG)/target/classes; cp -rf * $(CURDIR)/$(JAVA_CLASSPATH)/)

$(LIBSWT):
	(cd $(CURDIR)/swt-static/$(PLATFORM_TAG); make)

# Zetes Feet

$(ZETES_FEET_LIB): zetesfeet
$(ZETES_FEET_JAR): zetesfeet

zetesfeet:
	(cd $(CURDIR)/../zetesfeet; make all)
	
# Target
	
$(LIBRARY_PATH)/$(LIBRARY_NAME): $(C_OBJECTS) $(CPP_OBJECTS) $(LIBSWT) $(ZETES_FEET_LIB)
	@echo [$(APPLICATION_NAME)] Constructing $@...
	mkdir -p $(LIBRARY_PATH);
	
	# Extracting libswt objects
	( \
	    cd $(OBJECTS_PATH); \
	    mkdir -p libswt; \
	    cd libswt; \
	    ar x $(LIBSWT); \
	)

	mkdir -p $(JAVA_LIBRARY_PATH)

	# Making an object file from the java class library
	
	ar rs $@ $(CPP_OBJECTS) $(C_OBJECTS)
	ar rs $@ $(OBJECTS_PATH)/libswt/*.o

$(JAVA_LIBRARY_PATH)/$(JAVA_LIBRARY_NAME): $(ZETES_FEET_JAR) $(JAVA_CLASSES) $(JAVA_PLATFORM_SPECIFIC_CLASSES) swt_all
	@echo [$(APPLICATION_NAME)] Constructing $@...
	mkdir -p $(JAVA_LIBRARY_PATH)
	# Making the java class library
	( \
	    set -e; \
	    mkdir -p $(LIBRARY_PATH); \
	    ( \
	        cd $(JAVA_LIBRARY_PATH); \
	        "$(JAVA_HOME)/bin/jar" cf $(JAVA_LIBRARY_NAME) -C $(CURDIR)/$(JAVA_CLASSPATH) .; \
	    ) \
	)

$(TARGET)/$(PACKAGE_NAME): all
	@echo [$(APPLICATION_NAME)] Making package file '$@'...
	( \
	    cd $(TARGET); \
	    zip $(PACKAGE_NAME) $(subst $(TARGET)/,,$(LIBRARY_PATH)/$(LIBRARY_NAME) $(JAVA_LIBRARY_PATH)/$(JAVA_LIBRARY_NAME)); \
	)


clean:
	@echo [$(APPLICATION_NAME)] Cleaning all...
	rm -rf $(TARGET)

.PHONY: help all package clean zetesfeet swt_all
#.SILENT:
