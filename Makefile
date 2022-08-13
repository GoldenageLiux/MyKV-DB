main: 
	g++ main.cpp -o ./bin/main

stressTest:
	g++ ./stress/StressTest.cpp -o ./stress/StressTest -pthread

clean:
	rm -f ./bin/main && rm -f ./stress/StressTest