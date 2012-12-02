all: linux
	@echo "Done!"
clean:
	rm -rf ./Binaries
	rm -rf ./build
sks4200:
	make -C ./SKS3/sks4200
osx:
	mkdir -p ./Binaries
	xcodebuild
	mv ./build/Release/SKS3 ./Binaries/sks3
	rm -rf Build
linux:
	mkdir -p ./Binaries
	g++ ./SKS3/main.cpp ./SKS3/engine/*.cpp ./SKS3/engine/windows/*.cpp  ./SKS3/ks4200/*.cpp ./SKS3/sks4200/sks4200.cpp ./SKS3/engine/streamlib/stream.a ./SKS3/engine/nwin/libnwin.a -lncurses -pthread -o ./Binaries/sks3	
install:
	sudo cp ./Binaries/* /usr/bin
	sudo mkdir -p /usr/share/sks3
	sudo cp ./music/sks3/* /usr/share/sks3
	sudo cp ./mods/sks3/*.conf /usr/share/sks3
	sudo mkdir -p /usr/share/sks3/mods
	sudo cp ./mods/sks3/mods/*.conf /usr/share/sks3/mods
release: clean sks4200 linux
	@echo "Ready to build"
