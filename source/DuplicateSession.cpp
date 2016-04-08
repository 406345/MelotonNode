#include "DuplicateSession.h"
#include <MessageDuplicateDataRequest.pb.h>
#include <BlockHub.h>

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
    message->set_index     ( this->index_->Index );
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
        BlockHub::Instance()->SyncBlock( this->index_ );
        this->Close();
        return;
    }

    this->block_offset_ += msg->size();
    this->SendRequest();
}
