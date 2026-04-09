# arcade++

Mini desktop arcade app built with C++ and raylib.

## Commands

### Linux / macOS
```bash
cmake -S . -B build
cmake --build build
./build/arcadepp

cmake -S . -B build && cmake --build build && ./build/arcadepp

rm -rf build
```

### Windows
```bash
cmake -S . -B build
cmake --build build --config Release
.\build\Release\arcadepp.exe

cmake -S . -B build && cmake --build build --config Release && .\build\Release\arcadepp.exe

rmdir /s /q build
```