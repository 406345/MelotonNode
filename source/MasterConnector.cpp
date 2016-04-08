#include <MasterConnector.h>
#include <MasterSession.h>
#include <MRT.h>

MasterConnector::MasterConnector( string ip , int port )
    : MRT::Connector( ip , port )
{
    Logger::Sys( "connnecting master %:%" , ip , port );
}

MasterConnector::~MasterConnector()
{
}

Session * MasterConnector::CreateSession()
{
    return new MasterSession();
}

void MasterConnector::OnSessionOpen( Session * session )
{
    Logger::Sys( "connect master success" );
    auto master = scast<MasterSession*>( session );
}

void MasterConnector::OnSessionClose( Session * session )
{
    SAFE_DELETE( session );
    Logger::Sys( "master connecting disconnected" );
    sptr<MasterConnector> connector = make_sptr( MasterConnector , MASTER_IP , MASTER_NODE_PORT );
    MRT::Maraton::Instance()->Regist( connector );
}
