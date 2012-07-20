all:
	@echo "You must make either osx, linux, sks4200, or clean"
clean:
	rm -rf ./Binaries
sks4200:
	make -C ./SKS3/sks4200
osx:
	mkdir -p ./Binaries
	xcodebuild
	mv ./build/Release/SKS3 ./Binaries/sks3
	rm -rf Build
linux:
	mkdir -p ./Binaries
	g++ ./SKS3/main.cpp ./SKS3/engine/*.cpp ./SKS3/ks4200/*.cpp ./SKS3/sks4200/sks4200.cpp -lncurses -o ./Binaries/sks3
install:
	sudo cp ./Binaries/* /usr/bin
