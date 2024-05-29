#include "jetonProgres.h"

std::ostream& operator<<(std::ostream& out, const JetonProgres& jeton) {
    out << "Nom: " << jeton.getNomJeton();
    return out;
}
