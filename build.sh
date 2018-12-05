echo "building"
echo "building for host machine ..."
if [ ! -d "build" ]; then
  mkdir build
fi
pushd ./build
cmake ..
make
popd

echo "making javascript ..."
if [ ! -d "build_js" ]; then
  mkdir build_js
fi
pushd .
cd ./build_js
emconfigure cmake ..
emmake make
emcc libfmp.so -o final.html
popd

# time ./build/fast_mpd_parser