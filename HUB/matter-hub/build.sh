yarn tauri build
rm -rf ./dist/*
cp ./src-tauri/target/release/bundle/msi/matter-hub_1.0.0_x64_en-US.msi ./dist/matter-hub.msi
cd dist
lessmsi x matter-hub.msi
cp ./matter-hub/SourceDir/PFiles/matter-hub/matter-hub.exe ./MatterHub.exe
rm -rf ./matter-hub
rm -rf ./matter-hub.msi