# ROOT-Sim Topology Library

[![Build Status](https://github.com/ROOT-Sim/cROOT-Sim/workflows/ROOT-Sim%20core%20CI/badge.svg)](https://github.com/ROOT-Sim/cROOT-Sim/actions)
[![GitHub issues](https://img.shields.io/github/issues/ROOT-Sim/topology)](https://github.com/ROOT-Sim/cROOT-Sim/issues)
[![GitHub](https://img.shields.io/github/license/ROOT-Sim/topology)](https://github.com/ROOT-Sim/cROOT-Sim/blob/master/COPYING)

*Brought to you by the [High Performance Computing & Simulation (HPCS)](https://hpcs.ing.uniroma2.it/) Research Group*

----------------------------------------------------------------------------------------

## Overview

The ROOT-Sim Topology Library provides a collection of common topological structures designed for simulation models. It is a companion library for the [ROOT-Sim](https://github.com/ROOT-Sim/cROOT-Sim) framework, facilitating the setup and management of simulated physical or logical communication networks among Logical Processes (LPs).

## Features

This library supports mapping, adjacency management, and random neighbor selection for a variety of geometries:

*   **Linear/Ring Structures:** Rings and Bidirectional Rings.
*   **Grid Structures:** Square meshes, Hexagonal meshes, and Tori.
*   **Centralized Structures:** Star topologies.
*   **Fully Connected:** Fully Connected Meshes (FCMESH).
*   **Arbitrary Graphs:** Custom Graph topologies with probability-weighted edges and custom data.

## Integration

To use the topology library in your simulation models, include the main header:

```c
#include <ROOT-Sim/topology.h>
```

This is a CMake-based C11 project. To build and link the library, ensure you have a C11-compliant compiler (like Clang or GCC) and CMake 3.12 or newer.

```bash
mkdir build
cd build
cmake ..
make
```

## License

This project is licensed under the GPL-3.0-only license. See the `LICENSES` directory or the REUSE configuration for more details.
