#include <string>
#include <MasterConnector.h>
#include <ClientListener.h>
#include <BlockHub.h>

using std::string;

int main( int argc , char* argv[] )
{
    string ip   = "127.0.0.1";
    int    port = 100;

    sptr<MasterConnector> connector = make_sptr( MasterConnector , ip , port );
    sptr<ClientListener>  client    = make_sptr( ClientListener , ip , 101 );

    while ( true )
    {
        MRT::Maraton::Instance()->Regist( connector );
        MRT::Maraton::Instance()->Regist( client );
        MRT::Maraton::Instance()->Run();
    }

    return 0;
}