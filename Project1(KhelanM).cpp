// Automobile Speed / Distance Application Program with variable time interval and speed
// By Khelan Modi
// Date modified: Jun 13th, 2019

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

// FUNCTION PROTOTYES
void printCommandHelpMenu(); // prints the Command Help Menu on the console
void outputStatusHeader(); // displays the heading on the monitor

void accelerate(double& previousSpeed, double& currentSpeed, int delta = 5); // calculates the accerelation, with having default value of delta as 5
void brake(double& previousSpeed, double& currentSpeed, int delta = 5); // the brake function reduces the speed according to the user
void cruise(double& previousSpeed, double& currentSpeed, int delta = 5); // the cruise function keeps the speed constant 

void outputStatus(string& command, double& currentSpeed, double& intervalFeetTraveled, double& totalFeetTraveled, double& averageSpeed_FeetPerSecond, int delta = 5, double timeInterval = 1);
// Displays the speed, timeInteval and the total distance traveled
 // Calculates the average speed, the total distance traveled in miles as well as in feets, and the feet distance in a specific time interval

void updateDistanceTraveled(string& command, double& previousSpeed, double& currentSpeed, double& averageSpeed_FeetPerSecond, double& intervalFeetTraveled, double& totalFeetTraveled, double timeInterval = 1, int delta = 5);
// the function that Calculates the value of the total distance traveled by the car in feet as well as in miles
// this function has the output status function embedded in it that prints the data on the monitor

void demo(double& previousSpeed, double& currentSpeed, double& averageSpeed_FeetPerSecond, double& intervalFeetTraveled, double& totalFeetTraveled, int delta = 5, double timeInterval = 1);
// a demo function which has all the function calls in it

int main() // MAIN starts
{
	// variable lists 
	// initializing all the values to zero to avoid any garbage value
	double previousSpeed = 0, currentSpeed = 0, timeInterval = 1; // default time interval, can be changed with the t command
	double averageSpeed_FeetPerSecond= 0, intervalFeetTraveled = 0, totalFeetTraveled = 0;
	string command;
	int delta = 5; // Default value of speed.

	// Changing the console color and the title of the console
	system("color 3f");
	system("title Project 1 - Automobile Speed/ Distance Application Program by Khelan Modi");

	// the following functions are outside the forever loop, because they are going to be printed once
	cout 
		<< "\n\t                          The program simulates the speed of a car "
		<< "\n\t                 and calculates the distance traveled over a period of time"
		<< "\n\t This interactive program takes the input from the KEYBOARD and displays them on the MONITOR"
		<< "\n\t                                      By Khelan Modi"

		<< "\n\n The List of Commands: \n";
	printCommandHelpMenu(); // Has a list of commands that the user can enter. For eg: acc, cruise, brake, demo, exit or even ask the computer to show the menu again.

	// prints the header on the monitor, does not take any arguements nor it returns anything
	outputStatusHeader();

	// Formatting the number to display just one decimal value 
	cout << fixed << setprecision(1);

	// the forever loop starts.
	while (true) { // the forever loop, can be terminated by using the q command

		cout << "\nCommand: "; // initial prompt for the user
		cin >> command;
		cin.ignore(100, '\n'); // cleaning member function

		if (command == "a" || command == "A") // command for acceleration 
		{
			accelerate(previousSpeed, currentSpeed, delta); // calculates the speed. it has reference variables as its arguments
			updateDistanceTraveled(command, previousSpeed, currentSpeed, averageSpeed_FeetPerSecond, intervalFeetTraveled, totalFeetTraveled, timeInterval, delta); 
			// calculates the distance and the average speed of the vehicle
			// has the outputStatus function that prints the collected data on the screen 
		}

		else if (command == "r" || command == "R") { // command for the changing the value of speed. the default value of delta is 5 but can be changed by triggering the r command
			cout << "Enter a value for delta: ";
			cin >> delta;
			cin.ignore(100, '\n');

			while (delta <= 0) // Ask the user to enter a valid number if they enter a number less than or equal to 0. 
			{
				system("color 0f"); // changing the console color to grab the user's attention
				cout << "\t\aPlease enter a number greater than 0. Try again: "; // A error message to let the user know their mistake
				cin >> delta;
				cin.ignore(100, '\n');
			}
			system("color 3f"); // changing the color back to normal if the correct value has been entered
		}
		else if (command == "t" || command == "T" ) // command for variable time interval
		{
			cout << "Enter a valid number for Time Interval: ";
			cin >> timeInterval;
			cin.ignore(100, '\n');

			while (timeInterval <= 0) //Only allows the user to enter a number greater than zero
			{
				system("color 0f"); // changong the console color
				cout << "\t\aPlease enter a number greater than 0. Try again: ";
				cin >> timeInterval;
				cin.ignore(100, '\n');
			}
			system("color 3f");
		}

		else if (command == "d" || command == "D") // the demo command 
		{
			demo(previousSpeed, currentSpeed, averageSpeed_FeetPerSecond, intervalFeetTraveled, totalFeetTraveled, delta, timeInterval); 
			// it has a bunch of function calls to demonstrate the user what the program can do
		}

		else if (command == "c" || command == "C") // the cruise command
		{
			cruise(previousSpeed, currentSpeed, delta); // function keeps the speed constant for further calculations
			updateDistanceTraveled(command, previousSpeed, currentSpeed, averageSpeed_FeetPerSecond, intervalFeetTraveled, totalFeetTraveled, timeInterval, delta);
		}
		else if (command == "b" || command == "B") // the brake command
		{
			brake(previousSpeed, currentSpeed, delta); // function that reduces the speed and then sends the data to the other function for calculations
			updateDistanceTraveled(command, previousSpeed, currentSpeed, averageSpeed_FeetPerSecond, intervalFeetTraveled, totalFeetTraveled, timeInterval, delta);
		}
		else if (command == "q" || command == "Q" || command == "e" || command == "E") // exit command, that takes q and e as inputs
		{
			system("pause"); // halting the screen
			exit (0); // the exit function takes the integer arguments as well, where 0 means successful termination of the program
		}

		else if (command == "h" || command == "H") // the help menu command
		{
			cout << "Supported Commands: \n";
			printCommandHelpMenu(); // function that prints the list of commands on the screen 
		}

		else {
			cout << "\a\tInvalid Command. (Press the h for help)\n\t "; // the error message command, prompts the user to press the correct command
		}
	}
	system("pause"); // Halting the screen 
	return 0; // returns 0 when the program has successfully ended
} // MAIN ENDS HERE

