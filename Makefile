.PHONY: distclean
.PHONY: configurator
.PHONY: lobby

all: bin/configurator bin/lobby
configurator: bin/configurator
lobby: bin/lobby


bin/configurator: 
	@echo "COMPILING CONFIGURATOR"
	@echo ""
	@cd configurator && make --no-print-directory

bin/lobby:
	@echo "COMPILING LOBBY"
	@echo ""
	@cd lobby && make --no-print-directory    
	@make

distclean:
	@rm -rfv configurator/build
	@rm -rfv lobby/build
	@rm -rfv bin/*
