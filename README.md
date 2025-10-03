# landflow

Calculate the integrated surface water discharge from an elevation map and imposed precipitation, obtaining the steady-state configuration.

### Steps to compile the code ###

* Clone the landflow repository

* Compile the code in the `landflow/` directory:

    ```
    make all
    ``` 

* Unzip the `ETOPO1_SouthAmerica.xyz.zip` file:

    ```
    unzip ETOPO1_SouthAmerica.xyz.zip
    ```
* Run `./extract_flow` in the same folder with `ETOPO1_SouthAmerica.xyz` file.

* Run `./fluvial_Qr` to obtain the surface water discharge.

* View the map with `python create_Qr_map.py`

![Simulation result](images/Qr_map.png)


