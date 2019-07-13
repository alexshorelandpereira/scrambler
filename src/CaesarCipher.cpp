
//
// Created by alexa on 26/05/2019.
//

#include "CaesarCipher.h"


//////////////
//CONSTRUCTORS//
//////////////

/*
Default constructor
*/

CaesarCipher::CaesarCipher() {
	Input = DEFAULT_INPUT;
	key = keyGenerator();
}

/*
Destructor
*/

CaesarCipher::~CaesarCipher() {
	std::cout << "Destructor called on: " << this << '\n' << '\n';
}


/////////////////////
//GETTERS AND SETTERS//
/////////////////////

/*
Getter for currently stored Input
*/

std::string CaesarCipher::getInput() {
	return Input;
}

/*
Setter for Input
*/

void CaesarCipher::setInput(std::string newInput) {
	//Using move() to remove unnecessary copying of the variable
	Input = move(newInput);
	Input = preProcessString();
}

/*
Displays the contents of alphabet
*/

std::string CaesarCipher::getAlphabet() {
	std::string output;
	for (char c : alphabet) {
		output += c;
	}
	return output;
}

/*
Getter for the currently stored Key
*/

short int CaesarCipher::getKey() {
	return key;
}

/*
Setter for Key. Will not allow values outside of the range of 1-25 (inclusive) to prevent double (or more) wrapping around alphabet
because this is pointless, expensive and adds nothing to the security of the cipher.
*/

void CaesarCipher::setKey(short int newKey) {
	//If key is set to a value that is out of bounds, set it to the edge of the boundary.
	if (newKey >= 26) {
		key = 25;
	}
	else if (newKey <= 0) {
		key = 1;
	}
	else {
		key = newKey;
	}
}


//////////
//METHODS//
/////////

/*
The purpose of this method is to convert the string to be encrypted (Input) into a more suitable format by removing trailing whitespace
and capitalising the letters which allows "alphabet"'s size to be cut in half.
*/

std::string CaesarCipher::preProcessString() {
	std::string processedString;
	//Convert string to upper case
	transform(Input.begin(), Input.end(), Input.begin(), ::toupper);
	for (char i : Input) {
		if (i == ' ' && !isspace(processedString.back())) {
			processedString += ' ';
		}
		else {
			processedString += i;
		}

	}
	//Remove trailing whitespace
	std::size_t last = processedString.size() - 1; //watch
	while (last >= 0 && processedString[last] == ' ') {
		processedString.pop_back();
		--last;
	}
	return processedString;
}

/*
The purpose of this method is to generate a random number between 1 and 25 and return it
*/

short int CaesarCipher::keyGenerator() {
	//Generate seed from system clock
	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	//Use seed to construct mersenne_twister_engine
	//Seed is derived from system clock so will not exceed the maximum size of an unsigned int. Therefore, the cast is safe and is used to cover the C4244 warning.
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> distribution(1, sizeOfAlphabet - 1);
	//Pseudo-randomly select a value from the distribution vector
	short int newKey = distribution(generator);
	return newKey;
}

/*
The purpose of this method is to provide detail on the state of an instance of CaesarCipher
*/

void CaesarCipher::print() const {
	std::cout << "Print function called on " << this << '\n';
	std::cout << "Alphabet: ";
	for (char c : alphabet) {
		std::cout << c;
	}
	std::cout << '\n';
	std::cout << "Crisp input: " << Input << '\n';
	std::cout << "Key: " << key << '\n' << '\n';
}

/*
The purpose of this method is to perform an individual Caesar shift of a letter based on the value of key and return the shifted
letter
*/

char CaesarCipher::shift(short int index) {
	char shiftedLetter;
	if ((index + key) < sizeOfAlphabet) {
		//Set the current value in the input string to the index holding the corresponding letter, plus the
		//Caesar shift.
		shiftedLetter = alphabet[index + key];

		//Otherwise add one until at end of array then go back to the beginning however many times the key
		//Dictates that the alphabet will be shifted
	}
	else {
		//Could give y a better name
		for (short int y = 0; y < key; y++) {
			if ((index + 1) < sizeOfAlphabet) {
				index += 1;
			}
			else {
				index = 0;
			}
		}
		shiftedLetter = alphabet[index];
	}
	return shiftedLetter;
}

/*
The purpose of this method is to iterate over the input string and to call/perform the necessary functions to encrypt it.
*/

std::string CaesarCipher::encrypt() {
	short int index;
	std::string scrambledString;
	bool isALetter;

	//Iterate over input string
	for (char current : Input) {
		//Check if current character is in the alphabet by searching 'alphabet' array for any matching characters
		isALetter = std::find(std::begin(alphabet), std::end(alphabet), current) != std::end(alphabet);
		if (isALetter) {
			//Cast is because value being returned is an _int64 but value stored will never be larger than what a short int can hold. 
			index = (short int)std::distance(alphabet, std::find(alphabet, alphabet + sizeOfAlphabet, current));
			current = shift(index);
		}
		scrambledString += current;
	}
	return scrambledString;
}