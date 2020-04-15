#ifndef DRIVER_HH
#define DRIVER_HH

#include <dune/istl/bvector.hh>
#include <dune/istl/io.hh>
#include <dune/istl/operators.hh>
#include <dune/istl/preconditioners.hh>
#include <dune/istl/solvers.hh>
#include <dune/istl/superlu.hh>

#include <dune/pdelab/backend/istl.hh>
#include <dune/pdelab/common/function.hh>
#include <dune/pdelab/common/vtkexport.hh>

#include <dune/pdelab/constraints/conforming.hh>
#include <dune/pdelab/finiteelementmap/qkfem.hh>
#include <dune/pdelab/finiteelementmap/pkfem.hh>

#include <dune/pdelab/gridfunctionspace/genericdatahandle.hh>
#include <dune/pdelab/gridfunctionspace/gridfunctionspace.hh>
#include <dune/pdelab/gridfunctionspace/gridfunctionspaceutilities.hh>
#include <dune/pdelab/gridfunctionspace/interpolate.hh>
#include <dune/pdelab/gridoperator/gridoperator.hh>
#include <dune/pdelab/stationary/linearproblem.hh>

#include <dune/grid/io/file/gmshreader.hh>
#include <dune/grid/io/file/vtk/subsamplingvtkwriter.hh>

#include "bctype.hh"
#include "operator.hh"

#include <memory>

// GV = GridView tip, gv je GridView.
template<class GV>
void driver(const GV& gv)
{
     // 1. Izbor konačnog elementa
    const int k = 1;
    
   
    // 2. Tip ograničenja
  
    // 3. Tip vektora i matrica.
 


    // 4. Prostor konačnih elemenata.


    // 5. Konstruiraj spremnika za ograničenja u prostoru konačnih elemenata.


    // 6. Asembliranje Dirichleteovih ograničenja.



    // 7. Konstrukcija mrežnog operatora.




    // 8. Konstruirati vektor stupnjeva slobode



    // 9. Instancirati klasu koja daje Dirichletov rubni uvjet i ubaciti Dirichletove vrijednosti
    //    u vektor rješenja (stupnjeva slobode).


    // 10. Izbor linearnog rješavača i prekondicionera.


    // 11. Instanciranje linearnog ili nelinearnog rješavača i rješavanje problema




    //12. Grafički prikaz - kreiranje diskretnih mrežnih funkcija


    // Ako imamo egzaktno rješenje prikazujemo i njega i grešku.





    // 13. Grafički prikaz -- VTK writer





    // Greška u max-normi








}

#endif // DRIVER_HH
