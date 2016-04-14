#include <ClientListener.h>
#include <ClientSession.h>
ClientListener::ClientListener( string ip , int port )
    : Listener( ip , port )
{
    Logger::Log( "client listener on %:%" , ip , port );
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
}

void ClientListener::OnSessionClose( Session * session )
{
    SAFE_DELETE( session );
}
 