CS 417 Fall 2019
Aaron Berman
Semester project: CPU temperature analysis using piece-wise linear interpolation 
and least-squares approximation.

From project root:
build instructions:
	linux:
		./gradlew build
	windows:
		gradlew build

executable location:
	linux:
		build/exe/main/debug
	windows:
		build\exe\main\debug

Run instructions:
uses 4 core file with no labels
	linux:
		./build/exe/main/debug/CPUTemps "filename"
	windows:
		build\exe\main\debug\CPUTemps.exe "filename"

Output:
	"basename"-core-0.txt
	"basename"-core-1.txt
	"basename"-core-2.txt
	"basename"-core-3.txt

gradlew build - builds the executable and moves the provided data from the instruction to the same directory as the executable.

gradlew clean removes the build folder and all its contents.

gradlew run has no functionality.

gradlew doxygen also has no functionality.