#!bin/bash

read -p "Enter new version number (Format X.X-X): " version_number
echo $version_number

mkdir libhelikopter_$version_number
mkdir libhelikopter_$version_number/usr
mkdir libhelikopter_$version_number/usr/local
mkdir libhelikopter_$version_number/usr/local/lib
mkdir libhelikopter_$version_number/usr/local/lib/helikopter

mkdir libhelikopter_$version_number/DEBIAN
touch libhelikopter_$version_number/DEBIAN/control

echo "Package: libhelikopter" >> libhelikopter_$version_number/DEBIAN/control
echo "Version: $version_number" >> libhelikopter_$version_number/DEBIAN/control
echo "Section: base" >> libhelikopter_$version_number/DEBIAN/control
echo "Priority: optional" >> libhelikopter_$version_number/DEBIAN/control
echo "Architecture: armhf" >> libhelikopter_$version_number/DEBIAN/control
echo "#Depends: libsomethingorrather (>= 1.2.13), anotherDependency (>= 1.2.6)" >> libhelikopter_$version_number/DEBIAN/control
echo "Maintainer: Robin Lieb <roligs00@hs-esslingen.de>" >> libhelikopter_$version_number/DEBIAN/control
echo "Description: Libraries for the HElikopter project" >> libhelikopter_$version_number/DEBIAN/control
echo " Included libraries: libcommunication.so, liblld.so, libmotor.so, libsensor.so, libsig.so" >> libhelikopter_$version_number/DEBIAN/control
echo " These libraries are installed in the /usr/local/lib/helicopter directory" >> libhelikopter_$version_number/DEBIAN/control

cp ../build/*.so libhelikopter_$version_number/usr/local/lib/helikopter

for f in libhelikopter_$version_number/usr/local/lib/helikopter/*.so
do
    mv "$f" "$f."$version_number
    ln -s "$f."$version_number "$f"
done


dpkg-deb --build libhelikopter_$version_number
