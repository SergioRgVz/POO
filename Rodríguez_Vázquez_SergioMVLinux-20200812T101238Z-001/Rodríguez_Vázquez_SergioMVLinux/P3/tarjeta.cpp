#include "tarjeta.hpp"
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <string.h>
#include <iomanip>
#include <cctype>
bool luhn(const Cadena& numero);
/*
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
}*/
///////////////////////////////////////77
//CLASE NUMERO///
//-----------------------
///////////////////////
//CONSTRUCTORES
Numero::Numero(const Cadena &numero)
{
    /*
    Cadena aux = numero; 

    if(aux.length() == 0)
        throw Incorrecto(Razon::LONGITUD);
    
    eliminar_espacio(aux);
    comprobar_digitos(aux);

    if(aux.length() < 13 || aux.length() > 19)
        throw Incorrecto(Razon::LONGITUD);
    if(!luhn(aux))
        throw Incorrecto(Razon::NO_VALIDO);
    
    numero_ = aux;
    */

   char keys[] = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    size_t ii = strcspn(numero.c_str(), keys);
    if(ii < numero.length()) throw Incorrecto(Razon::DIGITOS);
    char* pch;
    char* aux = new char[30];
    pch = strpbrk(const_cast<char*>(numero.c_str()),"12348567890");
    int i = 0;
    while(pch != NULL)
    {
        aux[i++] = *pch;
        pch = strpbrk(pch + 1, "1234567890");
    }
    aux[i] = '\0';
    Cadena n(aux);
    delete[] aux;

    if(n.length() > 19 || n.length() < 13)
    {
        throw Incorrecto(Razon::LONGITUD);
    }
    if(!luhn(n))
        throw Incorrecto(Razon::NO_VALIDO);

    numero_ = n;

}

Numero::~Numero(){} //Destructor


//OPERADORES
bool operator<(const Numero &N1, const Numero &N2)
{
    return strcmp(N1, N2) < 0;
}
//operator const char *() const noexcept {return numero_.c_str(); }


//INCORRECTO
//DEFINIDOS DENTRO DE LA CLASE


//FUNCIONES
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

void Numero::comprobar_digitos(Cadena &cad)
{
    Cadena::const_iterator i = cad.begin();
    while(i != cad.end())
    {
        if(!isdigit(*i))
            throw Incorrecto(Razon::DIGITOS);
        
        i++;
    }
}
///////////////////////////////////7
//CLASE TARJETA///////////////////////////
//-----------------------------------
//CONSTRUCTORES
/*Tarjeta::Tarjeta(const Numero &n, Usuario &u, const Fecha &c): tipo_(esTipo()), numero_(n), titular_(&u), caducidad_(c), activa_(1)
{
    u.es_titular_de(*this);
}*/

Tarjeta::Tarjeta(const Numero &n, Usuario &u,const Fecha &c): numero_(n), titular_(&u), caducidad_(c), activa_(true)
{
    Cadena aux(n);
    if(Fecha() > c)
        throw Tarjeta::Caducada(c);

    //Cadena::iterator i = aux.begin();

    
    //unsigned char primer_numero = *i;

    unsigned char primer_numero = aux[0];

    switch(primer_numero)
    {
        case '3':{
            //i++;
            //unsigned char segundo_numero = *i;
            unsigned char segundo_numero = aux[1];
            if(segundo_numero == '4' || segundo_numero == '7') tipo_ = Tarjeta::AmericanExpress;
            else{tipo_ = Tarjeta::JCB;}
            break;
        }

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
    u.es_titular_de(*this);
}


//OPERADORES
std::ostream &operator<<(std::ostream &os, const Tarjeta::Tipo &tipo)
{
    switch(tipo)
    {
        case Tarjeta::Tipo::VISA: os << "VISA"; break;
        case Tarjeta::Tipo::Mastercard: os << "Mastercard"; break;
        case Tarjeta::Tipo::Maestro: os << "Maestro"; break;
        case Tarjeta::Tipo::JCB: os << "JCB"; break;
        case Tarjeta::Tipo::AmericanExpress: os << "AmericanExpress"; break;
        case Tarjeta::Tipo::Otro: os << "Otro"; break;

    };

    return os;
}

std::ostream &operator<<(std::ostream &os, const Tarjeta  &T)
{
    os
    << T.tipo() << std::endl << T.numero() << std::endl;

    Cadena aux = T.titular()->nombre();
    int i = 0;
    while(aux[i] != '\0')
    {
        if(islower(aux[i])) aux[i] = toupper(aux[i]);
        i++;
    } 
    os << aux << " ";

    i = 0;

    aux = T.titular()->apellidos();
    while ((aux[i]= '\0'))
    {
        if(islower(aux[i])) aux[i] = toupper(aux[i]);
        i++;        
    }
    
    os << aux << std::endl;
   
    os
    << "Caduca: " << std::setfill('0') << std::setw(2) << T.caducidad().mes() << '/' << std::setw(2) << (T.caducidad().anno() % 100) << std::endl;

    return os;
}

bool operator<(const Tarjeta& T1, const Tarjeta& T2){return T1.numero() < T2.numero();}

//OBSERVADORES
bool& Tarjeta::activa(bool a) noexcept
{
    activa_ = a;


    return activa_;
}

//NUM DUPLICADO
Tarjeta::Num_duplicado::Num_duplicado(const Numero &n): numer_(n){}

const Numero& Tarjeta::Num_duplicado::que() const{return numer_;}

//FUNCIONES
void Tarjeta::anula_titular()
{
        activa_ = false;
    const_cast<Usuario*&>(titular_) = nullptr;

}


//DESTRUCTOR
Tarjeta::~Tarjeta()
{
    if(titular_) titular_->no_es_titular_de(*this);
}



Tarjeta::Tipo Tarjeta::esTipo()
{
    int a = atoi(numero_.num().substr(0, 2).c_str());
    switch (a/10)
    {
    case 3:
        if(a==34 || a == 37) return Tarjeta::AmericanExpress;
        else return Tarjeta::JCB;
        break;
    case 4:
        return Tarjeta::VISA;
        break;
    case 5:
        return Tarjeta::Mastercard;
        break;
    case 6:
        return Tarjeta::Maestro;
        break;
    default:
        return Tarjeta::Otro;
        break;
    }
}