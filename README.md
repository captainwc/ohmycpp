# Leetcode Project

This is a CPP project on leetcode which uses CMake to manage the project structure.

You can use it as follows:

Fisrtly you are expected having some tools configured in your environment.

They are:

- `spdlog`: a header only log lib, see [here](https://github.com/gabime/spdlog).
- `doctest`: a header only test frame, see [here](https://blog.csdn.net/qq_43533638/article/details/133160638?spm=1001.2014.3001.5501) for more info.
- `gtest`: a famous but a bit complexer test frame, [here](https://blog.csdn.net/qq_43533638/article/details/133160638?spm=1001.2014.3001.5501) for more info too.

Then you can clone build and run like

```bash
git clone git@github.com:captainwc/leetcode-cpp.git
mkdir build
cd build
# if you want to build my Solutions as well, set the -DBUILD_SRC=ON
cmake ..
make -j6
```

## tips

A few tips might be useful.

Vscode has a famous plug-in called code-runner, which allows you to execute your current program by clicking on the triangle in the upper right corner, it is quite convenient.

You can also run an executable file in a cmake project in this way. All you need to do is configure as follows:

```bash
# add below to your ~/.bashrc or ~/.bash_aliases
BUILD=~/projects/leetcode/build
run(){
    cd ${BUILD}
    cmake -DBUILD_SRC=ON .. > /dev/null
    make -j4 $1 > /dev/null
    ./bin/$1 -ni -nv 
    cd - > /dev/null
} 
# then add this to your .vscode/settings.json
  "code-runner.executorMap": {
    "c": "run $fileNameWithoutExt",
    "cpp": "run $fileNameWithoutExt",
    "cc": "run $fileNameWithoutExt",
  },
```
