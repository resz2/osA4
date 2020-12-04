default:
	make compile
	make run
	make clear

compile:
	gcc main_2019459.c -lpthread -lrt -o main.out

run:
	./main.out

clear:
	rm main.out