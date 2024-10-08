#!/bin/bash

# Uninstall library
arduino-cli lib uninstall me_MemorySegment

# Uninstall dependencies
arduino-cli lib uninstall \
  me_Console \
  me_MemoryPoint \
  me_BaseTypes
