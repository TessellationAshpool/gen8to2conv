rm gen8to2conv.o
rm gen8to2conv
g++ -c src/gen8to2conv.cpp `libpng-config --cflags`
g++ -o gen8to2conv gen8to2conv.o `libpng-config --ldflags`
./gen8to2conv