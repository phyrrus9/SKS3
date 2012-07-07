all:
	@echo "You must make either osx, linux, sks4200, or clean"
clean:
	rm -rf ./Binaries
sks4200:
	make -C ./SKS3/sks4200
osx: sks4200
	xcodebuild
	mv ./build/Release/SKS3 ./Binaries/sks3
	rm -rf Build
linux: sks4200
	g++ ./SKS3/main.cpp ./SKS3/engine/*.cpp -lncurses -o ./Binaries/sks3
install:
	sudo cp ./Binaries/* /usr/bin