// FUNCTION DEFINITION
void printCommandHelpMenu() { // prints the Command Help Menu on the screen
							  // Has no arguments nor it returns anything to the screen
	cout 
		<< "\t\t A or a \t Accelerate.\n"
		<< "\t\t B or b \t Brake.\n"
		<< "\t\t C or c \t Cruise. \n"
		<< "\t\t D or d \t Demo. \n"
		<< "\t\t H or h \t print this help text\n"
		<< "\t\t T or t \t Change the Time interval\n"
		<< "\t\t R or r \t Change the value of Delta\n"
		<< "\t\t Q or e \t Quit (End this Program).\n\n";
}

// the header function prints the header on the monitor.
// it does not return anything nor does it take any arguments
void outputStatusHeader() {
	cout << "\n       Function     Current State   Current Speed   Interval Distance  Total Feet (and miles) traveled \n";
}

// the accelerate function that increases the speed according to the user's commands
// it firsts assigns the current speed to the previous speed and then adds the value of the delta to the current speed for futher calculations
void accelerate(double& previousSpeed, double& currentSpeed, int delta) {
	previousSpeed = currentSpeed;
	currentSpeed += delta;  // the value can be changed but it has a default value of 5 mph.
}

// the brake function reduces the speed by the value of delta
// if the speed is equal to or less than delta then the current speed becomes zero, instead of getting a negative value
void brake(double& previousSpeed, double& currentSpeed, int delta) {

	previousSpeed = currentSpeed; // copies the value of current speed to previous speed for calculating the distance traveled

	if (currentSpeed > delta)
	{
		currentSpeed -= delta;
	}
	else if (currentSpeed <= delta) // restricting the value to zero, instead of getting a negative value
	{
		currentSpeed = 0;
	}
}

// the cruise function copies the value of current speed to the previous value for further calculation
// Assiging the value of current speed to previous speed, results in calculating the distance traveled without changing the speed
void cruise(double& previousSpeed, double& currentSpeed, int delta) {
	previousSpeed = currentSpeed;
}

// DEMO function definition
// the demo functions has all the function calls 
// the for loop has been used to consolidate the code and at the same time get better results
void demo(double& previousSpeed, double& currentSpeed, double& averageSpeed_FeetPerSecond, double& intervalFeetTraveled, double& totalFeetTraveled, int delta, double timeInterval)
{
	string command;

	command = "c"; // the cruise command
	for (int i = 0; i < 3; i++) {
		cruise(previousSpeed, currentSpeed);
		updateDistanceTraveled(command, previousSpeed, currentSpeed, averageSpeed_FeetPerSecond, intervalFeetTraveled, totalFeetTraveled, timeInterval, delta);
	} // repeats 3 times 

	command = "a"; // the accelerate command
	for (int i = 0; i < 5; i++) {
		accelerate(previousSpeed, currentSpeed, delta);
		updateDistanceTraveled(command, previousSpeed, currentSpeed, averageSpeed_FeetPerSecond, intervalFeetTraveled, totalFeetTraveled, timeInterval, delta);
	} // repeats 5 times, increasing the speed each time

	command = "c"; // cruise command
	for (int i = 0; i < 5; i++) {
		cruise(previousSpeed, currentSpeed);
		updateDistanceTraveled(command, previousSpeed, currentSpeed, averageSpeed_FeetPerSecond, intervalFeetTraveled, totalFeetTraveled, timeInterval, delta);
	} // repeats 5 times, keeping the speed constant

	command = "b"; // brake command
	for (int i = 0; i < 8; i++) {
		brake(previousSpeed, currentSpeed, delta);
		updateDistanceTraveled(command, previousSpeed, currentSpeed, averageSpeed_FeetPerSecond, intervalFeetTraveled, totalFeetTraveled, timeInterval, delta);
	} // repeats 8 times, reducing the speed after every iteration
	cout << endl;
}

