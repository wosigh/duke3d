//-------------------------------------------------------------------------
/*
Duke Nukem Copyright (C) 1996, 2003 3D Realms Entertainment

This file is part of Duke Nukem 3D version 1.5 - Atomic Edition

Duke Nukem 3D is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  Dummy AudioLib stub implementation by Jonathon Fowler (jonof@edgenetwk.com)
*/
//-------------------------------------------------------------------------

#include "music.h"
#include "duke3d.h"
#include <SDL_mixer.h>


#define TRUE  ( 1 == 1 )
#define FALSE ( !TRUE )


int MUSIC_ErrorCode = MUSIC_Ok;


/* We're going to be requesting certain things from our audio
   device, so we set them up beforehand */
int audio_rate = 22050;
Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
int audio_channels = 2;
int audio_buffers = 4096;

Mix_Music *song_hdl = NULL;


/*---------------------------------------------------------------------
   Function: MUSIC_ErrorString

   Returns a pointer to the error message associated with an error
   number.  A -1 returns a pointer the current error.
---------------------------------------------------------------------*/

char *MUSIC_ErrorString
   (
   int ErrorNumber
   )

   {
   char *ErrorString;

   switch( ErrorNumber )
      {
      case MUSIC_Warning :
      case MUSIC_Error :
         ErrorString = MUSIC_ErrorString( MUSIC_ErrorCode );
         break;

      case MUSIC_Ok :
         ErrorString = "Music ok.";
         break;

      case MUSIC_ASSVersion :
         ErrorString = "Apogee Sound System Version   "
            "Programmed by Jim Dose\n"
            "(c) Copyright 1996 James R. Dose.  All Rights Reserved.\n";
         break;

      case MUSIC_SoundCardError :
         break;

      case MUSIC_MPU401Error :
         ErrorString = "Could not detect MPU-401.";
         break;

      case MUSIC_InvalidCard :
         ErrorString = "Invalid Music device.";
         break;

      case MUSIC_MidiError :
         ErrorString = "Error playing MIDI file.";
         break;

      case MUSIC_TaskManError :
         ErrorString = "TaskMan error.";
         break;

      case MUSIC_DPMI_Error :
         ErrorString = "DPMI Error in MUSIC.";
         break;

      default :
         ErrorString = "Unknown Music error code.";
         break;
      }

   return( ErrorString );
   }


/*---------------------------------------------------------------------
   Function: MUSIC_Init

   Selects which sound device to use.
---------------------------------------------------------------------*/

int MUSIC_Init(int SoundCard, int Address)
{
	int i;
	int status;

	initprintf("Try to open audio!\n");
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
		initprintf("Unable to open audio!\n");
		return MUSIC_Error;
	}

	/* If we actually care about what we got, we can ask here.  In this
	   program we don't, but I'm showing the function call here anyway
	   in case we'd want to know later. */
	Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);

	status = MUSIC_Ok;

	return( status );
}


/*---------------------------------------------------------------------
   Function: MUSIC_Shutdown

   Terminates use of sound device.
---------------------------------------------------------------------*/

int MUSIC_Shutdown(void)
{
   int status;

   status = MUSIC_Ok;

	Mix_CloseAudio();

   return( status );
}


/*---------------------------------------------------------------------
   Function: MUSIC_SetMaxFMMidiChannel

   Sets the maximum MIDI channel that FM cards respond to.
---------------------------------------------------------------------*/

void MUSIC_SetMaxFMMidiChannel(int channel)
{
}


/*---------------------------------------------------------------------
   Function: MUSIC_SetVolume

   Sets the volume of music playback.
---------------------------------------------------------------------*/

void MUSIC_SetVolume(int volume)
{
	Mix_VolumeMusic(volume);
}


/*---------------------------------------------------------------------
   Function: MUSIC_SetMidiChannelVolume

   Sets the volume of music playback on the specified MIDI channel.
---------------------------------------------------------------------*/

void MUSIC_SetMidiChannelVolume(int channel, int volume)
{
}


/*---------------------------------------------------------------------
   Function: MUSIC_ResetMidiChannelVolumes

   Sets the volume of music playback on all MIDI channels to full volume.
---------------------------------------------------------------------*/

void MUSIC_ResetMidiChannelVolumes(void)
{
}


/*---------------------------------------------------------------------
   Function: MUSIC_GetVolume

   Returns the volume of music playback.
---------------------------------------------------------------------*/

int MUSIC_GetVolume(void)
{
	return( 0 );
}


/*---------------------------------------------------------------------
   Function: MUSIC_SetLoopFlag

   Set whether the music will loop or end when it reaches the end of
   the song.
---------------------------------------------------------------------*/

