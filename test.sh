mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$(pwd)/../Demo/usr ..

cd build
make install
cd ..

linuxdeployqt.AppImage Demo/usr/bin/demo -bundle-non-qt-libs -verbose=3
