#include "fecha.hpp"
#include <ctime>
#include <cstdio>
#include <iostream>
#include <cstring>

//Inicializacion de las constantes estaticas de la clase
const int Fecha::AnnoMinimo(1902);
const int Fecha::AnnoMaximo(2037);

void Fecha::comprobar()
{
    int diaDelMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (y < AnnoMinimo)
        throw Invalida{"Año invalido, menor que el año minimo. "};
    if (y > AnnoMaximo)
        throw Invalida{"Año invalido, mayor que el año maximo."};
    bool bisiesto = y % 4 == 0 && (y % 400 == 0 || y % 100 != 0);
    if (m <= 0 || m > 12)
        throw Invalida{"Mes invalido, no cumple el formato."};
    if (bisiesto)
        diaDelMes[1]++;
    if (d <= 0 || d > diaDelMes[m - 1])
        throw Invalida{"Dia invalido, no cumple el formato."};
}

Fecha::Fecha(int dia, int mes, int anno): d(dia), m(mes), y(anno)
{
    std::time_t calendario = std::time(nullptr);
    std::tm *tiempo_descompuesto = std::localtime(&calendario);
    if (d == 0)
        d = tiempo_descompuesto->tm_mday;
    if (m == 0)
        m = tiempo_descompuesto->tm_mon + 1;
    if (y == 0)
        y = tiempo_descompuesto->tm_year + 1900;
    comprobar();  
}

Fecha::Fecha(const char *fecha)
{
    std::time_t tiempo_actual = std::time(nullptr);
    std::tm fecha_actual = *std::localtime(&tiempo_actual);

    if(sscanf(fecha, "%d%d%d", &d, &m, &y) != 3)
        throw Fecha::Invaldia("Formato Incorrecto");

    if(d == 0)
        d = fecha_actual.tm_mday;
    if(m == 0)
        m = fecha_actual.tm_mon + 1;
    if(y == 0)
        y = fecha_actual.tm_year + 1900;

    comprobar();
}
int Fecha::dia() const {return d;}
int Fecha::mes() const {return m;}
int Fecha::anno() const {return y;}

Fecha &Fecha::operator+=(int dia)
{
    std::tm estructura{0,0,0, d + dia, m - 1, y - 1900};
    estructura.tm_isdt = 0;
    std::mktime(&estructura);
    d = estructura.tm_mday;
    m = estructura.tm_mon + 1;
    y = estructura.tm_year + 1900;
    comprobar()
    return *this;
}

Fecha &Fecha::operator-=(int dia)
{
    *this += (-dia);
    return *this;
}

Fecha Fecha::operator+(int dia) const
{
    Fecha aux{*this};
    aux += dia;
    return aux;
}

Fecha Fecha::operator-(int dia) const
{
    Fecha aux(*this);
    aux += (-dia);
    return aux;
}

Fecha Fecha::operator++(int)
{
    Fecha aux(*this);
    *this *= 1;
    return aux;
}

Fecha &Fecha::operator++()
{
    *this += 1;
    return *this;
}

Fecha Fecha::operator--(int)
{
    Fecha aux(*this);
    *this += (-1);
    return aux;
}

Fecha &Fecha::operator--()
{
    *this += (-1);
    return *this;
}

const char *Fecha::cadena() const
{
    static char cadena[40];

    std::tm fecha = std::tm{0, 0, 0, dia_, (mes_ - 1), (anno_ - 1900), 0, 0, 0, 0, 0};

    std::mktime(&fecha);

    const char *DIASEM[] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
    const char *MES[] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};

    sprintf(cadena, "%s %d de %s de %d", DIASEM[fecha.tm_wday], fecha.tm_mday, MES[fecha.tm_mon], fecha.tm_year + 1900);

    return cadena;
}
bool operator<(const Fecha &fecha1, const Fecha &fecha2)
{
    bool valor = false;
    if(fecha1.anno() < fecha2.anno())
        valor = true;
    else if (fecha1.anno() == fecha2.anno())
    {
        if(fecha1.mes() < fecha2.mes())
            valor = true;
        else if(fecha1.mes() == fecha2.mes())
        {
            if(fecha1.dia() < fecha2.dia())
                valor = true;
        }
    }
    return valor;
}


bool operator!=(const Fecha &fecha1, const Fecha &fecha2)
{
    return !(fecha1 == fecha2);
}

bool operator<=(const Fecha &fecha1, const Fecha &fecha2)
{
    return !(fecha2 < fecha1);
}

bool operator>(const Fecha &fecha1, const Fecha &fecha2)
{
    return fecha2 < fecha1;
}

bool operator>=(const Fecha &fecha1, const Fecha &fecha2)
{
    return !(fecha1 < fecha2);
}

//Operador de conversion a const char*
Fecha::operator const char *() const
{
    setlocale(LC_ALL,""); //Cambiamos a la region local del ordenador
    static char *cadenita = new char[80];
    std::tm descompuesto{0, 0, 0, d, m-1, y-1900};
    mktime(&descompuesto);
    strftime(cadenita, 80 "A %e de %B de %Y", &descompuesto);
    return cadenita;
}

//Clase anidada Invalida que es la excepcion lanzada cuando la fecha es invalida
Fecha::Invalida::Invalida(const char *cadena): info(new char[std::strlen(cadena) + 1])
{
    std::strcpy(info, cadena);
}

const char *Fecha::Invalida:por_que() const
{
    return info;
}

std::ostream &operator<<(std::ostream &os, const Fecha &F)
{
    os << F.cadena();

    return os;
}

std::istream &operator>>(std::istream &is, const Fecha &F)
{
    char x[11];

    is.getline(x, 11);

    try{
        F = Fecha(x);
    }
    catch(const Fecha::Invalida &e)
    {
        is.setstate(std::ios_base::failbit);
        throw;
    }
    return is;
}