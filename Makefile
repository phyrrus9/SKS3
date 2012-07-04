all:
	@echo "You must make either osx or linux"
osx:
	xcodebuild
linux:
	g++ ./SKS3/main.cpp ./SKS3/engine/*.cpp -lncurses
