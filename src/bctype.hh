#ifndef BCTYPE_HH
#define BCTYPE_HH
#include <dune/common/fvector.hh>
#include <dune/pdelab/common/function.hh>
#include <dune/pdelab/constraints/common/constraintsparameters.hh>
#include <cmath>

#include "exact.hh"


// Klasa mora proširivati klasu PDELab::DirichletConstraintsParameters
// i u njoj prerađuje metodu isDirichlet() odlučuje je li neka točka
// na Dirichletovoj granici ili nije.
class DirichletBdry : public Dune::PDELab::DirichletConstraintsParameters
{
public:
  //  intersection = stranica elementa (u 3D) ili brid elementa (u 2D)
  //  coord        = lokalne koordinate točke na "intersectionu" koja se ispituje
  //  povratna vrijednost: true ako je točka na Dirichletovoj granici
  //                       false ako nije.
  template<typename I>
  bool isDirichlet(const I & intersection,
                   const Dune::FieldVector<typename I::ctype, I::mydimension> & coord  
                   ) const
  {
//    // Globalne koordinate točke (uočite da su dimenzije lokalne i globalne točke različite )
    auto xg = intersection.geometry().global( coord );
    if( xg[0]>1.0-1E-6 ) return false; //  na desnoj stranici nije Dirichletov uvjet

    return true;  // Dirichletov uvjet na ostalim granicama
  }
};

/*  Klasa koja određuje vrijednost Dirichletovog rubnog uvjeta i
    njegovo proširenje na čitavu domenu.
    Template parametri:
       GV = GridView
       RF = double = Range Field Type (tip kojim su predstavljeni elementi slike funkcije)

       Treći parametar u GridFunctionTraits je dimenzija slike funkcije (1 jer su
       naše funkcije skalarne). Ta se dimenzija ponavlja u zadnjem parametru
       GridFunctionTraits klase.
    */
template <typename GV>
using GFTraits = Dune::PDELab::GridFunctionTraits<GV,double,1,Dune::FieldVector<double,1>>;

template<typename GV>
class BCExtension
  : public Dune::PDELab::GridFunctionBase< GFTraits<GV>, BCExtension<GV> > {
 // Klasa čuva referencu na GridView objekt.
  const GV& gv;
public:
  typedef Dune::PDELab::GridFunctionTraits<GV,double,1,Dune::FieldVector<double,1> > Traits;

  // Konstruktor samo uzima referencu na  GridView objekt.
  BCExtension (const GV& gv_) : gv(gv_) {}

  // Izračunaj Dirichletovu vrijednost na elementu. Ako točka nije na
  // Dirichletovoj granici, nda funkcija daje proširenje Dirichletovog rubnog
  // uvjeta na čitavu domenu. To je proširenje u osnovi proizvoljno.
  // e     = element
  // xlocal = lokalne koordinate točke u kojoj se računa Dirichletova vrijednost
  // y      = izračunata Dirichletova vrijednost
  inline void evaluate (const typename Traits::ElementType& e,
                        const typename Traits::DomainType& xlocal,
                        typename Traits::RangeType& y) const
  {
    const int dim = GFTraits<GV>::GridViewType::Grid::dimension;

    // Pretvori lokalne koordinate u globalne
    Dune::FieldVector<double,dim> x = e.geometry().global(xlocal);
    y = exact(x);

    return;
  }

  // Vrati referencu na GridView
  inline const GV& getGridView () {return gv;}
};


// Pomoćna kratica.
template <typename GV>
using ATraits = Dune::PDELab::AnalyticGridFunctionTraits<GV,double,0>;// 1 = skalarna funkcija

// Klasa koja daje diskretnu mrežnu funkciju egzaktnog rješenja. 
template <typename GV>
class ExactGF : public Dune::PDELab::AnalyticGridFunctionBase<ATraits<GV>, ExactGF<GV>>
{
public:
   typedef Dune::PDELab::AnalyticGridFunctionBase<ATraits<GV>, ExactGF<GV> > BaseT;

   ExactGF(GV const & gv) : BaseT(gv) {}

   void evaluateGlobal(typename ATraits<GV>::DomainType const & x, typename ATraits<GV>::RangeType & y) const
   {
       y = exact(x);
   }
   // Bazna klasa daje metodu evaluate().
};


#endif // BCTYPE_HH
