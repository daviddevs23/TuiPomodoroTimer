default:
	g++ main.cpp -lncurses -o pomo-tui

run: default
	./pomo-tui 25 5 15 4

clean:
	rm -rf pomo-tui

install:
	echo "TDB"
