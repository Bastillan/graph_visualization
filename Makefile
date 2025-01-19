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
	pdm run python -m src.graph_viewer.gui
