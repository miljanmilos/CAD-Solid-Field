# CAD-Solid-Field
CAD Solid and Field is the University of Kragujevac and BioIRC’s in-house pre- and post- processing 3D modeling and visualization tool developed using the MFC (Microsoft Foundation Class) library. 
CAD is integrated with PAK simulation code, it simplifies model generation and can visualize and animate results of computational simulations. As already notified, CAD has two modules: preprocessor and postprocessor.
The preprocessor is used for model generation in a form that can be run using the FE simulation code. The creation of the model usually consists of geometry and mesh generation, adding constraints, loads, and materials. 
The model data are exported to a file with extension *.dat which is run by the FE solver PAK. The results of an FE simulation (field of displacement, velocities, pressures, concentrations, etc.) are exported to a file with extension *.unv that is automatically loaded
by the postprocessor of the CAD. Therefore, the postprocessor is used for importing the results, and then it is used for visualization of the results and analysis by plotting various representations (field vs. time, field vs. distance, etc.). 
Various libraries are integrated into CAD, such as Triangle 2D mesh generator (Shewchuk, 1996, Shewchuk, 2002), TetGen 3D mesh generator (Si, 2015), as well as Libigl library (Jacobson et al., 2018).

![alt text](https://github.com/miljanmilos/CAD-Solid-Field/blob/master/img.jpg?raw=true)

**Fibers** directory contains stl files for generation of the muscle fibers within heart model.  
  
**Heart** directory contains stl files of different heart components.  
  
**IGLEXE** directory contains libIGL files (library used for mesh morphing, deformation etc.)  
  
**PAK** directory contains pakFIS (Fields & Solids) solver  
  
**PAKT** direcoty contains PAKT (Transport) solver  
  
**CAD.exe** - CAD executable file   
  
**CAD Solid and Field - Manual-v1** - manual   
