#ifndef PLATFORM_PATHS_H
#define PLATFORM_PATHS_H

#include <iostream>

#include "filesystem.h"

std::string getResourcesPathString();
duoplot::filesystem::path getConfigDir();

#endif  // PLATFORM_PATHS_H