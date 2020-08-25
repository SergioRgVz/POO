#ifndef TARJETA_HPP
#define TARJETA_HPP


#include "fecha.hpp"
#include "cadena.hpp"
#include "usuario.hpp"
#include "articulo.hpp"


#include <iostream>
#include <set>
#include <cctype>

class  Usuario;     //Predeclaracion, necesaria para arreglar includes circulares

//CLASE NUMERO
class Numero
{
public:

    //CONSTRUCTOR
    Numero(const Cadena &numero);

    //CONSTANTES
    enum Razon
    {
        LONGITUD,
        DIGITOS,
        NO_VALIDO
    };

    //OPERADORES
    friend bool operator<(const Numero &N1, const Numero &N2);
    operator const char *() const noexcept {return numero_.c_str(); }


    //CLASE INCORRECTO
    class Incorrecto
    {
    public:
        Incorrecto(const Numero::Razon r): razon_(r) {}

        Numero::Razon razon() const noexcept {return razon_;}
    private:
        Razon razon_;
    };

    //OBSERVADOR
    const Cadena& num() const noexcept {return numero_;}

    //DESTRUCTOR
    ~Numero();      //HAY QUE IMPLEMENTAR
private:
    Cadena numero_;
    void eliminar_espacio(Cadena &cad);
    void comprobar_digitos(Cadena &cad);
};

class Tarjeta
{
public:

    //CONSTANTES
    enum Tipo
    {
        Otro,
        VISA,
        Mastercard,
        Maestro,
        JCB,
        AmericanExpress
    };

    //CONSTRUCTORES    
    Tarjeta(const Numero &n, Usuario &u,const Fecha &c);
    Tarjeta(const Tarjeta &T) = delete;
    Tarjeta& operator=(const Tarjeta &T) = delete;


    //CLASE CADUCADA
    class Caducada
    {
    public:
        Caducada(Fecha c): caduca_(c){}
        Fecha cuando() const {return caduca_;}

    private:
        Fecha caduca_;
    };

    //CLASE DESACTIVADA
    class Desactivada
    {};

    //CLASE DUPLICADO
     class Num_duplicado
    {
    public:
        Num_duplicado(const Numero&);
        const Numero& que() const;
    private:
        Numero numer_;
    };

    //FUNCIONES
    bool &activa(bool a = true) noexcept;
    void anula_titular();
    Tipo esTipo();

    friend std::ostream& operator<<(std::ostream& os, const Tarjeta& T);

    //OBSERVADORES
    const Tarjeta::Tipo tipo() const noexcept{return tipo_;}
    const Numero& numero() const noexcept{return numero_;}
    const Fecha& caducidad() const noexcept{return caducidad_;}
    Usuario *titular() const noexcept{return titular_;}
    const bool activa() const noexcept {return activa_;}

    //DESTRUCTOR
    ~Tarjeta();

private:
    Tipo tipo_;
    Numero numero_;
    Usuario* const titular_;
    Fecha caducidad_;
    bool activa_;
    static Numero numeros_; //esto es de BJ
};


std::ostream &operator<<(std::ostream &os, const Tarjeta &T);
std::ostream &operator<<(std::ostream &os, const Tarjeta::Tipo &T);

bool operator<(const Numero &N1, const Numero &N2);
bool operator<(const Tarjeta &T1, const Tarjeta &T2);
bool operator>(const Tarjeta &T1, const Tarjeta &T2); //Hay que implementarla
#endif //TARJETA_HPP
