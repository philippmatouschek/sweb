/**
 * @file MinixFSFile.cpp
 */

#include "MinixFSFile.h"
#include "MinixFSInode.h"
#include "Inode.h"

MinixFSFile::MinixFSFile ( Inode* inode, Dentry* dentry, uint32 flag ) : File ( inode, dentry, flag )
{
  f_superblock_ = inode->getSuperblock();
  // to get the real mode implement it in the inode constructor and get it from there
  // if you do so implement chmod and createInode with mode
  mode_ = ( A_READABLE ^ A_WRITABLE ) ^ A_EXECABLE;
  offset_ = 0;
}


MinixFSFile::~MinixFSFile()
{}


int32 MinixFSFile::read ( char *buffer, size_t count, l_off_t offset )
{
  if ( ( ( flag_ == O_RDONLY ) || ( flag_ == O_RDWR ) ) && ( mode_ & A_READABLE ) )
    return ( f_inode_->readData ( offset, count, buffer ) );
  else
  {
    // ERROR_FF
    return -1;
  }
}


int32 MinixFSFile::write ( const char *buffer, size_t count, l_off_t offset )
{
  if ( ( ( flag_ == O_WRONLY ) || ( flag_ == O_RDWR ) ) && ( mode_ & A_WRITABLE ) )
    return ( f_inode_->writeData ( offset, count, buffer ) );
  else
  {
    // ERROR_FF
    return -1;
  }
}

int32 MinixFSFile::flush()
{
  f_inode_->flush();
  return 0;
}

