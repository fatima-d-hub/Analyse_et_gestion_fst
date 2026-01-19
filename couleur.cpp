#include "couleur.h"


string bleu(const string& s)   { return "\033[34m" + s + "\033[0m"; }
string cyan(const string& s)   { return "\033[36m" + s + "\033[0m"; }
string jaune(const string& s)  { return "\033[33m" + s + "\033[0m"; }
string magenta(const string& s){ return "\033[35m" + s + "\033[0m"; }
