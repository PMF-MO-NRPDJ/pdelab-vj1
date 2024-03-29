#ifndef EXACT_HH
#define EXACT_HH

#include <dune/common/fvector.hh>

/** Metoda artificijelnog rješenja:  Koeficijenti za zadaću :
 *
 *   - div( grad u) + a(x) u = f(x)   u \Omega
 *                   u = g(x)   na \Gamma_D\subseteq\partial\Omega
 *        - grad u . n = j(x)   na \Gamma_N = \partial\Omega\setminus\Gamma_D
 *
 * sa konformnim konačnim elementima svih tipova u svim dimenzijama
 *
 */


// Egzaktno rješenje je dano kao jednostavna polinomijalna funkcija.
// Ovisi o 3 parametra i dana je 1D, 2D i 3D. Na ovom rješenju testiramo
// (validiramo) kod - metoda artificijelnog rješenjea.
const double A=10.0, B=2.0, C=-4.0;

template <int dim>
double exact(Dune::FieldVector<double, dim> const & glob){

    double rez = 0.0;
    if(dim == 1){
        const double x = glob[0];
        rez = A*x*x;
    }
    else if(dim ==2){
        const double x = glob[0];
        const double y = glob[1];
        rez = A*x*x + B*y*y*y;
    }
    else{
        const double x = glob[0];
        const double y = glob[1];
        const double z = glob[2];
        rez = A*x*x + B*y*y*y + C*z*z;
    }
    return rez;
}

// Gradijent egzaktnog rješenja. On nam treba za postavljanje rubnog 
// uvjeta (u testiranju metodom artificijelnog rješenja).
template <int dim>
Dune::FieldVector<double, dim>
grad_exact(Dune::FieldVector<double, dim> const & glob){

    Dune::FieldVector<double, dim> rez;
    if(dim == 1){
        const double x = glob[0];
        rez[0] = 2*A*x;
    }
    else if(dim ==2){
        const double x = glob[0];
        const double y = glob[1];
        rez[0] = 2*A*x;
        rez[1] = 3*B*y*y;
    }
    else{
        const double x = glob[0];
        const double y = glob[1];
        const double z = glob[2];
        rez[0] = 2*A*x;
        rez[1] = 3*B*y*y;
        rez[2] = 2*C*z;
    }
    return rez;
}

// Funkcija koja računa Laplaceov operator primijenjen na egzaktno
// rješenje. Račun je egzaktan.
template <int dim>
double laplace_exact(Dune::FieldVector<double, dim> const & glob){

    double rez = 0.0;
    if(dim == 1){
        rez = 2*A;
    }
    else if(dim ==2){
        const double x = glob[0];
        const double y = glob[1];
        rez = 2*A + 6*B*y;
    }
    else{
        const double x = glob[0];
        const double y = glob[1];
        const double z = glob[2];
        rez =2*A + 6*B*y + 2*C;
    }
    return rez;
}


// Reakcijski koeficijent. Koeficijent a(x) u operator.hh datoteci.  
template <int dim>
double react_coeff(Dune::FieldVector<double, dim> const & glob){
    return 100.0;
}

// Desna strana diferencijalne jednadžbe. Za jednadžbu vidjeti operator.hh datoteku.
template <int dim>
double RHS(Dune::FieldVector<double, dim> const & glob){
    return  - laplace_exact(glob)
            + react_coeff(glob)*exact(glob);
}


#endif
