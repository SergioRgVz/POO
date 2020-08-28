#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "cadena.hpp"
#include "fecha.hpp"
//#include <iostream>

class Articulo
{
public:
    //CONSTRUCTOR
    Articulo(const Cadena& referencia, const Cadena& titulo, const Fecha &f, double precio, unsigned numeroejemplar);

    //OBSERVADORES
    Cadena referencia() const noexcept {return referencia_;};
    Cadena titulo() const noexcept {return titulo_;};
    Fecha f_publi() const noexcept {return f_publi_;};
    double precio() const noexcept {return precio_;};
    double &precio() noexcept {return precio_;};
    unsigned stock() const noexcept {return stock_;};
    unsigned &stock() noexcept {return stock_;};

private:
    Cadena referencia_;
    Cadena titulo_;
    Fecha f_publi_;
    double precio_;
    unsigned stock_;
};


//OPERADOR SALIDA
std::ostream &operator<<(std::ostream &os, const Articulo &A) noexcept;

#endif //ARTICULO_HPP