void MUSIC_SetLoopFlag
   (
   int loopflag
   )

   {
   }


/*---------------------------------------------------------------------
   Function: MUSIC_SongPlaying

   Returns whether there is a song playing.
---------------------------------------------------------------------*/

int MUSIC_SongPlaying
   (
   void
   )

   {
   return( 0 );
   }


/*---------------------------------------------------------------------
   Function: MUSIC_Continue

   Continues playback of a paused song.
---------------------------------------------------------------------*/

void MUSIC_Continue(void)
{
	Mix_ResumeMusic();
}


/*---------------------------------------------------------------------
   Function: MUSIC_Pause

   Pauses playback of a song.
---------------------------------------------------------------------*/

void MUSIC_Pause(void)
{
	Mix_PauseMusic();
}


/*---------------------------------------------------------------------
   Function: MUSIC_StopSong

   Stops playback of current song.
---------------------------------------------------------------------*/

int MUSIC_StopSong(void)
{
	return( MUSIC_Ok );
}


/*---------------------------------------------------------------------
   Function: MUSIC_PlaySong

   Begins playback of MIDI song.
---------------------------------------------------------------------*/

int MUSIC_PlaySong(char *song, int loopflag)
{
	song_hdl = Mix_LoadMUS(song);
	initprintf("play %s : %d!\n", song, song_hdl);
	if (!song_hdl)
		return MUSIC_Error;
	Mix_PlayMusic(song_hdl, loopflag);
	return( MUSIC_Ok );
}


/*---------------------------------------------------------------------
   Function: MUSIC_SetContext

   Sets the song context.
---------------------------------------------------------------------*/

void MUSIC_SetContext
   (
   int context
   )

   {
   }


/*---------------------------------------------------------------------
   Function: MUSIC_GetContext

   Returns the current song context.
---------------------------------------------------------------------*/

int MUSIC_GetContext(void)
{
	return 0;
}


/*---------------------------------------------------------------------
   Function: MUSIC_SetSongTick

   Sets the position of the song pointer.
---------------------------------------------------------------------*/

void MUSIC_SetSongTick
   (
   unsigned long PositionInTicks
   )

   {
   }


/*---------------------------------------------------------------------
   Function: MUSIC_SetSongTime

   Sets the position of the song pointer.
---------------------------------------------------------------------*/

void MUSIC_SetSongTime
   (
   unsigned long milliseconds
   )

   {
   }


/*---------------------------------------------------------------------
   Function: MUSIC_SetSongPosition

   Sets the position of the song pointer.
---------------------------------------------------------------------*/

void MUSIC_SetSongPosition
   (
   int measure,
   int beat,
   int tick
   )

   {
   }


/*---------------------------------------------------------------------
   Function: MUSIC_GetSongPosition

   Returns the position of the song pointer.
---------------------------------------------------------------------*/

void MUSIC_GetSongPosition
   (
   songposition *pos
   )

   {
   }


/*---------------------------------------------------------------------
   Function: MUSIC_GetSongLength

   Returns the length of the song.
---------------------------------------------------------------------*/

void MUSIC_GetSongLength
   (
   songposition *pos
   )

   {
   }






/*---------------------------------------------------------------------
   Function: MUSIC_FadeVolume

   Fades music volume from current level to another over a specified
   period of time.
---------------------------------------------------------------------*/

int MUSIC_FadeVolume
   (
   int tovolume,
   int milliseconds
   )

   {
    return( MUSIC_Ok );
   }


/*---------------------------------------------------------------------
   Function: MUSIC_FadeActive

   Returns whether the fade routine is active.
---------------------------------------------------------------------*/

int MUSIC_FadeActive
   (
   void
   )

   {
   return( 0 );
   }


/*---------------------------------------------------------------------
   Function: MUSIC_StopFade

   Stops fading the music.
---------------------------------------------------------------------*/

void MUSIC_StopFade
   (
   void
   )

   {
   }


/*---------------------------------------------------------------------
   Function: MUSIC_RerouteMidiChannel

   Sets callback function to reroute MIDI commands from specified
   function.
---------------------------------------------------------------------*/

void MUSIC_RerouteMidiChannel
   (
   int channel,
   int ( *function )( int event, int c1, int c2 )
   )

   {
   }


/*---------------------------------------------------------------------
   Function: MUSIC_RegisterTimbreBank

   Halts playback of all sounds.
---------------------------------------------------------------------*/

void MUSIC_RegisterTimbreBank(unsigned char *timbres)
{
}


void MUSIC_Update(void)
{
}

