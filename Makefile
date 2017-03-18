.PHONY: distclean
.PHONY: configurator
.PHONY: lobby

ll: configurator lobby

configurator: 
	@echo "COMPILING CONFIGURATOR"
	@echo ""
	@cd configurator && make --no-print-directory

lobby:
	@echo "COMPILING LOBBY"
	@echo ""
	@cd lobby && make --no-print-directory    

distclean:
	@rm -rfv configurator/build
	@rm -rfv lobby/build
	@rm -rfv bin/*
