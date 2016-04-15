#include "DuplicateSession.h"
#include <MessageDuplicateDataRequest.pb.h>
#include <BlockHub.h>
#include <MRT.h>
#include <MasterSession.h>
#include <MessageSyncBlock.pb.h>

DuplicateSession::DuplicateSession()
{
}

DuplicateSession::DuplicateSession( uptr<MessageDuplicateBlock> msg )
{
    this->message_block_ = move_ptr( msg );
    this->index_ = BlockHub::Instance()->FindBlock( this->message_block_->path() , 
                                                    this->message_block_->partid() );
    
    if(this->index_ == nullptr )
        this->index_ = BlockHub::Instance()->CreateBlock( (int)this->message_block_->partid() ,
                                                          this->message_block_->fileoffset() ,
                                                          this->message_block_->path() );
    
}

DuplicateSession::~DuplicateSession()
{

}

void DuplicateSession::SendRequest()
{
    uptr<MessageDuplicateDataRequest> message = make_uptr( MessageDuplicateDataRequest );
    message->set_index     ( this->message_block_->index() );
    message->set_token     ( this->message_block_->token() );
    message->set_offset    ( this->block_offset_ );
    message->set_size      ( BLOCK_TRANSFER_SIZE );
    message->set_sessionid ( this->Id() );
    this->SendMessage      ( move_ptr( message ) );
}

void DuplicateSession::OnConnect()
{
}

void DuplicateSession::AcceptBlock( uptr<MessageDuplicateData> msg )
{
    BlockHub::Instance()->WriteBlock( this->index_->Index ,
                                      msg->offset() ,
                                      msg->data().c_str() ,
                                      msg->data().size() );

    this->index_->Size += msg->size();

    BlockHub::Instance()->SaveBlockIndex( this->index_ );

    if ( msg->islast() )
    { 
        auto sync = make_uptr   ( MessageBlockMeta );
        sync->set_fileoffset    ( this->index_->FileOffset );
        sync->set_index         ( this->index_->Index );
        sync->set_partid        ( this->index_->PartId );
        sync->set_path          ( this->index_->Path );
        sync->set_size          ( this->index_->Size );
        sync->set_status        ( 0 );
        MasterSession::Instance ()->SendMessage( move_ptr( sync ) );

        Logger::Log( "duplicate % part:% size:% from %" ,
                  this->index_->Path ,
                  this->index_->PartId ,
                  this->index_->Size,
                  this->message_block_->address() );

        this->Close();
        return;
    }

    this->block_offset_ += msg->size();
    this->SendRequest();
}
