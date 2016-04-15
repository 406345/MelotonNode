#include <MasterConnector.h>
#include <MasterSession.h>
#include <MRT.h>
#include <MelotonNode.h>

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
    auto session = new MasterSession();
    MasterSession::SetInstance( session );
    return session;
}

void MasterConnector::OnSessionOpen( Session * session )
{
    Logger::Sys( "connect master success" );
    auto master = scast<MasterSession*>( session );
}

void MasterConnector::OnSessionClose( Session * session )
{
    SAFE_DELETE( session );
    MasterSession::SetInstance( nullptr );
    Logger::Sys( "disconnect from master" );
    sptr<MasterConnector> connector = make_sptr( MasterConnector , MASTER_IP , MASTER_NODE_PORT );
    MRT::Maraton::Instance()->Regist( connector );
}
