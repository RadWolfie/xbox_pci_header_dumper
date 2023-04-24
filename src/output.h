// SPDX-FileCopyrightText: Xbox PCI Header Dumper authors
// SPDX-License-Identifier: MIT

#pragma once

#include <xboxkrnl/xboxkrnl.h>

void print(char* str, ...);

void open_output_file(char*);
BOOL close_output_file();
