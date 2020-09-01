#include "articulo.hpp"
#include "fecha.hpp"
#include "cadena.hpp"
#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <locale>


//CONSTRUCTOR ARTICULO
Articulo::Articulo(const Autores& autores, Cadena referencia, Cadena titulo, Fecha f, double precio): referencia_(referencia), titulo_(titulo), f_publi_(f), precio_(precio), autores_(autores)
{
    if(autores_.empty())
        throw Articulo::Autores_vacios();
}



//CONSTRUCTOR AUTOR
Autor::Autor(const Cadena &nombre, const Cadena &apellidos, const Cadena &direccion): nombre_(nombre), apellidos_(apellidos), direccion_(direccion)
{}


//Clase ARTICULOALMACENABLE
//CONSTRUCTOR
ArticuloAlmacenable::ArticuloAlmacenable(const Autores &autores, const Cadena &referencia, const Cadena &titulo, const Fecha &fpub, double precio, unsigned stock ): Articulo(autores, referencia, titulo, fpub, precio), stock_(stock){}

//Clase LibroDigital
LibroDigital::LibroDigital(const Autores &autores, const Cadena &referencia, const Cadena &titulo, const Fecha &publicacion, double precio, const Fecha &expiracion): Articulo(autores, referencia, titulo, publicacion, precio), f_expir_(expiracion)
{}
void LibroDigital::impresion_especifica(std::ostream &os) const{
	os << "A la venta hasta el " << f_expir_ << '.';
}



//Clase Libro
Libro::Libro(const Autores& autores, Cadena referencia, Cadena titulo, Fecha publicacion, double precio, unsigned paginas, unsigned stock): ArticuloAlmacenable(autores, referencia, titulo, publicacion, precio, stock), n_pag_(paginas)
{}
void Libro::impresion_especifica(std::ostream &os) const{
	os  << n_pag_ << " págs., " << stock_ << " unidades.";
}

//Clase Cederron
Cederron::Cederron(const Autores &autores, const Cadena &referencia, const Cadena &titulo, const Fecha &publicacion, double precio, unsigned mbs, unsigned stock): ArticuloAlmacenable(autores, referencia, titulo, publicacion, precio, stock), tam_(mbs)
{}
void Cederron::impresion_especifica(std::ostream &os) const{
	os << tam_ << " MB, " << stock_ << " unidades.";
}



void muestraAutores(std::ostream &os, const Articulo::Autores &a){
	bool primera = true;
	for(auto i : a){
		if(primera){
			os << i->apellidos();
			primera = false;
		}
		else
			os << ", " << i->apellidos();
	}
	os << ". ";
}
//OPERADOR SALIDA
std::ostream &operator<<(std::ostream &os, const Articulo &A){
	os << '[' << A.referencia() << "] \"" << A.titulo() << "\", de ";
	muestraAutores(os, A.autores());
	os << A.f_publi().anno() << ". " << std::fixed << std::setprecision(2) << A.precio() << " €\n\t";
	A.impresion_especifica(os);
	return os;
}

