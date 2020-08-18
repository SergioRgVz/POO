#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "cadena.hpp"
#include "fecha.hpp"
#include <iostream>

class Articulo
{
public:
    Articulo(const Cadena referencia, const Cadena titulo, const Fecha &f, double precio, unsigned numeroejemplar);

    Cadena referencia() const noexcept {return referencia_;};
    Cadena titulo() const noexcept {return titulo_;};
    Fecha f_pub() const noexcept {return publicacion_;};
    double precio() const noexcept {return precio_;};
    double &precio() noexcept {return precio_;};
    unsigned ejemplares() const noexcept {return ejemplares_;};
    unsigned &ejemplares() noexcept {return ejemplares;};

private:
    Cadena referencia_;
    Cadena titulo_;
    Fecha publicacion_;
    double precio_;
    unsigned ejemplares_;
};

std::ostream &operator<<(std::ostream &os, const Articulo &A);

#endif //ARTICULO_HPP