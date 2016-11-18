
main: main.cpp simulation.cpp category_1.cpp category_2.cpp category_3.cpp category_0.cpp ArrayList.cpp
	g++ main.cpp simulation.cpp category_1.cpp  category_2.cpp category_3.cpp category_0.cpp ArrayList.cpp -o main

clean:
	rm main
