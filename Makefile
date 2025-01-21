.PHONY:

compile:
	cd cpp && \
	conan install . -s build_type=Release --build=missing && \
	cmake --preset conan-release && \
	cmake --build --preset conan-release

compile_debug:
	cd cpp && \
	conan install . -s build_type=Debug --build=missing && \
	cmake --preset conan-debug && \
	cmake --build --preset conan-debug

test:
	cd cpp && \
	ctest --test-dir build/Debug

doxy:
	cd docs && \
	doxygen && \
	echo "Documentation available at 'docs/html/index.html'"

py_setup:
	cd python && \
	pdm install

run:
	cd python && \
	pdm run python -m src.graph_viewer.main

format_cpp:
	cd cpp && \
	find . -type f \( -iname "*.cpp" -o -iname "*.hpp" \) -not -path "build/*" | xargs clang-format -i --style=file

format_py:
	cd python && \
	pdm run format

lint_py:
	cd python && \
	pdm run lint
