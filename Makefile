all: libhar.a
	g++ -std=c++11 -ISources -L. -o har har-test/main.cpp -lhar

libhar.a: build/Archive.o build/DataBuffer.o build/File.o build/FileEntry.o build/Hierarchy.o
	ar rcs libhar.a build/Archive.o build/DataBuffer.o build/File.o build/FileEntry.o build/Hierarchy.o

build/Archive.o: Sources/Archive.cpp Sources/Archive.hpp Sources/DataBuffer.hpp Sources/File.hpp Sources/FileEntry.hpp Sources/Hierarchy.hpp Sources/types.h Sources/picosha2.h
	g++ -c -std=c++11 -o build/Archive.o Sources/Archive.cpp

build/DataBuffer.o: Sources/DataBuffer.cpp Sources/DataBuffer.hpp
	g++ -c -std=c++11 -o build/DataBuffer.o Sources/DataBuffer.cpp

build/File.o: Sources/File.cpp Sources/File.hpp Sources/picosha2.h Sources/types.h Sources/DataBuffer.hpp
	g++ -c -std=c++11 -o build/File.o Sources/File.cpp

build/FileEntry.o: Sources/FileEntry.cpp Sources/FileEntry.hpp Sources/Hierarchy.hpp Sources/types.h Sources/DataBuffer.hpp
	g++ -c -std=c++11 -o build/FileEntry.o Sources/FileEntry.cpp

build/Hierarchy.o: Sources/Hierarchy.cpp Sources/FileEntry.hpp Sources/Hierarchy.hpp Sources/types.h Sources/DataBuffer.hpp
	g++ -c -std=c++11 -o build/Hierarchy.o Sources/Hierarchy.cpp


