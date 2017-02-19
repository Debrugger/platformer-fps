APP_NAME := bin/lobby
CON_NAME	:= bin/configurator
INCLUDES :=  -I. -I/usr/share/mkspecs/linux-g++ -I/usr/include/qt -I/usr/include/qt/QtCore -I/usr/include/qt/QtGui -I/usr/include/qt/QtWidgets -I/usr/include
FLAGS   	:= -g -Wall -fdiagnostics-color=never -fno-diagnostics-show-caret -DARCH=\"$(shell uname -m)\" -fPIC
OBJLIST 	:= $(patsubst src/%.cpp,%.o,$(wildcard src/*.cpp)) moc_main.o
CONF_OBJLIST 	:= $(patsubst configurator_src/%.cpp,%.o,$(wildcard configurator_src/*.cpp)) moc_configurator.o
DEFINES 	:= -DQT_GUI_LIB -DQT_CORE_LIB -D_REENTRANT
LIBS		:= -lGL -lGLU -lQt5Core -lQt5Gui -lQt5Widgets -lpng

.PHONY: test
.PHONY: distclean
.PHONY: configurator

all: $(APP_NAME)


sinclude .depend


src/moc_%.cpp: src/%.h
	@echo "mocking $@ ..."
	@moc $(DEFINES) $(INCLUDES)  $< -o $@

configurator_src/moc_%.cpp: configurator_src/%.h
	@echo "mocking $@ ..."
	@moc $(DEFINES) $(INCLUDES)  $< -o $@

lobby_dialog_ui.h: rc/lobby_dialog.ui src/moc_main.cpp
	@echo "generating $@ ..."
	@uic $< -o $@

$(APP_NAME): $(OBJLIST)         
	@echo ""
	@echo "linking $(APP_NAME) ..."
	@g++ $(FLAGS) -o $(APP_NAME) $(filter-out configurator.o moc_configurator.o ,*.o) $(LIBS) 
	@echo ""
	@stat -c '%n      %s Bytes' $@
	@echo ""

%.o: src/%.cpp lobby_dialog_ui.h
	@echo "compiling $< ..."
	@g++ -c $(FLAGS) $(INCLUDES) -o $@ $<

.depend: src/*.cpp src/*.h
	@for f in src/*.cpp ; do k=$$(basename $$f); cpp $(FLAGS) $(DEFINES) $(INCLUDES) -M -MG -MT $${k%.*}.o $$f ; done > .depend

configurator_ui.h: rc/configurator.ui configurator_src/moc_configurator.cpp
	@echo "generating $@..."
	@uic $< -o $@

%.o: configurator_src/%.cpp configurator_ui.h
	@echo "compiling $<...."
	@g++ -c $(FLAGS) $(INCLUDES) -o $@ $<

$(CON_NAME): $(CONF_OBJLIST)
	@echo	"linking $(CON_NAME)..."
	@g++ $(FLAGS) -o $(CON_NAME) configurator.o moc_configurator.o $(LIBS)
	@echo ""
	@stat -c '%n      %s Bytes' $@
	@echo ""

d:
	@rm -vf *.o .depend src/*_ui.h src/moc_*.cpp *_ui.h *.o bin/*
	@rm -rfv cache

test:
	@echo "OBJLIST='$(OBJLIST)'"

configurator: $(CON_NAME)
