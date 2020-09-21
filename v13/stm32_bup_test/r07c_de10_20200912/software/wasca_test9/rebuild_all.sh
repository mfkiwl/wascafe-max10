#!/bin/bash
#
# Rebuild everything.

# Copy wasca link definition header
rm -f satcom_lib/wasca_link.h
cp -p /cygdrive/d/dev/Saturn/SatCom/satlink/wasca/wasca_link.h satcom_lib/wasca_link.h

# Rebuild BSP
cd ../wasca_test9_bsp/

make clean

./create-this-bsp

cd ../wasca_test9

# Update BSP with custom sources
cd custom_bsp

# Wait for short while in order to avoid mess with makefile ...
sleep 3
cp -f -r -v . ../../wasca_test9_bsp/

rm -rf obj/
rm -f libhal_bsp.a
cd ..

# Rebuild BSP with custom sources
cd ../wasca_test9_bsp/
make
cd ../wasca_test9


# Rebuild application
make clean
make

# Generate programming files
./rebuild_flash.sh
