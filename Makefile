################## default target ####################
all:
	+$(MAKE) -C src/

################### delete created files ################
clean:
	rm -f ./src/*.o
	rm -f ./bin/ChessGame
	rm -f ./bin/logfile.txt
	
################## create archive ######################
tar:	
	gtar cvzf Chess_Alpha_src.tar.gz COPYRIGHT.txt INSTALL.txt README.txt Makefile bin/ doc/ src/
