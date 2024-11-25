#include <string>
#include "TestResult.h"

using namespace std;

// Hilfsfunktion: Überprüft, ob ein Zeichen "nice" ist (beide Varianten vorhanden)
bool isCharNice(const string &s, int start, int end, char c) {
    bool hasLower = false, hasUpper = false;

    for (int i = start; i <= end; ++i) {
        if (s[i] == c) hasLower = true;
        if (s[i] == toupper(c)) hasUpper = true;
    }

    return hasLower && hasUpper;
}

// Rekursive Funktion: Findet die längste "nice"-Teilzeichenkette
TestResult findLongestNiceSubstring(const string &s, int start, int end) {
    if (start > end) return TestResult(-1, 0); // Basisfall: Leerer Bereich

    // Prüfe, ob der Bereich "nice" ist
    for (int i = start; i <= end; ++i) {
        char c = s[i];
        if (!isCharNice(s, start, end, tolower(c))) {
            // Zeichen c ist nicht "nice", teile den Bereich in zwei Hälften
            TestResult left = findLongestNiceSubstring(s, start, i - 1);
            TestResult right = findLongestNiceSubstring(s, i + 1, end);

            // Wähle das bessere Ergebnis
            return (left.length >= right.length) ? left : right;
        }
    }

    // Der Bereich ist vollständig "nice"
    return TestResult(start, end - start + 1);
}

// Hauptfunktion für Lösung B
TestResult LoesungB(const string &s) {
    return findLongestNiceSubstring(s, 0, s.size() - 1);
}
