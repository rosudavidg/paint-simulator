build: paint_simulator
paint_simulator: sursa.o
	gcc -o paint_simulator sursa.o
sursa.o: sursa.c
	gcc -c sursa.c -o sursa.o
run:
	./paint_simulator
clean:
	rm sursa.o paint_simulator
