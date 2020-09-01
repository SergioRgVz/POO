#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "cadena.hpp"
#include "fecha.hpp"
#include <set>
//#include <iostream>
class Autor
{
public:
    Autor(const Cadena &nombre, const Cadena &apellidos, const Cadena &direccion);
    Cadena nombre() const noexcept{return nombre_;}
    Cadena apellidos() const noexcept{return apellidos_;}
    Cadena direccion() const noexcept{return direccion_;}
private:
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
};
// class Autor;

class Articulo
{
public:
    typedef std::set<Autor*> Autores;
    class Autores_vacios
    {};


    //CONSTRUCTOR
    Articulo(const Autores& autores,  Cadena referencia,  Cadena titulo,  Fecha f, double precio);

    //OBSERVADORES
    Cadena referencia() const noexcept {return referencia_;};
    Cadena titulo() const noexcept {return titulo_;};
    Fecha f_publi() const noexcept {return f_publi_;};
    double precio() const noexcept {return precio_;};
    double &precio() noexcept {return precio_;};  //Metodo modificador
    //unsigned stock() const noexcept {return stock_;};
    //unsigned &stock() noexcept {return stock_;};
    virtual void impresion_especifica(std::ostream &os) const = 0; //CLASE
    Autores autores() const{return autores_;}

    //Destructor necesario para clase abstracta
    virtual ~Articulo() = default;

protected:
    Cadena referencia_;     //Codigo de referencia del articulo
    Cadena titulo_;         //Titulo del articulo
    Fecha f_publi_;         //Fecha de publicacion del articulo
    double precio_;         //Precio del articulo
    const Autores autores_; //Autores del articulo
    // const std::set<Autor*> autores_;
    //unsigned stock_;
};

//Clase ArticuloAlmacenable
class ArticuloAlmacenable : public Articulo 
{
public:
    ArticuloAlmacenable(const Autores &autores, const Cadena &referencia, const Cadena &titulo, const Fecha &fpub, double precio, unsigned stock = 0);
    unsigned stock() const noexcept{return stock_;}
    unsigned &stock() noexcept{return stock_;}
    virtual void impresion_especifica(std::ostream &os) const = 0;
    virtual ~ArticuloAlmacenable() = default;
protected:
    unsigned stock_;
};

//Clase LibroDigital
class LibroDigital:public Articulo
{
public:
    LibroDigital(const Autores&, const Cadena &, const Cadena &, const Fecha &, double, const Fecha &);
    Fecha f_expir() const noexcept{return f_expir_;}
    void impresion_especifica(std::ostream &os) const;
private:
    const Fecha f_expir_;
};


//Clase Libro
class Libro: public ArticuloAlmacenable
{
public:
    Libro(const Autores& autores,Cadena, Cadena, Fecha , double, unsigned, unsigned = 0);
    unsigned n_pag() const noexcept{return n_pag_;}
    void impresion_especifica(std::ostream &os) const;
private:
    const unsigned n_pag_;
};

//Clase Cederron
class Cederron:public ArticuloAlmacenable
{
public:
    Cederron(const Autores &, const Cadena &, const Cadena &, const Fecha &, double, unsigned, unsigned = 0);
    unsigned tam() const noexcept{return tam_;}
    void impresion_especifica(std::ostream &os) const;
private:
    const unsigned tam_;
};

//OPERADOR SALIDA
std::ostream &operator<<(std::ostream &os, const Articulo &A);

#endif //ARTICULO_HPP