#include "pch.h"
#include "../src/CaesarCipher.cpp"


//Tests for auto capitalisation and the deletion of trailing whitespace
TEST(CaesarCipher, PreProcessInput) {
	auto TestObj = new CaesarCipher();
	TestObj->setInput("hellO WoRld     ");
	std::string expected = ("HELLO WORLD");
	std::string actual = TestObj->getInput();
	EXPECT_EQ(expected, actual);
	delete TestObj;
}

//Test that this instance of KeyGenerator has generated a key that obeys the rules of key generation
TEST(CaesarCipher, KeyGenerator) {
	auto TestObj = new CaesarCipher();
	int key = TestObj->getKey();
	EXPECT_TRUE(key > 0 && key < 26);
	delete TestObj;
}

//Test for correct encryption mechanism for a given key
TEST(CaesarCipher, Encrypt) {
	auto TestObj = new CaesarCipher();
	TestObj->setInput("Hello world!12345*/&/");
	TestObj->setKey(4);
	std::string encryptedString = TestObj->encrypt();
	std::string expected = ("LIPPS ASVPH!12345*/&/");
	EXPECT_EQ(expected, encryptedString);
	delete TestObj;
}

