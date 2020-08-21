#include "fecha.hpp"

void Fecha::comprobar()
{
    int diaDelMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year_ < AnnoMinimo)
        throw Invalida{"Año invalido, menor que el año minimo. "};
    if (year_ > AnnoMaximo)
        throw Invalida{"Año invalido, mayor que el año maximo."};
    bool bisiesto = year_ % 4 == 0 && (year_ % 400 == 0 || year_ % 100 != 0);
    if (mes_ <= 0 || mes_ > 12)
        throw Invalida{"Mes invalido, no cumple el formato."};
    if (bisiesto)
        diaDelMes[1]++;
    if (dia_ <= 0 || dia_ > diaDelMes[mes_ - 1])
        throw Invalida{"Dia invalido, no cumple el formato."};
}

Fecha::Fecha(int dia, int mes, int anno): dia_(dia), mes_(mes), year_(anno)
{
    std::time_t calendario = std::time(nullptr);
    std::tm *tiempo_descompuesto = std::localtime(&calendario);
    if (dia_ == 0)
        dia_ = tiempo_descompuesto->tm_mday;
    if (mes_ == 0)
        mes_ = tiempo_descompuesto->tm_mon + 1;
    if (year_ == 0)
        year_ = tiempo_descompuesto->tm_year + 1900;
    comprobar();  
}

Fecha::Fecha(const char *fecha)
{
    std::time_t tiempo_actual = std::time(0);
    std::tm *fecha_actual = std::localtime(&tiempo_actual);

    if(sscanf(fecha, "%d/%d/%d", &dia_, &mes_, &year_)<3 ){
        throw Fecha::Invalida("Formato Incorrecto");
    }
    if(dia_ == 0)
        dia_ = fecha_actual->tm_mday;
    if(mes_ == 0)
        mes_ = fecha_actual->tm_mon + 1;
    if(year_ == 0)
        year_ = fecha_actual->tm_year + 1900;

    comprobar();
}
int Fecha::dia() const noexcept{return dia_;}
int Fecha::mes() const noexcept{return mes_;}
int Fecha::anno() const noexcept{return year_;}

Fecha &Fecha::operator+=(int dia)
{
    std::tm estructura{0,0,0, dia_ + dia, mes_ - 1, year_ - 1900};
    estructura.tm_isdst = 0;
    std::mktime(&estructura);
    dia_ = estructura.tm_mday;
    mes_ = estructura.tm_mon + 1;
    year_ = estructura.tm_year + 1900;
    comprobar();
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
    *this += 1;
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

const char* Fecha::cadena() const
{
    /*
    static char cadena[40];

    std::tm fecha = std::tm{0, 0, 0, dia_, (mes_ - 1), (year_ - 1900), 0, 0, 0, 0, 0};

    std::mktime(&fecha);

    const char *DIASEM[] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
    const char *MES[] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};

    sprintf(cadena, "%s %d de %s de %d", DIASEM[fecha.tm_wday], fecha.tm_mday, MES[fecha.tm_mon], fecha.tm_year + 1900);

    return cadena;
    */

   static char* buffer = new char[40];
   tm f = {};
   f.tm_mday = dia_;
   f.tm_mon = mes_ - 1;
   f.tm_year = year_ - 1900;

   mktime(&f);
   strftime(buffer, 40, "%A %d de %B de %Y", &f);

   return buffer;
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
/*
//Operador de conversion a const char*
Fecha::operator const char *() const
{
    /*setlocale(LC_ALL,""); //Cambiamos a la region local del ordenador
    static char *cadenita = new char[80];
    std::tm descompuesto{0, 0, 0, dia_, mes_ - 1, year_ - 1900};
    mktime(&descompuesto);
    strftime(cadenita, 80,  "A %e de %B de %Y", &descompuesto);
    return cadenita;
    
    char *aux=new char[40];
    tm f= {};
    f.tm_mday=dia_;
    f.tm_mon =mes_ -1;
    f.tm_year=year_ -1900;
    mktime(&f);
    strftime(aux, 40, "%A, %d de %B de %Y", &f);
    return aux;   
}
*/
//Clase anidada Invalida que es la excepcion lanzada cuando la fecha es invalida
Fecha::Invalida::Invalida(const char *cadena): info(new char[std::strlen(cadena) + 1])
{
    std::strcpy(info, cadena);
}

const char *Fecha::Invalida::por_que() const
{
    return info;
}

std::ostream &operator<<(std::ostream &os, const Fecha &F)
{
    os << F.cadena();

    return os;
}

std::istream &operator>>(std::istream &is, Fecha &F)
{
   char fecha[11];

    is.getline(fecha, 11);

    try{
        F = Fecha(fecha);
    }
    catch(const Fecha::Invalida &e)
    {
        is.setstate(std::ios_base::failbit);
        throw;
    }
    return is;
/*
    setlocale(LC_ALL, "");
    char* s = new char[11];
    is>>s;
    Fecha f2(s);
    f=f2;
    delete[] s;
    is.ignore();
    return is;*/
}