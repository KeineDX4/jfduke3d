// belle_config.h -- JFDuke3D -> Symbian Belle port: single source of truth for
// the on-device game-data directory (BELLE_GAME_DIR). This is the one place to
// change where the game expects its data (duke3d.grp sits right there) and where
// duke3d.log / duke3d.cfg / savegames land: the engine chdir()s the process into
// this directory in game.c, because the default Symbian process CWD is a
// private folder the user can't browse. Included only on Symbian builds.
#ifndef __belle_config_h__
#define __belle_config_h__

#define BELLE_GAME_DIR "E:/Games/Duke Nukem 3D"

#endif /* __belle_config_h__ */
