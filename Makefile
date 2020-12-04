default:
	make compile
	make run

compile:
	gcc main_2019459.c -lpthread -lrt -o main.out

run:
	./main.out
	rm main.out