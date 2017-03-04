APP_NAME := bin/lobby
CON_NAME	:= bin/configurator
INCLUDES :=  -I. -I/usr/share/mkspecs/linux-g++ -I/usr/include/qt -I/usr/include/qt/QtCore -I/usr/include/qt/QtGui -I/usr/include/qt/QtWidgets -I/usr/include
FLAGS   	:= -g -Wall -fdiagnostics-color=never -fno-diagnostics-show-caret -DARCH=\"$(shell uname -m)\" -fPIC
OBJLIST 	:= $(patsubst src/lobby/%.cpp,build/lobby/%.o,$(wildcard src/lobby/*.cpp)) build/lobby/moc_main.o
CONF_OBJLIST 	:= $(patsubst src/configurator/%.cpp,build/configurator/%.o,$(wildcard src/configurator/*.cpp)) build/configurator/moc_main.o
DEFINES 	:= -DQT_GUI_LIB -DQT_CORE_LIB -D_REENTRANT
LIBS		:= -lGL -lGLU -lQt5Core -lQt5Gui -lQt5Widgets -lpng

ifneq "$(MAKECMDGOALS)" "distclean"
DUMMY	:= $(shell mkdir -p build/{lobby,configurator})
endif

.PHONY: test
.PHONY: distclean
.PHONY: configurator

all: $(APP_NAME)

sinclude .depend
######################################Binaries################################################
$(CON_NAME): $(CONF_OBJLIST)
	@echo	"linking $(CON_NAME)..."
	@g++ $(FLAGS) -o $(CON_NAME) build/configurator/main.o build/configurator/moc_main.o $(LIBS)
	@echo ""
	@stat -c '%n      %s Bytes' $@
	@echo ""

$(APP_NAME): $(OBJLIST)         
	@echo ""
	@echo "linking $(APP_NAME) ..."
	@g++ $(FLAGS) -o $(APP_NAME) build/lobby/*.o $(LIBS) 
	@echo ""
	@stat -c '%n      %s Bytes' $@
	@echo ""
######################################.o's####################################################

build/lobby/%.o: src/lobby/%.cpp build/lobby/lobby_dialog_ui.h build/lobby/connect_dialog_ui.h
	@echo "compiling $< ..."
	@g++ -c $(FLAGS) $(INCLUDES) -o $@ $<


build/configurator/%.o: src/configurator/%.cpp build/configurator/save_dialog_ui.h
	@echo "compiling $<...."
	@g++ -c $(FLAGS) $(INCLUDES) -o $@ $<
######################################ui_h's##################################################

build/lobby/lobby_dialog_ui.h: rc/lobby_dialog.ui src/lobby/moc_main.cpp
	@echo "generating $@ ..."
	@uic $< -o $@

build/configurator/save_dialog_ui.h: rc/save_dialog.ui src/configurator/moc_main.cpp
	@echo "generating $@..."
	@uic $< -o $@

build/lobby/connect_dialog_ui.h: rc/connect_dialog.ui src/lobby/moc_main.cpp
	@echo "generating $@..."
	@uic $< -o $@
#####################################moc######################################################

src/lobby/moc_%.cpp: src/lobby/%.h
	@echo "mocking $@ ..."
	@moc $(DEFINES) $(INCLUDES)  $< -o $@

src/configurator/moc_%.cpp: src/configurator/%.h
	@echo "mocking $@ ..."
	@moc $(DEFINES) $(INCLUDES)  $< -o $@

build/.depend: src/lobby/*.cpp src/lobby/*.h
	@for f in src/*.cpp ; do k=$$(basename $$f); cpp $(FLAGS) $(DEFINES) $(INCLUDES) -M -MG -MT $${k%.*}.o $$f ; done > .depend


########################################################################################
d: distclean

distclean:
	@rm -vf *.o .depend bin/*
	@rm -rfv cache
	@rm -rf build
	@rm -rf src/**/moc*

test:
	@echo "OBJLIST='$(OBJLIST)'"

configurator: $(CON_NAME)
