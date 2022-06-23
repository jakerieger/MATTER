cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --target ALL_BUILD
cd ..
cd HUB/matter-hub
./build.sh
cd ../../
cd scripts
makensis create_installer.nsi
cd ..
echo "Done!"