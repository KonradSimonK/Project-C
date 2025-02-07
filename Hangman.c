#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//CHAR AUTHOR[25] = "Konrad Szymon Kedzia"    :-)

// Definition of an element in the list, each element is a string with a maximum of 50 characters
struct Element
{
    char k[50];
    struct Element *next; // Pointer to the next element in the list
};

// Function to display the Hangman state based on the number of mistakes
void druck(int f)
{
    // Definition of elements, each representing a part of the Hangman drawing
    struct Element e1 = {"\n\n\n\n\t/\n", NULL};
    struct Element e2 = {"\n\n\n\n\t/|\n", NULL};
    struct Element e3 = {"\n\n\n\n\t/|\\\n", NULL};
    struct Element e4 = {"\n\n\n\t |\n\t/|\\\n", NULL};
    struct Element e5 = {"\n\n\t |\n\t |\n\t/|\\\n", NULL};
    struct Element e6 = {"\n\t |\n\t |\n\t |\n\t/|\\\n", NULL};
    struct Element e7 = {"\n\t  _\n\t |\n\t |\n\t |\n\t/|\\\n", NULL};
    struct Element e8 = {"\n\t  __\n\t |\n\t |\n\t |\n\t/|\\\n", NULL};
    struct Element e9 = {"\n\t  ___\n\t |\n\t |\n\t |\n\t/|\\\n", NULL};
    struct Element e10 = {"\n\t  ____\n\t |\n\t |\n\t |\n\t/|\\\n", NULL};
    struct Element e11 = {"\n\t  ____\n\t |    O\n\t |\n\t |\n\t/|\\\n", NULL};
    struct Element e12 = {"\n\t  ____\n\t |    O\n\t |   /\n\t |\n\t/|\\\n", NULL};
    struct Element e13 = {"\n\t  ____\n\t |    O\n\t |   /|\n\t |\n\t/|\\\n", NULL};
    struct Element e14 = {"\n\t  ____\n\t |    O\n\t |   /|\\\n\t |\n\t/|\\\n", NULL};
    struct Element e15 = {"\n\t  ____\n\t |    O\n\t |   /|\\\n\t |   /\n\t/|\\\n", NULL};
    struct Element e16 = {"\n\t  ____\n\t |    O\n\t |   /|\\\n\t |   / \\\n\t/|\\\n", NULL};

    // Linking the list by setting pointers to the next elements
    e1.next = &e2;
    e2.next = &e3;
    e3.next = &e4;
    e4.next = &e5;
    e5.next = &e6;
    e6.next = &e7;
    e7.next = &e8;
    e8.next = &e9;
    e9.next = &e10;
    e10.next = &e11;
    e11.next = &e12;
    e12.next = &e13;
    e13.next = &e14;
    e14.next = &e15;
    e15.next = &e16;

    // Initializing the current element of the list
    struct Element *current = &e1;

    // Loop to move to the correct element based on the number of mistakes
    for (int i = 1; i < f; i++)
        current = current->next;

    // Print the current Hangman state
    printf("\n%s\n", current->k);
};

int main()
{
    char word[25]; // The word to be guessed
    char guessed[25]; // Array to store guessed letters
    char guess; // The currently guessed letter
    int j = 0; // Index of an array "words"
    int f = 0; // Counter for incorrect attempts
    int correct = 0; // Flag for correct letters
    int r, same;

    char words[150][25]; // Array to store words from the file
    char ranword[25]; // Currently read word from the file
    FILE *file; // File pointer to open the word list
    file = fopen("words.txt", "r"); // Open the file in read mode

    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Read words from the file and store them in the array
    while (fscanf(file, "%s", ranword) == 1)
    {
        strcpy(words[j], ranword); // Storing currently read word to the array "words" of Index j
        j++;
    }
    fclose(file); // Close the file

    srand(time(NULL)); // Initialize the random number generator
    r = rand() % j; // Randomly select a word
    strcpy(word, words[r]); // Saving randomly chosen word as a word to be guessed

    // Print placeholders for the word to be guessed
    for (int i = 0; i < strlen(word); i++)
        printf("_ ");

    do
    {
        printf("\n\nThe letter you are guessing: ");
        scanf(" %c", &guess); // Read the guessed letter
        guess = tolower(guess); // Convert to lowercase

        // Check if the guessed letter is in the word
        for (int i = 0; i < strlen(word); i++)
        {
            if (guess == word[i])
            {
                guessed[i] = word[i]; // Store the guessed letter
                correct = 1; // Set the flag for correct letters
            }
            if (guessed[i] == word[i])
                printf("%c ", word[i]); // Print the guessed letter
            else
                printf("_ "); // Print a placeholder
        }

        if (correct == 0)
        {
            f++; // Increment the incorrect attempt counter
            druck(f); // Print the current Hangman state
            if (f == 16)
            {
                printf("\nYou lose.!\n"); // Loss message after 16 incorrect attempts
                return 1;
            }
        }
        else
            printf("\n\nYou found the letter");

        correct = 0; // Reset the flag for the next attempt

        same = strncmp(word, guessed, strlen(word)); // Compare the guessed and actual word
    } while (same != 0);

    printf("\n\nYou win!\n"); // Winning message

    return 0;
}
