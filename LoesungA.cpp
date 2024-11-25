#include <string>
#include <cctype>
#include "TestResult.h"

using namespace std;

// Funktion: Prüft, ob eine Teilzeichenkette "nice" ist
bool isNice(const char* start, int length) {
    bool lowercase[26] = {false};
    bool uppercase[26] = {false};

    // Iteriere über die Teilzeichenkette
    for (int i = 0; i < length; ++i) {
        char c = *(start + i); // Aktuelles Zeichen
        if (islower(c)) {
            lowercase[c - 'a'] = true; // Kleinbuchstabe markieren
        } else if (isupper(c)) {
            uppercase[c - 'A'] = true; // Großbuchstabe markieren
        }
    }

    // Überprüfe, ob jedes Zeichen beide Varianten enthält
    for (int i = 0; i < 26; ++i) {
        if ((lowercase[i] && !uppercase[i]) || (uppercase[i] && !lowercase[i])) {
            return false;
        }
    }

    return true;
}

// Hauptfunktion: Findet die längste "nice"-Teilzeichenkette
TestResult LoesungA(const string &s) {
    int maxLen = 0;
    int startIndex = -1;

    // Iteriere über alle möglichen Teilzeichenketten
    for (int i = 0; i < s.size(); ++i) {
        for (int j = i; j < s.size(); ++j) {
            int length = j - i + 1;
            const char* start = &s[i]; // Pointer auf den Anfang der Teilzeichenkette

            if (isNice(start, length)) {
                if (length > maxLen) {
                    maxLen = length;
                    startIndex = i;
                }
            }
        }
    }

    return TestResult(startIndex, maxLen); // Rückgabe des Ergebnisses
}
