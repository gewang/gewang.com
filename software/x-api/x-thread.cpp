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
// name: x-thread.cpp
// desc: thread library
//
// authors: Ge Wang (ge@ccrma.stanford.edu)
//          Jieun Oh (jieun@ccrma.stanford.edu)
//          adapted from ChucK programming language
//          adapted from Synthesis Toolkit
//    date: Fall 2010
//-----------------------------------------------------------------------------
#include "x-thread.h"




//-----------------------------------------------------------------------------
// name: XThread()
// desc: ...
//-----------------------------------------------------------------------------
XThread::XThread( )
{
    thread = 0;
}




//-----------------------------------------------------------------------------
// name: ~XThread()
// desc: ...
//-----------------------------------------------------------------------------
XThread::~XThread( )
{
    if( thread != 0 )
    {
#if defined(__PLATFORM_MACOSX__) || defined(__PLATFORM_LINUX__) || defined(__WINDOWS_PTHREAD__)
        pthread_cancel(thread);
        pthread_join(thread, NULL);
#elif defined(__PLATFORM_WIN32__)
        TerminateThread((HANDLE)thread, 0);
#endif
    }
}




//-----------------------------------------------------------------------------
// name: start()
// desc: ...
//-----------------------------------------------------------------------------
bool XThread::start( THREAD_FUNCTION routine, void * ptr )
{
    bool result = false;
    
#if ( defined(__PLATFORM_MACOSX__) || defined(__PLATFORM_LINUX__) || defined(__WINDOWS_PTHREAD__) )
    if( pthread_create( &thread, NULL, *routine, ptr ) == 0 )
        result = true;
#elif defined(__PLATFORM_WIN32__)
    unsigned thread_id;
    thread = _beginthreadex( NULL, 0, routine, ptr, 0, &thread_id );
    if( thread ) result = true;
#endif
    return result;
}




//-----------------------------------------------------------------------------
// name: wait()
// desc: ...
//-----------------------------------------------------------------------------
bool XThread::wait( long milliseconds )
{
    bool result = false;
    
#if ( defined(__PLATFORM_MACOSX__) || defined(__PLATFORM_LINUX__) || defined(__WINDOWS_PTHREAD__) )
    pthread_cancel(thread);
    pthread_join(thread, NULL);
#elif defined(__PLATFORM_WIN32__)
    DWORD timeout, retval;
    if( milliseconds < 0 ) timeout = INFINITE;
    else timeout = milliseconds;
    retval = WaitForSingleObject( (HANDLE)thread, timeout );
    if( retval == WAIT_OBJECT_0 ) {
        CloseHandle( (HANDLE)thread );
        thread = 0;
        result = true;
    }
#endif

  return result;
}




//-----------------------------------------------------------------------------
// name: test()
// desc: ...
//-----------------------------------------------------------------------------
void XThread :: test( )
{
#if ( defined(__PLATFORM_MACOSX__) || defined(__PLATFORM_LINUX__) || defined(__WINDOWS_PTHREAD__) )
    pthread_testcancel();
#endif
}




//-----------------------------------------------------------------------------
// name: XMutex()
// desc: ...
//-----------------------------------------------------------------------------
XMutex::XMutex( )
{
#if ( defined(__PLATFORM_MACOSX__) || defined(__PLATFORM_LINUX__) || defined(__WINDOWS_PTHREAD__) )
    pthread_mutex_init(&mutex, NULL);
#elif defined(__PLATFORM_WIN32__)
    InitializeCriticalSection(&mutex);
#endif 
}




//-----------------------------------------------------------------------------
// name: XMutex()
// desc: ...
//-----------------------------------------------------------------------------
XMutex::~XMutex( )
{
#if ( defined(__PLATFORM_MACOSX__) || defined(__PLATFORM_LINUX__) || defined(__WINDOWS_PTHREAD__) )
    pthread_mutex_destroy( &mutex );
#elif defined(__PLATFORM_WIN32__)
    DeleteCriticalSection(&mutex);
#endif 
}




//-----------------------------------------------------------------------------
// name: acquire()
// desc: ...
//-----------------------------------------------------------------------------
void XMutex::acquire( )
{
#if ( defined(__PLATFORM_MACOSX__) || defined(__PLATFORM_LINUX__) || defined(__WINDOWS_PTHREAD__) )
    pthread_mutex_lock(&mutex);
#elif defined(__PLATFORM_WIN32__)
    EnterCriticalSection(&mutex);
#endif 
}




//-----------------------------------------------------------------------------
// name: unlock()
// desc: ...
//-----------------------------------------------------------------------------
void XMutex::release( )
{
#if ( defined(__PLATFORM_MACOSX__) || defined(__PLATFORM_LINUX__) || defined(__WINDOWS_PTHREAD__) )
    pthread_mutex_unlock(&mutex);
#elif defined(__PLATFORM_WIN32__)
    LeaveCriticalSection(&mutex);
#endif 
}
