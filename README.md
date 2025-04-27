
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

## Further information, questions, issues and bugs:

 + prisms-pf-users@googlegroups.com (user forum)
 + prisms-pf@umich.edu  (developer email list)
