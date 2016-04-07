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
                                                 "127.0.0.1" ,
                                                 MASTER_NODE_PORT );

    sptr<ClientListener>  client    = make_sptr( ClientListener ,
                                                 "0.0.0.0" ,
                                                 NODE_CLIENT_PORT );

    while ( true )
    {
        MRT::Maraton::Instance()->Regist( connector );
        MRT::Maraton::Instance()->Regist( client );
        MRT::Maraton::Instance()->Run();
    }

    return 0;
}