#include <stdio.h>
#include <iostream>

using namespace std;

void viderBuffer() {
    int c;
    int count = 0; // Pour compter les caractères lus
    while ((c = getchar()) != '\n' && c != EOF) {
        cout << "Lu: " << static_cast<char>(c) << endl;
        count++;
    }
    cout << count << " caracteres lus et vides du buffer." << endl;
}

unsigned int min(unsigned int a, size_t b) {
    if (a<=b) return a;
    return b;
}
