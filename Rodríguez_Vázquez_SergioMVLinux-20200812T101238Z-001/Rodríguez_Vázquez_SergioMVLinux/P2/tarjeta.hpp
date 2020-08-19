#ifndef TARJETA_HPP
#define TARJETA_HPP

#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"
#include <iostream>
#include <set>
#include <cctype>

class Numero
{
public:
    Numero(Cadena &numero);

    enum Razon
    {
        LONGITUD,
        DIGITOS,
        NO_VALIDO
    };

    class Incorrecto
    {
    public:
        Incorrecto(Razon r): razon_(r) {}

        const Razon &razon() const noexcept {return razon_;}
    private:
        Razon razon_;
    };

    friend bool operator<(const Numero &N1, const Numero &N2);

    operator const char *() const noexcept {return numero_.c_str(); }

    const Cadena &num() const noexcept {return numero_;}

private:
    Cadena numero_;
    void eliminar_espacio(Cadena &cad);
    void comprobar_digitos(Cadena &cad);
};

class Tarjeta
{
public:
    enum Tipo
    {
        Otro,
        VISA,
        Mastercard,
        Maestro,
        JCB,
        AmericanExpress
    };
    
    Tarjeta(Numero n, Usuario &u, Fecha c);
    Tarjeta(const Tarjeta &T) = delete;
    Tarjeta operator=(const Tarjeta &T) = delete;

    class Caducada
    {
    public:
        Caducada(Fecha c): caduca_(c){}
        Fecha cuando() const {return caduca_;}

    private:
        Fecha caduca_;
    }
    class Desactivada
    {};

    bool activa(bool a = true) noexcept;
    void anula_titular();


    //Metodos observadores
    Tipo tipo() const noexcept{return tipo_;}
    Numero numero() const noexcept{return numero_;}
    Fecha caducidad() const noexcept{return caducidad_;}
    const Usuario *titular() const noexcept{return titular_;}
    bool activa() const noexcept {return activa_;}

    ~Tarjeta();
private:
    Tipo tipo_;
    Numero numero_;
    const Usuario *titular_;
    Fecha caducidad_;
    bool activa_;
    static Numeros numeros_;
};

std::ostream &operator<<(std::ostream &os, const Tarjeta &T);
std::ostream &operator<<(std::ostream &os, const Tarjeta::Tipo &T);

bool operator<(const Tarjeta &T1, const Tarjeta &T2);

#endif //TARJETA_HPP
