#ifndef OPERATOR_HH
#define OPERATOR_HH
#include <dune/geometry/quadraturerules.hh>
#include <dune/geometry/referenceelements.hh>

#include <dune/pdelab/localoperator/defaultimp.hh>
#include <dune/pdelab/localoperator/flags.hh>
#include <dune/pdelab/localoperator/pattern.hh>
#include <dune/pdelab/finiteelement/localbasiscache.hh>

#include "bctype.hh"
#include "exact.hh"
/** Lokalni operator za zadaću :
 *
 *   - div( grad u) + a(x) u = f(x)   u \Omega
 *                   u = g(x)   na \Gamma_D\subseteq\partial\Omega
 *        - grad u . n = j(x)   na \Gamma_N = \partial\Omega\setminus\Gamma_D
 *
 * sa konformnim konačnim elementima svih tipova u svim dimenzijama
 *
 * \tparam BCType klasa koja indicira rubni uvjet
 */


template<typename BCType, typename FEM>
class DiffusionLOP : // derivacijska lista -- jakobijan i pattern računa PDELab
  public Dune::PDELab::NumericalJacobianApplyVolume  <DiffusionLOP<BCType, FEM> >,
  public Dune::PDELab::NumericalJacobianVolume       <DiffusionLOP<BCType, FEM> >,
  public Dune::PDELab::NumericalJacobianApplyBoundary<DiffusionLOP<BCType, FEM> >,
  public Dune::PDELab::NumericalJacobianBoundary     <DiffusionLOP<BCType, FEM> >,
  public Dune::PDELab::FullVolumePattern,
  public Dune::PDELab::LocalOperatorDefaultFlags
{
public:
  // Zastavice koje signaliziraju da na svakom elementu treba zvati:
  enum { doPatternVolume = true };  // metodu za računanje patterna (iz volumnih doprinosa)
  enum { doAlphaVolume = true };    // alpha_volume
  enum { doAlphaBoundary = true };  // alpha_boundary

  using  LocalBasis = typename FEM::Traits::FiniteElementType::Traits::LocalBasisType ;

  DiffusionLOP(const BCType& bctype_, // boundary cond.type
               const FEM & fem_,
               unsigned int intorder_=2) :
    bctype( bctype_ ), fem(fem_), intorder( intorder_ )
  {}

  // Računanje volumnog integrala
  // eg   = element (geometry)
  // lfsu = lokalni prostor funkcija za rješenje
  // lfsv = lokalni prostor funkcija za test funkciju
  // x    = vektor koeficijenata rješenja
  // r    = lokalni rezidual
  template<typename EG, typename LFSU, typename X, typename LFSV, typename R>
  void alpha_volume (const EG& eg, const LFSU& lfsu, const X& x, const LFSV& lfsv, R& r) const
  {
   
  }

  // integral po rubu
  // ig     = intersection (= stranica elementa)
  // lfsu_s = lokalni prostor funkcija na stranici za rješenje
  // lfsu_v = lokalni prostor funkcija na stranici za test funkciju
  // x_s    = vektor koeficijenata rješenja (na stranici)
  // r_s    = rezidual (na stranici)
  template<typename IG, typename LFSU, typename X, typename LFSV, typename R>
  void alpha_boundary (const IG& ig, const LFSU& lfsu_s, const X& x_s,
                       const LFSV& lfsv_s, R& r_s) const
  {
   
  }

private:
  BCType const & bctype;
  FEM const & fem;
  unsigned int intorder;
  Dune::PDELab::LocalBasisCache<LocalBasis> cache;
};

#endif // OPERATOR_HH
