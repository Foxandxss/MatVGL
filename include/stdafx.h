// MatVGL gaming library. Cross platform library to create games.
// Copyright (C) 2015 Víctor Matía Rodríguez <vmatir@gmail.com>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef STDAFX_H
#define STDAFX_H

// OS that use standard C/C++ (AKA not Windows systems).
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))

#include <stdint.h>

using Int16 = int16_t;
using Int32 = int32_t;
using UInt32 = uint32_t;

#endif // Linux definitions

#endif // STDAFX_H
