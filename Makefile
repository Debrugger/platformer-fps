.PHONY: distclean
.PHONY: configurator
.PHONY: client

ll: configurator client server

configurator: 
	@echo "Building configurator..."
	@echo ""
	@cd configurator && make --no-print-directory

client:
	@echo "Building client..."
	@echo ""
	@cd client && make --no-print-directory    

server:
	@echo "Building server..."
	@echo ""
	@cd client && make --no-print-directory

distclean:
	rm -rfv configurator/build
	rm -rfv client/build
	rm -rfv server/build
	rm -rfv bin/*
