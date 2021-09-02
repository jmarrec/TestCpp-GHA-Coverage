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

## Multi platform support

`Person.cpp` has a few compiler specific macros, so that we can test merging reports from several platforms on codecov. See [src/Person.cpp#L18-L27](https://github.com/jmarrec/TestCpp-GHA-Coverage/blob/408d98bb68b05222006d052dd6367090827ed8fc/src/Person.cpp#L18-L27)


See [PR#5](https://github.com/jmarrec/TestCpp-GHA-Coverage/pull/5) for more info including before/after screenshots when I added Mac in addition to Ubuntu

![Mac+Ubuntu](https://user-images.githubusercontent.com/5479063/131817697-44e8ac87-577e-4531-9bf5-fd05a07bba28.png)


See [PR#6](https://github.com/jmarrec/TestCpp-GHA-Coverage/pull/6) when I added Windows (via OpenCppCoverage) in addition to Mac and Ubuntu. **Looks like Windows's report don't merge correctly to codecov?**

![image](https://user-images.githubusercontent.com/5479063/131827053-6bff2bdf-ed92-4ddc-aa5a-efcaed3c3220.png)

**Note: Looks like there is a viewing problem where the clang line is no longer green, yet report is correctly at 100%**
