#include <ClientListener.h>
#include <ClientSession.h>
ClientListener::ClientListener( string ip , int port )
    : Listener( ip , port )
{
}

ClientListener::~ClientListener()
{
}

Session * ClientListener::CreateSession()
{
    return new ClientSession();
}

void ClientListener::OnSessionOpen( Session * session )
{
    Logger::Log( "<%:%> client connected" , session->ip_address() , session->port() );
}

void ClientListener::OnSessionClose( Session * session )
{
    Logger::Log( "<%:%> client disconnected" , session->ip_address() , session->port() );
    SAFE_DELETE( session );
}
 