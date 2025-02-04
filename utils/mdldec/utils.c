/*
utils.c - Useful helper functions
Copyright (C) 2020 Andrey Akhmichin

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "xash3d_types.h"
#include "port.h"
#include "crtlib.h"
#include "utils.h"

/*
============
MakeDirectory
============
*/
qboolean MakeDirectory( const char *path )
{
	if( -1 == _mkdir( path ))
	{
		if( errno == EEXIST )
		{
			// TODO: when filesystem library will be ready
			// use FS_SysFolderExists here or replace this whole function
			// with FS_CreatePath
#if XASH_WIN32
		        DWORD   dwFlags = GetFileAttributes( path );

		        return ( dwFlags != -1 ) && ( dwFlags & FILE_ATTRIBUTE_DIRECTORY );
#else
		        struct stat buf;

		        if( !stat( path, &buf ))
				return S_ISDIR( buf.st_mode );
#endif
		}
		return false;
	}

	return true;
}

/*
============
GetFileSize
============
*/
off_t GetSizeOfFile( FILE *fp )
{
	struct stat	st;
	int		fd;

	fd = fileno( fp );
	fstat( fd, &st );

	return st.st_size;
}

/*
============
LoadFile
============
*/
byte *LoadFile( const char *filename )
{
	FILE	*fp;
	byte	*buf;
	off_t	 size;
	size_t bytesRead = 0;

	fp = fopen( filename, "rb" );

	if( !fp )
		return NULL;

	size = GetSizeOfFile( fp );

	buf = malloc( size );

	if( !buf )
		return NULL;

	bytesRead = fread( buf, size, 1, fp );
	fclose( fp );

	return buf;
}
