main:
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` main.c `pkg-config --libs-only-l MLV` -o puissance4

clear:
	rm puissance4