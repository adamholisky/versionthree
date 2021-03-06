#/bin/bash

mkdir /versionthree/tools/src
mkdir /versionthree/tools/originals
mkdir /versionthree/tools/build

cd /versionthree/tools/originals
wget https://ftp.gnu.org/gnu/binutils/binutils-2.32.tar.gz -q --show-progress
echo Extracting... please wait.
tar -xzf binutils-2.32.tar.gz
mv binutils-2.32 binutils
mv binutils ../src
echo Binutils downloaded and moved

cd /versionthree/tools/originals
wget https://ftp.gnu.org/gnu/gcc/gcc-8.3.0/gcc-8.3.0.tar.gz -q --show-progress
echo Extracting... please wait.
tar -xzf gcc-8.3.0.tar.gz
mv gcc-8.3.0 gcc
mv gcc ../src
echo GCC downloaded and moved

#TODO: Finish writing this out...

wget https://ftp.gnu.org/gnu/mpc/mpc-1.1.0.tar.gz -q --show-progress
wget https://ftp.gnu.org/gnu/mpfr/mpfr-4.0.2.tar.gz -q --show-progress
wget https://ftp.gnu.org/gnu/gmp/gmp-6.1.2.tar.xz -q --show-progress
wget https://www.nasm.us/pub/nasm/releasebuilds/2.14.02/nasm-2.14.02.tar.gz -q --show-progress
wget http://www.agner.org/optimize/objconv.zip -q --show-progress
wget https://ftp.gnu.org/gnu/grub/grub-2.02.tar.gz -q --show-progress
wget https://download.qemu.org/qemu-4.0.0.tar.xz -q --show-progress

echo All files downloaded, only binutils and gcc moved accordingly. 