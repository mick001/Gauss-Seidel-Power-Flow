#include<iostream>
#include<fstream>
#include<vector>
#include<complex>
#include<string>

using std::vector;
using std::cin;
using std::cout;
using std::complex;
using std::string;
using std::endl;
using std::ifstream;
using std::ofstream;

/*
*********************************************************************************************************
                                IO functions for vectors
*********************************************************************************************************
*/

namespace io_vectors_data
{

    // This function checks if a file exists
    bool check_if_file_exists(string file_path)
    {
        ifstream file(file_path);
        bool file_existance_status = file.good();
        file.close();
        return file_existance_status;
    }

    // This function saves a complex array to a file in a CSV format
    void save_results_to_file(const vector< complex<double> > &V,
                              const vector< complex<double> > &I,
                              const vector< complex<double> > &S,
                              string file_path)
    {
        // Check if the file already exists
        if(check_if_file_exists(file_path))
        {
            cout << "File: " << file_path << " Already exists... OVERWRITE? (y/n) ";
            string answer;
            cin >> answer;

            if(answer != "y")
            {
                cout << "Data not saved!" << endl;
                return;
            }

            cout << "Overwriting..." << endl;
        }

        // Open file
        ofstream file(file_path);

        // If the file is open save data to it
        if(file.is_open())
        {
            int n_data = V.size();

            // Set header
            file << "Vreal," << "Vimag," << "Ireal," << "Iimag," << "Sreal," << "Simag" << "\n";

            // Feed data to the file
            for(int i = 0; i < n_data; i++)
            {
                file << V[i].real() << "," << V[i].imag() << "," << I[i].real() << "," << I[i].imag() << "," << S[i].real() << "," << S[i].imag() << "\n";
            }

            // Close stream
            file.close();
            cout << "Data successfully saved to file in the following path: " << file_path << endl;

        }else
        {
            cout << "Unable to open file... Data has not been saved." << endl;
        }
    }

}

