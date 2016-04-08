#include <DuplicateConnector.h>
#include <DuplicateSessionPool.h>

DuplicateConnector::DuplicateConnector( uptr<MessageDuplicateBlock> msg )
    : Connector( msg->address() , DUPLICATE_PORT )
{
    this->message_ = move_ptr( msg );
}

DuplicateConnector::~DuplicateConnector()
{
}

Session * DuplicateConnector::CreateSession()
{
    return new DuplicateSession( move_ptr( this->message_ ) );
}

void DuplicateConnector::OnSessionOpen( Session * session )
{
    auto s = scast<DuplicateSession*>( session );
    DuplicateSessionPool::Instance()->Push( s );
    s->SendRequest();
}

void DuplicateConnector::OnSessionClose( Session * session )
{
    DuplicateSessionPool::Instance()->Pop( scast<DuplicateSession*>( session ) );
    SAFE_DELETE( session );
}
