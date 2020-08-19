#include "tarjeta.hpp"
#include <cstring>
#include <algorithm>
#include <iomanip>


bool luhn(const Cadena& numero)
{
    size_t n = numero.length();
    size_t suma = 0;
    bool alt = false;
    for(int i = n - 1; i > - 1; --i)
    {
        n = numero[size_t(i)] - '0';
        if(alt){
            n *= 2;
            if(n > 9)
                n = (n % 10) + 1;
        }
        alt = !alt;
        suma += n;
    }
    return !(suma % 10);
}

Numero::Numero(const Cadena &numero)
{
    Cadena aux = numero; 

    if(aux.length() == 0)
        throw Incorrecto(Razon::LONGITUD);
    
    eliminar_espacio(cad);
    comprobar_digitos(cad);

    if(cad.length() < 13 || cad.length() > 19)
        throw Incorrecto(Razon::LONGITUD);
    if(!luhn(cad))
        throw Incorrecto(Razon::NO_VALIDO);
    
    num_ = cad;
}

void Numero::eliminar_espacio(Cadena &cad)
{
    Cadena aux(cad.length());
    size_t j = 0;
    Cadena::iterator i = cad.begin();

    while(i != cad.end())
    {
        if(!isspace(*i))
            aux[j++] = *i;
        
        i++;
    }
    cad = aux.substr(0, j);
}

void comprobar_digitos(Cadena &cad)
{
    Cadena::const_iterator i = cad.begin();
    while(i != cad.end())
    {
        if(!isdigit(*i))
            throw Incorrecto(Razon::DIGITOS);
        
        i++;
    }
}

bool operator<(const Numero &N1, const Numero &N2)
{
    return N1.numero_ < N2.numero_;
}
Tarjeta::Tarjeta(Numero n, Usuario &u, Fecha c): numero_(n), titular_(&u), caducidad_(c), activa_(true)
{
    if(Fecha() > c)
        throw Tarjeta::Caducada(c);

    Cadena::iterator i = n.begin();

    
    char primer_numero = numero_[*i];

    switch(primer_numero)
    {
        case '3':
            i++;
            char segundo_numero = numero_[*i];
            if(segundo_numero == '4' || segundo_numero == '7') tipo_ = Tarjeta::AmericanExpress;
            else{tipo_ = Tarjeta::JCB;}
            break;

        case '4':
            tipo_ = Tarjeta::VISA;
            break;

        case '5':
            tipo_ = Tarjeta::Mastercard;
            break;

        case '6':
            tipo_ = Tarjeta::Maestro;
            break;

        default:
            tipo_ = Tarjeta::Otro;
            break;

    }
    u->es_titular_de(*this);
}

bool Tarjeta::activa(bool a) noexcept
{
    activa_ = a;


    return activa_;
}

void Tarjeta::anula_titular()
{
    titular_ = nullptr;
    activa_ = false;
}

Tarjeta::~Tarjeta()
{
    if(Usuario *u = const_cast<Usuario *>(titular_))
    u->no_es_titular_de(*this);
}


std::ostream &operator<<(std::ostream &os, const Tarjeta::Tipo &tipo)
{
    switch(tipo)
    {
        case Tarjeta::Tipo::Visa: os << "VISA"; break;
        case Tarjeta::Tipo::Mastercard: os << "Mastercard"; break;
        case Tarjeta::Tipo::Maestro: os << "Maestro"; break;
        case Tarjeta::Tipo::JCB: os << "JCB"; break;
        case Tarjeta::Tipo::AmericanExpress: os << "AmericanExpress"; break;

    };

    return os;
}

std::ostream &operator<<(std::ostream &os, const Tarjeta::Tipo  &T)
{
    os
    << T.tipo() << std.endl
    << T.numero() << std.endl
    << toupper(T.titular()->nombre()) << " " << toupper(T.titular()->apellidos()) << std::endl
    << "Caduca: " << std::setfill('0') << std::setw(2) << T.caducidad().mes() << '/' << std::setw(2) << (T.caducidad().anno() % 100);

    return os;
}
