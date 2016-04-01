#include <string>
#include <MasterConnector.h>
#include <ClientListener.h>
#include <BlockHub.h>
#include <Settings.h>

using std::string;

int main( int argc , char* argv[] )
{

    BlockHub::Instance()->LoadFromDisk();

    sptr<MasterConnector> connector = make_sptr( MasterConnector ,
                                                 Settings::Instance()->MasterAddress() ,
                                                 Settings::Instance()->MasterPort() );

    sptr<ClientListener>  client    = make_sptr( ClientListener ,
                                                 Settings::Instance()->ListenerAddress() ,
                                                 Settings::Instance()->ListenerPort() );

    while ( true )
    {
        MRT::Maraton::Instance()->Regist( connector );
        MRT::Maraton::Instance()->Regist( client );
        MRT::Maraton::Instance()->Run();
    }

    return 0;
}