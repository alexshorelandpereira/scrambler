//
// Created by alexa on 26/05/2019.
//

#include<string>
#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include <random>
#include <chrono>




#ifndef ENCRYPTOR_ENCRYPTOR_H

class CaesarCipher {
public:

	//////////////
	//CONSTRUCTORS//
	//////////////

	CaesarCipher();
	~CaesarCipher();


	/////////////////////
	//GETTERS AND SETTERS//
	/////////////////////

	std::string getInput();
	void setInput(std::string);
	std::string getAlphabet();
	short int getKey();
	void setKey(short int);


	//////////
	//METHODS//
	/////////

	void print() const;
	std::string encrypt();
	std::string decrypt(std::string, short int key); //Possibly do this in another object
	short int keyGenerator();
	std::string preProcessString();
	char shift(short int key);


	///////////////////
	//MEMBER VARIABLES//
	//////////////////

private:
	const char alphabet[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
							   'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	std::string Input;
	short int sizeOfAlphabet = sizeof(alphabet) / sizeof(char);
	short int key;
};

#define ENCRYPTOR_ENCRYPTOR_H

const constexpr auto DEFAULT_INPUT = "HELLO WORLD";

#endif ENCRYPTOR_ENCRYPTOR_H

