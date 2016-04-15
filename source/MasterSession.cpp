#include <MasterSession.h>
#include <MessageAlive.pb.h>
#include <BlockHub.h>
#include <MessageBlockMeta.pb.h>
#include <MessageSyncBlock.pb.h>

MasterSession* MasterSession::instance_ = nullptr;
MasterSession * MasterSession::Instance()
{
    return MasterSession::instance_;
}

void MasterSession::SetInstance( MasterSession * session )
{
    MasterSession::instance_ = session;
}

MasterSession::MasterSession()
{
    alive_worker_ = MRT::SyncWorker::Create( 1000 , [this] ( MRT::SyncWorker* worker )
    {
        auto msg = make_uptr( MessageAlive );
        msg->set_blockcount( BlockHub::Instance()->BlockCount() );
        msg->set_cpu( SystemInfo::CPUNum() );
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

void MasterSession::OnConnect()
{
    auto block_count = BlockHub::Instance()->BlockCount();

    for ( size_t i = 0; i < block_count; i++ )
    {
        auto block = BlockHub::Instance()->FindBlock( i );
        auto sync = make_uptr   ( MessageBlockMeta );
        sync->set_fileoffset    ( block->FileOffset );
        sync->set_index         ( block->Index );
        sync->set_partid        ( block->PartId );
        sync->set_path          ( block->Path );
        sync->set_size          ( block->Size );
        sync->set_status        ( 0 );
        MasterSession::Instance()->SendMessage( move_ptr( sync ) );
    }

    Logger::Log( "sync % blocks " , block_count );

}
