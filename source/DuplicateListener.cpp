#include <DuplicateListener.h>
#include <DuplicateSession.h>

DuplicateListener::DuplicateListener( string ip , int port )
    : Listener( ip , port )
{
    Logger::Log( "duplicate listener on %:%" , ip , port );
}

DuplicateListener::~DuplicateListener()
{
}

Session * DuplicateListener::CreateSession()
{
    return new DuplicateSession();
}

void DuplicateListener::OnSessionOpen( Session * session )
{
    Logger::Log( "duplicate %:% connected" , session->ip_address() , session->port() );
}

void DuplicateListener::OnSessionClose( Session * session )
{
    Logger::Log( "duplicate %:% disconnected" , session->ip_address() , session->port() );
    SAFE_DELETE( session );
}
 