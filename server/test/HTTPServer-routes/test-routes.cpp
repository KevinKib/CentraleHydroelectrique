#include "../../libs/http/httplib.h"
#include "../../includes/typedefs.h"
#include <string>
#include <iostream>

using namespace std;

/**
 * The HTTP server must be opened
 **/
bool testHydraulicsRoute()
{
    JSON waitingResult;
    JSON temp, array = JSON::array ( );

    array.push_back("Groupe1");
    array.push_back("Groupe2");

    temp["Avignon"] = array;
    waitingResult["data"] = temp;

    httplib::Client client ( "127.0.0.1", 8070 );
    auto get = client.Get ( "/hydraulics" );

    if ( ! get )
    {
        return false;
    }

    JSON currentResult = JSON::parse ( get->body );

    return currentResult == waitingResult;
}

bool testCurrentDataRouteWithValidArgs()
{
    string url = "/current-data?hydraulic=Avignon&turbine=Groupe1&attribute=Puissance";
    bool waitingSuccess = true;

    httplib::Client client ( "127.0.0.1", 8070 );
    auto get = client.Get ( url.c_str ( ) );

    if ( ! get )
    {
        return false;
    }

    JSON currentResult = JSON::parse ( get->body );
    bool currentSuccess = currentResult["success"].get<bool>( );

    return currentSuccess == waitingSuccess;
}

bool testCurrentDataRouteWithInvalidArgs ( string url )
{
    bool waitingSuccess = false;
    string waitingError = "Error !";

    httplib::Client client ( "127.0.0.1", 8070 );
    auto get = client.Get ( url.c_str ( ) );

    if ( ! get )
    {
        return false;
    }

    if ( get->body.empty ( ) )
    {
        return false;
    }

    JSON currentResult = JSON::parse ( get->body );

    bool currentSuccess = currentResult["success"].get<bool>();
    string currentError = currentResult["content"];

    return ( currentSuccess == waitingSuccess) && ( waitingError == currentError );
}

int main(int argc, const char **argv)
{
    if ( ! testHydraulicsRoute ( ) )
    {
        cerr << "The test of the hydraulics route has failed !" << endl;
        return 1;
    }

    // All of the args are given and they are correct
    if ( ! testCurrentDataRouteWithValidArgs ( ) )
    {
        cerr << "The test of the current data route has failed !" << endl;
        return 1;
    }

    // The attribute is not given
    if ( ! testCurrentDataRouteWithInvalidArgs ( "/current-data?hydraulic=Avignon&turbine=Groupe1" ) )
    {
        cerr << "The test of the current data route without attribute has failed !" << endl;
        return 1;
    }

    // There is not args
    if ( ! testCurrentDataRouteWithInvalidArgs ( "/current-data") ) 
    {
        cerr << "The test of the current data route without args has failed !" << endl;
        return 1;
    }

    // The hydraulic is not given
    if ( ! testCurrentDataRouteWithInvalidArgs ( "/current-data?turbine=Groupe1&attribute=Puissance") )
    {
        cerr << "The test of the current data route without hydraulic has failed !" << endl;
        return 1;
    }

    // The turbine is not given
    if ( ! testCurrentDataRouteWithInvalidArgs ( "/current-data?hydraulic=Avignon&attribute=Puissance") )
    {
        cerr << "The test of the current data route without turbine has failed !" << endl;
        return 1;
    }

    // The turbine and the hydraulic are not given
    if ( ! testCurrentDataRouteWithInvalidArgs ( "/current-data?attribute=Puissance") )
    {
        cerr << "The test of the current data route without hydraulic/turbine has failed !" << endl;
        return 1;
    }

    // All of the args are given but the attribute is not correct
    if ( ! testCurrentDataRouteWithInvalidArgs ( "/current-data?hydraulic=Avignon&turbine=Groupe1&attribute=badAttribute" ) )
    {
        cerr << "The test of the current data route with invalid attribute has failed !" << endl;
        return 1;
    }

    // All of the args are given but the hydraulic is not correct
    if ( ! testCurrentDataRouteWithInvalidArgs ( "/current-data?hydraulic=badHydraulic&turbine=Groupe1&attribute=Puissance" ) )
    {
        cerr << "The test of the current data route with invalid hydraulic has failed !" << endl;
        return 1;
    }

    // All of the args are given but the turbine is not correct
    if ( ! testCurrentDataRouteWithInvalidArgs ( "/current-data?hydraulic=Avignon&turbine=badTurbine&attribute=Puissance" ) )
    {
        cerr << "The test of the current data route with invalid turbine has failed !" << endl;
        return 1;
    }

    cout << "All of the tests are correct" << endl;

    return 0;
}