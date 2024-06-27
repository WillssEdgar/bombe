
#include "Plug_Board/plug_board.h"
#include "Reflector/reflector.h"
#include "Rotor/rotor.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void brute_force(char *encrypted_message, char *decrypted_message,
                 struct Rotor *rotor_one, struct Rotor *rotor_two,
                 struct Rotor *rotor_three) {

  char encoded[256];

  struct PlugBoard plug_board;
  initializePlugBoard(&plug_board);

  struct Reflector reflector;
  initializeReflector(&reflector);

  size_t len = strlen(encrypted_message);
  if (encrypted_message[len - 1] == '\n') {
    encrypted_message[len - 1] = '\0';
    len--;
  }

  for (size_t i = 0; i < len; i++) {
    encrypted_message[i] = toupper(encrypted_message[i]);
    decrypted_message[i] = toupper(decrypted_message[i]);
  }
  encrypted_message[len] = '\0'; // Ensure the string is null-terminated
  decrypted_message[len] = '\0';
  // int count = 0;
  for (int rotor_three_position = 0; rotor_three_position < 26;
       rotor_three_position++) {
    for (int rotor_two_position = 0; rotor_two_position < 26;
         rotor_two_position++) {
      for (int rotor_one_position = 0; rotor_one_position < 26;
           rotor_one_position++) {

        // Initialize rotor positions
        initializeRotor(rotor_one);
        initializeRotor(rotor_two);
        initializeRotor(rotor_three);

        for (int i = 0; i < rotor_one_position; i++)
          rotateRotor(rotor_one);
        for (int i = 0; i < rotor_two_position; i++)
          rotateRotor(rotor_two);
        for (int i = 0; i < rotor_three_position; i++)
          rotateRotor(rotor_three);

        strcpy(encoded, encrypted_message); // Copy encrypted_message to avoid
                                            // modifying the original
        // Decrypt message with current rotor positions
        for (size_t i = 0; i < len; i++) {
          char originalChar = encoded[i];
          if (isalpha(originalChar)) {
            char newChar =
                sendLetterThroughPlugBoard(&plug_board, originalChar);
            newChar = sendLetterThroughRotor(rotor_one, newChar, true);
            newChar = sendLetterThroughRotor(rotor_two, newChar, true);
            newChar = sendLetterThroughRotor(rotor_three, newChar, true);
            newChar = sendLetterThroughReflector(&reflector, newChar);
            newChar = sendLetterThroughRotor(rotor_three, newChar, false);
            newChar = sendLetterThroughRotor(rotor_two, newChar, false);
            newChar = sendLetterThroughRotor(rotor_one, newChar, false);
            newChar = sendLetterThroughPlugBoard(&plug_board, newChar);
            encoded[i] = newChar;

            // Rotate rotors
            rotateRotor(rotor_one);
            if (rotor_one->rotation_count == 0) {
              rotateRotor(rotor_two);
              if (rotor_two->rotation_count == 0) {
                rotateRotor(rotor_three);
              }
            }
          } else {
            encoded[i] =
                originalChar; // Non-alphabetic characters are not encrypted
          }
        }
        encoded[len] = '\0'; // Ensure encoded string is properly terminated

        // Compare decoded message with decrypted_message
        if (strcmp(encoded, decrypted_message) == 0) {
          printf("%*s Decrypted message found: %s\n",
                 format_string("Decrypted message found: "), "", encoded);
          printf("%*s Rotor Positions:\n", format_string("Rotor Positions: "),
                 "");
          printf("%*s Rotor One: %d\n", format_string("Rotor One: "), "",
                 rotor_one_position);
          printf("%*s Rotor Two: %d\n", format_string("Rotor Two: "), "",
                 rotor_two_position);
          printf("%*s Rotor Three: %d\n", format_string("Rotor Three: "), "",
                 rotor_three_position);
          return; // Exit function after finding correct rotor positions
        }
      }
    }
  }

  printf("Decrypted message not found.\n");
}

void bombe() {

  struct Rotor rotor_one = {"Rotor One", NULL, NULL, 0};
  initializeRotor(&rotor_one);
  rotor_one.rotation_count = 10;

  struct Rotor rotor_two = {"Rotor Two", NULL, NULL, 0};
  initializeRotor(&rotor_two);

  struct Rotor rotor_three = {"Rotor Three", NULL, NULL, 0};
  initializeRotor(&rotor_three);

  char encrypted_message[256];
  char *enter_encrypted_message = "Enter the encrypted message";
  printf("%*s%s: ", format_string(enter_encrypted_message), "",
         enter_encrypted_message);
  fgets(encrypted_message, sizeof(encrypted_message), stdin);
  encrypted_message[strcspn(encrypted_message, "\n")] = '\0'; // Remove newline

  char decrypted_message[256];
  char *enter_decrypted_message = "Enter the decrypted message";
  printf("%*s%s: ", format_string(enter_decrypted_message), "",
         enter_decrypted_message);
  fgets(decrypted_message, sizeof(decrypted_message), stdin);
  decrypted_message[strcspn(decrypted_message, "\n")] = '\0'; // Remove newline

  brute_force(encrypted_message, decrypted_message, &rotor_one, &rotor_two,
              &rotor_three);

  // Clean up
  freeRotor(&rotor_one);
  freeRotor(&rotor_two);
  freeRotor(&rotor_three);
}

int main() {
  bombe();
  return 0;
}
