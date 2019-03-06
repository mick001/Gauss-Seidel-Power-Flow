#include<vector>
#include<complex>
#include<string>
#include<helper_functions.hpp>
#include<io_vectors.hpp>

using std::cout;
using std::conj;
using std::arg;
using std::polar;
using vector_functions::row_column_product;
using vector_functions::print_vector;
using vector_functions::vector_norm_euclidean;
using io_vectors_data::save_results_to_file;


/*
*********************************************************************************************************
                                ElectricalGrid class implementation
*********************************************************************************************************
*/


class ElectricalGrid
{
    private:
        vector<vector< complex<double> >> Y_bus;                    // Bus admittance matrix
        vector< complex<double> > S_injections;                     // Complex power injections
        vector<string> bus_type;                                    // Bus type
        vector<double> pv_busses_voltage;                           // Voltages of PV busses (0 for non-PV busses)
        vector< complex<double> > V;                                // Voltage bus
        int number_of_busses;                                       // Number of busses
        bool solved;                                                // Solved?

    public:

        // Public constructor
        ElectricalGrid(vector<vector< complex<double> >> Y,
                       vector< complex<double> > S,
                       vector<string> bus_type_,
                       vector<double> pv_voltage,
                       vector< complex<double> > initial_bus_voltage,
                       bool already_solved = false)
        {
            Y_bus = Y;
            S_injections = S;
            bus_type = bus_type_;
            pv_busses_voltage = pv_voltage;
            V = initial_bus_voltage;
            number_of_busses = initial_bus_voltage.size();
            solved = already_solved;
        }

        // Calculate complex power injection in each bus
        vector< complex<double> > calculate_power_injections()
        {
            vector< complex<double> > complex_power (number_of_busses);

            for(int i = 0; i < number_of_busses; i++)
            {
                complex_power[i] = V[i] * conj(row_column_product(Y_bus, V, i));
            }

            return complex_power;
        }

        // Calculate complex current injections in each bus
        vector< complex<double> > calculate_current_injections()
        {
            vector< complex<double> > currents (number_of_busses);

            for(int i = 0; i < number_of_busses; i++)
            {
                currents[i] = row_column_product(Y_bus, V, i);
            }

            return currents;
        }


        // Run Gauss Seidel algorithm on the network
        void run_gauss_seidel(int itermax)
        {
            string current_bus = "";
            complex<double> temp_s {0.0, 0.0};
            complex<double> UNO {1.0, 0.0};
            double theta = 0.0;
            vector< complex<double> > V_previous = V;

            // GAUSS SEIDEL iteration loop
            for(int i = 0; i < itermax; i++)
            {
                cout << "ITERATION NUMBER: " << i + 1 << endl;

                // BUS loop: loops on every bus
                for(int k = 0; k < number_of_busses; k++)
                {
                    // Set current bus type
                    current_bus = bus_type[k];

                    if(current_bus == "PV")
                    {
                        // Handle PV bus
                        temp_s = V[k] * conj(row_column_product(Y_bus, V, k));
                        S_injections[k] = { S_injections[k].real(), temp_s.imag() };
                        theta = arg( ( UNO/Y_bus[k][k] ) * ( conj(S_injections[k]/V[k]) - row_column_product(Y_bus, V, k) + V[k]*Y_bus[k][k] ) );
                        V[k] = polar(pv_busses_voltage[k], theta);
                    }
                    else if(current_bus == "SLACK")
                    {
                        // Handle Slack bus
                        S_injections[k] = V[k] * conj(row_column_product(Y_bus, V, k));
                    }
                    else
                    {
                        // Handle PQ bus
                        V[k] = ( UNO/Y_bus[k][k] ) * ( conj(S_injections[k]/V[k]) - row_column_product(Y_bus, V, k) + V[k]*Y_bus[k][k] );
                    }
                }

                // cout some information on the process
                cout << "End of iteration " << i + 1 << endl;
                cout << "Euclidean norm: " << vector_norm_euclidean(V, V_previous) << endl;
                print_vector(V, "Bus voltages");
                cout << endl << "---------------------------------------------------------" << endl;

                // Update voltages
                V_previous = V;

            }

            solved = true;
        }

        // Print the results
        void print_results()
        {
            vector< complex<double> > I = calculate_current_injections();
            vector< complex<double> > S = calculate_power_injections();

            cout << "=========================================================" << endl;
            cout << endl << endl << "Iteration procedure ended! Final results:" << endl;
            print_vector(V, "Bus voltages");
            print_vector(I, "Current injections");
            print_vector(S, "Complex power injections");
            cout << endl << "=========================================================" << endl;
        }

        // Save the data to file
        void export_data_to_file(string file_path)
        {
            save_results_to_file(V, calculate_current_injections(), calculate_power_injections(), file_path);
        }

};
