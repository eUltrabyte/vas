alias g := generate
alias b := build
alias c := clean
alias r := run
alias a := all

generate:
    cmake -DCMAKE_GENERATOR="Unix Makefiles" . -B Build/ -DVCPKG_TARGET_TRIPLET=x64-linux --toolchain /home/szymon/vcpkg/scripts/buildsystems/vcpkg.cmake

build:
    cmake --build Build/ -j 12

clean:
    rm -rf Build
    mkdir Build
    rm -rf log.txt

run:
    rm -rf log.txt
    ./Build/App/App

all:
    rm -rf Build
    mkdir Build
    cmake -DCMAKE_GENERATOR="Unix Makefiles" . -B Build/ -DVCPKG_TARGET_TRIPLET=x64-linux --toolchain /home/szymon/vcpkg/scripts/buildsystems/vcpkg.cmake
    cmake --build Build/ -j 12
    rm -rf log.txt
    ./Build/App/App
