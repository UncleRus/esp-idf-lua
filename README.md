# Lua component for ESP-IDF

https://www.lua.org

Version 5.4.4

## What is Lua?

Lua is a powerful, efficient, lightweight, embeddable scripting language. 
It supports procedural programming, object-oriented programming, functional
programming, data-driven programming, and data description.

Lua combines simple procedural syntax with powerful data description
constructs based on associative arrays and extensible semantics. Lua is
dynamically typed, runs by interpreting bytecode with a register-based
virtual machine, and has automatic memory management with incremental
garbage collection, making it ideal for configuration, scripting, and
rapid prototyping. 

## How to use

Clone this repository into `components` subdir of yout project:

```Shell
cd ~/my_esp_idf_project
mkdir components
cd components
git clone https://github.com/UncleRus/esp-idf-lua.git
```

Or clone it to any other directory and add it to your project `Makefile` or `CMakeLists.txt`:

```Makefile
PROJECT_NAME := my-esp-project
EXTRA_COMPONENT_DIRS := $(HOME)/my/work/path/esp-idf-lua
include $(IDF_PATH)/make/project.mk
```

```cmake
cmake_minimum_required(VERSION 3.5)
set(EXTRA_COMPONENT_DIRS $ENV{HOME}/my/work/path/esp-idf-lua)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(my-esp-project)
```

See examples.
