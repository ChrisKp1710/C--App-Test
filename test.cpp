// Test semplice per verificare che il compilatore funzioni
#include <iostream>
#include <string>

int main() {
  std::cout << "Test compilazione C++ - OK!" << std::endl;
  std::cout << "Se vedi questo messaggio, il compilatore funziona."
            << std::endl;

  std::string input;
  std::cout << "\nPremi INVIO per continuare...";
  std::getline(std::cin, input);

  return 0;
}
