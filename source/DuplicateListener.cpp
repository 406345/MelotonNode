#include <DuplicateListener.h>
#include <DuplicateSendBlockSession.h>

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
    return new DuplicateSendBlockSession();
}

void DuplicateListener::OnSessionOpen( Session * session )
{
}

void DuplicateListener::OnSessionClose( Session * session )
{
    SAFE_DELETE( session );
}
 