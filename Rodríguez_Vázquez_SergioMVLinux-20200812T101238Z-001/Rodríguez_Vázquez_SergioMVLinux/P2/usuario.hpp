#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <unistd.h>
#include <iostream>
class Numero;
class Tarjeta;
class Clave
{
public:
    enum Razon
    {
        CORTA,
        ERROR_CRYPT
    };
    
    Clave(const char *c);

    Cadena clave() const noexcept {return password_;};

    class Incorrecta
    {
    public:
        Incorrecta(Razon r): razon_(r) {}
        Razon razon() const noexcept {return razon_;}
    private:
        Razon razon_;
    };

    bool verifica(const char *c) const;
private:
    Cadena password_;
};

class Usuario
{
public:
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    typedef std::unordered_map<Articulo *, unsigned int> Articulos;
    typedef std::unordered_set<Cadena> Usuarios;

    Usuario(const Cadena &id, const Cadena &nombre, const Cadena &apell, const Cadena &direccion, const Clave &clave);
    Usuario(const Usuario &U) = delete;

    Usuario &operator=(const Usuario &U) = delete;

    const Cadena &id() const noexcept {return identificador_;}
    const Cadena &nombre() const noexcept {return nombre_;}
    const Cadena &apellidos() const noexcept {return apellidos_;}
    const Cadena &direccion() const noexcept {return direccion_;}
    const Tarjetas& tarjetas() const noexcept {return tarjetas_;} //TODO:, comprobar porque falla de la forma que estaba hecha la insercion de flujo
    const Articulos & compra() const noexcept {return articulos_;}

    unsigned n_articulos() const;

    void es_titular_de(Tarjeta &T);
    void no_es_titular_de(Tarjeta &T);
    void compra(Articulo &A, unsigned cantidad = 1);

    ~Usuario();

    friend std::ostream &operator<<(std::ostream &os, const Usuario &U);

    class Id_duplicado
    {
    public:
        Id_duplicado(Cadena id):id_(id){}
        Cadena idd() const noexcept {return id_;}

    private:
        Cadena id_;
    };

private:
    Cadena identificador_;
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
    Clave contrasena_;
    Tarjetas tarjetas_;
    Articulos articulos_;
    static Usuarios usuarios_;

};

void mostrar_carro(std::ostream &os, const Usuario &U);

#endif //USUARIO_HPP