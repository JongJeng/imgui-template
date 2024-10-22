
set -e

cmake -B build $@
cmake --build build --config Release --parallel $(nproc)