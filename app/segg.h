#pragma once

struct Segg{
    enum Szag : char{
        Budos,
        Illatos
    };
    Szag Szagol() const { return szag; }
    void Befosik() { szag = Budos; }
private:
    Szag szag = Illatos;
};
