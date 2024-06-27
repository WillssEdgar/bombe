// Rotor Structure
#include "plug_board.h"
#include "../Rotor/rotor.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * changePlugBoard - Allows the user to change the plugboard wiring by swapping
 * pairs of letters.
 *
 * @plugBoard: Pointer to the PlugBoard structure that holds the current
 * plugboard wiring.
 *
 * This function prompts the user to input two letters, then swaps their
 * mappings in the plugboard wiring. The new mappings are printed to the
 * console.
 */
void changePlugBoard(struct PlugBoard *plugBoard) {
  char first_letter;
  char *message = "First letter you would like to change";
  printf("\n%*s %s: ", format_string(message), "", message);
  scanf(" %c", &first_letter); // Note the space before %c
  first_letter = toupper(first_letter);

  char second_letter;
  message = "Second letter you would like to change";
  printf("%*s %s: ", format_string(message), "", message);
  scanf(" %c", &second_letter); // Note the space before %c
  second_letter = toupper(second_letter);

  char first_letter_partner = plugBoard->wiring[first_letter - 'A'];
  char second_letter_partner = plugBoard->wiring[second_letter - 'A'];

  plugBoard->wiring[first_letter - 'A'] = second_letter;
  plugBoard->wiring[second_letter - 'A'] = first_letter;
  plugBoard->wiring[first_letter_partner - 'A'] = second_letter_partner;
  plugBoard->wiring[second_letter_partner - 'A'] = first_letter_partner;
  printf("\n%*s New Mappings:\n", format_string("New Mappings:"), "");
  printf("%48c -> %c \n", first_letter, plugBoard->wiring[first_letter - 'A']);
  printf("%48c -> %c \n", second_letter,
         plugBoard->wiring[second_letter - 'A']);
  printf("%48c -> %c \n", first_letter_partner,
         plugBoard->wiring[first_letter_partner - 'A']);
  printf("%48c -> %c \n", second_letter_partner,
         plugBoard->wiring[second_letter_partner - 'A']);
}

/**
 * initializePlugBoard - Initializes the plugboard with a predefined set of
 * wiring mappings.
 *
 * @plugBoard: Pointer to the PlugBoard structure that will be initialized.
 *
 * This function sets up the initial state of the plugboard by mapping each
 * letter to itself, and then applying specific swaps to create the predefined
 * wiring.
 */
void initializePlugBoard(struct PlugBoard *plugBoard) {
  for (int i = 0; i < 26; i++) {
    plugBoard->wiring[i] = 'A' + i; // Initialize with 'A' to 'Z'
  }
  plugBoard->wiring['A' - 'A'] = 'D'; // Map 'A' to 'D'
  plugBoard->wiring['D' - 'A'] = 'A'; // Map 'D' to 'A'
  plugBoard->wiring['B' - 'A'] = 'F'; // Map 'B' to 'F'
  plugBoard->wiring['F' - 'A'] = 'B'; // Map 'F' to 'B'
  plugBoard->wiring['C' - 'A'] = 'G'; // Map 'C' to 'G'
  plugBoard->wiring['G' - 'A'] = 'C'; // Map 'G' to 'C'
  plugBoard->wiring['E' - 'A'] = 'J'; // Map 'E' to 'J'
  plugBoard->wiring['J' - 'A'] = 'E'; // Map 'J' to 'E'
  plugBoard->wiring['H' - 'A'] = 'K'; // Map 'H' to 'K'
  plugBoard->wiring['K' - 'A'] = 'H'; // Map 'K' to 'H'
  plugBoard->wiring['I' - 'A'] = 'M'; // Map 'I' to 'M'
  plugBoard->wiring['M' - 'A'] = 'I'; // Map 'M' to 'I'
  plugBoard->wiring['L' - 'A'] = 'N'; // Map 'L' to 'N'
  plugBoard->wiring['N' - 'A'] = 'L'; // Map 'N' to 'L'
  plugBoard->wiring['O' - 'A'] = 'P'; // Map 'O' to 'P'
  plugBoard->wiring['P' - 'A'] = 'O'; // Map 'P' to 'O'
  plugBoard->wiring['Q' - 'A'] = 'S'; // Map 'Q' to 'S'
  plugBoard->wiring['S' - 'A'] = 'Q'; // Map 'S' to 'Q'
  plugBoard->wiring['R' - 'A'] = 'T'; // Map 'R' to 'T'
  plugBoard->wiring['T' - 'A'] = 'R'; // Map 'T' to 'R'
  plugBoard->wiring['U' - 'A'] = 'V'; // Map 'U' to 'V'
  plugBoard->wiring['V' - 'A'] = 'U'; // Map 'V' to 'U'
  plugBoard->wiring['W' - 'A'] = 'X'; // Map 'W' to 'X'
  plugBoard->wiring['X' - 'A'] = 'W'; // Map 'X' to 'W'
  plugBoard->wiring['Y' - 'A'] = 'Z'; // Map 'Y' to 'Z'
  plugBoard->wiring['Z' - 'A'] = 'Y'; // Map 'Z' to 'Y'
}

/**
 * sendLetterThroughPlugBoard - Simulates sending a letter through the
 * plugboard.
 *
 * @plugBoard: Pointer to the PlugBoard structure that holds the current
 * plugboard wiring.
 * @letter: The letter to be sent through the plugboard.
 *
 * This function returns the letter that the input letter is mapped to in the
 * plugboard wiring.
 *
 * Return: The letter mapped to the input letter.
 */
char sendLetterThroughPlugBoard(struct PlugBoard *plugBoard, char letter) {
  return plugBoard->wiring[letter - 'A'];
}

/**
 * outputPlugBoard - Prints the current state of the plugboard mappings.
 *
 * @plugBoard: Pointer to the PlugBoard structure that holds the current
 * plugboard wiring.
 *
 * This function prints the current plugboard mappings to the console in a
 * formatted manner, showing which letters are mapped to each other.
 */
void outputPlugBoard(struct PlugBoard *plugBoard) {
  char *plugboard_string = "------------Current Plug Board-------------";
  int total_width = 100;
  int str_len = strlen(plugboard_string);
  int padding = (total_width - str_len) / 2;

  printf("%*s%s%*s\n\n", padding, "", plugboard_string, padding, "");
  for (int i = 0; i < 26; i++) {
    char currentLetter = 'A' + i;
    if (i % 2 == 0) {
      printf("%37c -> %c", currentLetter, plugBoard->wiring[i]);
    } else {
      printf("%15c -> %c\n", currentLetter, plugBoard->wiring[i]);
    }
  }
}
