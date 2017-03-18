.PHONY: distclean
.PHONY: configurator
.PHONY: lobby

all: configurator lobby

configurator: 
	@echo "COMPILING CONFIGURATOR"
	@echo ""
	@cd configurator && make --no-print-directory

lobby:
	@echo "COMPILING LOBBY"
	@echo ""
	@cd lobby && make --no-print-directory    
	@make

distclean:
	@rm -rfv configurator/build
	@rm -rfv lobby/build
	@rm -rfv bin/*
