APP_NAME := ../bin/$(shell basename $$(pwd))

INCLUDES :=  -I. -Ibuild -Iinclude -I/usr/share/mkspecs/linux-g++ -I/usr/include/qt -I/usr/include/qt/QtCore -I/usr/include/qt/QtGui -I/usr/include/qt/QtWidgets -I/usr/include
FLAGS   	:= -g -Wall -fdiagnostics-color=never -fno-diagnostics-show-caret -DARCH=\"$(shell uname -m)\" -fPIC

MOCLIST	:= $(patsubst src/include/%.h,build/%.genmoc,$(wildcard src/include/*.h))
UICLIST	:= $(patsubst src/ui/%.ui,build/%.genh,$(wildcard src/ui/*.ui))
OBJLIST	:= $(patsubst src/cpp/%.cpp,build/%.o,$(wildcard src/src/*.cpp)) $(patsubst build/%.genmoc,build/%.geno,$(MOCLIST))

DEFINES 	:= -DQT_GUI_LIB -DQT_CORE_LIB -D_REENTRANT
LIBS		:= -lGL -lGLU -lQt5Core -lQt5Gui -lQt5Widgets -lpng

.PHONY: distclean
.PHONY: configurator

%: %.cpp
%.o: %.cpp
.PRECIOUS: build/%.o build/%.genmoc build/%.genh

ifneq "$(MAKECMDGOALS)" "distclean"
ifneq "$(MAKECMDGOALS)" "test"
DUMMY	:= $(shell mkdir -p build)
sinclude .depend
endif
endif

all: $(APP_NAME)

$(APP_NAME): $(OBJLIST)
	@echo	"linking $(APP_NAME)..."
	@g++ $(FLAGS) -o $(APP_NAME) $(OBJLIST) $(LIBS)
	@echo ""
	@stat -c '%n      %s Bytes' $@
	@echo ""

build/%.o: src/cpp/%.cpp build/%.genh
	@echo "compiling $<...."
	@g++ -c $(FLAGS) $(INCLUDES) -o $@ $<

build/%.geno: build/%.genmoc
	@echo "compiling $<...."
	@g++ -c $(FLAGS) $(INCLUDES) -o $@ $<

build/%.genmoc: src/include/%.h
	@echo "mocking $@ ..."
	@touch $@
	@moc --no-notes $(DEFINES) $(INCLUDES)  $< -o $@

build/%.genh: src/ui/%.ui build/%.genmoc
	@echo "UIC-ing $@ ..."
	@uic $< -o $@

build/.depend: src/cpp/*.cpp src/include/*.h src/ui/*.ui
	@for f in src/cpp/*.cpp ; do k=$$(basename $$f); cpp $(FLAGS) $(DEFINES) $(INCLUDES) -M -MG -MT build/$${k%.*}.o $$f ; done > .depend

d: distclean

distclean:
	@rm -rfv .depend build/*

test:
	@echo "OBJLIST='$(OBJLIST)'"
	@echo ""
	@echo "MOCLIST='$(MOCLIST)'"
	@echo ""
	@echo "UICLIST='$(UICLIST)'"
