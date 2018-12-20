echo "building"
echo "building for host machine ..."
if [ ! -d "build" ]; then
  mkdir build
fi
pushd ./build
cmake ..
make
./fmp_test
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
node ./fmp_test.js
popd

# time ./build/fast_mpd_parser