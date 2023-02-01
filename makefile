default:
	g++ main.cpp -lncursesw -o pomo-tui

run: default
	./pomo-tui 25 5 15 4

clean:
	rm -rf pomo-tui

install: default
	cp pomo-tui ding.ogg /usr/local/bin/
