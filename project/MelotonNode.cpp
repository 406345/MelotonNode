#include <string>
#include <MasterConnector.h>

#include <BlockHub.h>

using std::string;

int main( int argc , char* argv[] )
{
    string ip   = "127.0.0.1";
    int    port = 100;

    BlockHub::Instance()->LoadIndex("");

    while ( true )
    {
        Logger::Sys( "try connecting master at %:%" , ip , port );
        sptr<MasterConnector> connector = make_sptr( MasterConnector , ip , port );

        MRT::Maraton::Instance()->Regist( connector );
        MRT::Maraton::Instance()->Run();
    }

    return 0;
}