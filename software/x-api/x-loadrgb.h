/*----------------------------------------------------------------------------
  MCD-X: General API for audio/graphics/interaction programming
    (sibling of MCD-Y API)
    http://www.gewang.com/software/mcd-api/

  Copyright (c) 2007-present Ge Wang
    All rights reserved.
    http://www.gewang.com/

  Music, Computing, Design Group @ CCRMA, Stanford University
    http://ccrma.stanford.edu/groups/mcd/

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  U.S.A.
-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// file: x-loadrgb.h
// desc: rgb file loader
//
// author: Ge Wang (ge@ccrma.stanford.edu)
//   date: Winter 2009
//-----------------------------------------------------------------------------
#ifndef __MCD_X_LOAD_RGB_H__
#define __MCD_X_LOAD_RGB_H__




//-----------------------------------------------------------------------------
// Name: struct GeImageData
// Desc: holds basic image data
//-----------------------------------------------------------------------------
struct GeImageData
{
    int width;
    int height;
    unsigned * bits;
    
    GeImageData( int w = 0, int h = 0, unsigned * p = 0 )
    : width( w ), height( h ), bits( p )
    { }
};

bool ge_read_image( const char * filename, GeImageData * pImgData );




#endif
