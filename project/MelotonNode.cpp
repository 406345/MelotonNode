#include <string>
#include <MasterConnector.h>
#include <ClientListener.h>
#include <BlockHub.h>
#include <Settings.h>
#include <DuplicateListener.h>

using std::string;

int main( int argc , char* argv[] )
{ 
    BlockHub::Instance()->LoadFromDisk();

    sptr<MasterConnector> connector     = make_sptr( MasterConnector ,
                                                     MASTER_IP ,
                                                     MASTER_NODE_PORT );

    sptr<ClientListener>  client        = make_sptr( ClientListener ,
                                                     "0.0.0.0" ,
                                                     NODE_CLIENT_PORT );

    sptr<DuplicateListener>  duplicate  = make_sptr( DuplicateListener ,
                                                     "0.0.0.0" ,
                                                     DUPLICATE_PORT );
    
    MRT::Maraton::Instance()->Regist( connector );
    MRT::Maraton::Instance()->Regist( client );
    MRT::Maraton::Instance()->Regist( duplicate );

    while ( true )
    {
        MRT::Maraton::Instance()->Run();
    }

    return 0;
}