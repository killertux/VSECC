#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "app/ECC.hpp"

void help();
void generatePrivate();
void generatePublic();

int main(int argc, char **argv) {
	if (argc < 2) {
		help();
		return 0;
	}
	std::string option = std::string(argv[1]);
	if (option == "generate" && argc == 3) {
		std::string type = std::string(argv[2]);
		if(type == "private")
			generatePrivate();
		else
			generatePublic();
		return 0;
	}

	help();
	return 0;
}

void help() {
	std::cout << "USAGE: ECC " << std::endl;
}

void generatePrivate() {
	std::ofstream private_key_file;
	ECC ecc;
	std::string private_key = ecc.generatePrivateKey();
	private_key_file.open("private.key", std::ios::out);
	private_key_file << private_key;
	private_key_file.close();
}

void generatePublic() {
	std::ifstream private_key_file;
	std::string private_key;
	std::string public_key;

	private_key_file.open("private.key", std::ios::in);
	if (!private_key_file.is_open()) {
		std::cout << "Private key not found!" << std::endl;
		return;
	}
	if(!getline(private_key_file, private_key) || private_key.empty()) {
		std::cout << "Private key not found!" << std::endl;
		return;
	}
	private_key_file.close();

	ECC ecc;
	public_key = ecc.generatePublicKey(private_key);

	std::ofstream public_key_file;
	public_key_file.open("public.key", std::ios::out);
	public_key_file << public_key;
	public_key_file.close();
}