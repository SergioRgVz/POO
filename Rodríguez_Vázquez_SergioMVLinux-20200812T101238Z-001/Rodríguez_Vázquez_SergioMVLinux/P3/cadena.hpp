#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <functional>
#include <iostream>

class Cadena
{
    public:
        //CONSTRUCTORES
        explicit Cadena(unsigned n = 0, char relleno = ' ');
        Cadena(const Cadena& copia);
        Cadena(const char* caracteres);
        Cadena(Cadena &&C);         //Constructor de movimiento


        Cadena &operator=(const Cadena& copia) noexcept;
        Cadena &operator=(const char *cadena) noexcept;
        Cadena &operator=(Cadena &&C) noexcept;
        Cadena &operator+=( const Cadena& copia) noexcept;

        friend Cadena operator+(const Cadena& cad1, const Cadena& cad2);

        char& operator[](unsigned i);
        char operator[](unsigned i)const;



        const char *c_str() const noexcept;
        char at(unsigned i) const;
        char& at(unsigned i) ;

        Cadena substr(unsigned i, unsigned tam) const;

        unsigned length() const noexcept {return tam_;}

        typedef char *iterator;
        typedef const char *const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        iterator begin() {return s_;}
        const_iterator begin() const{return cbegin();} //return s_
        const iterator cbegin() const{return s_;}
        reverse_iterator rbegin() {return reverse_iterator(end());}
        const_reverse_iterator rbegin() const {return crbegin();}
        const_reverse_iterator crbegin() const {return const_reverse_iterator(end());}

        iterator end() {return s_ + tam_;}
        const_iterator end() const {return cend();} //return s_ + tam_
        const_iterator cend() const {return s_ + tam_;}
        reverse_iterator rend() {return reverse_iterator(begin());}
        const_reverse_iterator rend() const {return crend();}
        const_reverse_iterator crend() const {return const_reverse_iterator(begin());}        


        //DESTRUCTOR
        ~Cadena();

        private:
            
            char *s_;
            unsigned tam_;
};

bool operator==(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator<(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator>(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator!=(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator<=(const Cadena& cad1, const Cadena& cad2) noexcept;
bool operator>=(const Cadena& cad1, const Cadena& cad2) noexcept;

std::ostream &operator<<(std::ostream &os, const Cadena &C);
std::istream &operator>>(std::istream &is, Cadena &C);

namespace std
{
    template <>
    struct hash<Cadena>
    {
        size_t operator()(const Cadena &cad) const
        {
            return hash<string>{}(cad.c_str());
        }
    };
}   //namespace std

#endif //CADENA_HPP_