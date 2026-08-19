// belle_music.c -- JFDuke3D -> Symbian Belle port: MUSIC_* API shim.
//
// Belle has no MIDI/OPL2 synth (no MT32 / sound card), and jfduke3d's music is
// deferred. What plays is handled by the game itself: sounds.c playmusic()
// probes <base>.ogg / music/<base>.ogg next to duke3d.grp and, finding an OggS
// file, plays it straight through the FX/vorbis path
// (FX_PlayLoopedAuto -> MV_PlayLoopedVorbis, jfaudiolib + the background ring
// decoder in belle_main.cpp) with the MUSIC_ID callback sentinel -- MUSIC_* is
// never touched on that path.
//
// This shim exists to satisfy the OTHER half of music.h and the MusicStartup
// contract: MUSIC_Init() MUST return MUSIC_Ok or MusicStartup (sounds.c) calls
// exit(-1) and kills the game. The MIDI calls (reached only when playmusic has
// a real .mid and no .ogg) are silent no-ops -- music is deferred, the MIDI
// path simply plays nothing. drop a music/<name>.ogg to hear that track.
//
// Only the 9 functions jfduke3d references are defined (sounds.c + game.c
// loadtmb); the rest of music.h is unused by this game. No belle_music.h is
// needed: nothing outside this file sets a song name -- the OGG probe lives in
// sounds.c's playmusic(), so no other translation unit calls into this shim.

#include "compat.h"   // buildprintf (fatal-path diagnostics)
#include "music.h"

#ifdef __SYMBIAN32__

int MUSIC_ErrorCode = MUSIC_Ok;

const char *MUSIC_ErrorString(int ErrorNumber)
{
    (void)ErrorNumber;
    return "Belle has no MIDI synth; music is OGG only";
}

int MUSIC_Init(int SoundCard, const char *params)
{
    (void)SoundCard; (void)params;
    // MUST succeed: MusicStartup (sounds.c) exits the game on MUSIC_Init failure.
    MUSIC_ErrorCode = MUSIC_Ok;
    return MUSIC_Ok;
}

int MUSIC_Shutdown(void)
{
    MUSIC_ErrorCode = MUSIC_Ok;
    return MUSIC_Ok;
}

void MUSIC_SetVolume(int volume)
{
    // Music is deferred (OGG plays through the FX path, whose volume the game
    // sets itself); the FX volume in driver_belle is handled by the mixer.
    (void)volume;
}

int MUSIC_PlaySong(void *song, unsigned int length, int loopflag)
{
    // Reached only for a real .mid with no .ogg alongside: silently play
    // nothing. (void) the params so GCCE has nothing to warn about.
    (void)song; (void)length; (void)loopflag;
    MUSIC_ErrorCode = MUSIC_Ok;
    return MUSIC_Ok;
}

int MUSIC_StopSong(void)
{
    MUSIC_ErrorCode = MUSIC_Ok;
    return MUSIC_Ok;
}

void MUSIC_Pause(void) {}
void MUSIC_Continue(void) {}
void MUSIC_RegisterTimbreBank(unsigned char *timbres) { (void)timbres; }

#endif /* __SYMBIAN32__ */
