name = rep
binpath = /usr/local/bin

rep :
	g++ -o bin/${name} sources/main.cpp


run :
	make
	bin/${name} 

clean :
	rm bin/${name}
	sudo rm ${binpath}/${name}

install :
	make
	sudo cp bin/${name} ${binpath}/${name}

symlink :
	make
	sudo ln -fs `pwd`/bin/${name} ${binpath}/${name}

