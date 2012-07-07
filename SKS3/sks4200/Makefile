#
# Super Key Seeker 4200
#

BIN_DIR = ../../Binaries
VPATH = ./
CPP = g++ 

.PHONY : all
all: bin $(BIN_DIR)/sks4200 $(BIN_DIR)/sks4200-update  \
			$(BIN_DIR)/ks4200.unix $(BIN_DIR)/sks4200-rand.unix \
			$(BIN_DIR)/sks4200-zom.unix $(BIN_DIR)/sks4200-boss.unix \
			$(BIN_DIR)/sks4200-single.unix $(BIN_DIR)/sks4200-mapcreator.unix  \
	  

.PHONY : clean
clean:
	rm -rf $(BIN_DIR)
	
bin:
	mkdir -p $(BIN_DIR)


# $< refers to the first prereq 
# $@ refers to the target
$(BIN_DIR)/sks4200 : betalauncher.cpp engine.cpp sks4200-sp-defines.cpp | bin
	$(CPP) $< -o $@ -lncurses

$(BIN_DIR)/sks4200-update : sks4200-update.cpp  | bin
	$(CPP) $< -o $@
	
$(BIN_DIR)/ks4200.unix : ks4200.cpp | bin
	$(CPP) $< -o $@

$(BIN_DIR)/sks4200-rand.unix : sks4200-rand.cpp  | bin
	$(CPP) $< -o $@ -lncurses

$(BIN_DIR)/sks4200-zom.unix : sks4200-zom.cpp | bin
	$(CPP) $< -o $@ -lncurses

$(BIN_DIR)/sks4200-boss.unix : sks4200-boss.cpp | bin
	$(CPP) $< -o $@ -lncurses

$(BIN_DIR)/sks4200-single.unix : sks4200-sp.cpp maps.cpp engine.cpp sks4200-sp-defines.cpp | bin
	$(CPP) $< -o $@ -lncurses

$(BIN_DIR)/sks4200-mapcreator.unix : sks4200-mapcreator.cpp  | bin
	$(CPP) $< -o $@
	

	
	

