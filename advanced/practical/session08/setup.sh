mkdir lib lib64 usr etc
mount --bind /lib lib
mount --bind /lib64 lib64
mount --bind /usr usr
mount --bind /etc etc
ln -s /usr/bin bin
mkdir proc sys
