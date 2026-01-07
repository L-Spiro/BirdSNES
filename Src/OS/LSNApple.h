/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: macOS/iOS/tvOS macros and header.
 */

#pragma once

#ifdef __APPLE__

#define _FILE_OFFSET_BITS 						64
#include <cstdio>
#include <stdexcept>

#define LSN_APPLE


#endif  // #ifdef __APPLE__
