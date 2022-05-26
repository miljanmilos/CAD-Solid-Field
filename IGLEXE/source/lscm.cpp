#include <igl/boundary_loop.h>
#include <igl/readOBJ.h>
#include <igl/lscm.h>

using namespace Eigen;
using namespace std;

MatrixXd V, V_uv;
MatrixXi F;


void ExportUV()
{
    FILE* f = fopen("lscm_output.txt","w");
    int nSize = V.size()/3;
    fprintf(f,"3D coords (x,y,z) 2D coords (u,v)\n");
    fprintf(f, "%d\n", nSize);
    for (int i = 0; i < nSize; i++) 
        fprintf(f,"%10.2e%10.2e%10.2e%10.2e%10.2e\n", V(i,0), V(i, 1), V(i, 2), V_uv(i, 0), V_uv(i, 1));
    fclose(f);
}

int main(int argc, char *argv[])
{  
  igl::readOBJ("hollow_model/Model.obj", V, F);

  VectorXi bnd,b(2,1);
  igl::boundary_loop(F,bnd);
  b(0) = bnd(0);
  b(1) = bnd(bnd.size()/2);
  MatrixXd bc(2,2);
  bc<<0,0,1,0;

  // LSCM parametrization
  igl::lscm(V,F,b,bc,V_uv);

  // Scale the uv
  V_uv *= atoi(argv[1]);
  ExportUV();
}
