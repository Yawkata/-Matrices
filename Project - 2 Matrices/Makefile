# only runs if there are changes in the two task files
task: file.cpp  calculations.cpp matrix.cpp
	g++ *.cpp -o task 

#runs if there are changes in any file (probably won't be needed)
all: matrix.h matrix.cpp calculations.h calculations.cpp file.h file.cpp main.cpp
	g++ *.cpp -o all 

#used to remove the executable
clean: 
	$(RM) task
	$(RM) all