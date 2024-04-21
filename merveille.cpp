#include "merveille.h"

ostream& operator<<(ostream& f, const Merveille& m) {
    f << "Merveille : " << m.getNom();
    return f;
}
