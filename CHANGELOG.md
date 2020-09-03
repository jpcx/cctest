# Changelog

## [Upcoming](https://github.com/jpcx/cctest/compare/0.4.2...devel)

## [0.4.2](https://github.com/jpcx/cctest/releases/tag/0.4.2) \[[diff](https://github.com/jpcx/cctest/compare/0.4.1...0.4.2)\]

### Changed

- added EXCLUDE_FROM_DEFUALT_BUILD to test target for compatibility
- fixed Changelog typo

## [0.4.1](https://github.com/jpcx/cctest/releases/tag/0.4.1) \[[diff](https://github.com/jpcx/cctest/compare/0.4.0...0.4.1)\]

### Changed

- removed test from default target

## [0.4.0](https://github.com/jpcx/cctest/releases/tag/0.4.0) \[[diff](https://github.com/jpcx/cctest/compare/0.3.0...0.4.0)\]

### Changed

- moved C++17 requirement check from CMake to header

## [0.3.0](https://github.com/jpcx/cctest/releases/tag/0.3.0) \[[diff](https://github.com/jpcx/cctest/compare/0.2.3...0.3.0)\]

### Changed

- made result variables inline, normalized specifier order

## [0.2.3](https://github.com/jpcx/cctest/releases/tag/0.2.3) \[[diff](https://github.com/jpcx/cctest/compare/0.2.2...0.2.3)\]

### Changed

- cleaned up README

## [0.2.2](https://github.com/jpcx/cctest/releases/tag/0.2.2) \[[diff](https://github.com/jpcx/cctest/compare/0.2.1...0.2.2)\]

### Changed

- added `clean` target to `.PHONY` 
- removed patch version from find_package documentation

## [0.2.1](https://github.com/jpcx/cctest/releases/tag/0.2.1) \[[diff](https://github.com/jpcx/cctest/compare/0.2.0...0.2.1)\]

### Changed

- fixed versioning configure file destination

## [0.2.0](https://github.com/jpcx/cctest/releases/tag/0.2.0) \[[diff](https://github.com/jpcx/cctest/compare/0.1.5...0.2.0)\]

### Changed

- removed extra semicolons from test macros
- moved include directory from root to `include/`
- switched build system to CMake
- updated README.md with new CMake documentation
- added note regarding static tests and macro helpers to README.md
- reverted library entry point back to `cctest.h` (from `cctest/cctest.h`)

### Added

- added `[[noreturn]]` attribute to `dynamic_fail`
- added diff links to CHANGELOG.md
- added root Makefile helper for new CMake build system

## [0.1.5](https://github.com/jpcx/cctest/releases/tag/0.1.5) \[[diff](https://github.com/jpcx/cctest/compare/0.1.4...0.1.5)\]

### Changed

- fixed installation destination documentation

## [0.1.4](https://github.com/jpcx/cctest/releases/tag/0.1.4) \[[diff](https://github.com/jpcx/cctest/compare/0.1.3...0.1.4)\]

### Changed

- changed cctest.h install directory to cctest/cctest.h

## [0.1.3](https://github.com/jpcx/cctest/releases/tag/0.1.3) \[[diff](https://github.com/jpcx/cctest/compare/0.1.2...0.1.3)\]

### Changed

- fixed CHANGELOG.md links; made absolute

## [0.1.2](https://github.com/jpcx/cctest/releases/tag/0.1.2) \[[diff](https://github.com/jpcx/cctest/compare/0.1.1...0.1.2)\]

### Removed

- removed repo link from README.md; localized to webpage

## [0.1.1](https://github.com/jpcx/cctest/releases/tag/0.1.1) \[[diff](https://github.com/jpcx/cctest/compare/0.1.0...0.1.1)\]

### Added

- added link to repo from documentation homepage

### Changed

- fixed private documentation for cctest::detail_::nocvref
- updated two documentation example descriptions
- fixed CHANGELOG.md Upcoming link

## [0.1.0](https://github.com/jpcx/cctest/releases/tag/0.1.0)

### Added

- Basic features, documentation, and tests
