APP_NAME := bin/lobby
CON_NAME	:= bin/configurator
INCLUDES :=  -I. -I/usr/share/mkspecs/linux-g++ -I/usr/include/qt -I/usr/include/qt/QtCore -I/usr/include/qt/QtGui -I/usr/include/qt/QtWidgets -I/usr/include
FLAGS   	:= -g -Wall -fdiagnostics-color=never -fno-diagnostics-show-caret -DARCH=\"$(shell uname -m)\" -fPIC
OBJLIST 	:= $(patsubst src/lobby/%.cpp,build/lobby/%.o,$(wildcard src/lobby/*.cpp)) build/lobby/moc_main.o
CONF_OBJLIST 	:= $(patsubst src/configurator/%.cpp,build/configurator/%.o,$(wildcard src/configurator/*.cpp)) build/configurator/moc_configurator.o
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

src/lobby/moc_%.cpp: src/lobby/%.h
	@echo "mocking $@ ..."
	@moc $(DEFINES) $(INCLUDES)  $< -o $@

src/configurator/moc_%.cpp: src/configurator/%.h
	@echo "mocking $@ ..."
	@moc $(DEFINES) $(INCLUDES)  $< -o $@

build/lobby/lobby_dialog_ui.h: rc/lobby_dialog.ui src/lobby/moc_main.cpp
	@echo "generating $@ ..."
	@uic $< -o $@

$(APP_NAME): $(OBJLIST)         
	@echo ""
	@echo "linking $(APP_NAME) ..."
	@g++ $(FLAGS) -o $(APP_NAME) build/lobby/*.o $(LIBS) 
	@echo ""
	@stat -c '%n      %s Bytes' $@
	@echo ""

build/lobby/%.o: src/lobby/%.cpp build/lobby/lobby_dialog_ui.h
	@echo "compiling $< ..."
	@g++ -c $(FLAGS) $(INCLUDES) -o $@ $<

build/.depend: src/lobby/*.cpp src/lobby/*.h
	@for f in src/*.cpp ; do k=$$(basename $$f); cpp $(FLAGS) $(DEFINES) $(INCLUDES) -M -MG -MT $${k%.*}.o $$f ; done > .depend

build/configurator/configurator_ui.h: rc/configurator.ui src/configurator/moc_configurator.cpp
	@echo "generating $@..."
	@uic $< -o $@

build/configurator/%.o: src/configurator/%.cpp build/configurator/configurator_ui.h
	@echo "compiling $<...."
	@g++ -c $(FLAGS) $(INCLUDES) -o $@ $<

$(CON_NAME): $(CONF_OBJLIST)
	@echo	"linking $(CON_NAME)..."
	@g++ $(FLAGS) -o $(CON_NAME) build/configurator/configurator.o build/configurator/moc_configurator.o $(LIBS)
	@echo ""
	@stat -c '%n      %s Bytes' $@
	@echo ""

d: distclean

distclean:
	@rm -vf *.o .depend bin/*
	@rm -rfv cache
	@rm -rf build

test:
	@echo "OBJLIST='$(OBJLIST)'"

configurator: $(CON_NAME)
