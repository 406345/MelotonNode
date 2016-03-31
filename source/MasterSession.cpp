#include <MasterSession.h>
#include <MessageAlive.pb.h>
#include <BlockHub.h>

MasterSession::MasterSession()
{
    alive_worker_ = MRT::SyncWorker::Create( 1000 , [ this ] ( MRT::SyncWorker* worker ) {

        auto msg = make_uptr( MessageAlive );
        msg->set_blockcount( BlockHub::Instance()->BlockCount() );
        msg->set_cpu( 0 );
        msg->set_memory( MRT::SystemInfo::MemoryFreeSize() );
        this->SendMessage( move_ptr( msg ) );

        return false;
    } , nullptr , nullptr );
}

MasterSession::~MasterSession()
{
    if ( alive_worker_ != nullptr )
    {
        MRT::SyncWorker::Stop( alive_worker_ );
    }
}
