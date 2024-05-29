#ifndef JETONPROGRES_H
#define JETONPROGRES_H

#include <iostream>
#include <string>

class JetonProgres{
private:
    std::string nomJeton;
    std::string effet;
    int pointsVictoire;
public:
    JetonProgres()=default;
    JetonProgres(std::string n, std::string e, int p) : nomJeton(std::move(n)), effet(std::move(e)), pointsVictoire(p) {}
    ~JetonProgres()=default;
    std::string getNomJeton() const {return nomJeton;}
    std::string getEffetJeton() const {return effet;}
    int getPointsVictoire() const {return pointsVictoire;}
};

std::ostream& operator<<(std::ostream& out, const JetonProgres& jeton);

#endif // JETONPROGRES_H