// the function that CALCULATES the values for the program
// All the arguments are passed as reference variables 
// the distance is converted to feet
// the speed is converted to feet per sec
void updateDistanceTraveled(string &command, double& previousSpeed, double& currentSpeed, double& averageSpeed_FeetPerSecond, double& intervalFeetTraveled, double& totalFeetTraveled, double timeInterval, int delta)
{
	double averageSpeed = (previousSpeed + currentSpeed) / 2.0; // For cruise command average speed equals to the current speed 
	averageSpeed_FeetPerSecond = averageSpeed * 5280.0 / 3600.0; // converts the value to feets per second from miles per hour
	intervalFeetTraveled = averageSpeed_FeetPerSecond * timeInterval; // calculating the distance in a specific time interval
	totalFeetTraveled += intervalFeetTraveled; // Accumulator that keeps on collecting the total distance traveled by the car. 

	outputStatus(command, currentSpeed, intervalFeetTraveled, totalFeetTraveled, averageSpeed_FeetPerSecond, delta, timeInterval); // displays the data on the screen
}

// the function prints the data on the monitor 
// the data is printed in feets/sec and miles per hour
// it also shows the current state of the vehicle and the command the user has entered.
void outputStatus(string& command, double& currentSpeed, double& intervalFeetTraveled, double& totalFeetTraveled, double& averageSpeed_FeetPerSecond, int delta, double timeInterval) {

	// Accelerate command has only one state,  Accelerating
	if (command == "a" || command == "A") {
		cout << setw(15) << right << "  Accelerate " << setw(20) << right << " Accelerating \t " << setw(8) << left << currentSpeed << " \t" << setw(8) << left
			<< intervalFeetTraveled << " \t  " << setw(8) << left << totalFeetTraveled << " ( " << fixed << setprecision(3) << totalFeetTraveled / 5280.0 << " )"
			<< fixed << setprecision(1) << endl;
	}
	// Cruise command has two different states: stopped and cruising
	else if (command == "c" || command == "C") {
		if (currentSpeed == 0) // when the current speed becomes zero, the current state changes to Stopped
			cout << setw(15) << right << "  Cruise " << setw(20) << right << " Stopped \t " << setw(8) << left << currentSpeed << " \t" << setw(8) << left 
			<< intervalFeetTraveled << " \t  " << setw(8) << left << totalFeetTraveled << " ( "  << fixed << setprecision(3) << totalFeetTraveled / 5280.0 
			<< " )" << fixed << setprecision(1) << endl;
		else // if the current speed is greater than zero the car is still in motion and cruising at that constant speed
			cout << setw(15) << right << "  Cruise " << setw(20) << right << " Cruising \t " << setw(8) << left << currentSpeed << " \t" << setw(8) << left
			<< intervalFeetTraveled << " \t  " << setw(8) << left << totalFeetTraveled << " ( " << fixed << setprecision(3) << totalFeetTraveled / 5280.0
			<< " )" << fixed << setprecision(1) << endl;
	}
	// Brake command also has two states: Stopped and Braking (which are nested in the else if loop)
	else if (command == "b" || command == "B") { 
		if (currentSpeed == 0) // This state means that the car has come to a halt, i.e. speed is equal to zero
			cout << setw(15) << right << "  Brake " << setw(20) << right << " Stopped \t " << setw(8) << left << currentSpeed << " \t" << setw(8) << left 
			<< intervalFeetTraveled << " \t  " << setw(8) << left << totalFeetTraveled << " ( " << fixed << setprecision(3) << totalFeetTraveled / 5280.0
			<< " )" << fixed << setprecision(1) << endl;
		else // The car is deaccelerating at a constant speed, before coming to a complete halt  
			cout << setw(15) << right << "  Brake " << setw(20) << right << " Braking \t " << setw(8) << left << currentSpeed << " \t" << setw(8) << left 
			<< intervalFeetTraveled << " \t  " << setw(8) << left << totalFeetTraveled << " ( " << fixed << setprecision(3) << totalFeetTraveled / 5280.0
			<< " )" << fixed << setprecision(1) << endl;
	}
} // FUNCTION DEFINITIONS END