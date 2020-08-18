#include "articulo.hpp"

Articulo::Articulo(const Cadena referencia, const Cadena titulo, const Fecha &f, double precio, unsigned numeroejemplar = 0): referencia_(referencia), titulo_(titulo), publicacion_(f), precio_(precio), ejemplares_(numeroejemplar)
{}

std::ostream &operator<<(std::ostream &os, const Articulo &A)
{
    os << "[" << A.referencia() << "] \"" << A.titulo() << "\", " << A.f_pub().anno() << ". " << A.precio() << " €";

    return os;
}
