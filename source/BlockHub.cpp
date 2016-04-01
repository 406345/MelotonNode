#include <BlockHub.h>
#include <Path.h>

#ifdef _WIN32
#define fseek _fseeki64 
#define ftell _ftelli64
#else
#define fseek fseeko64
#define ftell ftello64
#endif

void BlockHub::LoadFromDisk()
{
    this->index_file_ = fopen( "index.dat" , "rb+" );
    this->data_file_ = fopen( "block.dat" , "rb+" );

    if ( this->index_file_ == NULL )
    {
        this->index_file_ = fopen( "index.dat" , "wb+" );
    }

    if ( this->data_file_ == NULL )
    {
        this->data_file_ = fopen( "block.dat" , "wb+" );
    }

    this->LoadIndex();
}

void BlockHub::LoadIndex()
{
    int index = 0;
    do
    {
        auto bi = make_sptr( BlockIndex );
        auto reads = fread( ( void* ) bi.get() ,
                            1 ,
                            sizeof( BlockIndex ) ,
                            this->index_file_ );
        
        if ( reads == 0 )
        {
            break;
        }

        this->index_list_[index] = bi;

        if ( bi->Used == false )
        {
            this->empty_list_[this->block_empty_count_++] = bi;
        }

        index++;
    }
    while ( true );

    fseek( this->index_file_ , 0 , SEEK_SET );
    this->block_count_ = index;
}

sptr<BlockIndex> BlockHub::FindBlock( size_t index )
{
    if ( index >= BLOCK_INDEX_ARRAY_SIZE )
        return nullptr;

    return this->index_list_[index];
}

sptr<BlockIndex> BlockHub::CreateBlock( int partId , size_t fileOffset , string path )
{
    sptr<BlockIndex> idx = nullptr;

    if ( this->block_empty_count_ > 0 )
    {
        idx = this->empty_list_[this->block_empty_count_ - 1];
        --this->block_empty_count_;
    }
    else
    {
        idx = make_sptr( BlockIndex );
        idx->Index = this->block_count_;
        this->index_list_[this->block_count_] = idx;
        ++this->block_count_;
    }

    idx->Used       = true;
    idx->FileOffset = fileOffset;
    idx->Location   = idx->Index * BLOCK_SIZE;
    idx->PartId     = partId;

    memcpy( idx->Path , path.c_str() , path.size() );

    return idx;
}

bool BlockHub::RemoveBlock( size_t index )
{
    this->empty_list_[this->block_empty_count_]         = this->index_list_[index];
    this->empty_list_[this->block_empty_count_]->Used   = false;
    this->index_list_[index] = nullptr;
    ++this->block_empty_count_;

    return false;
}

size_t BlockHub::WriteBlock( int blockid ,
                             size_t offset ,
                             const char* data ,
                             size_t len )
{
    auto    block        =  this->index_list_[blockid];
    size_t  write_size   =  ( offset + len ) > BLOCK_SIZE ?
                            ( BLOCK_SIZE - offset + 1 ) : len;

    if ( block == nullptr )
        return 0;

    fseek( this->data_file_ , block->Location + offset , SEEK_SET );
    fwrite( data , 1 , write_size , this->data_file_ );

    return write_size;
}

uptr<Buffer> BlockHub::ReadBlock( int blockid ,
                                  size_t offset ,
                                  size_t len )
{
    auto         block        = this->index_list_[blockid];
    size_t       read_size    = ( offset + len ) > BLOCK_SIZE ?
        ( BLOCK_SIZE - offset + 1 ) : len;

    if ( block == nullptr )
        return nullptr;

    uptr<Buffer> result       = make_uptr( Buffer , read_size );

    fseek( this->data_file_ , block->Location + offset , SEEK_SET );
    fread( result->Data() , 1 , read_size , this->data_file_ );

    return move_ptr( result );
}

BlockHub::BlockHub()
{

}

BlockHub::~BlockHub()
{

}

void BlockHub::SaveBlockIndex( sptr<BlockIndex> block )
{
    auto block_instance                 = block.get();
    size_t pos                          = block->Index * sizeof( BlockIndex );

    fseek( this->index_file_ , pos , SEEK_SET );

    auto count = fwrite( (void*)block_instance ,
                         1 , 
                         sizeof( BlockIndex ) ,
                         this->index_file_ );
    fflush( this->index_file_ );
}
