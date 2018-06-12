#include <iostream>
#include <fstream>
#include <sstream>
#include "app/ECC.hpp"

void help();
void generatePrivate();
void generatePublic();
void encrypt(std::string file, std::string their_key);
void decrypt(std::string file);

int main(int argc, char **argv) {
	if (argc < 2) {
		help();
		return 0;
	}
	std::string option = std::string(argv[1]);
	if (option == "generate" && argc == 3) {
		std::string type(argv[2]);
		if(type == "private") {
			generatePrivate();
			return 0;
		}
		else if (type == "public") {
			generatePublic();
			return 0;
		}
	} else if (option == "encrypt" && argc == 4) {
		std::string file(argv[2]);
		std::string their_key(argv[3]);
		encrypt(file, their_key);
		return 0;
	} else if (option == "decrypt" && argc == 3) {
		std::string file(argv[2]);
		decrypt(file);
		return 0;
	}

	help();
	return 0;
}

void help() {
	std::cout << "Options:\n\n";
	std::cout << "generate private \t\t Use to generate the private key\n\r";
	std::cout << "generate public \t\t Use to generate the public key\n";
	std::cout << "encrypt file public_key \t Use to encrypt a given [file] using the public_key\n\r";
	std::cout << "decrypt file \t\t\t Use to decrypt a given [file]\n\r";
}

void generatePrivate() {
	std::ofstream private_key_file;
	ECC ecc;
	unsigned char *private_key = ecc.generatePrivateKey();
	private_key_file.open("private.key", std::ios::out | std::ios::binary);
	private_key_file.write((const char*)private_key, N_BYTES);
	private_key_file.close();
	delete [] private_key;
}

void generatePublic() {
	std::ifstream private_key_file;
	unsigned char private_key[N_BYTES];
	unsigned char *public_key;

	private_key_file.open("private.key", std::ios::in | std::ios::binary);
	if (!private_key_file.is_open()) {
		std::cout << "Private key not found!" << std::endl;
		return;
	}
	private_key_file.read((char*)private_key, N_BYTES);
	private_key_file.close();

	ECC ecc;
	public_key = ecc.generatePublicKey(private_key);

	std::ofstream public_key_file;
	public_key_file.open("public.key", std::ios::out | std::ios::binary);
	public_key_file.write((const char*)public_key, N_BYTES * 2);
	public_key_file.close();
	delete [] public_key;
}

void encrypt(std::string file, std::string their_key) {
	ECC ecc;
	unsigned char my_public_key[N_BYTES * 2];
	unsigned char their_public_key[N_BYTES * 2];
	unsigned char private_key[N_BYTES];

	std::ifstream my_public_key_file;
	my_public_key_file.open("public.key", std::ios::in | std::ios::binary);
	if (!my_public_key_file.is_open()) {
		std::cout << "Your public key not found!" << std::endl;
		return;
	}
	my_public_key_file.read((char*) my_public_key, N_BYTES * 2);
	my_public_key_file.close();

	std::ifstream private_key_file;
	private_key_file.open("private.key", std::ios::in | std::ios::binary);
	if (!private_key_file.is_open()) {
		std::cout << "Your private key not found!" << std::endl;
		return;
	}
	private_key_file.read((char*) private_key, N_BYTES * 2);
	private_key_file.close();

	std::ifstream their_public_key_file;
	their_public_key_file.open(their_key, std::ios::in | std::ios::binary);
	if (!their_public_key_file.is_open()) {
		std::cout << "Their public key not found!" << std::endl;
		return;
	}
	their_public_key_file.read((char*) their_public_key, N_BYTES * 2);
	their_public_key_file.close();

	std::ifstream file_stream;
	file_stream.open(file, std::ios::in | std::ios::binary);
	if (!file_stream.is_open()) {
		std::cout << "Failure to open file!" << std::endl;
		return;
	}
	ecc.encrypt(&file_stream, my_public_key, private_key, their_public_key);

	file_stream.close();
}

void decrypt(std::string file) {
	ECC ecc;
	unsigned char private_key[N_BYTES];

	std::ifstream private_key_file;
	private_key_file.open("private.key", std::ios::in | std::ios::binary);
	if (!private_key_file.is_open()) {
		std::cout << "Your private key not found!" << std::endl;
		return;
	}
	private_key_file.read((char*) private_key, N_BYTES);
	private_key_file.close();

	std::ifstream file_stream;
	file_stream.open(file, std::ios::in | std::ios::binary);
	if (!file_stream.is_open()) {
		std::cout << "Failure to open file!" << std::endl;
		return;
	}
	ecc.decrypt(&file_stream, private_key);

	file_stream.close();
}