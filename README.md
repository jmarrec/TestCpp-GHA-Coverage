# TestCpp-GHA-Coverage

[![C++ CI](https://github.com/jmarrec/TestCpp-GHA-Coverage/actions/workflows/build.yml/badge.svg)](https://github.com/jmarrec/TestCpp-GHA-Coverage/actions/workflows/build.yml)
[![codecov](https://codecov.io/gh/jmarrec/TestCpp-GHA-Coverage/branch/main/graph/badge.svg?token=CZCY313ERT)](https://codecov.io/gh/jmarrec/TestCpp-GHA-Coverage)
[![clang-format](https://github.com/jmarrec/TestCpp-GHA-Coverage/actions/workflows/clang-format-check.yml/badge.svg)](https://github.com/jmarrec/TestCpp-GHA-Coverage/actions/workflows/clang-format-check.yml)
[![cppcheck](https://github.com/jmarrec/TestCpp-GHA-Coverage/actions/workflows/cppcheck.yml/badge.svg)](https://github.com/jmarrec/TestCpp-GHA-Coverage/actions/workflows/cppcheck.yml)

A repo to test how to report coverage of a C++ project using Github Actions, using https://codecov.io.

See:
* Example PRs [increasing](https://github.com/jmarrec/TestCpp-GHA-Coverage/pull/1) and [decreasing](https://github.com/jmarrec/TestCpp-GHA-Coverage/pull/2) coverage
* the Github Actions workflow at [.github/workflows/build.yml](.github/workflows/build.yml)

----

## Additional

Additionally, it includes a [cppcheck action](.github/workflows/cppcheck.yml) with a custom python script ([ci/colorize_cppcheck_results.py](./ci/colorize_cppcheck_results.py)) I created that will print a summary of offenses and add color to your action.

![cppcheck](./docs/cppcheck.png)

There is also a [clang-format action](.github/workflows/clang-format-check.yml) that uses the `.clang-format` file in the repo.

(Note: A `.clang-tidy` file is also provided, but I didn't bother adding an action for that.)
