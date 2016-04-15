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
}

void DuplicateListener::OnSessionClose( Session * session )
{
    SAFE_DELETE( session );
}
 