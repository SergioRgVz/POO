#ifndef FECHA_HPP
#define FECHA_HPP
#include <ctime>
#include <cstdio>
#include <iostream>
#include <cstring>

class Fecha
{
public:

    //Constantes estaticas de la clase
    static const int AnnoMinimo = 1902;
    static const int AnnoMaximo = 2037;


    //Constructores de la clase Fecha
    explicit Fecha(int dia=0, int mes=0, int anno=0);
    Fecha(const char *fecha);
    Fecha (const Fecha &F) = default;
    const char *cadena() const; //Conversor a const char *

    //Observadores de la clase
    int dia() const noexcept;
    int mes() const noexcept;
    int anno() const noexcept;


    //Clase anidada Invalida que es el tipo de las excepciones
    class Invalida
    {
    public:
        Invalida(const char *cadena);
        const char *por_que() const;
    private:
        char *info;
    };


//OPERADORES DE LA CLASE ///////
    //Operadores de asignacion de suma y resta
    Fecha &operator+=(int dia);
    Fecha &operator-=(int dia);
    //Predecremento y postidecremento
    Fecha& operator--();
    Fecha operator--(int);
    //Preincremento y postincremento
    Fecha& operator ++();
    Fecha operator++(int);
    //Operador suma de una Fecha con un entero
    Fecha operator +(int dia) const;
    //Operador resta de una Fecha con un entero
    Fecha operator -(int dia) const;


    private:
        int dia_, mes_, year_;
        void comprobar();
};


//OPERADORES LOGICOS 

    bool operator==(const Fecha &fecha1, const Fecha &fecha2);
    bool operator<(const Fecha &fecha1, const Fecha &fecha2);
    bool operator>(const Fecha &fecha1, const Fecha &fecha2);
    bool operator!=(const Fecha &fecha1, const Fecha &fecha2);
    bool operator<=(const Fecha &fecha1, const Fecha &fecha2);
    bool operator>=(const Fecha &fecha1, const Fecha &fecha2);

    inline bool operator==(const Fecha &fecha1, const Fecha &fecha2)
    {
        return (fecha1.dia() == fecha2.dia() && fecha1.mes() == fecha2.mes() && fecha1.anno() == fecha2.anno());
    }

//ENTRADA-SALIDA//
std::ostream &operator<<(std::ostream &os, const Fecha &F);
std::istream &operator>>(std::istream &is, Fecha &F);
#endif //FECHA_HPP