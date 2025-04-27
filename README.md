
I have solved the Cahn-Hillard PF model presented in the paper as follows:
![image](https://github.com/user-attachments/assets/ffb8fa99-9836-405b-bcc4-1180e9ed004c)

I have implemented the computational model for different free energy expressions from the paper in the Opensource gihub page PRISMS-PF v2.4.0 (https://prisms-center.github.io/phaseField)
The model implementation and the updated code can be found in application/phaseTreeAssg folder.

### Installation:
Please refer to the [installation section of the user manual](https://prisms-center.github.io/phaseField/doxygen_files/install.html) for details.
1) Install CMake, p4est, and deal.II (version 9.5 recommended)<br>
2) Clone the PRISMS-PF GitHub repository <br>
```
$ git clone https://github.com/prisms-center/phaseField.git
$ cd phaseField
$ git checkout master
$ cmake .
$ make -j <nprocs>
```
[here <nprocs> denotes the number of processors]

### Applicaion instruction for the assignment
The code structure and run the application for the assignment:
cd application/phaseTreeAssg
1.	main C++ code to run is equations.cc
2.	ICs_and_BCs.cc is used to define the initial spinodal decomposition of the phase to start with
3.	Postprocess.cc is used to postprocess the output for visualization of any variable
4.	Finally, the “customPDE.h” is the definition file of all the variables used or initiate in any of the code above.
5.	parameters.prm  is used to define the parameter of the model such as M, K, c -range, domain size, iteration time, steps and the material parameters. 
To execute the code, do the following
1.	$ cmake .
2.	$ make -j <num of available processor>
3.	$ mpirun -n <num of available processor> main
This is start running and provide the results file in solutions-iteraions-number.vtu. This is visualized in paraview.

Initially, the implementation was not converging with material parameters of the paper stiffness matrix components. Therefore, the execute the same model equation of the paper I have used an isotropic elastic material with material parameters given in parameters.prm
However, the model equation is same as the reference paper.

### DISCLAIMER
It is worth noting that while executing the cmake and make -j  <nprocs> in the main phase-field folder after git clone, It is very much necessary to install and update Install CMake, p4est, and deal.II (version 9.6.0 or above required).
I had a lot of trouble to install deal.II and make work with ninja due to my computer does not have right amount of swap memory in WSL ubuntu. I spent almost 2-3 days to make things clear then work on the PRISMS-PF modules.

#### These are few tips to make things work while installing deal.II
rm -rf build/
mkdir build
cd build
cmake -DDEAL_II_DIR=/path/to/dealii ..
make -j$(nproc)

#### You can increase swap size temporarily (example for 8GB swap):
sudo dd if=/dev/zero of=/swapfile bs=1M count=8192
sudo mkswap /swapfile
sudo swapon /swapfile

