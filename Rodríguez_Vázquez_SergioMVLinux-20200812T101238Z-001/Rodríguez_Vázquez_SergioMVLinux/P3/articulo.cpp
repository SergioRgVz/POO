#include "articulo.hpp"
#include "fecha.hpp"
#include "cadena.hpp"
#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <locale>


//CONSTRUCTOR
Articulo::Articulo(const Cadena& referencia, const Cadena& titulo, const Fecha &f, double precio, unsigned numeroejemplar = 0): referencia_(referencia), titulo_(titulo), f_publi_(f), precio_(precio), stock_(numeroejemplar)
{}


//OPERADOR SALIDA
std::ostream &operator<<(std::ostream &os, const Articulo &A) noexcept
{
    os << "[" << A.referencia() << "]\"" << A.titulo() << "\", " << A.f_publi().anno() << ". " << A.precio() << " €";

    return os;
}
