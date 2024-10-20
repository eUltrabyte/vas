[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/c%2B%2B-20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

# Vulkan Application Setup

vas is library for vulkan rendering api. It uses cmake, c++20 and vulkan headers. The goal of this project is to simplify first steps in building vulkan-based app.

### TODO

- [x] Instance creation
- [x] Debug messenger creation
- [x] Getting physical devices
- [ ] Physical devices choosing criteria
- [x] Device creation
- [ ] Getting queues
- [ ] Swapchain creation

### Libraries

[Vulkan SDK](https://lunarg.com/vulkan-sdk/) - Vulkan is a new generation graphics and compute API that provides high-efficiency, cross-platform access to modern graphics processing units, which are used in a wide variety of devices from PCs and consoles to mobile phones and embedded platforms.

### Installation

Compilation should work under g++14, clang18 and latest msvc.
```bash
git clone https://github.com/eUltrabyte/vas.git
cd vas && mkdir Build
cd Build && cmake ..
```
After successful compilation you just need to add library to your project.

### Bugs

Bugs are reported to [issue tracker](https://github.com/eUltrabyte/vas/issues)

#### Report Example

```
Operating System:
CPU:
GPU:
Branch:
Short description:
```