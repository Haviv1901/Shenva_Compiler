#pragma once
#ifndef MASMANDLINK_H
#define MASMANDLINK_H
#define BAT_FILE_NAME "run.bat"
#include <stdio.h>
#include <stdlib.h>
#include "fileHelper.h"
#include <Windows.h>
#include <stdbool.h>

void runMasmAndLink(const char* outputName);

#endif 
