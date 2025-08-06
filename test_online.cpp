/*
 * Windows Helper - Versione per Test Online
 *
 * ISTRUZIONI:
 * 1. Copia questo codice
 * 2. Vai su https://www.onlinegdb.com/online_c++_compiler
 * 3. Incolla il codice e clicca "Run"
 *
 * Nota: Questa versione non ha l'interfaccia grafica Windows
 * ma mostra la logica dell'applicazione.
 */

#include <iostream>
#include <limits>
#include <string>
#include <vector>

class WindowsHelper {
private:
  std::vector<std::string> messages;

public:
  void addMessage(const std::string &message) {
    messages.push_back(message);
    std::cout << "[NUOVO MESSAGGIO] " << message << std::endl;
  }

  void showAllMessages() {
    std::cout << "\n=== TUTTI I MESSAGGI ===" << std::endl;
    if (messages.empty()) {
      std::cout << "Nessun messaggio presente." << std::endl;
    } else {
      for (size_t i = 0; i < messages.size(); ++i) {
        std::cout << (i + 1) << ". " << messages[i] << std::endl;
      }
    }
    std::cout << "========================\n" << std::endl;
  }

  void clearMessages() {
    messages.clear();
    std::cout << "Lista messaggi pulita!" << std::endl;
  }

  void showMenu() {
    std::cout << "\n--- WINDOWS HELPER MENU ---" << std::endl;
    std::cout << "1. Aggiungi messaggio" << std::endl;
    std::cout << "2. Mostra tutti i messaggi" << std::endl;
    std::cout << "3. Pulisci lista messaggi" << std::endl;
    std::cout << "4. Esci" << std::endl;
    std::cout << "Scegli un'opzione (1-4): ";
  }
};

int main() {
  WindowsHelper app;

  std::cout << "===============================================" << std::endl;
  std::cout << "    WINDOWS HELPER - VERSIONE CONSOLE" << std::endl;
  std::cout << "===============================================" << std::endl;

  app.addMessage("Benvenuto in Windows Helper!");
  app.addMessage("Questa è la versione console per testare la logica.");

  int choice;
  std::string userInput;

  while (true) {
    app.showMenu();

    if (!(std::cin >> choice)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Input non valido! Riprova." << std::endl;
      continue;
    }

    std::cin.ignore(); // Pulisce il buffer

    switch (choice) {
    case 1:
      std::cout << "Inserisci il tuo messaggio: ";
      std::getline(std::cin, userInput);
      if (!userInput.empty()) {
        app.addMessage("Utente: " + userInput);
      } else {
        std::cout << "Messaggio vuoto non aggiunto." << std::endl;
      }
      break;

    case 2:
      app.showAllMessages();
      break;

    case 3:
      app.clearMessages();
      break;

    case 4:
      std::cout << "Grazie per aver usato Windows Helper!" << std::endl;
      return 0;

    default:
      std::cout << "Opzione non valida! Scegli 1-4." << std::endl;
      break;
    }
  }

  return 0;
}
