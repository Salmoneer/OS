set -e

COMPONENTS="bootload libc kernel"

for COMPONENT in $COMPONENTS; do
    cd $COMPONENT
    make
    cd ..
done

dd if=/dev/zero of=boot.img bs=512 count=4096 status=none
mkfs.vfat -F 12 -r 224 -s 1 -S 512 boot.img > /dev/null
dd if=bootload/bootload.bin of=boot.img bs=512 count=1 conv=notrunc status=none

rm -rf loop
mkdir loop

sudo mount -o fat=12,loop -t msdos boot.img loop
sudo cp kernel/kernel.bin loop/
sudo umount loop
rm -rf loop

mkdir sysroot/boot
mv boot.img sysroot/boot/boot.img

./run.sh
