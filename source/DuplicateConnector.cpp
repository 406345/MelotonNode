#include <DuplicateConnector.h>
#include <DuplicateSessionPool.h>
#include <MRT.h>

DuplicateConnector::DuplicateConnector( uptr<MessageDuplicateBlock> msg )
    : Connector( msg->address() , msg->port() )
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
    auto s = DuplicateSessionPool::Instance()->Pop( scast<DuplicateSession*>( session ) );

    if ( session->LastError().Code() != 0 &&
         session->LastError().Code() != -4095 )
    {
        Logger::Error( "duplicate error <%>%" , session->LastError().Code() ,
                       session->LastError().Message() );
    }

    if ( session->LastError().Code() == -4078 )
    {
        Logger::Log( "retring duplicate % from %" ,
                     this->message_->path() ,
                     this->message_->address() );
        auto connector = make_uptr( DuplicateConnector , move_ptr( this->message_ ) );
        MRT::Maraton::Instance()->Regist( move_ptr( connector ) );
    }

    if ( !s->DuplicateFinish() )
    {
        Logger::Log( "duplication is not finish!" );
    }

    SAFE_DELETE( session );
}
