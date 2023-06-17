COMPONENTS="bootload libc kernel"

for COMPONENT in $COMPONENTS; do
	cd $COMPONENT
	make clean
	cd ..
done
