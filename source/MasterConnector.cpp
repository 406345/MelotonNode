#include <MasterConnector.h>
#include <MasterSession.h>

MasterConnector::MasterConnector( string ip , int port )
    : MRT::Connector( ip , port )
{

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
}
