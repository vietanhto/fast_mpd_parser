pushd ./build
cmake ..
make
popd

time ./build/fast_mpd_parser