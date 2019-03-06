#include<vector>
#include<complex>
#include<string>
#include<electrical_grid.hpp>

using std::vector;
using std::complex;
using std::string;

/*
*********************************************************************************************************
                                Grid parameters
*********************************************************************************************************
*/

const vector<vector< complex<double> > > Y { { {0, -8.312}, {0, 3.3611}, {0, 5.0417}, {0, 0} },         // Y BUS: bus admittance matrix
                                            { {0, 3.3611}, {0, -9.0368}, {0, 5.7619}, {0, 0} },
                                            { {0, 5.0417}, {0, 5.7619}, {0, -23.2365}, {0, 13.3319} },
                                            { {0, 0}, {0, 0}, {0, 13.3319}, {0, -14.2203} }
                                            };

const vector< complex<double> > V{ {1.06, 0}, {1, 0}, {1, 0}, {0.99, 0} };                            // Bus voltage vector
const vector< complex<double> > S{ {0.9, 0}, {-1.4, -0.5964}, {0, 0}, {0, 0} };                       // Complex power injections at each bus
const vector<string> bus_type{"PV", "PQ", "PQ", "SLACK"};                                             // Bus type
const vector<double> PV_BUSSES_VOLTAGE {1.06, 0.0, 0.0, 0.0};                                         // Voltages of PV busses (0 for non-PV busses)
const int ITERMAX = 9;
const string FILE_PATH = "C:/users/michy/desktop/data.txt";
const bool SAVE_TO_FILE = false;

/*
*********************************************************************************************************
                                MAIN
*********************************************************************************************************
*/

// MAIN
int main()
{
    ElectricalGrid grid(Y, S, bus_type, PV_BUSSES_VOLTAGE, V);
    grid.run_gauss_seidel(ITERMAX);
    grid.print_results();
    grid.export_data_to_file(FILE_PATH);

    system("PAUSE");
    return 0;
}




