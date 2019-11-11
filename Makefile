build:
	g++ -w -std=c++14 -Wfatal-errors \
	./*.cpp \
	-o fractalGenerator;

clean:
	rm ./fractalGenerator;

run:
	./fractalGenerator;