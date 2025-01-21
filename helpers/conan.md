```bash
cd cpp
conan profile detect --force

conan install . --build=missing
conan install . -s build_type=Debug --build=missing

cmake --preset conan-release
cmake --build --preset conan-release


cmake --preset conan-debug
cmake --build --preset conan-debug

```